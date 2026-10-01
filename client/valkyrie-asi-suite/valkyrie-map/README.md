# Valkyrie Map for GTA San Andreas

The map centers on stock San Andreas with zoom limits of 300 to 1100.
Build using `./build.ps1 -Target map -Release` from the repository root.
Install `valkyrie-map.asi` with the game closed and an x86 ASI loader.

The native map works without a composed overview. An optional stock overview
built from the player's own tiles is named `sprp-map-sa-overview.txd`; the old
edition overview filename is ignored so it cannot replace San Andreas' map.
The overview builder creates a texture from supplied tiles; it does not supply
game textures. Build success is separate from in-game map/navigation testing.
