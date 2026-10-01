# Element type regression tests

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
