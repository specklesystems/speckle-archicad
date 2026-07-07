#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IHttpClient.h"
#include "IProcessWindow.h"
#include "ReceiveConversionResult.h"

// The Speckle 4.0 native artefact receive pipeline for Archicad — replaces the
// C# desktop service AND the receive-via-browser fallback:
//
//   1. GET /api/v2/.../versions/{v}/artifacts  → presigned parquet downloads
//      (only the files receive needs: geometries + envelope nodes/relations +
//      eav objects; the server-built viewer.dat is skipped).
//   2. Read the bundle with the embedded DuckDB (read_parquet): objects,
//      DISPLAY/DEFINES/HAS_MATERIAL/DISPLAY_INSTANCE/DEFINES_INSTANCE
//      relations, INSTANCE + MATERIAL nodes, SGEO geometry blobs.
//   3. Per object: decode SGEO meshes, scale to meters, bake instance
//      transforms (DEFINES geometry × DISPLAY_INSTANCE placement, nested
//      DEFINES_INSTANCE composed, world coords) — geometry and materials only,
//      exactly the scope of the old desktop-service path.
//   4. Write one GDL <Symbol> XML per object into Batch_NNN folders and run
//      LP_XMLConverter `x2l` on the folders in parallel (up to 8 processes),
//      collecting .gsm files into {root}\_output.
//
// No ACAPI calls in here — the caller (ReceiveBridge) deletes the previous
// bake, registers/places the produced GSMs via LibpartPlacer, and reports.
class ArtifactReceiver
{
public:
    struct Result
    {
        std::string rootDir;   // %APPDATA%\Speckle\Archicad\receive_temp\{rand16} — caller cleans up
        std::string gsmFolder; // rootDir\_output — feed to LibpartPlacer::RegisterLibpartsBatched
        std::vector<ReceiveConversionResult> conversionResults;
        int objectCount = 0;   // objects written to XML
    };

    ArtifactReceiver(
        std::shared_ptr<IHttpClient> http,
        const std::string& serverUrl,
        const std::string& token);

    // The version to receive: the card's selectedVersionId, or the model's
    // latest version (GraphQL) when the card has none pinned.
    std::string ResolveVersionId(
        const std::string& projectId,
        const std::string& modelId,
        const std::string& selectedVersionId);

    // Runs steps 1–4. Throws on fatal errors (no bundle, download failure,
    // converter missing); per-object conversion failures land in
    // Result::conversionResults instead. Honours processWindow cancellation
    // (throws UserCancelledException).
    Result Receive(
        const std::string& projectId,
        const std::string& modelId,
        const std::string& versionId,
        const std::string& xmlConverterPath,
        IProcessWindow& processWindow);

private:
    std::shared_ptr<IHttpClient> _http;
    std::string _serverUrl; // no trailing slash
    std::string _token;
};
