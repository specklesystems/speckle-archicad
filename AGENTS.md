# speckle-archicad

Speckle connector for Archicad: a native C++20 Archicad Add-On (`.apx`) that embeds Speckle's shared
DUI3 web UI (loaded from `https://dui.speckle.systems/`) in an Archicad palette and bridges that
JavaScript UI to Archicad API calls that read/write model geometry, properties and metadata.
Supported Archicad versions: **27, 28, 29** (`ci-build/Consts.cs`). Windows is the primary and only
CI-built platform; the code has mac branches.

```
AddOns/Speckle/Sources/
  AddOn/            the C++ implementation — nearly all work happens here
    AddOnMain.cpp   Archicad add-on callbacks (Initialize, RegisterInterface, CheckEnvironment, FreeData)
    Connector/      Connector singleton, Binding, databases, Bridges/, artifact root builder
    Converter/      HostToSpeckle/ and SpeckleToHost/, one file per conversion concern
    Artifacts/      parquet bundle send/receive: BundleWriter, SgeoEncoder, ArtifactUploader, ArtifactReceiver
    Auth/           in-connector OAuth (OAuthFlow, LoopbackListener, CryptoUtils/PKCE, AccountFactory)
    Browser/        IBrowserAdapter keeps DG::Browser out of binding logic; ArchiCad (real) / Dummy (no-op) impls
    Network/ Storage/ DataTypes/ Diagnostics/ Utils/
  AddOnResources/   .grc/.rc2 resources, images, Tools/*.py compilers; RINT/AddOn.grc = name + injected version
ci-build/           Bullseye build orchestrator (Program.cs, Consts.cs) run by build.ps1 and CI
Libs/               acapi27|28|29 DevKits (Support/ only), json, spdlog, sqlite, sha, md5, zstd, minipq, bundlespec
```

## Procedures (skills)

- `/build-addon` — one-version Debug build (`generate_project_NN.bat` → `build_NN/archicad-speckle.slnx`,
  VS 2026, v142 for 27/28, v143 for 29) or the CI-style `./build.ps1`; toolchain; gotchas.
- `/cut-installer` — test installer via an `installer-test/<name>` push, public release via an
  unprefixed CalVer tag (`2026.9.0`); how `SEMVER`/`FILE_VERSION` reach the `.apx`.
- `/research-archicad-api` — before using an Archicad API new to this codebase: primary sources only
  (`ARCHICAD_API_RESOURCES.md`), never recollection; the surface changed noticeably 24→29.

## Architecture

**Entry point.** `AddOnMain.cpp` on `Initialize`: constructs the `Connector` singleton, registers the
menu handler that toggles the `BrowserPalette`, initializes the `BrowserBridge`, loads the UI URL, and
wires Archicad notifications (`ProjectOpened`, `ProjectClosed`, `SelectionChanged`) to bridge callbacks.

**Two singletons.** `Connector` (`Connector/Connector.{h,cpp}`, macro `CONNECTOR`) owns the backend
services behind interfaces constructed in `InitConnector()`: `IAccountDatabase`, `IJsonObjectDatabase`,
`IModelCardDatabase`, `IHostToSpeckleConverter`, `ISpeckleToHostConverter`, `HostAppEvents`,
`IProcessWindow`. `BrowserBridge` (`Connector/Bridges/BrowserBridge.{h,cpp}`, macro `BROWSERBRIDGE`)
owns all the bridges and the `IBrowserAdapter`.

**Bridge / Binding (JS ↔ C++)** — the core mechanism, mirroring Speckle's DUI3 binding model. Each
bridge (`AccountBridge`, `BaseBridge`, `ConfigBridge`, `SelectionBridge`, `SendBridge`,
`ReceiveBridge`, `TestBridge`) implements `IBridge::RunMethod(RunMethodEventArgs&)` and owns a
`Binding` (`Connector/Binding.{h,cpp}`), which registers a JS object name + method names with the
browser, routes incoming JS calls to `RunMethod`, resolves them with `SetResult`, and pushes events
back with `Send` (`setModelSendResult`, `triggerCancel`, …). `RunMethod` is a manual
`if (args.methodName == "...")` dispatch; unknown names throw `InvalidMethodNameException`. **To add
a UI-callable method:** append its name to the `Binding`'s method-name vector in the bridge
constructor, add the `else if` branch in `RunMethod`, implement the handler. The JS-facing names are a
shared contract with the DUI3 frontend — never rename unilaterally.

