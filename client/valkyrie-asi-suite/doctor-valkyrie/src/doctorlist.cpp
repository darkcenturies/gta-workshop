#include "doctorlist.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

namespace doctorlist {
namespace {

// One parsed block. Empty match vectors mean "this key was not declared",
// which is different from "declared and empty" - a rule with no keys at all
// never matches anything and is dropped at load.
struct Rule {
    std::vector<unsigned long> addresses;
    std::vector<std::string> libraries;
    std::vector<std::string> files;
    std::vector<std::string> modules;   // lowercase "name+0xoffset"
    std::vector<unsigned long> codes;
    std::string body;
    std::string source;
    int keys = 0;
};

std::vector<Rule> g_rules;
std::vector<std::string> g_spanishBodies;

std::string Lower(std::string s) {
    for (char& c : s) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return s;
}

std::string Trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return std::string();
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

// Their lists write several addresses on one Error: line, comma separated, and
// sometimes with a parenthetical aside after them. Take every 0x value we can
// see and ignore the prose around it.
std::vector<unsigned long> ParseAddresses(const std::string& value) {
    std::vector<unsigned long> out;
    size_t i = 0;
    while ((i = value.find("0x", i)) != std::string::npos) {
        const char* start = value.c_str() + i + 2;
        char* end = nullptr;
        const unsigned long v = strtoul(start, &end, 16);
        if (end != start) {
            out.push_back(v);
        }
        i += 2;
    }
    return out;
}

// Comma or slash separated names, lowercased. "discord-rpc.asi, bass.dll".
std::vector<std::string> ParseNames(const std::string& value) {
    std::vector<std::string> out;
    std::string current;
    for (char c : value) {
        if (c == ',' || c == '|') {
            const std::string t = Trim(current);
            if (!t.empty()) out.push_back(Lower(t));
            current.clear();
        } else {
            current += c;
        }
    }
    const std::string t = Trim(current);
    if (!t.empty()) out.push_back(Lower(t));
    return out;
}

// A key line is "Word:" or "Word 1:" at the start of a line. Anything else is
// a continuation of the previous body line, which their list relies on.
bool SplitKey(const std::string& line, std::string& key, std::string& value) {
    const size_t colon = line.find(':');
    if (colon == std::string::npos || colon == 0 || colon > 24) {
        return false;
    }
    for (size_t i = 0; i < colon; ++i) {
        const char c = line[i];
        if (!isalpha(static_cast<unsigned char>(c)) && c != ' ' && !isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    key = Lower(Trim(line.substr(0, colon)));
    value = Trim(line.substr(colon + 1));
    // "problem 1" and "solution 2" are the same keys as "problem"/"solution".
    while (!key.empty() && (isdigit(static_cast<unsigned char>(key.back())) || key.back() == ' ')) {
        key.pop_back();
    }
    return !key.empty();
}

void Finish(Rule& rule, std::vector<Rule>& into, const char* source) {
    rule.keys = static_cast<int>(!rule.addresses.empty()) +
                static_cast<int>(!rule.libraries.empty()) +
                static_cast<int>(!rule.files.empty()) +
                static_cast<int>(!rule.modules.empty()) +
                static_cast<int>(!rule.codes.empty());
    rule.body = Trim(rule.body);
    if (rule.keys > 0 && !rule.body.empty()) {
        rule.source = source;
        into.push_back(rule);
    }
    rule = Rule();
}

// Substring rather than equality, in both directions. A log says
// "C:\Games\GTA SA\AUDIO\CONFIG\BANKSLOT.DAT" and the rule says
// "BANKSLOT.DAT"; a log can also say "bass" where the rule says "bass.dll".
bool NameMatches(const std::vector<std::string>& wanted, const std::string& actual) {
    if (wanted.empty()) return true;
    if (actual.empty()) return false;
    const std::string lower = Lower(actual);
    for (const std::string& w : wanted) {
        if (lower.find(w) != std::string::npos) return true;
        if (w.find(lower) != std::string::npos) return true;
    }
    return false;
}

bool ValueMatches(const std::vector<unsigned long>& wanted, unsigned long actual) {
    if (wanted.empty()) return true;
    return std::find(wanted.begin(), wanted.end(), actual) != wanted.end();
}

}  // namespace

int LoadText(const char* data, size_t size, const char* sourceName) {
    if (!data || !sourceName || size == 0 || size > 4 * 1024 * 1024) return -1;
    std::vector<Rule> loaded;
    Rule rule;
    std::string line;
    std::string lastBodyKey;

    size_t position = 0;
    while (position < size) {
        size_t end = position;
        while (end < size && data[end] != '\n') ++end;
        line.assign(data + position, end - position);
        position = end < size ? end + 1 : size;
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
            line.pop_back();
        }

        if (Trim(line).empty()) {
            Finish(rule, loaded, sourceName);
            lastBodyKey.clear();
            continue;
        }
        if (line[0] == '#' || line.compare(0, 2, "//") == 0) {
            continue;
        }

        std::string key, value;
        if (SplitKey(line, key, value)) {
            if (key == "error") {
                // Their Error: line carries addresses, but also bare module
                // names - "CLEO.asi", "std.bank.dll". Take both readings.
                const std::vector<unsigned long> addrs = ParseAddresses(value);
                if (!addrs.empty()) {
                    rule.addresses.insert(rule.addresses.end(), addrs.begin(), addrs.end());
                }
                if (value.find('.') != std::string::npos && addrs.empty()) {
                    const std::vector<std::string> names = ParseNames(value);
                    rule.libraries.insert(rule.libraries.end(), names.begin(), names.end());
                }
                lastBodyKey.clear();
                continue;
            }
            if (key == "library") {
                const std::vector<std::string> n = ParseNames(value);
                rule.libraries.insert(rule.libraries.end(), n.begin(), n.end());
                lastBodyKey.clear();
                continue;
            }
            if (key == "file") {
                const std::vector<std::string> n = ParseNames(value);
                rule.files.insert(rule.files.end(), n.begin(), n.end());
                lastBodyKey.clear();
                continue;
            }
            if (key == "module") {
                const std::vector<std::string> n = ParseNames(value);
                rule.modules.insert(rule.modules.end(), n.begin(), n.end());
                lastBodyKey.clear();
                continue;
            }
            if (key == "code") {
                const std::vector<unsigned long> c = ParseAddresses(value);
                rule.codes.insert(rule.codes.end(), c.begin(), c.end());
                lastBodyKey.clear();
                continue;
            }
            // Everything else is prose we print back: Problem, Solution,
            // About, Type, Mod, Backtrace, Last command, and their numbered
            // variants.
            if (!rule.body.empty()) rule.body += "\n";
            rule.body += line;
            lastBodyKey = key;
            continue;
        }

        // A wrapped body line.
        if (!lastBodyKey.empty()) {
            rule.body += "\n";
            rule.body += line;
        }
    }
    Finish(rule, loaded, sourceName);

    g_rules.insert(g_rules.end(), loaded.begin(), loaded.end());
    return static_cast<int>(loaded.size());
}

int LoadSpanishText(const char* data, size_t size) {
    if (!data || size == 0 || size > 4 * 1024 * 1024) return -1;
    std::vector<std::string> loaded;
    std::string body;
    std::string lastBodyKey;
    bool hasMatchKey = false;
    size_t position = 0;
    while (position < size) {
        size_t end = position;
        while (end < size && data[end] != '\n') ++end;
        std::string line(data + position, end - position);
        position = end < size ? end + 1 : size;
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
            line.pop_back();
        }
        if (Trim(line).empty()) {
            body = Trim(body);
            if (hasMatchKey && !body.empty()) loaded.push_back(body);
            body.clear();
            lastBodyKey.clear();
            hasMatchKey = false;
            continue;
        }
        if (line[0] == '#' || line.compare(0, 2, "//") == 0) continue;
        std::string key, value;
        if (SplitKey(line, key, value)) {
            if (key == "error" || key == "library" || key == "file" ||
                key == "module" || key == "code") {
                // Mirror the English parser's validity checks. CrashInfo has a
                // few malformed key-like blocks; counting those here would
                // shift every later translation onto the wrong diagnosis.
                if (key == "error") {
                    const auto addresses = ParseAddresses(value);
                    hasMatchKey = hasMatchKey || !addresses.empty() ||
                                  (value.find('.') != std::string::npos &&
                                   !ParseNames(value).empty());
                } else if (key == "code") {
                    hasMatchKey = hasMatchKey || !ParseAddresses(value).empty();
                } else {
                    hasMatchKey = hasMatchKey || !ParseNames(value).empty();
                }
                lastBodyKey.clear();
                continue;
            }
            if (!body.empty()) body += "\n";
            body += line;
            lastBodyKey = key;
        } else if (!lastBodyKey.empty()) {
            body += "\n";
            body += line;
        }
    }
    body = Trim(body);
    if (hasMatchKey && !body.empty()) loaded.push_back(body);
    g_spanishBodies.insert(g_spanishBodies.end(), loaded.begin(), loaded.end());
    return static_cast<int>(loaded.size());
}

int Load(const char* path, const char* sourceName) {
    FILE* f = fopen(path, "rb");
    if (!f) return -1;
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return -1;
    }
    const long length = ftell(f);
    if (length <= 0 || length > 4 * 1024 * 1024) {
        fclose(f);
        return -1;
    }
    rewind(f);
    std::string text(static_cast<size_t>(length), '\0');
    const size_t read = fread(&text[0], 1, text.size(), f);
    fclose(f);
    if (read != text.size()) return -1;
    return LoadText(text.data(), text.size(), sourceName);
}

