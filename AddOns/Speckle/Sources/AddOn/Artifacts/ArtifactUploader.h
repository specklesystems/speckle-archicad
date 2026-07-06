#pragma once

#include <map>
#include <memory>
#include <string>

#include "IHttpClient.h"

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
        const std::string& sourceApplicationVersion);

    // sign -> PUT each file (collecting ETags) -> complete. files maps basename -> local path.
    // rootId is the synthetic "binary-{versionId}". Returns the (authoritative) versionId.
    std::string UploadFiles(
        const std::string& ingestionId,
        const std::string& versionId,
        const std::map<std::string, std::string>& files,
        const std::string& rootId,
        int totalChildrenCount);

    void FailWithError(const std::string& ingestionId, const std::string& errorReason);
    void FailWithCancel(const std::string& ingestionId, const std::string& cancellationMessage);

private:
    std::string GraphQl(const std::string& query, const std::string& variablesJson);

    std::shared_ptr<IHttpClient> _http;
    std::string _serverUrl; // no trailing slash
    std::string _token;
    std::string _projectId;
};
