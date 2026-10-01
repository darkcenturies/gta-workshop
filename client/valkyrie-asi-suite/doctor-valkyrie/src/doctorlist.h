// The crash rule list, and matching a crash against it.
//
// The file format is deliberately CrashInfo's, so that JuniorDjjr's list
// (github.com/JuniorDjjr/CrashInfo, MIT) drops in unmodified and every entry
// the MixMods community has built up over the years keeps working:
//
//     Error: 0x004DD5A3
//     Problem: ...
//     Solution: ...
//
// blank-line separated blocks, one key per line. Their numbered variants
// ("Problem 1:", "Solution 2:") and their prose keys ("About:", "Type:",
// "Mod:", "Backtrace:") are body text and are printed back verbatim.
//
// We add four match keys, because an address on its own cannot identify most
// of what actually crashes GTA SA:
//
//     Library:  matches "Last library loaded"   discord-rpc.asi, bass.dll
//     File:     matches "Last file loaded"      AUDIO\CONFIG\BANKSLOT.DAT
//     Module:   matches module+offset           bass.dll+0xF6DD
//     Code:     matches the exception code      0xC0000094
//
// Module: is the one that earns its place. Anything crashing inside a
// dynamically loaded module - the Discord plugin, the audio library, a GPU
// driver - has a different address every launch, because the module lands at a
// different base. Across 219 GTA SA crash logs the Discord case alone
// produced 16 distinct addresses; the offset within the module was the same
// every time. Keying on module+offset survives that, and a plain address
// cannot.
//
// A rule matches only when every declared key matches. More matching keys
// take precedence; an address alone cannot establish a module-specific cause.
#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace doctorlist {

// What we know about a crash, gathered by doctor.cpp before we go looking.
struct Crash {
    unsigned long code = 0;         // EXCEPTION_ACCESS_VIOLATION etc
    unsigned long address = 0;      // absolute, as the log prints it
    std::string lastFile;           // last file the game opened
    std::string lastLibrary;        // last library the process loaded
    std::string module;             // module the address is inside, or empty
    unsigned long offset = 0;       // offset within that module
};

struct Match {
    std::string body;   // Problem:/Solution:/About: lines, printed as-is
    std::string bodySpanish; // offline UTF-8 translation, if embedded
    std::string source; // which list file it came from
    int keys = 0;       // how many match keys had to agree
};

// Loaded components are kept independent from Win32's MODULEENTRY32 so the
// duplicate detector can be regression-tested without starting GTA.
struct LoadedComponent {
    std::string name;
    std::string path;
};

// Load a list file, appending to whatever is already loaded. Call with our own
// list first: on an equal-specificity tie the earlier file wins. Returns the
// number of rules read, or -1 when the file could not be opened.
int Load(const char* path, const char* sourceName);

// Load the same format from an embedded Win32 resource. This is what makes the
// release genuinely single-file; external lists can still be used as newer
// overrides without being required for baseline diagnosis support.
int LoadText(const char* data, size_t size, const char* sourceName);

// Load translated prose in the same rule order as the English databases.
// Translation resources never participate in matching.
int LoadSpanishText(const char* data, size_t size);

// Every rule that matches, best first.
std::vector<Match> Find(const Crash& crash);

// How many rules are loaded in total.
size_t Count();

// The DIAGNOSIS section, exactly as it is written into a crash report.
// Lives here rather than in doctor.cpp so that the preview tool renders the
// same text the player gets - a preview that formats its own output is a
// preview of something nobody will ever see.
std::string Render(const std::vector<Match>& matches);
std::string RenderSpanish(const std::vector<Match>& matches);

// Report duplicate active ASI/CLEO modules by basename, including every path.
// Dormant files on disk are intentionally ignored.
std::string FindLoadedDuplicates(const std::vector<LoadedComponent>& components);

}  // namespace doctorlist
