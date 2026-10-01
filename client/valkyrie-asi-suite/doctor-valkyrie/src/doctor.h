// doctor-valkyrie: say what the crash was, in the crash log, in English.
//
// GTA SA already writes a crash log - another ASI's, the one every player in
// #bugs-problems posts. It is a good log: game build, last file loaded, last
// library loaded, the exception, registers, stack. What it does not do is tell
// the player what any of that means, so every crash becomes a thread and
// somebody reads the log by hand and says "your game is not 1.0".
//
// This reads the same evidence and appends the answer. It does not replace
// another ASI's reporter: the filter chains to whatever was installed before it, so
// the log the player already knows how to find is still written, and both exist
// if another ASI's is more complete for some crash we did not anticipate. Two crash
// reporters that both try to own the exception is how CrashInfoSA.asi got a
// reputation for being incompatible with other mods; we are not doing that.
//
// The knowledge itself lives in doctor-valkyrie.txt, not in this code, so a
// new crash pattern is a text edit and not a build. The format is CrashInfo's,
// so JuniorDjjr's community list works unmodified alongside ours - see
// doctorlist.h.
#pragma once

namespace doctor {

// Load the rule lists and install the exception filter. Safe to call twice.
bool Install();

// Put Doctor back on top. Windows gives the crash to whoever called
// SetUnhandledExceptionFilter last, so a plugin that loads after us would
// otherwise take it and open another reporter. Doctor owns the one visible
// report for this launch.
void Reassert();

// Check CLEO's log for a newly suspended script. This is deliberately
// separate from fatal crash handling because CLEO catches these errors and
// leaves GTA running.
void CheckCleoErrors();

}  // namespace doctor
