#include "ArtifactUploader.h"
#include "WinHttpClient.h"
#include "json.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <thread>

#ifndef INGESTION_BASELINE
#include "IngestionCompleteUnconfirmedException.h"
#include "IngestionHeartbeat.h"
#include "IProcessWindow.h"
#endif

using nlohmann::json;
using namespace std::chrono_literals;

void Require(bool condition, const std::string& message)
{
    if (!condition) throw std::runtime_error(message);
}

json Inspect(WinHttpClient& http, const std::string& server, const IngestionInfo& info)
{
    const auto response = http.Get(server + "/control/" + info.ingestionId, "");
    Require(response.IsSuccess(), "fixture inspection failed");
    return json::parse(response.body);
}

#ifndef INGESTION_BASELINE
class CancelledWindow : public IProcessWindow
{
public:
    void Init(const std::string&, int) override {}
    void SetNextProcessPhase(const std::string&, int) override {}
    void SetProcessValue(int) override {}
    bool IsProcessCanceled() override { return true; }
    void Close() override {}
};

CompletionPolling FastPolling()
{
    CompletionPolling polling;
    polling.firstInterval = 20ms;
    polling.maxInterval = 40ms;
    polling.deadline = 600ms;
    polling.maxConsecutiveFailures = 3;
    return polling;
}

template<typename Action>
void RequireThrows(Action action, const std::string& message)
{
    bool threw = false;
    try { action(); }
    catch (const std::exception&) { threw = true; }
    Require(threw, message);
}

void RequireServerOwnership(const json& state)
{
    Require(state.at("complete").get<bool>(), "ingestion was not handed to server");
    Require(state.at("type") == "ModelIngestionProcessingStatus", "detached ingestion changed status");
    Require(state.at("failMutations") == 0, "client failed a server-owned ingestion");
    Require(state.at("cancelMutations") == 0, "client cancelled a server-owned ingestion");
    Require(!state.at("versionExists").get<bool>(), "detached ingestion unexpectedly has a version");
}

