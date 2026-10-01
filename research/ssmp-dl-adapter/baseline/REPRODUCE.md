# Historical two-file baseline reproduction

This is the earlier experimental implementation, not the standalone installation. See the parent README and SESSION-STATUS for the later official-launcher failure.

Install Python 3 dependencies with `python -m pip install -r requirements.txt` from this directory. Obtain your own original S&SMP with the exact hash in the parent README. Run:

```bat
python port/build_port.py --source "X:\path\to\original\ssmptw.asi"
```

The builder creates `port/ssmptw-dl-test.asi`, checks the original hash, and does not overwrite its input. From an x86 Visual Studio Native Tools Command Prompt, compile the guard:

```bat
cd port
build.cmd
```

The output is `port/build/Valkyrie-DL-Guard.dll`. No vendor binaries are included in this repository. Historical reproduction hashes and section comparisons are recorded in BUILD-VERIFICATION.md.

Only in a separately backed-up test installation, use a copy of the generated ASI named `ssmptw.asi` together with this guard. Do not combine these with the standalone adapter. Keep exact dependencies consistent with the parent environment fingerprints. Verify the loaded DL hash in the guard log, a reachable artwork endpoint, and actual movement/rendering. The historical successful run used a custom harness, not the official launcher UI.

To restore that test copy, close GTA, restore its backed-up original S&SMP, and restore the previous guard if one existed; otherwise rename just the test guard inactive. No recursive deletion is needed. The source retains historical rejection text mentioning Restore-Eagle.ps1; that script is not included and must not be assumed available.
