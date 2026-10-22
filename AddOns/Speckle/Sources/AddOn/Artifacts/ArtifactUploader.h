#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include "IHttpClient.h"
#include "json.hpp"

class IProcessWindow;
class IngestionHeartbeat;

struct IngestionInfo
{
    std::string ingestionId;
    std::string versionId; // pre-allocated by the server; empty = server has no v2 data endpoints
};

enum class IngestionOutcome
{
    Published,
    StillProcessing,
};

struct CompletionPolling
{
    std::chrono::milliseconds firstInterval = std::chrono::seconds(1);
    std::chrono::milliseconds maxInterval = std::chrono::seconds(10);
    // ENG-10394: allow three 1800-second datgen attempts and pod scheduling.
    std::chrono::milliseconds deadline = std::chrono::minutes(100);
    int maxConsecutiveFailures = 5;
};

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
        IProcessWindow* processWindow = nullptr,
        IngestionHeartbeat* heartbeat = nullptr);

    // ENG-10394: the server owns the ingestion after complete, so stopping this wait must not cancel it.
    IngestionOutcome WaitForCompletion(const std::string& ingestionId, const std::string& versionId,
        IProcessWindow* processWindow, const CompletionPolling& polling = {});

    void UpdateProgress(const std::string& ingestionId, const std::string& progressMessage);

    void FailWithError(const std::string& ingestionId, const std::string& errorReason);
    void FailWithCancel(const std::string& ingestionId, const std::string& cancellationMessage);

private:
    nlohmann::json QueryIngestion(const std::string& ingestionId);
    std::string GraphQl(const std::string& query, const std::string& variablesJson);

    std::shared_ptr<IHttpClient> _http;
    std::string _serverUrl; // no trailing slash
    std::string _token;
    std::string _projectId;
};