**Send (Archicad → Speckle).** Speckle 4.0 artifact send: C++ writes a parquet bundle locally and
uploads it natively; the frontend relays no object data. `SendBridge::Send` shows the 3D view, reads
`sendProperties` off the model card, then `SendViaArtifacts` runs
`ArchicadArtifactRootObjectBuilder::BuildAndUpload`: convert the selected element IDs via
`HostToSpeckleConverter`, write the tables with `Artifacts/BundleWriter` (meshes via `SgeoEncoder`,
`Libs/minipq` as parquet engine, `Libs/bundlespec` for the schema), then `ArtifactUploader` does sign →
presigned PUT → complete with the `IAccountDatabase` token. `versionId` + per-element
`SendConversionResult`s reach the UI via `setModelSendResult`; `UserCancelledException` becomes
`triggerCancel`; progress is six named `IProcessWindow` phases; layer visibility the send changed is
restored afterwards.

**Receive (Speckle → Archicad).** `ReceiveBridge` + `Artifacts/ArtifactReceiver` download the
version's parquet bundle, read it with the in-tree minipq reader, decode the SGEO meshes, write one
GDL `<Symbol>` XML per object and convert them to `.gsm` via `LP_XMLConverter`; `LibpartPlacer`
(`Converter/SpeckleToHost/`) registers and places the produced library parts.

**Converters.** `Converter/HostToSpeckle/` and `Converter/SpeckleToHost/` — one file per concern
(`GetElementBody.cpp`, `GetElementProperties.cpp`, `GetLayers.cpp`, `LibpartPlacer.cpp`, …) behind
`IHostToSpeckleConverter` / `ISpeckleToHostConverter`. Element-type and property mapping work lives here.

**Data model.** `DataTypes/`: plain structs with `nlohmann::json` (de)serialization — model cards
(`SenderModelCard`/`ReceiverModelCard`), send filters (selection, element type, layer, views; what
`GetSendFilters` returns controls what gets sent), geometry/model data (`Mesh`, `ElementBody`,
`Material`, `ObjectInstance`, levels, layers, room topology), UI config, conversion results.

**Persistence.** `ModelCardDatabase` — sender/receiver model cards, persisted into the Archicad
document via `IDataStorage`/`ArchiCadDataStorage` (survives save/open; reloaded on `ProjectOpened`).
`SqliteJsonObjectDatabase` — SQLite-backed keyed JSON store (`Libs/sqlite`) for the DUI3 config the UI
reads/writes: `"Archicad"` (connector config), `"accounts"`, `"workspaces"`. `AccountDatabase` —
accounts and tokens from the shared local Speckle DB `%APPDATA%\Speckle\Accounts.db`; `Auth/` lets
the connector add an account itself (`AccountBridge::AddAccount` / `AuthenticateAccount`) instead of
depending on Speckle Manager.

## Build and release facts

- No C++ unit-test suite. PR CI (`pr.yml`) and `release.yml` both run `./build.ps1`; `build.sh` is dead.
- Versioning is tag-driven (`/cut-installer`). The `build` target substitutes `SEMVER` into
  `AddOnResources/RINT/AddOn.grc` (`STR# 5010`) — the version the UI shows and the
  `envelope.meta.producer_version` of every bundle, so a wrong value is visible server-side. Running
  `build.ps1` locally rewrites that tracked file; `git checkout` it afterwards.
- `CMakeLists.txt` detects the DevKit major from `ACAPinc.h` and defines `AC27`/`AC28`/`AC29`.

## Conventions

- Interfaces are header-only `I*.h` abstract classes; singleton getters throw `std::runtime_error` if
  a dependency was not initialized. New backend services follow the interface +
  `Connector`-owned-`unique_ptr` pattern so they can be swapped/mocked.
