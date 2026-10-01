#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>

#include "IHttpClient.h"

class IProcessWindow;

struct IngestionInfo
{
    std::string ingestionId;
    std::string versionId; // pre-allocated by the server; empty = server has no v2 data endpoints
};

// The C++ mirror of the SDK's ArtifactPipeline + the ingestion bracket from
// SendOperation.SendViaArtifacts: create ingestion (GraphQL, which pre-allocates
// the versionId baked into the parquet filenames) -> sign -> presigned PUT per
// file -> complete (which creates the version). failWithError / failWithCancel
// close the ingestion on the failure paths.
class ArtifactUploader
{
public:
    ArtifactUploader(
        std::shared_ptr<IHttpClient> http,
        const std::string& serverUrl,
        const std::string& token,
        const std::string& projectId);

    // GraphQL IngestionCreate. Returns the ingestion id + the server-pre-allocated versionId.
    IngestionInfo CreateIngestion(
        const std::string& modelId,
        const std::string& progressMessage,
        const std::string& sourceApplicationSlug,
        const std::string& sourceApplicationVersion,
        const std::string& connectorVersion);

    // GraphQL IngestionUpdateProgress. Best-effort: a failed update never fails the send.
    // progress is a 0..1 fraction.
    void UpdateProgress(const std::string& ingestionId, const std::string& progressMessage, std::optional<double> progress);

    // sign -> PUT each file (collecting ETags) -> complete. files maps basename -> local path.
    // rootId is the synthetic "binary-{versionId}". Returns the (authoritative) versionId.
    // processWindow (optional) drives two phases: "Uploading" with continuous
    // KiB-level progress fed from inside the streamed PUTs (cancellable between
    // chunks — throws UserCancelledException), then "Creating version" while the
    // server-side complete call runs.
    std::string UploadFiles(
        const std::string& ingestionId,
        const std::string& versionId,
        const std::map<std::string, std::string>& files,
        const std::string& rootId,
        int totalChildrenCount,
        IProcessWindow* processWindow = nullptr);

    void FailWithError(const std::string& ingestionId, const std::string& errorReason);
    void FailWithCancel(const std::string& ingestionId, const std::string& cancellationMessage);

private:
    std::string GraphQl(const std::string& query, const std::string& variablesJson);
    void GraphQlBestEffort(const std::string& query, const std::string& variablesJson) noexcept;

    std::shared_ptr<IHttpClient> _http;
    std::string _serverUrl; // no trailing slash
    std::string _token;
    std::string _projectId;
};
