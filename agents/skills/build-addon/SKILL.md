---
name: build-addon
description: Build the Archicad add-on (.apx) — single-version Debug via the generate_project_NN.bat + Visual Studio/msbuild route, or the CI-style all-versions Release build through build.ps1. Use for any compile, link, or toolchain question.
---

# Building the add-on

Two routes. Both need CMake ≥ 3.16, Visual Studio 2026 with the **v142 and v143** toolsets, the
.NET SDK (build orchestrator) and Python (Archicad resource-compilation tools). The Archicad API
DevKit comes from `AC_API_DEVKIT_DIR`; the vendored ones are `Libs/acapi27`, `Libs/acapi28`,
`Libs/acapi29`. `CMakeLists.txt` reads the major version out of the DevKit's `ACAPinc.h` and
defines `AC27`/`AC28`/`AC29` — version-specific code branches on those macros.

## Local development: one version, Debug

```
generate_project_27.bat   # or _28 / _29 → build_27/ (build_28/, build_29/)
```

The generator is `cmake -G "Visual Studio 18 2026"` with `-T v142` for 27/28 and `-T v143` for 29
(see the `.bat` files), so it emits **`build_27/archicad-speckle.slnx`** — the `.slnx` solution
format, not `.sln`. Open it in Visual Studio 2026 and build, or debug with Archicad as the startup
project (README § Debugging — the README still describes the older VS 2019/2022 + `.sln` setup).

Headless from a developer shell:

```
msbuild build_29\archicad-speckle.slnx /p:Configuration=Debug /p:Platform=x64 /m
```

MSB8020 means the required toolset is not in that VS install — switch to one that has it.

## CI-style: all versions, Release, zipped installers

```
./build.ps1              # Windows — what pr.yml and release.yml run
```

`build.ps1` runs the Bullseye target runner in `ci-build/Program.cs` (`ci-build/Build.csproj`).
Targets: `clean`, `restore-tools`, `build-cmake`, `build`, `zip`, and `default` (= `zip` → `build`
→ `build-cmake`); `clean` and `restore-tools` are standalone. This path configures into
`build/<version>/` (not `build_<version>/`) and packages `build/<version>/INT/Release/*.apx` into
`output/archicad.zip`.

The `build` target reads `SEMVER` / `FILE_VERSION` from the environment (fallback
`0.0.0-localBuild` / `0.0.0.9999`), substitutes `SEMVER` for the `connector_build_num` placeholder
in `AddOnResources/RINT/AddOn.grc`, and passes both to msbuild. **Running it locally rewrites the
tracked `AddOn.grc` in place** — `git checkout` it afterwards.

## Gotchas

- `build.sh` runs `dotnet run --project Build/Build.csproj`, which does not exist; the active
  project is `ci-build/`. `build.sh` is dead — use `build.ps1`.
- `ci-build/Consts.cs` has a `Solutions` array with stale paths (`build_27/speckle-archicad.slnx`)
  that nothing references; the real msbuild invocation is in `Program.cs`.
- There is no C++ unit-test suite: `enable_testing()` is set in CMake but no tests are registered.
  `Connector/Bridges/TestBridge.cpp` (`SayHi`, `GetComplexType`, `TriggerEvent`) exercises the
  JS↔C++ bridge round-trip from the UI; it is not a test runner.