std::vector<Match> Find(const Crash& crash) {
    // "bass.dll+0x1f6dd", the form Module: rules are written in.
    std::string moduleKey;
    if (!crash.module.empty()) {
        char buf[256];
        _snprintf_s(buf, sizeof(buf), _TRUNCATE, "%s+0x%lX",
                    Lower(crash.module).c_str(), crash.offset);
        moduleKey = Lower(buf);
    }

    struct Scored {
        int keys;
        size_t order;
        Match match;
    };
    std::vector<Scored> hits;

    for (size_t i = 0; i < g_rules.size(); ++i) {
        const Rule& r = g_rules[i];
        if (!ValueMatches(r.addresses, crash.address)) continue;
        if (!ValueMatches(r.codes, crash.code)) continue;
        if (!NameMatches(r.libraries, crash.lastLibrary)) continue;
        if (!NameMatches(r.files, crash.lastFile)) continue;
        if (!r.modules.empty()) {
            if (moduleKey.empty()) continue;
            bool ok = false;
            for (const std::string& m : r.modules) {
                if (moduleKey.find(m) != std::string::npos) { ok = true; break; }
            }
            if (!ok) continue;
        }
        Match m;
        m.body = r.body;
        if (i < g_spanishBodies.size()) m.bodySpanish = g_spanishBodies[i];
        m.source = r.source;
        m.keys = r.keys;
        hits.push_back(Scored{r.keys, i, m});
    }

    // A GTA SA-specific diagnosis takes priority over a generic
    // CrashInfo hint even when the generic rule happens to use more fields.
    // The game is a heavily modified GTA build, so upstream's broad collision
    // or engine rules are useful secondary context, not the headline answer.
    std::stable_sort(hits.begin(), hits.end(), [](const Scored& a, const Scored& b) {
        const bool aLocalRules =
            a.match.source.find("CrashInfo") == std::string::npos;
        const bool bLocalRules =
            b.match.source.find("CrashInfo") == std::string::npos;
        if (aLocalRules != bLocalRules) return aLocalRules;
        if (a.keys != b.keys) return a.keys > b.keys;
        return a.order < b.order;
    });

    std::vector<Match> out;
    out.reserve(hits.size());
    for (const Scored& s : hits) out.push_back(s.match);
    return out;
}

