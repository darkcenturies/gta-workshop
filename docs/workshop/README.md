# Maintaining the colored workshop atlas

The atlas has five complementary maps, a detailed [reference catalog](CATALOG.md),
[structured catalog](catalog.json), [publication backlog](PUBLICATION-BACKLOG.md)
and [worked routes](EXAMPLES.md). The main reading order is in
[GTA-WORKSHOP.md](../GTA-WORKSHOP.md).

| Map | Question answered | Editable source | Rendered image |
| --- | --- | --- | --- |
| Library navigation | How do readers find references, methods and evidence and return knowledge? | [ownership.mmd](ownership.mmd) | [ownership.svg](ownership.svg) |
| Task flow | How does a research question become tested, reusable findings? | [task-flow.mmd](task-flow.mmd) | [task-flow.svg](task-flow.svg) |
| Evidence requirements | Which prerequisites and checks does each method need? | [dependencies.mmd](dependencies.mmd) | [dependencies.svg](dependencies.svg) |
| Dryxio routes | Which task family uses each of the 18 repo references and separate texture reference? | [dryxio-routes.mmd](dryxio-routes.mmd) | [dryxio-routes.svg](dryxio-routes.svg) |
| Publication | What knowledge is public, proposed or excluded and why? | [publication.mmd](publication.mmd) | [publication.svg](publication.svg) |

## Color and edge contract

Use blue for workshop intake and durable evidence, green for already-public
knowledge or accepted public contributions, purple for work outside the library,
teal for external/tool references, amber for decisions/review/proposals, coral
for withheld inputs or failed/blocked paths. Each node also says what it is; color alone never carries
visibility or approval. These are documentation states, not live health colors.

Solid arrows carry the relation written on them or the diagram's declared flow.
Dotted arrows denote consultation, integration or optional actions, with labels.
Evidence arrows point from a method to its requirements; task-flow arrows point in
execution order. Do not combine those meanings without labeling the edge.

## Updating facts and diagrams

1. Recheck upstream references, provenance and recorded evaluation status. Use current
   metadata and explicit evidence, rather than treating the catalog as live state.
2. Update both catalog.json and CATALOG.md: task family, target applicability, reference revisions,
   fork parents, evaluation status, applicable checks and required return.
   Preserve stable topic IDs; private product inventory does not belong here.
3. Update affected `.mmd` sources and regenerate their SVGs. Keep node labels
   bounded; retain separate maps instead of a single unreadable graph. The main
   document embeds SVGs so readers see the intended colors consistently.
4. Review public safety, original credits, links and evidence limits. Never
   copy private implementation or restricted findings to make a map look complete.
5. Add reviewed paths to the public manifest; verify defined tool scope,
   local links, catalog/source consistency and exact research hashes.
   Tool checkers and synthetic examples are public; mod implementation stays excluded.
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
