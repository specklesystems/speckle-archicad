# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A Speckle connector for Archicad, implemented as a native C++20 Archicad Add-On (`.apx`). It embeds a web-based UI (Speckle's shared DUI3 frontend, loaded from `https://dui.speckle.systems/`) inside an Archicad palette, and bridges that JavaScript UI to native Archicad API calls that read/write model geometry, properties, and metadata.

Supported Archicad versions: **27, 28, 29** (declared in `ci-build/Consts.cs`). Windows is the primary/CI-built platform (the code has mac branches but CI builds Windows only).

## Researching the Archicad API

When implementing a new feature that needs an Archicad API you haven't used before (a new element type, property, geometry, MEP, IFC, etc.), do the research from primary sources rather than recollection — the C++ API surface changed noticeably across versions 24→29. See **`ARCHICAD_API_RESOURCES.md`** in the repo root: it lists the official doc site, the developer portal, the GitHub DevKit repo/releases, and the community forum, and includes `gh`/`curl` recipes for downloading the DevKit release zip and grepping its `Examples/` and `Support/Modules/` without a browser. The release zip's `Examples/<Area>_Test/` add-ons and the `ACAPI::<Area>` namespaces on the doc site are the ground truth for whether an API supports something. The vendored DevKits under `Libs/acapi27|28|29/` contain only `Support/` (headers/libs), not the examples — download the zip for those. Keep that file's "Last verified" date and latest-release note current if you re-check the sources.

## Building

Two ways to build:

**Local development (single version, Debug):** run the generator for your Archicad version, then build the generated solution.
```
generate_project_27.bat   # or _28 / _29 — creates build_27/ (build_28/, build_29/)
```
The generator is `cmake -G "Visual Studio 18 2026"`, so it emits **`build_27/archicad-speckle.slnx`** (the newer `.slnx` solution format, not `.sln`). Open it in Visual Studio 2026 and build, or debug with Archicad as the startup project (see README "Debugging" — note the README itself still describes the older VS 2019/2022 + `.sln` setup). Toolset is **v142** for 27/28 and **v143** for 29 (see the `.bat` files and `ci-build/Program.cs`).

Headless msbuild works too, e.g. `msbuild build_29\archicad-speckle.slnx /p:Configuration=Debug /p:Platform=x64 /m` from a developer shell. The v142 toolset is not present in every VS install — if you hit MSB8020, switch to an install that has it.

**Full CI-style build (all versions, Release, zipped installers):**
```
./build.ps1              # Windows — runs ci-build/build.csproj
```
`build.ps1` is what CI (`.github/workflows/pr.yml` and `release.yml`) runs. It invokes the Bullseye target runner in `ci-build/Program.cs`. Targets: `clean`, `restore-tools`, `build-cmake`, `build`, `zip`, and `default` (which chains `zip` → `build` → `build-cmake`); `clean` and `restore-tools` are standalone. The CI path configures into `build/<version>/` (not `build_<version>/`) and packages `build/<version>/INT/Release/*.apx` into `output/archicad.zip`.

> Note: `build.sh` runs `dotnet run --project Build/Build.csproj`, which does not exist — the active project is `ci-build/`. `build.sh` is dead; use `build.ps1`.
>
> Note: `ci-build/Consts.cs` also has a `Solutions` array with stale paths (`build_27/speckle-archicad.slnx`); nothing references it. The real msbuild invocation lives in `Program.cs`.

Requirements: CMake ≥ 3.16, Visual Studio 2026 with v142 **and** v143 toolsets, .NET SDK (for the build orchestrator), Python (Archicad resource build tools). The Archicad API DevKit is resolved from `AC_API_DEVKIT_DIR`; the bundled DevKits live in `Libs/acapi27`, `Libs/acapi28`, `Libs/acapi29`. `CMakeLists.txt` auto-detects the Archicad major version from `ACAPinc.h` and defines `AC27`/`AC28`/`AC29` accordingly — version-specific code branches on these macros.

## Versioning and releases

Versioning is **tag-driven**, not GitVersion (GitVersion was removed in `fe9f5e4`; there is no `GitVersion.yml`). `main` is the production branch.

