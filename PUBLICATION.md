# Public knowledge and research boundary

GTA Workshop publishes information on making and improving GTA mods: guides,
catalogs, workflow maps, reference inventories, findings, exact-target metadata,
checksums and generated research archives. It publishes no mod implementation,
authored research tools, experimental adapter source, build recipes or releases.

Doctor/Crashfix, Map and Repair implementation is private in Valkyrie Workshop.
Phone remains public in its separate existing repository. See
[the owner table](README.md#projects-and-implementation-owners) and
[component catalog](docs/workshop/CATALOG.md).

The owner explicitly retained public findings and generated decompilation/
disassembly, including reconstructed research pseudocode and approved IDA
databases. These are third-party-derived evidence, not permission to distribute
game inputs or an assertion that vendor source is owned or runnable.

Authored scripts, mod source and experimental implementation are preserved in
the private owner. Do not import them here, including through a public staging
branch. Explain methods with documentation; use independently obtained inputs
and public-safe observations. Code snippets in a guide are illustrative
instruction, not a packaged implementation.

The fresh knowledge-only public history replaces former implementation history
at the owner's request. The old reachable branches were preserved privately
before replacement. Existing downloads, outside copies and GitHub cached PR
views cannot be recalled by a Git history rewrite.

`publication/approved-files.json` inventories approved public knowledge paths
and pins research evidence hashes. Repository CI checks the knowledge-only scope
and archive checksums. Scope review remains necessary even when checks pass.

Never publish player records, credentials, production configuration, private
history, input executables or copied game assets. Cataloging a private component
does not approve a source export. Proposed future implementation releases need
a separate destination and explicit owner decision; this workshop remains the
knowledge hub.

Every originating task returns committed public-safe findings through a PR.
Review, source merge, artifact release and deployment are separate statuses.
