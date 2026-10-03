#include "IngestionProgressWindow.h"
#include "ArtifactUploader.h"
#include "UserCancelledException.h"
#include "json.hpp"

#include <iostream>
#include <stdexcept>

struct Window : IProcessWindow
{
    int value = 0;
    bool cancelled = false;
    void Init(const std::string&, int) override {}
    void SetNextProcessPhase(const std::string&, int) override {}
    void SetProcessValue(int v) override { value = v; }
    bool IsProcessCanceled() override { return cancelled; }
    void Close() override {}
};

void Require(bool value, const char* message)
{
    if (!value) throw std::runtime_error(message);
}

struct Http : IHttpClient
{
    IngestionProgressWindow::Clock::time_point* now;
    IngestionProgressWindow::Clock::time_point updatedAt{};
    int updates = 0;
    int statusCode = 200;
    bool cancelled = false;
    bool wrongId = false;
    bool graphqlError = false;

    HttpResponse PostJson(const std::string& url, const std::string& body, const std::string& token) override
    {
        Require(url == "https://example.invalid/graphql", "Unexpected progress endpoint");
        Require(token == "test-token", "Missing bearer token");
        const auto request = nlohmann::json::parse(body);
        const auto& input = request.at("variables").at("input");
        Require(input.at("ingestionId") == "test-ingestion", "Wrong ingestion target");
        Require(input.at("projectId") == "test-project", "Wrong project target");
        Require(!input.at("progressMessage").get<std::string>().empty(), "Missing message");
        Require(request.at("query").get<std::string>().find("updateProgress(input: $input)") != std::string::npos,
            "Wrong progress mutation");
        ++updates;
        updatedAt = *now;
        if (graphqlError) return {200, R"({"errors":[{"message":"Test error"}]})", {}};
        nlohmann::json response;
        response["data"]["data"]["data"]["data"] = {
            {"id", wrongId ? "different-ingestion" : "test-ingestion"}, {"cancellationRequested", cancelled}};
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
    throw std::runtime_error("Expected progress failure was swallowed");
}

int main()
{
    using Clock = IngestionProgressWindow::Clock;
    auto now = Clock::time_point{};
    auto http = std::make_shared<Http>();
    http->now = &now;
    ArtifactUploader uploader(http, "https://example.invalid/", "test-token", "test-project");
    Window window;
    IngestionProgressWindow progress(window, [&](const std::string& phase)
    {
        Require(!phase.empty(), "Server progress message is missing");
        uploader.UpdateProgress("test-ingestion", phase);
    }, [&] { return now; });
    progress.SetNextProcessPhase("Converting elements", 1800);
    for (int second = 1; second <= 1800; ++second)
    {
        now += std::chrono::seconds(1);
        progress.SetProcessValue(second);
        Require(now - http->updatedAt < std::chrono::seconds(600),
            "FAIL: advancing native conversion exceeded the server's 600-second idle limit");
    }
    Require(window.value == 1800, "Native progress was not forwarded");
    Require(http->updates == 60, "Server updates must be throttled");
    progress.SetNextProcessPhase("Uploading", 1800);
    for (int second = 1; second <= 1800; ++second)
    {
        now += std::chrono::seconds(1);
        progress.SetProcessValue(second);
        Require(now - http->updatedAt < std::chrono::seconds(600), "Upload progress went idle");
    }
    Require(http->updates == 120, "Upload updates must be throttled");
    window.cancelled = true;
    now += std::chrono::seconds(30);
    progress.SetProcessValue(1800);
    Require(http->updates == 120, "Cancelled native progress must not keep an ingestion alive");
    Require(progress.IsProcessCanceled(), "Native cancellation was lost");
    window.cancelled = false;
    http->cancelled = true;
    bool serverCancel = false;
    try { uploader.UpdateProgress("test-ingestion", "Converting"); }
    catch (const UserCancelledException&) { serverCancel = true; }
    Require(serverCancel, "Server cancellation was not propagated");
    http->cancelled = false;
    http->statusCode = 503;
    RequireThrows([&] { uploader.UpdateProgress("test-ingestion", "Converting"); });
    http->statusCode = 200;
    http->graphqlError = true;
    RequireThrows([&] { uploader.UpdateProgress("test-ingestion", "Converting"); });
    http->graphqlError = false;
    http->wrongId = true;
    RequireThrows([&] { uploader.UpdateProgress("test-ingestion", "Converting"); });
    std::cout << "PASS: 30-minute advancing native conversion stays alive, throttled updates and cancellation preserved\n";
}