size_t Count() { return g_rules.size(); }

std::string FindLoadedDuplicates(
    const std::vector<LoadedComponent>& components) {
    std::map<std::string, std::vector<std::string>> byName;
    for (const LoadedComponent& component : components) {
        const std::string lower = Lower(component.name);
        const bool asi = lower.size() >= 4 &&
                         lower.compare(lower.size() - 4, 4, ".asi") == 0;
        const bool cleo = lower.size() >= 5 &&
                          lower.compare(lower.size() - 5, 5, ".cleo") == 0;
        if (!asi && !cleo) continue;
        byName[lower].push_back(component.path);
    }

    std::string out;
    for (const auto& [name, paths] : byName) {
        if (paths.size() < 2) continue;
        out += "  " + name + " loaded " + std::to_string(paths.size()) +
               " times:\n";
        for (const std::string& path : paths) out += "    " + path + "\n";
    }
    return out;
}

std::string Render(const std::vector<Match>& matches) {
    std::string out;
    out += "===============================================================\n";
    out += " DIAGNOSIS\n";
    out += "===============================================================\n\n";

    if (matches.empty()) {
        out +=
            "No rule matched this crash. Unfortunately Valkyrie does not have\n"
            "enough evidence to name the cause safely.\n\n"
            "Post this whole file in #bugs-problems. Check first that the\n"
            "\"Last file loaded\" line above is not itself a .log file; if it is,\n"
            "this crash followed another one and the earlier log is the useful\n"
            "one.\n";
        if (g_rules.empty()) {
            out +=
                "\nNote: no rule list was loaded at all. doctor-valkyrie.txt is\n"
                "missing from the game folder, so nothing could be matched.\n";
        }
        return out;
    }

    // More than one rule can fit; the most specific is first and is nearly
    // always the answer. The rest are printed because a crash address can
    // genuinely have several causes, and the player is the one who knows which
    // mods they installed.
    int shown = 0;
    char note[160];
    for (const Match& m : matches) {
        if (shown >= 4) break;
        if (shown == 0) {
            out += m.body;
            _snprintf_s(note, sizeof(note), _TRUNCATE,
                        "\n\n   [matched on %d field%s, from %s]\n", m.keys,
                        m.keys == 1 ? "" : "s", m.source.c_str());
            out += note;
        } else {
            if (shown == 1) {
                out += "\n---------------------------------------------------------------\n";
                out += " Other possibilities for the same crash\n";
                out += "---------------------------------------------------------------\n\n";
            }
            out += m.body;
            out += "\n\n";
        }
        ++shown;
    }
    return out;
}

