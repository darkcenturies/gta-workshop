# Public references, research and tooling boundary

GTA Workshop publishes GTA mod-making guides, upstream references, workflow maps,
findings, approved generated research and **source for the ten defined Valkyrie
tool families**. The owner's 2026-10-01 instruction supersedes the earlier
documentation-only restriction specifically for these tools and their helpers.

| Material | Boundary |
| --- | --- |
| Defined tool source, helpers, launcher, tests and synthetic examples | Public under `tooling/`, inventoried by `tooling/registry.json` |
| Guides, upstream references, findings and approved generated research | Public with provenance, target metadata and evidence limits |
| New tools outside the defined ten-family scope | Separate scope review; no bulk export of unrelated scripts |
| Mod implementations, runtime adapters, mod binaries and release packages | Excluded; stay in their implementation destinations |
| Game executables/assets, copied content packs, credentials, player/live data | Excluded; users supply independently permitted inputs |
| Private project ownership, local routing and private Git history | Excluded; stay in the workspace index/private repositories |

Tool source is distinct from the private implementation it may inspect, build
or test. A tool requiring a project tree does not authorize exporting that tree.
Some existing scripts reference historical targets, external host APIs or
project-specific layouts; retain attribution and document prerequisites.
Source publication does not claim compatibility or completed runtime validation.

Preserve original source notices and per-collection licenses. Linking a dependency
does not rebrand or relicense it. Generated research remains third-party-derived
evidence, not original vendor source; the root license does not override its rights.

The earlier owner-authorized knowledge-only history migration remains historical.
This change adds reviewed current tool files without private history or mod code.
Outside downloads/caches cannot be recalled by rewriting history.

The approved public path inventory includes these tool sources; CI checks tool
hashes, Python syntax, defined scope and three synthetic examples, plus research
checksums and documentation. Review actual content even when checks pass.
Every task returns committed safe findings. Merge, mod release and deployment
are separate outcomes; publishing tools does not authorize executing deployment.
