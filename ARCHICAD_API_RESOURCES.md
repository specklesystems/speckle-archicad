# Archicad C++ API — Resources

Quick reference to where the actual Archicad Add-On API (C++) lives online, plus recipes for
fetching the ground truth without a browser. Written to be useful to any developer or agent working
on an Archicad add-on — not specific to any one API area.

**Last verified: 2026-10-18** (against DevKit release `30.3000`). Every link and claim below was
checked by direct download/inspection, not recollection.

## Official docs

- **API reference site** — https://graphisoft.github.io/archicad-api-devkit/
  Doxygen-generated reference. Currently documents the **Archicad 30 C++ API**. Best place to look
  up an exact class/method signature (e.g. `ACAPI::MEP::v1::RoutingElement`, `ACAPI::Element`), the
  classic C-style API (`ACAPI_Element_GetElemList`, `API_ElemType`, `API_Guid`, …), and add-on
  lifecycle types (`API_EnvirParams`, `API_MenuParams`, `API_MenuItemRef`).

- **Developer portal** — https://archicadapi.graphisoft.com/
  Main entry point for API developers: registration, downloads, guides, FAQ, blog. Also links out to
  the BIMx and BIMcloud APIs.
  - Getting started guide: https://archicadapi.graphisoft.com/getting_started_with_api_development_kit
  - SDK / older Development Kit downloads (pre-v25, before GitHub releases): https://archicadapi.graphisoft.com/downloads
  - Registration: https://archicadapi.graphisoft.com/registration/personal

## GitHub — the Development Kit itself

- **Repo**: https://github.com/GRAPHISOFT/archicad-api-devkit
  Holds the API documentation source and, via **Releases**, the actual Development Kit downloads from
  v25 onward.
- **Releases**: https://github.com/GRAPHISOFT/archicad-api-devkit/releases
  Release tags follow a `<major>.<build>` scheme (e.g. `29.3100`, `28.4001`, `27.6003`). The **latest
  as of this writing is `30.3000`** (build 3000, Archicad 30 v30.0.0, published 2026-10-07).
  Each release attaches the Development Kit as two downloadable ZIP assets, named:
  - `API.Development.Kit.WIN.<version>.zip`  (~15 MB — e.g. 14 MB for 29.3100, 17 MB for 30.3000)
  - `API.Development.Kit.MAC.<version>.zip`  (~75 MB)

  From `30.3000` on, a release also attaches `LP_XMLConverter.{WIN,MAC}.<version>.zip` and
  `Rendering.Development.Kit.{WIN,MAC}.<version>.zip`, so match asset names on the
  `API.Development.Kit` prefix.

  These are real ZIPs you can download directly (no auth, no registration). They contain two
  top-level folders:
  - `Support/` — the actual API headers and import libs, organized by API area under
    `Support/Modules/<Area>API/` (e.g. `ArchicadAPI`, `MEPAPI`, `PropertyOperationsAPI`,
    `IFCInOutAPI`, `AnalyticalModelAPI`, `DesignOptionsAPI`, `KeynoteAPI`, `UserInterfaceAPI`,
    `RoomBoundaryManagerAPI`, plus the framework modules `GSRoot`, `Geometry`, `DGLib`, `GSModeler`,
    …). Modern headers live under an `ACAPI/` subfolder as `ACAPI/*.hpp`
    (e.g. `ArchicadAPI/ACAPI/Element/Opening/Opening.hpp`), which maps to the `ACAPI::` C++ namespaces
    in the doc site.
  - `Examples/` — ~50 complete, buildable example add-ons (52 in 29.3100 and in 30.3000), one per API area. These are
    the fastest way to see real, working usage. Notable ones: `Element_Test`, `Property_Test`,
    `Property_Registration_Test`, `Geometry_Test`, `3D_Test`, `IFC_Test`, `IFCHook_Test`,
    `Classification_Test`, `Navigator_Test`, `Selection_Manager`, `Teamwork_Control`, `MEP_Test`,
    `StructuralAnalyticalModel_Test`, `LibPart_Test`, `Attribute_Test`, `DesignOptions_Test`,
    `Opening_Test`, `Keynote_Test`, `Browser_Control`, `DG_Test`, `Panel_Test`, `Notification_Manager`.

  > Note: the `Examples/` and Doxygen `docs/` source that ship in the release zip are **not** vendored
  > into this repo — the bundled DevKits under `Libs/acapi27|28|29|30/` contain only `Support/`. To read
  > example code or docs source, download the release zip.

## Fetching the ground truth without a browser (agent-friendly)

The GitHub Releases zip is the ground truth for "does the API support X". Recipes using `gh` + `curl`
(no auth needed for the download itself, but `gh` must be logged in for the API queries):

```bash
# List the most recent releases (tag, date, name)
gh api repos/GRAPHISOFT/archicad-api-devkit/releases \
  --jq '.[0:6][] | "\(.tag_name)\t\(.published_at)\t\(.name)"'

# List a release's assets with sizes
gh api repos/GRAPHISOFT/archicad-api-devkit/releases/tags/29.3100 \
  --jq '.assets[] | "\(.name)\t\(.size/1048576|floor)MB"'

# Download the Windows DevKit zip by asset API URL (streams the binary)
URL=$(gh api repos/GRAPHISOFT/archicad-api-devkit/releases/tags/29.3100 \
  --jq '.assets[] | select(.name|startswith("API.Development.Kit.WIN")) | .url')
curl -sL -H "Accept: application/octet-stream" "$URL" -o devkit.zip

# Peek inside without extracting
unzip -Z1 devkit.zip | grep -oE '^Examples/[^/]+/' | sort -u   # list example add-ons
unzip -Z1 devkit.zip | grep -oE '^Support/Modules/[^/]+/' | sort -u   # list API modules
```

## Community / forum

- **Archicad C++ API board** — https://community.graphisoft.com/t5/Archicad-C-API/bd-p/forum-ac-api
  Official Graphisoft Community forum for add-on developers. Good for searching whether a specific
  problem/question has already been answered (e.g. "how do I get X from element Y"), and for release
  announcements — new Development Kit versions are usually posted here first. (The board blocks
  automated fetchers with HTTP 403; open it in a browser.)
- **Developer Hub** — https://community.graphisoft.com/t5/Developer-Hub/ct-p/developer
  Broader landing area on the same community site, linking out to API, GDL, and other developer boards.

## Notes for future lookups

- Prefer the **release zip** over general knowledge when checking whether an API detail (function
  name, header, example) is current — the C++ API surface (namespaces, class names) has changed
  noticeably across Archicad versions (24 → 29), especially for newer areas like MEP.
- Match the DevKit version to the supported Archicad versions in this repo (**27, 28, 29, 30** — see
  `ci-build/Consts.cs`). This repo vendors `27`, `28`, `29`, `30` DevKits under `Libs/acapi27|28|29|30/`; the
  build auto-detects the major version and defines `AC27`/`AC28`/`AC29`/`AC30` (see `CMakeLists.txt`).
- This file is intentionally general-purpose. For area-specific detail, dig into the matching
  `Examples/<Area>_Test/` in the devkit zip and the corresponding `ACAPI::<Area>` namespace in the doc
  site.
