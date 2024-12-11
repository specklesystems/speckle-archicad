#pragma once

#include <string>
#include "json.hpp"

struct AfterSendObjectsArgs
{
    std::string modelCardId;
    std::string projectId;
    std::string modelId;
    std::string token;
    std::string serverUrl;
    std::string accountId;
    std::string message;
    nlohmann::json sendConversionResults;
    std::string referencedObjectId;

};

void to_json(nlohmann::json& j, const AfterSendObjectsArgs& args);
void from_json(const nlohmann::json& j, AfterSendObjectsArgs& args);

