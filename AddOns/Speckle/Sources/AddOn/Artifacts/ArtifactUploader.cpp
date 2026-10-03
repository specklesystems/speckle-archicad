#include "ArtifactUploader.h"

#include <algorithm>
#include <chrono>
#include <thread>
#include "IngestionHeartbeat.h"
#include <cstdint>
#include <filesystem>
#include <stdexcept>

#include "json.hpp"

#include "IProcessWindow.h"
#include "UserCancelledException.h"
#include "Utf8Path.h"

using nlohmann::json;

namespace
{
    std::string TrimTrailingSlash(const std::string& url)
    {
        std::string result = url;
        while (!result.empty() && result.back() == '/')
            result.pop_back();
        return result;
    }

    // The ModelIngestion GraphQL selection shared by every mutation we call.
    constexpr const char* INGESTION_FIELDS = "id modelId projectId versionId cancellationRequested";
}

ArtifactUploader::ArtifactUploader(
    std::shared_ptr<IHttpClient> http,
    const std::string& serverUrl,
    const std::string& token,
    const std::string& projectId)
    : _http(std::move(http)), _serverUrl(TrimTrailingSlash(serverUrl)), _token(token), _projectId(projectId)
{
}

std::string ArtifactUploader::GraphQl(const std::string& query, const std::string& variablesJson)
{
    json body;
    body["query"] = query;
    body["variables"] = json::parse(variablesJson);

    HttpResponse response = _http->PostJson(_serverUrl + "/graphql", body.dump(), _token);
    if (!response.IsSuccess())
        throw std::runtime_error("GraphQL request failed with HTTP " + std::to_string(response.statusCode) + ": " + response.body);

    json parsed = json::parse(response.body);
    if (parsed.contains("errors") && !parsed["errors"].empty())
        throw std::runtime_error("GraphQL error: " + parsed["errors"].dump());
    return parsed["data"].dump();
}

IngestionInfo ArtifactUploader::CreateIngestion(
    const std::string& modelId,
    const std::string& progressMessage,
    const std::string& sourceApplicationSlug,
    const std::string& sourceApplicationVersion)
{
    // Mirrors Speckle.Sdk ModelIngestionResource.Create (mutation IngestionCreate).
    const std::string query =
        std::string("mutation IngestionCreate($input: ModelIngestionCreateInput!) { "
                    "data: projectMutations { data: modelIngestionMutations { data: create(input: $input) { ") +
        INGESTION_FIELDS + " } } } }";

    json input;
    input["modelId"] = modelId;
    input["projectId"] = _projectId;
    input["progressMessage"] = progressMessage;
    input["sourceData"] = {
        { "sourceApplicationSlug", sourceApplicationSlug },
        { "sourceApplicationVersion", sourceApplicationVersion },
        { "fileName", nullptr },
        { "fileSizeBytes", nullptr },
    };
    input["maxIdleTimeoutSeconds"] = 600;

    json variables;
    variables["input"] = input;

    json data = json::parse(GraphQl(query, variables.dump()));
    json ingestion = data["data"]["data"]["data"];

    IngestionInfo info;
    info.ingestionId = ingestion.value("id", "");
    if (ingestion.contains("versionId") && ingestion["versionId"].is_string())
        info.versionId = ingestion["versionId"].get<std::string>();
    if (info.ingestionId.empty())
        throw std::runtime_error("Ingestion create returned no id");
    return info;
}

