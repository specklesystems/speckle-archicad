---
name: research-archicad-api
description: Research an Archicad C++ API area from primary sources (doc site, DevKit release zip examples, developer portal, forum) before building on it — use whenever a feature needs an Archicad API you have not used in this codebase before (new element type, property, geometry, MEP, IFC, …).
---

# Researching the Archicad API

The C++ API surface changed noticeably across versions 24→29, so do the research from primary
sources, never from recollection. The map of those sources is **`ARCHICAD_API_RESOURCES.md`** in
the repo root: the official doc site, the developer portal, the GitHub DevKit repo/releases, the
community forum, and `gh`/`curl` recipes for downloading a DevKit release zip and grepping its
`Examples/` and `Support/Modules/` without a browser.

## Procedure

1. Read `ARCHICAD_API_RESOURCES.md`; note its "Last verified" date and latest-release note.
2. Ground truth for "does the API support X": the release zip's `Examples/<Area>_Test/` add-on and
   the `ACAPI::<Area>` namespace on the doc site. Download the zip with the recipes in that file —
   the vendored DevKits under `Libs/acapi27|28|29/` contain only `Support/` (headers/libs), not the
   examples.
3. Check the behaviour on every supported version (27, 28, 29): gate differences on the
   `AC27`/`AC28`/`AC29` compile definitions.
4. If you re-checked the sources, update the "Last verified" date and the latest-release note in
   `ARCHICAD_API_RESOURCES.md` so the next session can trust it.
