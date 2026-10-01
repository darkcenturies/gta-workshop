# Package verification

- Rebuilt the patched ASI from the exact original using the packaged portable builder. Output SHA-256 matches the user-tested ASI byte-for-byte: `76d4e0a72cd9c9875331bd8359f0bbdeaeb28a572d6cff9d992d6822858e5301`.
- Rebuilt the tested guard source using Visual Studio 2019 x86 Build Tools with the documented flags. `.text`, `.data` and `.reloc` sections match the user-tested guard exactly. Two timestamp bytes differ in `.rdata`; the historical handoff package supplied the original tested DLL; this public repository contains source only.
- The optional five-additional-lookups source was compiled separately but was not installed into the user-confirmed successful run.
- The user confirmed вЂњit works!вЂќ after the 418-native/282-generated lookup build remained running past the previous skin crash. This confirmation does not substitute for the release regression checklist.