void RunFixed(const std::string& server, const std::string& artifact)
{
    auto http = std::make_shared<WinHttpClient>(1);
    ArtifactUploader uploader(http, server, "loopback-test-token", "runtime-project");
    const auto create = [&](const std::string& scenario) {
        return uploader.CreateIngestion(scenario, "Converting", "archicad", "29");
    };
    const auto upload = [&](const IngestionInfo& info, IngestionHeartbeat* heartbeat = nullptr) {
        return uploader.UploadFiles(info.ingestionId, info.versionId,
            {{"runtime.parquet", artifact}}, "binary-" + info.versionId, 1, nullptr, heartbeat);
    };

    const auto live = create("publish");
    IngestionHeartbeat heartbeat([&](const std::string& message) {
        uploader.UpdateProgress(live.ingestionId, message);
    }, "Converting", 100ms);
    std::this_thread::sleep_for(1100ms);
    const auto alive = Inspect(*http, server, live);
    Require(alive.at("type") == "ModelIngestionProcessingStatus", "heartbeat did not keep conversion active");
    Require(alive.at("updates").get<int>() >= 3, "real progress requests did not reach server");
    Require(upload(live, &heartbeat) == live.versionId, "upload did not return reserved version");
    const auto handedOff = Inspect(*http, server, live);
    RequireServerOwnership(handedOff);
    Require(handedOff.at("uploadedBytes") == 4096, "real WinHTTP PUT bytes differed");
    std::this_thread::sleep_for(250ms);
    const auto stopped = Inspect(*http, server, live);
    Require(stopped.at("updates") == handedOff.at("updates"), "heartbeat continued after complete");
    Require(uploader.WaitForCompletion(live.ingestionId, live.versionId, nullptr, FastPolling()) == IngestionOutcome::Published,
        "exact Success did not publish");
    const auto published = Inspect(*http, server, live);
    Require(published.at("versionExists").get<bool>(), "Published returned before fixture version existed");
    Require(published.at("completionPolls") == 3, "Processing returned Published before exact Success");
    std::cout << "PASS heartbeat preserved no-callback conversion across 650ms idle window; stopped before complete; Published followed exact Success; real PUT=4096 bytes\n";

    for (const std::string scenario : {"complete-malformed", "complete-mismatch"})
    {
        const auto info = create(scenario);
        Require(upload(info) == info.versionId, "successful complete did not hand off on " + scenario);
        RequireServerOwnership(Inspect(*http, server, info));
        Require(uploader.WaitForCompletion(info.ingestionId, info.versionId, nullptr, FastPolling()) == IngestionOutcome::Published,
            "authoritative status did not publish after " + scenario);
        const auto state = Inspect(*http, server, info);
        Require(state.at("versionExists").get<bool>(), "published version did not exist after " + scenario);
        Require(state.at("failMutations") == 0 && state.at("cancelMutations") == 0,
            "successful complete response caused failure mutation");
        std::cout << "PASS HTTP 2xx " << scenario << " retained server ownership and exact Success published\n";
    }

    const auto lost = create("complete-lost");
    bool unconfirmed = false;
    try { upload(lost); }
    catch (const IngestionCompleteUnconfirmedException&) { unconfirmed = true; }
    Require(unconfirmed, "dropped complete response did not report unconfirmed handoff");
    const auto accepted = Inspect(*http, server, lost);
    RequireServerOwnership(accepted);
    Require(accepted.at("completeAcceptances") == 1, "complete retry accepted ingestion more than once");
    Require(accepted.at("completeRequests").get<int>() >= 1, "complete request did not reach fixture");
    Require(uploader.WaitForCompletion(lost.ingestionId, lost.versionId, nullptr, FastPolling()) == IngestionOutcome::Published,
        "lost complete response prevented authoritative publication");
    const auto confirmed = Inspect(*http, server, lost);
    Require(confirmed.at("type") == "ModelIngestionSuccessStatus" && confirmed.at("versionExists").get<bool>(),
        "unconfirmed complete returned Published before exact Success");
    Require(confirmed.at("completionPolls") == 3, "unconfirmed complete skipped Processing observations");
    Require(confirmed.at("failMutations") == 0 && confirmed.at("cancelMutations") == 0,
        "client changed ingestion after accepted complete response was lost");
    std::cout << "PASS accepted complete with dropped response preserved server ownership; complete requests="
        << confirmed.at("completeRequests") << "; exact Success published without fail/cancel mutations\n";

    const auto retry = create("retry");
    upload(retry);
    Require(uploader.WaitForCompletion(retry.ingestionId, retry.versionId, nullptr, FastPolling()) == IngestionOutcome::Published,
        "transient polling failures prevented publication");
    Require(Inspect(*http, server, retry).at("completionPolls") == 6, "retry sequence did not reach authoritative Success");
    std::cout << "PASS polling recovered from two failures, Processing, two failures, then Success\n";

    for (const std::string scenario : {"mismatch", "failed", "cancelled", "invalid", "unknown"})
    {
        const auto info = create(scenario);
        upload(info);
        RequireThrows([&] { uploader.WaitForCompletion(info.ingestionId, info.versionId, nullptr, FastPolling()); },
            "completion should reject " + scenario);
        const auto state = Inspect(*http, server, info);
        Require(state.at("completionPolls") == 1, "terminal result was retried instead of rejected");
        Require(state.at("failMutations") == 0 && state.at("cancelMutations") == 0,
            "terminal observation changed server-owned ingestion");
        std::cout << "PASS completion rejected " << scenario << " without writing ingestion\n";
    }

    const auto cancel = create("deadline");
    upload(cancel);
    CancelledWindow window;
    Require(uploader.WaitForCompletion(cancel.ingestionId, cancel.versionId, &window, FastPolling()) == IngestionOutcome::StillProcessing,
        "cancelled wait did not detach");
    RequireServerOwnership(Inspect(*http, server, cancel));
    std::cout << "PASS cancelled wait returned StillProcessing and left server ingestion Processing\n";

    const auto pending = create("deadline");
    upload(pending);
    auto deadlinePolling = FastPolling();
    deadlinePolling.deadline = 180ms;
    const auto start = std::chrono::steady_clock::now();
    Require(uploader.WaitForCompletion(pending.ingestionId, pending.versionId, nullptr, deadlinePolling) == IngestionOutcome::StillProcessing,
        "deadline did not return StillProcessing");
    Require(std::chrono::steady_clock::now() - start < 1500ms, "deadline wait was unbounded");
    RequireServerOwnership(Inspect(*http, server, pending));
    std::cout << "PASS 180ms polling deadline detached without changing ingestion\n";

    const auto budget = create("failure-budget");
    upload(budget);
    Require(uploader.WaitForCompletion(budget.ingestionId, budget.versionId, nullptr, FastPolling()) == IngestionOutcome::StillProcessing,
        "poll failure budget did not detach");
    const auto budgetState = Inspect(*http, server, budget);
    RequireServerOwnership(budgetState);
    Require(budgetState.at("completionPolls") == 3, "configured consecutive failure budget was not respected");
    std::cout << "PASS three consecutive HTTP failures detached without changing ingestion\n";

    const auto transient = create("heartbeat-retry");
    IngestionHeartbeat retryHeartbeat([&](const std::string& message) {
        uploader.UpdateProgress(transient.ingestionId, message);
    }, "Converting", 100ms);
    std::this_thread::sleep_for(500ms);
    retryHeartbeat.Stop();
    retryHeartbeat.CheckCancellation();
    const auto retryState = Inspect(*http, server, transient);
    Require(retryState.at("type") == "ModelIngestionProcessingStatus", "progress retries lost the active ingestion");
    Require(retryState.at("updates").get<int>() >= 1, "heartbeat did not recover from two failed progress writes");
    std::cout << "PASS heartbeat recovered from two HTTP 503 progress writes and preserved Processing\n";

    for (const std::string type : {"ModelIngestionFailedStatus", "ModelIngestionCancelledStatus", "ModelIngestionInvalidStatus"})
    {
        const auto info = create("stopped");
        const auto response = http->PostJson(server + "/control/" + info.ingestionId,
            json({{"type", type}}).dump(), "");
        Require(response.IsSuccess(), "fixture setup failed");
        RequireThrows([&] { uploader.UpdateProgress(info.ingestionId, "Converting"); }, "progress revived terminal ingestion");
        const auto state = Inspect(*http, server, info);
        Require(state.at("type") == type && state.at("updates") == 0, "terminal ingestion was mutated by progress");
        std::cout << "PASS progress preserved terminal " << type << '\n';
    }

    const auto stalled = create("stalled");
    IngestionHeartbeat stalledHeartbeat([&](const std::string& message) {
        uploader.UpdateProgress(stalled.ingestionId, message);
    }, "Converting", 50ms);
    const auto waitUntil = std::chrono::steady_clock::now() + 1000ms;
    while (!Inspect(*http, server, stalled).value("stalledReceived", false))
    {
        Require(std::chrono::steady_clock::now() < waitUntil, "heartbeat request did not reach stalled endpoint");
        std::this_thread::sleep_for(10ms);
    }
    const auto stopStart = std::chrono::steady_clock::now();
    stalledHeartbeat.Stop();
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - stopStart).count();
    Require(elapsed < 6500, "heartbeat shutdown exceeded receive-phase timeout allowance: " + std::to_string(elapsed) + "ms");
    Require(!Inspect(*http, server, stalled).value("stalledResponded", false), "heartbeat Stop waited for 12s fixture response");
    std::cout << "PASS stalled HTTP receive heartbeat Stop elapsed=" << elapsed << "ms with WinHttpClient(1); receive-phase bound, not whole-request deadline\n";
    std::cout << "Fixed runtime component integration passed (no live Archicad/S-Life claim).\n";
}

