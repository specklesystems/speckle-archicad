# Speckle for Archicad

[![Twitter Follow](https://img.shields.io/twitter/follow/SpeckleSystems?style=social)](https://twitter.com/SpeckleSystems) [![Community forum users](https://img.shields.io/discourse/users?server=https%3A%2F%2Fdiscourse.speckle.works&style=flat-square&logo=discourse&logoColor=white)](https://discourse.speckle.works) [![website](https://img.shields.io/badge/https://-speckle.systems-royalblue?style=flat-square)](https://speckle.systems) [![docs](https://img.shields.io/badge/docs-speckle.guide-orange?style=flat-square&logo=read-the-docs&logoColor=white)](https://speckle.guide/dev/)

This repository contains Speckle's native C++ connector for Archicad 27, 28, and 29. It embeds Speckle's web UI in an Archicad palette and converts model geometry and metadata through the Archicad C++ API.

The connector builds on Windows and macOS. macOS builds are universal (`arm64` and `x86_64`) by default and support macOS 12.6 or newer.

## Developing & Debugging

### Build on macOS

Requirements:

- Xcode command-line tools
- CMake 3.16 or newer
- Python 3
- `curl` and `unzip` (included with macOS)

Build a release bundle for the installed Archicad major version:

```bash
./build.sh 27 Release
# or: ./build.sh 28 Release
# or: ./build.sh 29 Release
```

The script downloads the matching official Graphisoft macOS DevKit and official universal DuckDB binary on first use. DevKits are cached under `.cache/archicad-devkits`; CMake caches DuckDB in the build tree. The output is:

```text
build/mac/<version>/INT/<configuration>/Speckle.bundle
```

Useful overrides:

```bash
# Use an already downloaded macOS DevKit (the directory containing Support/)
AC_API_DEVKIT_DIR=/path/to/devkit ./build.sh 27 Debug

# Faster local Apple Silicon-only build
SPECKLE_MAC_ARCHITECTURES=arm64 ./build.sh 27 Debug

# Use an already downloaded DuckDB directory containing libduckdb.dylib
SPECKLE_DUCKDB_ROOT=/path/to/duckdb ./build.sh 27 Release

# Sign with an Apple Developer ID instead of the default ad-hoc signature
SPECKLE_CODESIGN_IDENTITY="Developer ID Application: Example Corp (TEAMID)" ./build.sh 27 Release
```

The build embeds `libduckdb.dylib` in the bundle and signs the finished bundle. Distribution outside local development still requires an appropriate Developer ID signature and Apple notarization.

### Build on Windows

Requirements are CMake 3.16 or newer, Python 3, the .NET SDK, and Visual Studio 2022 with the v142 and v143 C++ toolsets.

- Run `generate_project_27.bat`, `generate_project_28.bat`, or `generate_project_29.bat` for a local Visual Studio solution.
- Run `build.ps1` for the full CI-style release build.
- Toolset v142 is used for Archicad 27/28 and v143 for Archicad 29.

### Installation

1. Open **Options → Add-On Manager** in the matching Archicad version.
2. Add `Speckle.bundle` on macOS or `Speckle.apx` on Windows.
3. Restart Archicad if it was already running when the add-on was copied or rebuilt.

For local macOS development you can instead copy the bundle to:

```text
/Applications/Graphisoft/Archicad <version>/Add-Ons/Speckle/Speckle.bundle
```

### Debugging

- On macOS, attach Xcode or LLDB to the matching running Archicad process after installing a Debug bundle.
- On Windows, set `SpeckleAddOn` as the Visual Studio startup project and use **Local Windows Debugger**.

For Archicad API help, see [Getting started with Archicad Add-Ons](https://archicadapi.graphisoft.com/getting-started-with-archicad-add-ons) and [ARCHICAD_API_RESOURCES.md](ARCHICAD_API_RESOURCES.md).

## Contributing

Please make sure you read the [contribution guidelines](.github/CONTRIBUTING.md) and [code of conduct](.github/CODE_OF_CONDUCT.md) for an overview of the practices we try to follow.

## Community

The Speckle Community hangs out on [the forum](https://discourse.speckle.works), do join and introduce yourself & feel free to ask us questions!

## Security

For any security vulnerabilities or concerns, please contact us directly at security[at]speckle.systems.

## License

Unless otherwise described, the code in this repository is licensed under the Apache-2.0 License. Please note that some modules, extensions or code herein might be otherwise licensed. This is indicated either in the root of the containing folder under a different license file, or in the respective file's header. If you have any questions, don't hesitate to get in touch with us via [email](mailto:hello@speckle.systems).