- Version-specific Archicad API differences are gated on `AC27`/`AC28`/`AC29`.
- Bundled third-party libs are CMake subdirectories grouped under a `Libs` solution folder; don't
  vendor duplicates. `minipq` (in-tree parquet writer/reader, zstd-only dependency) and `zstd` compile
  statically into the `.apx`; `Libs/minipq/README.md` documents provenance and local modifications.

## Agent config (ADR-0008)

Tracked: this file, `agents/skills/`, hooks `.claude/settings.json`, `.codex/hooks.json`,
`.omp/extensions/atlas-sync.js`. `.claude/skills/`, `.agents/skills/`, `.mcp.json`, `.codex/config.toml`
and the block below are written by `../atlas/scripts/sync-agents.py` at session start or by
`mise run agents-sync` — edit the source. Details: `../atlas/agents/README.md`.

<!-- atlas:shared:begin -->

<!-- Duplicated from the atlas checkout root AGENTS.md by atlas/scripts/sync-agents.py for clients that stop at this repo's git root (Codex, Grok). Edit the atlas copy. -->

# Code comments: decision significance only

Write a comment only when it states a decision or constraint the code
cannot show — the why behind a non-obvious choice, with the ticket, spec,
or ADR reference when one exists. Never write comments that:

- describe the current state of the world elsewhere ("the chart ignores
  this value for now", "X hasn't landed yet") — they go stale silently
  the moment that other thing changes;
- retell the spec, plan, or PR narrative — reference the ticket instead;
- explain what the next line does.

That context belongs in the commit message, PR body, or ticket. This
policy overrides matching the comment density of the surrounding file:
a legacy heavy-comment file does not license new narrative comments.

# Ticket workflow: claim before you code

When starting implementation of a Linear ticket — via /implement, /tdd, or
no skill at all — first claim it:

1. Move the ticket to **In Progress**.
2. Assign it to the developer running the session (`linear-server`
   `get_user` with query "me").

If the ticket is already In Progress and assigned to someone else, stop
and confirm with the user before touching it — it may be claimed by a
parallel session, and double-resolving a claimed ticket has burned us
before.

This applies only to work tracked as a Linear ticket; untracked work and
repo-local trackers with their own conventions are unaffected. Claiming is
the only transition this rule owns — later states (review, done) belong to
the PR flow.

# Ways of working (Speckle stack)

When the user starts describing a feature, refactor, bug, or plan, suggest
the matching entry point instead of diving into implementation: `/wayfinder`
for big/foggy multi-session work, `/grill-me` (or `/grill-with-docs`) to
stress-test one plan, `/prototype` when "how should it look/behave" is open,
then `/to-spec` → `/to-tickets` → `/implement` (which calls `/code-review`).
The full loop: `atlas/ways-of-working.md` in the speckle-atlas checkout root
(`../atlas/ways-of-working.md` from this repo in the standard nested layout)
— read it before shaping non-trivial work.

Specs: cross-repo → the atlas repo's `atlas/specs/`; local to this repo →
this repo's `specs/` folder. Same structure everywhere: `YYYY-MM-title.md`,
a linked Linear project, worked via PR. Check both places when picking up
spec work.

ADR linking is two-way (atlas ADR-0003 + its amendment): a repo-local ADR
born from a cross-repo project back-links the owning atlas spec in its
header and is indexed from that spec; and when a stack-level ADR — standing
(`atlas/adr/`) or a spec's — governs a specific module of this repo, that
module carries a **pointer ADR** in its local ADR home. A pointer is a thin
stub, never a fork of the atlas content: it keeps the atlas ADR's number and
title, names the atlas text as canonical, links it and its spec by relative
path (never GitHub URLs), summarizes the decision and what it binds in this
module, and is registered in the module's docs index and the repo's context
map. The pointer lands with the work that makes the decision bind the
module. If a pointer's atlas links don't resolve, this checkout is missing
the atlas layer — ask the user to set up the speckle-atlas checkout above
this repo before acting on that decision.

Shared skills, MCP definitions, and conventions change **in the speckle-atlas
repo via PR** — never by editing synced outputs (`.agents/skills`,
`.claude/skills`, `.mcp.json`, `.codex/config.toml`, this block) or forking a
local copy in this repo. A repo-local skill with a shared skill's name fails
the sync (ADR-0008); there is no override.

<!-- atlas:shared:end -->
