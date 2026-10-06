# Component tests

## Ingestion lifecycle

`IngestionProgressTests` runs the production uploader and heartbeat against
fake HTTP responses and a process window that rejects worker-thread calls.
It checks silent-operation heartbeats, worker shutdown before complete,
matching publication identity, server stops, and cancellation as detach
after handoff. It requires a C++20 compiler and CMake, without an Archicad
installation or SDK runtime.

Run from the repository root with the Visual Studio generator used by the
add-on build:

```powershell
cmake -S tests -B build/ingestion-tests -G "Visual Studio 18 2026" -A x64 -T v143
cmake --build build/ingestion-tests --config Release --target IngestionProgressTests
ctest --test-dir build/ingestion-tests -C Release -R '^IngestionProgress$' --output-on-failure
```

The separate runtime script compiles the production `ArtifactUploader` and
`WinHttpClient`, then starts a Python standard-library HTTP server on
loopback. It requires Visual Studio C++ tools with the developer shell and
Python 3 on PATH. Run it in PowerShell 7 (`pwsh`). No third-party Python packages are needed. The script
records compile, server and runtime logs under `.audit/runtime-fixed-*`.

```powershell
./scripts/test_ingestion_runtime.ps1
./scripts/test_ingestion_runtime.ps1 -ProductionWindow
```

The default run uses short timing fixtures. `-ProductionWindow` adds a
650-second silent operation against a 600-second server idle timeout,
using the production 30-second heartbeat interval and default completion
polling. These runs exercise actual WinHTTP components. They do not open
Archicad or publish to a live Speckle server. A send from Archicad still
verifies the native process window and DUI result handling.

## Element type regression tests

The Windows test executable compiles the production converter against the
selected Archicad SDK. It supplies distinct MEP class IDs because the MEP
runtime requires an Archicad host. It checks every supported MEP class,
stable type names across SDK versions, unknown external classes, and all
non-MEP enum types.

Run from the repository root with CMake that supports your Visual Studio
installation. Use v142 for SDK 27/28 and v143 for SDK 29:

```powershell
cmake -S tests -B build_29/tests -G "Visual Studio 18 2026" -A x64 -T v143 -DARCHICAD_VERSION=29
cmake --build build_29/tests --config Debug
$env:PATH = 'C:/Program Files/Graphisoft/Archicad 29;' + $env:PATH
ctest --test-dir build_29/tests -C Debug --output-on-failure
```

The Archicad installation directory on PATH supplies `GSRoot.dll` and its
dependencies. If CMake selects a Visual Studio installation without the
required toolset, pass `-DCMAKE_GENERATOR_INSTANCE=<installation path>`.

These tests cover naming policy. Publishing `MEP Designer Sample File.pln`
and `objects.pln` in Archicad verifies the scene tree and host behavior.