std::string ArtifactUploader::UploadFiles(
    const std::string& ingestionId,
    const std::string& versionId,
    const std::map<std::string, std::string>& files,
    const std::string& rootId,
    int totalChildrenCount,
    IProcessWindow* processWindow,
    IngestionHeartbeat* heartbeat)
{
    const std::string base = _serverUrl + "/api/v2/projects/" + _projectId + "/modelingestion/" + ingestionId;

    // Total upload size drives the "Uploading" progress bar. KiB units keep the
    // per-phase max inside Int32 (2^31 KiB = 2 TiB) with ~1MB-chunk resolution.
    std::int64_t totalBytes = 0;
    for (const auto& kv : files)
    {
        std::error_code ec;
        const auto size = std::filesystem::file_size(Utf8Path::FromUtf8(kv.second), ec);
        if (!ec)
            totalBytes += static_cast<std::int64_t>(size);
    }
    if (processWindow)
        processWindow->SetNextProcessPhase(
            "Uploading", static_cast<int>(std::max<std::int64_t>(1, totalBytes / 1024)));

    // 1. sign: the server presigns one PUT per artefact basename under versions/{versionId}/
    json signRequest;
    signRequest["files"] = json::array();
    for (const auto& kv : files)
        signRequest["files"].push_back(kv.first);

    HttpResponse signResponse = _http->PostJson(base + "/uploads/sign", signRequest.dump(), _token);
    if (!signResponse.IsSuccess())
        throw std::runtime_error("artifacts sign failed with HTTP " + std::to_string(signResponse.statusCode) + ": " + signResponse.body);

    json signed_ = json::parse(signResponse.body);
    if (!signed_.contains("uploads"))
        throw std::runtime_error("artifacts sign returned no uploads: " + signResponse.body);

    // 2. presigned PUT per file, collecting ETags
    json etags = json::object();
    std::int64_t uploadedBytes = 0; // completed files
    for (const auto& kv : files)
    {
        if (!signed_["uploads"].contains(kv.first))
            throw std::runtime_error("Server did not sign an upload for file '" + kv.first + "'");

        const json& presigned = signed_["uploads"][kv.first];
        const std::string url = presigned["url"].get<std::string>();

        std::map<std::string, std::string> extraHeaders;
        if (presigned.contains("additionalRequestHeaders") && presigned["additionalRequestHeaders"].is_object())
        {
            for (auto it = presigned["additionalRequestHeaders"].begin(); it != presigned["additionalRequestHeaders"].end(); ++it)
                extraHeaders[it.key()] = it.value().get<std::string>();
        }

        // Continuous progress + cancellation from inside the streamed PUT
        // (called after every ~1MB chunk).
        UploadProgress progress;
        if (processWindow)
        {
            progress = [&](std::int64_t fileBytesSent)
            {
                processWindow->SetProcessValue(static_cast<int>((uploadedBytes + fileBytesSent) / 1024));
                if (processWindow->IsProcessCanceled())
                    throw UserCancelledException("The user cancelled the send operation");
            };
        }

        HttpResponse putResponse = _http->PutFile(url, kv.second, extraHeaders, progress);
        if (!putResponse.IsSuccess())
            throw std::runtime_error("Presigned PUT of '" + kv.first + "' failed with HTTP " + std::to_string(putResponse.statusCode));

        std::error_code ec;
        const auto size = std::filesystem::file_size(Utf8Path::FromUtf8(kv.second), ec);
        if (!ec)
            uploadedBytes += static_cast<std::int64_t>(size);

        auto etagIt = putResponse.headers.find("etag");
        if (etagIt == putResponse.headers.end())
            throw std::runtime_error("Presigned PUT of '" + kv.first + "' returned no ETag header");
        etags[kv.first] = etagIt->second;
    }

    // 3. complete: verifies the etags and creates the version (commit PK = the pre-allocated versionId)
    if (processWindow)
        processWindow->SetNextProcessPhase("Creating version", 1);

    if (heartbeat)
    {
        heartbeat->Stop();
        heartbeat->CheckCancellation();
    }

    json completeRequest;
    completeRequest["etags"] = etags;
    completeRequest["rootId"] = rootId;
    completeRequest["totalChildrenCount"] = totalChildrenCount;

    HttpResponse completeResponse = _http->PostJson(base + "/uploads/complete", completeRequest.dump(), _token);
    if (!completeResponse.IsSuccess())
        throw std::runtime_error("artifacts complete failed with HTTP " + std::to_string(completeResponse.statusCode) + ": " + completeResponse.body);

    // The pre-allocated id is authoritative; if the server echoes one it must match.
    if (!completeResponse.body.empty())
    {
        json completed = json::parse(completeResponse.body, nullptr, false);
        if (!completed.is_discarded() && completed.contains("versionId") && completed["versionId"].is_string())
        {
            const std::string echoed = completed["versionId"].get<std::string>();
            if (!echoed.empty() && echoed != versionId)
                throw std::runtime_error("Server completed version '" + echoed + "' but the pre-allocated id was '" + versionId + "'");
        }
    }
    WaitForCompletion(ingestionId, versionId, processWindow);
    return versionId;
}

