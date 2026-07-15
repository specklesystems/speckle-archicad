# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A Speckle connector for Archicad, implemented as a native C++20 Archicad Add-On (`.apx`). It embeds a web-based UI (Speckle's shared DUI3 frontend, loaded from `https://dui.speckle.systems/`) inside an Archicad palette, and bridges that JavaScript UI to native Archicad API calls that read/write model geometry, properties, and metadata.

Supported Archicad versions: **27, 28, 29** (declared in `ci-build/Consts.cs`). The connector builds on Windows and macOS; CI currently builds Windows only.

## Researching the Archicad API

When implementing a new feature that needs an Archicad API you haven't used before (a new element type, property, geometry, MEP, IFC, etc.), do the research from primary sources rather than recollection — the C++ API surface changed noticeably across versions 24→29. See **`ARCHICAD_API_RESOURCES.md`** in the repo root: it lists the official doc site, the developer portal, the GitHub DevKit repo/releases, and the community forum, and includes `gh`/`curl` recipes for downloading the DevKit release zip and grepping its `Examples/` and `Support/Modules/` without a browser. The release zip's `Examples/<Area>_Test/` add-ons and the `ACAPI::<Area>` namespaces on the doc site are the ground truth for whether an API supports something. The vendored DevKits under `Libs/acapi27|28|29/` contain only `Support/` (headers/libs), not the examples — download the zip for those. Keep that file's "Last verified" date and latest-release note current if you re-check the sources.

## Building

Two ways to build:

**Local development (single version, Debug):** run the generator for your Archicad version, then build the generated Visual Studio solution.
```
generate_project_27.bat   # or _28 / _29 — creates build_27/ (build_28/, build_29/)
```
Then open `build_27/archicad-speckle.sln` in Visual Studio 2022 and build, or debug with Archicad as the startup project (see README "Debugging"). Toolset is **v142** for 27/28 and **v143** for 29 (see the `.bat` files and `ci-build/Program.cs`).

**macOS (one version, Debug or Release):**
```
./build.sh 27 Release       # or 28 / 29
```
This downloads and caches the official macOS Graphisoft DevKit for the selected version, builds a universal `arm64;x86_64` bundle, embeds DuckDB, and ad-hoc signs it. Output: `build/mac/<version>/INT/<configuration>/Speckle.bundle`. Use `AC_API_DEVKIT_DIR` for a local DevKit, `SPECKLE_DUCKDB_ROOT` for a local DuckDB package, `SPECKLE_MAC_ARCHITECTURES=arm64` for a faster local build, and `SPECKLE_CODESIGN_IDENTITY` at CMake configuration time for distribution signing.

**Full Windows CI-style build (all versions, Release, zipped installers):**
```
./build.ps1              # Windows — runs ci-build/build.csproj
```
`build.ps1` is what CI (`.github/workflows/pr.yml`) runs. It invokes the Bullseye target runner in `ci-build/Program.cs`. Targets: `clean`, `restore-tools`, `build-server-version`, `build-cmake`, `build`, `zip` (default target chains through `zip`). The `build` target injects the GitVersion-derived version string into `AddOnResources/RINT/AddOn.grc` before running msbuild.

Windows requirements: CMake ≥ 3.16, Visual Studio 2022 with v142 **and** v143 toolsets, .NET SDK (for the build orchestrator), and Python 3 (Archicad resource build tools). macOS requires Xcode command-line tools, CMake ≥ 3.16, Python 3, curl, and unzip. `CMakeLists.txt` auto-detects the Archicad major version from `ACAPinc.h` and defines `AC27`/`AC28`/`AC29` accordingly — version-specific code branches on these macros.

## Testing

There is no C++ unit-test suite. `enable_testing()` is set in CMake but no tests are registered. The `TestBridge` (`Connector/Bridges/TestBridge.cpp`) exposes methods (`SayHi`, `GetComplexType`, `TriggerEvent`) used to exercise the JS↔C++ bridge round-trip from the UI, not an automated test runner.

## Architecture

All add-on source lives under `AddOns/Speckle/Sources/`:
- `AddOn/` — the C++ implementation (this is where nearly all work happens).
- `AddOnResources/` — Archicad `.grc`/`.rc2` resource definitions, images, and `Tools/*.py` resource-compilation scripts. `RINT/AddOn.grc` holds the add-on name/description and the build-injected version.

### Entry point and lifecycle
`AddOn/AddOnMain.cpp` implements the Archicad Add-On callbacks (`Initialize`, `RegisterInterface`, `CheckEnvironment`, `FreeData`). On `Initialize` it: constructs the `Connector` singleton, registers the menu handler that toggles the `BrowserPalette`, catches Archicad project/selection notifications, initializes the `BrowserBridge`, loads the UI URL, and wires Archicad events (`ProjectOpened`, `ProjectClosed`, `SelectionChanged`) to bridge callbacks.

