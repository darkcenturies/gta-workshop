# Public export validation

The published build targets are Map 0.2.0, Doctor 0.3.2, Crashfix 2.3.0-test and Repair 1.2. Map has been restored to its earlier source baseline to exclude private Radar additions. The exact later Map 0.2.1 source is not claimed here.

Initial Doctor/Crashfix/Repair builds passed on Windows. Repair passed 26 isolated self-tests and Crashfix passed its native tests. Current CI rebuilds these projects and the Map baseline. Archive checks verify four decompilation targets and 31 files against checksums and metadata.

Crashfix emits the existing MSVC C4733 warning for an inline-assembly exception handler. It remains a test build. No game is launched, no mod is installed and no server is deployed by these checks. Full decompilation was not rerun; the existing output is preserved byte-for-byte.
