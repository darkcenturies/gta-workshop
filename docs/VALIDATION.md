# Validating public library contributions

For documentation changes, check local paths and anchors, catalog/inventory
consistency, attribution, publication scope and affected rendered diagrams.
Update the approved knowledge-path inventory when adding a file.

Generated research has a separate evidence gate: verify
`docs/reverse-engineering/SHA256SUMS` and target manifests without modifying
archives merely to change documentation. The generated index covers six targets
and 45 files; approved IDA evidence has its separate manifest.

Public CI checks the knowledge-only tree, research checksums and overview
formatting. It does not build mods, install tools or establish gameplay behavior.
Report only checks actually run. Follow [build/validation methods](BUILDING.md)
for project experiments and return their evidence through a finding.