std::string RenderSpanish(const std::vector<Match>& matches) {
    if (matches.empty()) {
        return
            "===============================================================\n"
            " DIAGNÓSTICO\n"
            "===============================================================\n\n"
            "Ninguna regla coincidió con este fallo. Valkyrie no tiene "
            "pruebas suficientes para identificar la causa con seguridad.\n\n"
            "Publique el archivo completo en #bugs-problems e indique qué "
            "estaba haciendo justo antes del fallo.\n";
    }
    std::vector<Match> translated = matches;
    for (Match& match : translated) {
        if (!match.bodySpanish.empty()) match.body = match.bodySpanish;
    }
    std::string out = Render(translated);
    const struct { const char* from; const char* to; } replacements[] = {
        {" DIAGNOSIS\n", " DIAGNÓSTICO\n"},
        {" Other possibilities for the same crash\n",
         " Otras posibilidades para el mismo fallo\n"},
        {"No rule matched this crash.", "Ninguna regla coincidió con este fallo."},
        {"Unfortunately Valkyrie does not have\nenough evidence to name the cause safely.",
         "Lamentablemente, Valkyrie no tiene pruebas suficientes para\n"
         "nombrar la causa con seguridad."},
        {"Post this whole file in #bugs-problems. Check first that the\n"
         "\"Last file loaded\" line above is not itself a .log file; if it is,\n"
         "this crash followed another one and the earlier log is the useful\n"
         "one.",
         "Publique este archivo completo en #bugs-problems. Compruebe primero\n"
         "que la línea \"Último archivo cargado\" no sea un archivo .log; si\n"
         "lo es, este fallo ocurrió después de otro y el registro anterior es\n"
         "el útil."},
        {"[matched on ", "[coincidencia en "},
        {" fields, from ", " campos, fuente: "},
        {" field, from ", " campo, fuente: "},
    };
    for (const auto& replacement : replacements) {
        size_t at = 0;
        while ((at = out.find(replacement.from, at)) != std::string::npos) {
            out.replace(at, strlen(replacement.from), replacement.to);
            at += strlen(replacement.to);
        }
    }
    return out;
}

}  // namespace doctorlist
