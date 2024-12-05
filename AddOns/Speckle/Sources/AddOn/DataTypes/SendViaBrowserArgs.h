#pragma once

#include <string>
#include "json.hpp"

struct SendViaBrowserArgs
{
    std::string modelCardId;
    std::string projectId;
    std::string modelId;
    std::string token;
    std::string serverUrl;
    std::string accountId;
    //std::string message;
    //nlohmann::json sendObject;
    //nlohmann::json sendConversionResults;
    int totalBatch;
    int currentBatch;
    std::string referencedObjectId;
    std::string batch;
};

void to_json(nlohmann::json& j, const SendViaBrowserArgs& c);
void from_json(const nlohmann::json& j, SendViaBrowserArgs& card);
