#include "IngestionProgressWindow.h"
#include "ArtifactUploader.h"
#include "IngestionStoppedByServerException.h"
#include "UserCancelledException.h"
#include "json.hpp"

#include <atomic>
#include <future>
#include <iostream>
#include <stdexcept>
#include <vector>

using nlohmann::json;

void Require(bool value, const char* message)
{
    if (!value) throw std::runtime_error(message);
}

struct Window : IProcessWindow
{
    std::thread::id owner = std::this_thread::get_id();
    int value = 0;
    bool cancelled = false;
    void Check() { Require(std::this_thread::get_id() == owner, "Native UI called from worker thread"); }
    void Init(const std::string&, int) override { Check(); }
    void SetNextProcessPhase(const std::string&, int) override { Check(); }
    void SetProcessValue(int v) override { Check(); value = v; }
    bool IsProcessCanceled() override { Check(); return cancelled; }
    void Close() override { Check(); }
};

struct Http : IHttpClient
{
    std::atomic<int> updates{0};
    std::atomic<int> statusCode{200};
    std::atomic<bool> cancelled{false};
    std::atomic<bool> wrongId{false};
    std::atomic<bool> graphqlError{false};
    std::vector<json> states;
    size_t reads = 0;
    int checks = 0;
    int pollFailures = 0;
    json heartbeatState = {{"id", "test-ingestion"}, {"cancellationRequested", false},
        {"statusData", {{"__typename", "ModelIngestionProcessingStatus"}}}};
    bool completed = false;
    int updatesAtComplete = 0;

    HttpResponse PostJson(const std::string& url, const std::string& body, const std::string& token) override
    {
        Require(token == "test-token", "Missing bearer token");
        if (url.ends_with("/uploads/sign")) return {200, R"({"uploads":{}})", {}};
        if (url.ends_with("/uploads/complete"))
        {
            completed = true;
            updatesAtComplete = updates;
            return {202, R"({"versionId":"test-version"})", {}};
        }
        Require(url == "https://example.invalid/graphql", "Unexpected progress endpoint");
        const auto request = json::parse(body);
        if (request.at("query").get<std::string>().find("IngestionStatus") != std::string::npos)
        {
            const auto& variables = request.at("variables");
            Require(variables.at("ingestionId") == "test-ingestion", "Wrong ingestion query");
            json response;
            if (!completed)
            {
                ++checks;
                response["data"]["project"]["ingestion"] = heartbeatState;
                return {200, response.dump(), {}};
            }
            Require(updates == updatesAtComplete, "Client heartbeat continued after server handoff");
            if (pollFailures > 0) { --pollFailures; return {503, "Service Unavailable", {}}; }
            Require(reads < states.size(), "Unexpected extra server poll");
            response["data"]["project"]["ingestion"] = {
                {"id", "test-ingestion"}, {"cancellationRequested", false}, {"statusData", states[reads++]}};
            return {200, response.dump(), {}};
        }
        const auto& input = request.at("variables").at("input");
        Require(input.at("ingestionId") == "test-ingestion", "Wrong ingestion target");
        Require(input.at("projectId") == "test-project", "Wrong project target");
        Require(!input.at("progressMessage").get<std::string>().empty(), "Missing message");
        Require(request.at("query").get<std::string>().find("updateProgress(input: $input)") != std::string::npos,
            "Wrong progress mutation");
        ++updates;
        if (graphqlError) return {200, R"({"errors":[{"message":"Test error"}]})", {}};
        json response;
        response["data"]["data"]["data"]["data"] = {
            {"id", wrongId ? "different-ingestion" : "test-ingestion"}, {"cancellationRequested", bool(cancelled)}};
        return {statusCode, response.dump(), {}};
    }
    HttpResponse PutFile(const std::string&, const std::string&, const std::map<std::string,std::string>&,
        const UploadProgress&) override { throw std::runtime_error("Unexpected PUT"); }
    HttpResponse Get(const std::string&, const std::string&) override { throw std::runtime_error("Unexpected GET"); }
    HttpResponse GetToFile(const std::string&, const std::string&, const std::string&) override
        { throw std::runtime_error("Unexpected download"); }
};

