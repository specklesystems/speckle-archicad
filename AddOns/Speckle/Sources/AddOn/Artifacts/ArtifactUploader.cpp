#include "ArtifactUploader.h"

#include <stdexcept>

#include "json.hpp"

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
    int totalChildrenCount)
{
    const std::string base = _serverUrl + "/api/v2/projects/" + _projectId + "/modelingestion/" + ingestionId;

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

        HttpResponse putResponse = _http->PutFile(url, kv.second, extraHeaders);
        if (!putResponse.IsSuccess())
            throw std::runtime_error("Presigned PUT of '" + kv.first + "' failed with HTTP " + std::to_string(putResponse.statusCode));

        auto etagIt = putResponse.headers.find("etag");
        if (etagIt == putResponse.headers.end())
            throw std::runtime_error("Presigned PUT of '" + kv.first + "' returned no ETag header");
        etags[kv.first] = etagIt->second;
    }

    // 3. complete: verifies the etags and creates the version (commit PK = the pre-allocated versionId)
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
    return versionId;
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