- `ci-build/Program.cs` reads the version from the `SEMVER` and `FILE_VERSION` environment variables, falling back to `0.0.0-localBuild` / `0.0.0.9999`. The `build` target substitutes `SEMVER` for the `connector_build_num` placeholder in `AddOnResources/RINT/AddOn.grc` and passes both to msbuild.
- `.github/workflows/release.yml` builds and then dispatches the `Build Installers` workflow in `specklesystems/connector-installers`. It triggers on:
  - **push to `installer-test/**`** → a *test* installer. Version is synthesized as `v0.0.0.<run_number>`, `is_public_release: false`. To cut one off any branch: `git push origin <branch>:installer-test/<name>`.
  - **push of a `v202*.*.*` tag** (calendar versioning, e.g. `v2026.6.0`) → a *public* installer, `is_public_release: true`. The old `v3.x` tags no longer match the trigger.
- Known gap: `release.yml` computes `semver`/`fileVersion` as step outputs but never exports them as `SEMVER`/`FILE_VERSION` for the `./build.ps1` step, so the `.apx` resource version is the `0.0.0-localBuild` fallback for both test *and* tagged builds. Only the installer package downstream carries the real version.

## Testing

There is no C++ unit-test suite. `enable_testing()` is set in CMake but no tests are registered. The `TestBridge` (`Connector/Bridges/TestBridge.cpp`) exposes methods (`SayHi`, `GetComplexType`, `TriggerEvent`) used to exercise the JS↔C++ bridge round-trip from the UI, not an automated test runner.

## Architecture

All add-on source lives under `AddOns/Speckle/Sources/`:
- `AddOn/` — the C++ implementation (this is where nearly all work happens). Subfolders: `Connector/` (singleton, bridges, databases), `Converter/`, `Artifacts/` (parquet bundle send/receive), `Auth/` (OAuth), `Browser/`, `Network/`, `Storage/`, `DataTypes/`, `Diagnostics/`, `Utils/`.
- `AddOnResources/` — Archicad `.grc`/`.rc2` resource definitions, images, and `Tools/*.py` resource-compilation scripts. `RINT/AddOn.grc` holds the add-on name/description and the build-injected version.

### Entry point and lifecycle
`AddOn/AddOnMain.cpp` implements the Archicad Add-On callbacks (`Initialize`, `RegisterInterface`, `CheckEnvironment`, `FreeData`). On `Initialize` it: constructs the `Connector` singleton, registers the menu handler that toggles the `BrowserPalette`, catches Archicad project/selection notifications, initializes the `BrowserBridge`, loads the UI URL, and wires Archicad events (`ProjectOpened`, `ProjectClosed`, `SelectionChanged`) to bridge callbacks.

### Two singletons
- **`Connector`** (`Connector/Connector.{h,cpp}`, macro `CONNECTOR`) — owns the backend services: `IAccountDatabase`, `IJsonObjectDatabase`, `IModelCardDatabase`, `IHostToSpeckleConverter`, `ISpeckleToHostConverter`, `HostAppEvents`, `IProcessWindow`. Everything is accessed through interfaces and constructed in `InitConnector()`.
- **`BrowserBridge`** (`Connector/Bridges/BrowserBridge.{h,cpp}`, macro `BROWSERBRIDGE`) — owns all the bridges and the `IBrowserAdapter`.

### The Bridge / Binding pattern (JS ↔ C++)
This is the core communication mechanism and mirrors Speckle's DUI3 binding model.
- Each **Bridge** (`AccountBridge`, `BaseBridge`, `ConfigBridge`, `SelectionBridge`, `SendBridge`, `ReceiveBridge`, `TestBridge`) implements `IBridge::RunMethod(RunMethodEventArgs&)` and owns a `Binding`.
- A **`Binding`** (`Connector/Binding.{h,cpp}`) registers a JS object name + a list of method names with the browser (via `IBrowserAdapter`), routes incoming JS calls to the bridge's `RunMethod`, resolves the call with `SetResult`, and pushes asynchronous events back to JS with `Send` (e.g. `setModelSendResult`, `triggerCancel`).
- `RunMethod` implementations are a manual `if (args.methodName == "...")` dispatch. **To add a new UI-callable method:** add its name to the `Binding`'s method-name vector in the bridge constructor, add the `else if` branch in `RunMethod`, and implement the handler. Unknown names throw `InvalidMethodNameException`.
- The `IBrowserAdapter` abstraction (`Browser/`) keeps Archicad's `DG::Browser` dependency out of the binding logic; `ArchiCadBrowserAdapter` is the real impl and `DummyBrowserAdapter` is the no-op.

### Send flow (Archicad → Speckle)
Speckle 4.0 "artifact" send: the C++ side writes a parquet bundle locally and uploads it natively — the frontend no longer relays object data.