void RequireThrows(const std::function<void()>& call)
{
    try { call(); } catch (const std::exception&) { return; }
    throw std::runtime_error("Expected failure was swallowed");
}

std::string RequireServerStop(const std::function<void()>& call)
{
    try { call(); }
    catch (const IngestionStoppedByServerException& e) { return e.what(); }
    catch (const UserCancelledException&) { throw std::runtime_error("Server stop reported as a user cancel"); }
    throw std::runtime_error("Server stop was swallowed");
}

int main()
{
    const CompletionPolling fast{std::chrono::milliseconds(1), std::chrono::milliseconds(4),
        std::chrono::milliseconds(200), 3};
    auto http = std::make_shared<Http>();
    ArtifactUploader uploader(http, "https://example.invalid/", "test-token", "test-project");
    Window window;
    std::promise<void> reported;
    auto ready = reported.get_future();
    IngestionHeartbeat heartbeat([&](const std::string& message)
    {
        uploader.UpdateProgress("test-ingestion", message);
        if (http->updates == 5) reported.set_value();
    }, "Converting elements", std::chrono::milliseconds(10));
    IngestionProgressWindow progress(window, heartbeat);
    progress.SetNextProcessPhase("Converting elements", 1);
    // No native callbacks until this single long operation ends.
    Require(ready.wait_for(std::chrono::seconds(2)) == std::future_status::ready,
        "Long native operation went idle between progress callbacks");
    Require(window.value == 0, "Heartbeat unexpectedly touched native progress");
    progress.SetProcessValue(1);
    window.cancelled = true;
    Require(progress.IsProcessCanceled(), "Native cancellation was lost");
    window.cancelled = false;
    http->states = {{{"__typename", "ModelIngestionProcessingStatus"}},
        {{"__typename", "ModelIngestionSuccessStatus"}, {"versionId", "test-version"}}};
    Require(uploader.UploadFiles("test-ingestion", "test-version", {}, "root", 0, &progress, &heartbeat)
        == "test-version", "Wrong published version");
    Require(http->reads == 0, "UploadFiles polled the server it just handed the ingestion to");
    Require(uploader.WaitForCompletion("test-ingestion", "test-version", &window, fast) == IngestionOutcome::Published,
        "Server success was not reported as published");
    Require(http->reads == 2, "Returned preallocated version before server success");
    const int stoppedAt = http->updates;
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    Require(http->updates == stoppedAt, "Heartbeat survived server handoff");

    for (const auto& state : std::vector<json>{
        {{"__typename", "ModelIngestionFailedStatus"}, {"errorReason", "Test timeout"}},
        {{"__typename", "ModelIngestionInvalidStatus"}, {"validationMessage", "Invalid"}},
        {{"__typename", "ModelIngestionCancelledStatus"}, {"cancellationMessage", nullptr}}})
    {
        http->states = {state}; http->reads = 0;
        RequireServerStop([&] { uploader.WaitForCompletion("test-ingestion", "test-version", nullptr, fast); });
    }
    http->states = {{{"__typename", "ModelIngestionSuccessStatus"}, {"versionId", "wrong-version"}}};
    http->reads = 0;
    RequireThrows([&] { uploader.WaitForCompletion("test-ingestion", "test-version", nullptr, fast); });

    const json processing = {{"__typename", "ModelIngestionProcessingStatus"}};
    const json success = {{"__typename", "ModelIngestionSuccessStatus"}, {"versionId", "test-version"}};
    http->states = {processing, success}; http->reads = 0; http->pollFailures = 2;
    Require(uploader.WaitForCompletion("test-ingestion", "test-version", nullptr, fast) == IngestionOutcome::Published,
        "A transient poll failure ended the wait");
    http->states = {success}; http->reads = 0; http->pollFailures = 3;
    Require(uploader.WaitForCompletion("test-ingestion", "test-version", nullptr, fast)
        == IngestionOutcome::StillProcessing, "Persistent poll failures were not reported as unknown");
    Require(http->reads == 0, "Kept polling past the failure budget");
    http->pollFailures = 0;
    http->states = std::vector<json>(1000, processing); http->reads = 0;
    Require(uploader.WaitForCompletion("test-ingestion", "test-version", nullptr, fast)
        == IngestionOutcome::StillProcessing, "Wait ignored its deadline");
    Require(http->reads < 1000, "Wait ignored its deadline");
    http->states = {success}; http->reads = 0;
    window.cancelled = true;
    Require(uploader.WaitForCompletion("test-ingestion", "test-version", &window, fast)
        == IngestionOutcome::StillProcessing, "Cancel during the wait was not a detach");
    Require(http->reads == 0, "Polled after the user stopped waiting");
    window.cancelled = false;

    http->completed = false;
    http->cancelled = true;
    RequireServerStop([&] { uploader.UpdateProgress("test-ingestion", "Converting"); });
    http->cancelled = false;

    // The server's idle-timeout sweep: progress must not revive the ingestion or hide the reason.
    http->heartbeatState["cancellationRequested"] = true;
    http->heartbeatState["statusData"] = {{"__typename", "ModelIngestionFailedStatus"},
        {"errorReason", "The job failed due to handler being unresponsive for 600 seconds."}};
    int writes = http->updates;
    Require(RequireServerStop([&] { uploader.UpdateProgress("test-ingestion", "Converting"); })
        .find("unresponsive") != std::string::npos, "Server timeout reason was lost");
    Require(http->updates == writes, "Progress was written over a timed-out ingestion");
    // A cancellation requested from the web while the ingestion is still Processing.
    http->heartbeatState["statusData"] = {{"__typename", "ModelIngestionProcessingStatus"}};
    RequireServerStop([&] { uploader.UpdateProgress("test-ingestion", "Converting"); });
    Require(http->updates == writes, "Progress was written over a cancelled ingestion");
    http->heartbeatState["cancellationRequested"] = false;

    std::promise<void> stopped;
    auto stopReady = stopped.get_future();
    IngestionHeartbeat stopping([&](const std::string&)
    {
        stopped.set_value();
        throw IngestionStoppedByServerException("Stopped by server");
    }, "Converting elements", std::chrono::milliseconds(10));
    IngestionProgressWindow stoppingProgress(window, stopping);
    Require(stopReady.wait_for(std::chrono::seconds(2)) == std::future_status::ready, "Heartbeat never reported");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    RequireServerStop([&] { stoppingProgress.SetProcessValue(2); });
    stopping.Stop();
    http->statusCode = 503;
    RequireThrows([&] { uploader.UpdateProgress("test-ingestion", "Converting"); });
    http->statusCode = 200;
    http->graphqlError = true;
    RequireThrows([&] { uploader.UpdateProgress("test-ingestion", "Converting"); });
    http->graphqlError = false;
    http->wrongId = true;
    RequireThrows([&] { uploader.UpdateProgress("test-ingestion", "Converting"); });
    http->wrongId = false;
    std::promise<void> retried;
    auto retryReady = retried.get_future();
    int attempts = 0;
    IngestionHeartbeat retries([&](const std::string& message)
    {
        if (++attempts == 1) throw std::runtime_error("Transient transport failure");
        if (attempts == 2) { uploader.UpdateProgress("test-ingestion", message); retried.set_value(); }
    }, "Writing bundle", std::chrono::milliseconds(10));
    Require(retryReady.wait_for(std::chrono::seconds(2)) == std::future_status::ready,
        "Transient heartbeat failure stopped reporting");
    retries.Stop();
    std::cout << "PASS: heartbeat covers a single long native operation, stops at server handoff, retries transient errors, and waits for exact server success\n";
}
