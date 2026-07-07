#pragma once

// duckdb.dll is delay-loaded (/DELAYLOAD). Windows resolves plugin dependencies
// against Archicad.exe's folder, not the .apx folder, so it must be loaded by
// full path from the add-on's own directory before the FIRST duckdb call on
// ANY code path (send's BundleWriter and receive's ArtifactReceiver both hit
// DuckDB). Without this the delay-load helper raises a structured exception
// (not a C++ exception) and takes Archicad down.
namespace DuckDbRuntime
{
    void EnsureLoaded();
}