`SendBridge::Send` shows the 3D view, reads the `sendProperties` setting off the model card, then `SendViaArtifacts` runs `ArchicadArtifactRootObjectBuilder::BuildAndUpload` (`Connector/`): convert the selected element IDs via `HostToSpeckleConverter`, write the parquet tables with `Artifacts/BundleWriter` (meshes encoded by `Artifacts/SgeoEncoder`, `Libs/minipq` as the parquet engine, `Libs/bundlespec` for the schema), then `Artifacts/ArtifactUploader` does sign → presigned PUT → complete against the server using the token from `IAccountDatabase`. The resulting `versionId` and the per-element `SendConversionResult`s go to the UI via the `setModelSendResult` event; a `UserCancelledException` becomes `triggerCancel`. Progress is reported through `IProcessWindow` as six named phases. Layer visibility that the send temporarily changed is restored afterward.

### Receive flow (Speckle → Archicad)
`ReceiveBridge` + `ArtifactReceiver` (`Artifacts/`) download the version's parquet bundle, read it with the in-tree minipq reader, decode the SGEO meshes, write one GDL `<Symbol>` XML per object and convert them to `.gsm` via `LP_XMLConverter`; `LibpartPlacer` (`Converter/SpeckleToHost/`) then registers and places the produced library parts.

### Converters
`Converter/HostToSpeckle/` and `Converter/SpeckleToHost/` hold one file per conversion concern (e.g. `GetElementBody.cpp`, `GetElementProperties.cpp`, `GetLayers.cpp`, `LibpartPlacer.cpp`). The `IHostToSpeckleConverter` / `ISpeckleToHostConverter` interfaces are the seam. This is the place for element-type and property mapping work.

### Data model
`DataTypes/` holds plain structs with `nlohmann::json` (de)serialization: model cards (`SenderModelCard`/`ReceiverModelCard`), send filters (`ArchicadSelectionFilter`, `ArchicadElementTypeFilter`, `ArchicadLayerFilter`, `ArchicadViewsFilter`), geometry and model data (`Mesh`, `ElementBody`, `Material`, `ColorProxy`, `ObjectInstance`, `ArchicadLevel`, `ArchicadLayer`, `ArchicadRoomTopology`), UI config (`ConnectorConfig`, `AccountsConfig`, `WorkspacesConfig`), and conversion results. Filters returned by `GetSendFilters` control what gets sent.

### Persistence
- `IModelCardDatabase` / `ModelCardDatabase` — the sender/receiver model cards shown in the UI. Persisted into the Archicad document itself via `IDataStorage`/`ArchiCadDataStorage` (survives project save/open; reloaded on `ProjectOpened`).
- `IJsonObjectDatabase` / `SqliteJsonObjectDatabase` — SQLite-backed keyed JSON document store (`Libs/sqlite`) holding the DUI3 config the UI reads and writes: `"Archicad"` (connector config), `"accounts"`, `"workspaces"`.
- `IAccountDatabase` / `AccountDatabase` — Speckle accounts and tokens, read from the shared local Speckle account DB at `%APPDATA%\Speckle\Accounts.db`.
- `Auth/` — in-connector OAuth: `OAuthFlow` + `LoopbackListener` + `CryptoUtils` (PKCE) drive the browser login and `AccountFactory` writes the resulting account, so the connector can add an account itself (`AccountBridge`'s `AddAccount` / `AuthenticateAccount`) instead of depending on Speckle Manager. HTTP goes through `Network/IHttpClient` (`WinHttpClient` on Windows).

## Conventions

- Interfaces are `I*.h` header-only abstract classes; the singleton getters throw `std::runtime_error` if a dependency wasn't initialized. New backend services should follow the interface + `Connector`-owned-`unique_ptr` pattern so they can be swapped/mocked.
- Version-specific Archicad API differences are gated on the `AC27`/`AC28`/`AC29` compile definitions.
- The JS-facing method names in a `Binding` must exactly match what the DUI3 frontend calls — these are a shared contract with the Speckle frontend, not free to rename unilaterally.
- Bundled third-party libs (`Libs/json`, `spdlog`, `sqlite`, `sha`, `md5`, `zstd`, `minipq`, `bundlespec`) are added as CMake subdirectories and grouped under a `Libs` solution folder; don't vendor duplicates. `minipq` (in-tree parquet writer/reader, zstd-only dependency) is the parquet engine for the artifact send/receive pipeline — it and `zstd` compile statically into the .apx, and `Libs/minipq/README.md` documents its provenance and local modifications.
- The connector version is injected into resources at build time, not hardcoded — see "Versioning and releases".