### Two singletons
- **`Connector`** (`Connector/Connector.{h,cpp}`, macro `CONNECTOR`) — owns the backend services: `IAccountDatabase`, `IJsonObjectDatabase` (SQLite), `IModelCardDatabase`, `IHostToSpeckleConverter`, `ISpeckleToHostConverter`, `HostAppEvents`, `IProcessWindow`. Everything is accessed through interfaces and constructed in `InitConnector()`.
- **`BrowserBridge`** (`Connector/Bridges/BrowserBridge.{h,cpp}`, macro `BROWSERBRIDGE`) — owns all the bridges and the `IBrowserAdapter`.

### The Bridge / Binding pattern (JS ↔ C++)
This is the core communication mechanism and mirrors Speckle's DUI3 binding model.
- Each **Bridge** (`AccountBridge`, `BaseBridge`, `ConfigBridge`, `SelectionBridge`, `SendBridge`, `ReceiveBridge`, `TestBridge`) implements `IBridge::RunMethod(RunMethodEventArgs&)` and owns a `Binding`.
- A **`Binding`** (`Connector/Binding.{h,cpp}`) registers a JS object name + a list of method names with the browser (via `IBrowserAdapter`), routes incoming JS calls to the bridge's `RunMethod`, and returns results/emits events back to JS. Results can be returned synchronously (`SetResult`) or streamed via the browser (`SendBatchViaBrowser`, `CreateVersionViaBrowser`).
- `RunMethod` implementations are a manual `if (args.methodName == "...")` dispatch. **To add a new UI-callable method:** add its name to the `Binding`'s method-name vector in the bridge constructor, add the `else if` branch in `RunMethod`, and implement the handler. Unknown names throw `InvalidMethodNameException`.
- The `IBrowserAdapter` abstraction (`Browser/`) keeps Archicad's `DG::Browser` dependency out of the binding logic; `ArchiCadBrowserAdapter` is the real impl and `DummyBrowserAdapter` is the no-op.

### Send flow (Archicad → Speckle)
The current artifact pipeline builds an EAV Parquet bundle with DuckDB and uploads it through the platform HTTP client (WinHTTP on Windows and NSURLSession on macOS). Earlier JSON bridge code remains in the codebase for the legacy send path. Layer visibility that send temporarily changes is restored afterward.

### Receive flow (Speckle → Archicad)
`ReceiveBridge` downloads the artifact bundle, decodes geometry, generates library-part XML, invokes Archicad's `LP_XMLConverter`, and places the resulting GSM library parts through `LibpartPlacer`. Process launch is implemented with `CreateProcessW` on Windows and `posix_spawn` on macOS.

### Converters
`Converter/HostToSpeckle/` and `Converter/SpeckleToHost/` hold one file per conversion concern (e.g. `GetElementBody.cpp`, `GetElementProperties.cpp`, `GetLayers.cpp`, `CreateMorph.cpp`). The `IHostToSpeckleConverter` / `ISpeckleToHostConverter` interfaces are the seam. This is the place for element-type and property mapping work.

### Data model
`DataTypes/` holds plain structs with `nlohmann::json` (de)serialization: model cards (`SenderModelCard`/`ReceiverModelCard`), send filters (`ArchicadSelectionFilter`, `ArchicadElementTypeFilter`, `ArchicadLayerFilter`, `ArchicadViewsFilter`), Speckle proxies (`ColorProxy`, `RenderMaterialProxy`, `InstanceProxy`, `LevelProxy`), geometry (`Mesh`, `ElementBody`), and conversion results. Filters returned by `GetSendFilters` control what gets sent.

### Persistence
- `IModelCardDatabase` / `ModelCardDatabase` — the sender/receiver model cards shown in the UI. Persisted into the Archicad document itself via `IDataStorage`/`ArchiCadDataStorage` (survives project save/open; reloaded on `ProjectOpened`).
- `IJsonObjectDatabase` / `SqliteJsonObjectDatabase` — SQLite-backed object cache (`Libs/sqlite`).
- `IAccountDatabase` / `AccountDatabase` — Speckle accounts and tokens (read from the local Speckle account config).

## Conventions

- Interfaces are `I*.h` header-only abstract classes; the singleton getters throw `std::runtime_error` if a dependency wasn't initialized. New backend services should follow the interface + `Connector`-owned-`unique_ptr` pattern so they can be swapped/mocked.
- Version-specific Archicad API differences are gated on the `AC27`/`AC28`/`AC29` compile definitions.
- The JS-facing method names in a `Binding` must exactly match what the DUI3 frontend calls — these are a shared contract with the Speckle frontend, not free to rename unilaterally.
- Bundled third-party libs (`Libs/json`, `spdlog`, `sqlite`, `sha`, `md5`) are added as CMake subdirectories and grouped under a `Libs` solution folder; don't vendor duplicates.
- Versioning is GitVersion/GitFlow (`GitVersion.yml`); the connector version is injected into resources at build time, not hardcoded.