void RunProductionWindow(const std::string& server, const std::string& artifact)
{
    auto uploadHttp = std::make_shared<WinHttpClient>();
    auto controlHttp = std::make_shared<WinHttpClient>(10);
    ArtifactUploader uploader(uploadHttp, server, "loopback-test-token", "runtime-project");
    ArtifactUploader control(controlHttp, server, "loopback-test-token", "runtime-project");
    const auto info = uploader.CreateIngestion("production-heartbeat", "Converting", "archicad", "29");
    IngestionHeartbeat heartbeat([&](const std::string& message) {
        control.UpdateProgress(info.ingestionId, message);
    }, "Converting without native callbacks");
    const auto start = std::chrono::steady_clock::now();
    for (int checkpoint = 1; checkpoint <= 13; ++checkpoint)
    {
        std::this_thread::sleep_until(start + std::chrono::seconds(checkpoint * 50));
        heartbeat.CheckCancellation();
        const auto state = Inspect(*controlHttp, server, info);
        Require(state.at("type") == "ModelIngestionProcessingStatus", "production idle window expired despite heartbeat");
        std::cout << "ACTIVE elapsed=" << checkpoint * 50 << "s updates=" << state.at("updates")
            << "; production heartbeat interval and 600s idle window" << std::endl;
    }
    Require(uploader.UploadFiles(info.ingestionId, info.versionId, {{"runtime.parquet", artifact}},
        "binary-" + info.versionId, 1, nullptr, &heartbeat) == info.versionId, "production upload did not hand off");
    const auto handedOff = Inspect(*controlHttp, server, info);
    RequireServerOwnership(handedOff);
    Require(control.WaitForCompletion(info.ingestionId, info.versionId, nullptr) == IngestionOutcome::Published,
        "production completion policy did not confirm exact Success");
    const auto published = Inspect(*controlHttp, server, info);
    Require(published.at("versionExists").get<bool>(), "production Published returned without a version");
    Require(published.at("updates") == handedOff.at("updates"), "production heartbeat wrote after complete");
    Require(published.at("uploadedBytes") == 4096, "production upload payload differed");
    std::cout << "PASS production 30s heartbeat kept ingestion active through 650s without native callbacks; "
        "600s idle boundary crossed; heartbeat stopped at handoff; exact Success confirmed with default polling"
        << std::endl;
}
#endif

