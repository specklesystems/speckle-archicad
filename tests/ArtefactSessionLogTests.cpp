#include "ArtefactSessionLog.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace
{
    std::string ReadAll(const fs::path& path)
    {
        std::ifstream stream(path, std::ios::binary);
        std::ostringstream contents;
        contents << stream.rdbuf();
        return contents.str();
    }

    void Require(bool condition, const std::string& message)
    {
        if (!condition)
            throw std::runtime_error(message);
    }
}

int main()
{
    const std::string versionId =
        "session-log-test-" + std::to_string(
            std::chrono::steady_clock::now().time_since_epoch().count());
    std::string basePath;
    nlohmann::json payload;
    payload["modelCardId"] = "card-a";
    payload["versionId"] = versionId;
    payload["sendConversionResults"] = nlohmann::json::array({ {
        { "status", 1 },
        { "sourceId", "WALL-A" },
        { "sourceType", "Wall" },
        { "resultId", "" },
        { "resultType", "ArchicadObject" },
        { "error", { { "message", "" }, { "stackTrace", "" } } },
    } });

    {
        ArtefactSessionLog session("Archicad", "project-a", versionId);
        basePath = session.GetBasePath();
        session.RecordObject("WALL-A", "Wall", "SUCCESS", "", 1.25);
        session.SetStat("files", 13);
    }
    ArtefactSessionLog::WriteSetModelSendResult(basePath, payload);
    ArtefactSessionLog::WriteSetModelSendResult("", payload);

    const fs::path ndjson = basePath + ".ndjson";
    const fs::path summary = basePath + ".summary.txt";
    const fs::path sendResult = basePath + ".set-model-send-result.json";
    const std::vector<fs::path> matching = { ndjson, summary, sendResult };

    try
    {
        Require(fs::is_regular_file(ndjson), "NDJSON session log was not written");
        Require(fs::is_regular_file(summary), "session summary was not written");
        Require(fs::is_regular_file(sendResult), "setModelSendResult JSON was not written");
        Require(ReadAll(sendResult) == payload.dump() + "\n", "setModelSendResult bytes changed");
        Require(nlohmann::json::parse(ReadAll(sendResult)) == payload, "persisted payload changed semantically");
    }
    catch (...)
    {
        for (const auto& path : matching)
            fs::remove(path);
        throw;
    }

    for (const auto& path : matching)
        fs::remove(path);
    std::cout << "ArtefactSessionLog tests passed\n";
    return 0;
}