void ArtifactUploader::WaitForCompletion(const std::string& ingestionId, const std::string& versionId,
    IProcessWindow* processWindow)
{
    const std::string query =
        "query IngestionStatus($projectId: String!, $ingestionId: ID!) { project(id: $projectId) { "
        "ingestion(id: $ingestionId) { id statusData { __typename "
        "... on ModelIngestionSuccessStatus { versionId } "
        "... on ModelIngestionFailedStatus { errorReason } "
        "... on ModelIngestionInvalidStatus { validationMessage } "
        "... on ModelIngestionCancelledStatus { cancellationMessage } } } } }";
    const json variables = { { "projectId", _projectId }, { "ingestionId", ingestionId } };
    while (true)
    {
        if (processWindow && processWindow->IsProcessCanceled())
            throw UserCancelledException("The user cancelled the send operation");
        const auto data = json::parse(GraphQl(query, variables.dump()));
        const auto& ingestion = data.at("project").at("ingestion");
        if (ingestion.at("id").get<std::string>() != ingestionId)
            throw std::runtime_error("Server returned a different ingestion");
        const auto& status = ingestion.at("statusData");
        const auto type = status.at("__typename").get<std::string>();
        if (type == "ModelIngestionSuccessStatus")
        {
            if (status.at("versionId").get<std::string>() != versionId)
                throw std::runtime_error("Server published a different version");
            return;
        }
        if (type == "ModelIngestionCancelledStatus")
            throw UserCancelledException(status.at("cancellationMessage").get<std::string>());
        if (type == "ModelIngestionFailedStatus")
            throw std::runtime_error(status.at("errorReason").get<std::string>());
        if (type == "ModelIngestionInvalidStatus")
            throw std::runtime_error(status.at("validationMessage").get<std::string>());
        if (type != "ModelIngestionQueuedStatus" && type != "ModelIngestionProcessingStatus")
            throw std::runtime_error("Server returned an unknown ingestion status");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void ArtifactUploader::UpdateProgress(const std::string& ingestionId, const std::string& progressMessage)
{
    const std::string query =
        "mutation IngestionProgress($input: ModelIngestionUpdateInput!) { "
        "data: projectMutations { data: modelIngestionMutations { "
        "data: updateProgress(input: $input) { id cancellationRequested } } } }";
    json variables;
    variables["input"] = {
        { "ingestionId", ingestionId },
        { "projectId", _projectId },
        { "progressMessage", progressMessage },
    };
    json data = json::parse(GraphQl(query, variables.dump()));
    const auto& ingestion = data["data"]["data"]["data"];
    if (ingestion.at("id").get<std::string>() != ingestionId)
        throw std::runtime_error("Server updated a different ingestion");
    if (ingestion.at("cancellationRequested").get<bool>())
        throw UserCancelledException("The server requested cancellation of the send operation");
}

void ArtifactUploader::FailWithError(const std::string& ingestionId, const std::string& errorReason)
{
    const std::string query =
        std::string("mutation IngestionFail($input: ModelIngestionFailedInput!) { "
                    "data: projectMutations { data: modelIngestionMutations { data: failWithError(input: $input) { ") +
        INGESTION_FIELDS + " } } } }";

    json variables;
    variables["input"] = {
        { "ingestionId", ingestionId },
        { "projectId", _projectId },
        { "errorReason", errorReason },
        { "errorStacktrace", nullptr },
    };
    try
    {
        GraphQl(query, variables.dump());
    }
    catch (...)
    {
        // Best-effort: failing the ingestion must never mask the original error.
    }
}

void ArtifactUploader::FailWithCancel(const std::string& ingestionId, const std::string& cancellationMessage)
{
    const std::string query =
        std::string("mutation IngestionCancel($input: ModelIngestionCancelledInput!) { "
                    "data: projectMutations { data: modelIngestionMutations { data: failWithCancel(input: $input) { ") +
        INGESTION_FIELDS + " } } } }";

    json variables;
    variables["input"] = {
        { "ingestionId", ingestionId },
        { "projectId", _projectId },
        { "cancellationMessage", cancellationMessage },
    };
    try
    {
        GraphQl(query, variables.dump());
    }
    catch (...)
    {
        // Best-effort.
    }
}