int main(int argc, char** argv)
{
    try
    {
        Require(argc == 3 || argc == 4, "usage: IngestionRuntimeTests serverUrl artifactPath [--production-window]");
        const std::string server = argv[1];
        const std::string artifact = argv[2];
        std::ofstream(artifact, std::ios::binary) << std::string(4096, 'a');
#ifdef INGESTION_BASELINE
        auto http = std::make_shared<WinHttpClient>();
        ArtifactUploader uploader(http, server, "loopback-test-token", "runtime-project");
        const auto idle = uploader.CreateIngestion("idle", "Converting", "archicad", "29");
        std::this_thread::sleep_for(1100ms);
        const auto idleState = Inspect(*http, server, idle);
        Require(idleState.at("type") == "ModelIngestionFailedStatus", "baseline did not reproduce idle timeout");
        Require(idleState.at("updates") == 0, "baseline unexpectedly sent heartbeat updates");
        std::cout << "REPRODUCED: no-callback conversion exceeded 650ms idle window; ingestion Failed; updates=0\n";
        const auto early = uploader.CreateIngestion("deadline", "Uploading", "archicad", "29");
        const auto returned = uploader.UploadFiles(early.ingestionId, early.versionId,
            {{"runtime.parquet", artifact}}, "binary-" + early.versionId, 1);
        const auto state = Inspect(*http, server, early);
        Require(returned == early.versionId, "baseline did not return reserved ID");
        Require(state.at("type") == "ModelIngestionProcessingStatus", "fixture was not Processing at return");
        Require(!state.at("versionExists").get<bool>(), "fixture version unexpectedly exists");
        Require(state.at("uploadedBytes") == 4096, "real HTTP PUT payload was not received");
        std::cout << "REPRODUCED: UploadFiles returned reserved ID while ingestion Processing; versionExists=false; real PUT bytes=4096\n";
        std::cout << "Baseline runtime component integration reproduced both defects (no live Archicad/S-Life claim).\n";
#else
        if (argc == 4)
        {
            Require(std::string(argv[3]) == "--production-window", "unknown runtime test option");
            RunProductionWindow(server, artifact);
        }
        else
            RunFixed(server, artifact);
#endif
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
