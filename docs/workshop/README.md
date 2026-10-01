# Maintaining the colored workshop atlas

The atlas has five complementary maps, a detailed [component catalog](CATALOG.md),
[structured catalog](catalog.json), [publication backlog](PUBLICATION-BACKLOG.md)
and [worked routes](EXAMPLES.md). The main reading order is in
[GTA-WORKSHOP.md](../GTA-WORKSHOP.md).

| Map | Question answered | Editable source | Rendered image |
| --- | --- | --- | --- |
| Ownership | Where does each kind of GTA work go and where do findings return? | [ownership.mmd](ownership.mmd) | [ownership.svg](ownership.svg) |
| Task flow | What happens from intake through implementation, failure, merge and return? | [task-flow.mmd](task-flow.mmd) | [task-flow.svg](task-flow.svg) |
| Dependencies | Which owner supplies shared source, host integration and local prerequisites? | [dependencies.mmd](dependencies.mmd) | [dependencies.svg](dependencies.svg) |
| Dryxio routes | Which task family uses each of the 18 repo references and separate texture reference? | [dryxio-routes.mmd](dryxio-routes.mmd) | [dryxio-routes.svg](dryxio-routes.svg) |
| Publication | What is already public, proposed, withheld, merged, released or deployed? | [publication.mmd](publication.mmd) | [publication.svg](publication.svg) |

## Color and edge contract

Use blue for workshop intake and durable evidence, green for already-public
source or accepted public contributions, purple for private source/evidence,
teal for external/tool references, amber for decisions/review/proposals, coral
for withheld inputs or failed/blocked paths, and orange for separate artifact
publication/deployment. Each node also says what it is; color alone never carries
visibility or approval. These are documentation states, not live health colors.

Solid arrows carry the relation written on them or the diagram's declared flow.
Dotted arrows denote consultation, integration or optional actions, with labels.
Dependency arrows point from consumer to provider; task-flow arrows point in
execution order. Do not combine those meanings without labeling the edge.

## Updating facts and diagrams

1. Recheck relevant owner instructions and source visibility. Use current
   metadata and explicit evidence, rather than treating the catalog as live state.
2. Update both catalog.json and CATALOG.md: owner, target, scope, source state,
   withholding reason, reference fit, applicable checks and required return.
   Preserve exact component IDs so related references can be reconciled.
3. Update affected `.mmd` sources and regenerate their SVGs. Keep node labels
   bounded; retain separate maps instead of a single unreadable graph. The main
   document embeds SVGs so readers see the intended colors consistently.
4. Review public safety, original credits, links and known source gaps. Never
   copy private implementation or restricted findings to make a map look complete.
5. Add reviewed new documentation paths to the public manifest, run the public
   boundary check and verify that implementation hashes have not drifted.
   Run `python tools/check_workshop.py` from the root to check maintained local
   links/anchors, component IDs, public entrypoints and catalog counts.
6. Inspect rendered maps at full size for cropped text, intersections and readable
   labels. Check light/dark GitHub presentation: the SVG has its own light canvas
   and contrasting text so the diagram remains legible in either page theme.
7. Commit/push sources, rendered images, catalog and returned findings together
   through a PR. Record actual validation and any unresolved coverage.

## Reproducing the render

The diagrams were rendered with **@mermaid-js/mermaid-cli 12.0.0**, using an
installed Chromium-family browser and no game assets. This documentation-only
renderer is not a dependency of the mod builds.

Example from a chosen documentation tooling environment:

```powershell
npx --yes --package @mermaid-js/mermaid-cli@12.0.0 mmdc -i docs/workshop/ownership.mmd -o docs/workshop/ownership.svg -c docs/workshop/mermaid-config.json --no-font-embed -b white --size 2200
```

Use the CLI's `-p` configuration when selecting an already installed browser;
do not commit user-specific absolute browser paths. Repeat for each source.
The shared mermaid-config.json pins the layout, font and pure SVG text labels;
generated diagrams use no HTML foreign objects, embedded fonts or remote assets.
The sources use documented flowchart syntax, explicit class styles, accessible
titles/descriptions and neutral structural edges. See
[Mermaid flowcharts](https://mermaid.js.org/syntax/flowchart.html) and
[the CLI](https://github.com/mermaid-js/mermaid-cli).
