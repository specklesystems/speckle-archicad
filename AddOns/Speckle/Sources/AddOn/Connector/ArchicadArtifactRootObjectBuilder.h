#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "SendConversionResult.h"

struct NativeSendResult
{
    std::string versionId;
    int objectCount = 0;
};

// The Speckle 4.0 artefact send path for Archicad — the C++ analogue of the
// connectors-repo IArtifactRootObjectBuilder implementations (Rhino/Revit on
// branch big-truck). Walks the selected elements ONCE via the existing
// HostToSpeckle converters and emits the flat bundle directly:
//
//   element GUID          -> interned object + EAV properties (+ name/type/level root scalars)
//   display meshes        -> SGEO blobs with DETERMINISTIC ids "{guid}:{i}" + DISPLAY edges
//   modeler material idx  -> MATERIAL node + HAS_MATERIAL (geometry -> node)
//   story                 -> LEVEL node + ON_LEVEL
//   beam/column segments  -> child objects + SUBELEMENT edges
//   default scene view    -> [Rel(ON_LEVEL), Eav("type")]  (Story -> Element type)
//
// The parquet bundle lands in %TEMP%\Speckle\artifacts\{versionId}\ and is
// uploaded sign -> presigned PUT -> complete (complete creates the version).
// Everything runs synchronously on the ACAPI main thread: minipq and WinHTTP
// are synchronous APIs, so the C# worker-thread requirement (sync-over-async
// parquet IO) does not apply here.
class ArchicadArtifactRootObjectBuilder
{
public:
    NativeSendResult BuildAndUpload(
        const std::vector<std::string>& elementIds,
        bool includeProperties,
        const std::string& serverUrl,
        const std::string& token,
        const std::string& projectId,
        const std::string& modelId,
        std::vector<SendConversionResult>& conversionResults);
};
