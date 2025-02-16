#pragma once

#include "SendFilter.h"

struct ReceiverModelCard
{
    std::string projectName;
    std::string modelName;
    std::string typeDiscriminator;
    std::string modelId;
    std::string projectId;
    std::string accountId;
    std::string serverUrl;
    bool expired;
    std::string modelCardId;
    std::string selectedVersionId;
    std::vector<std::string> bakedObjectIds;
};

void to_json(nlohmann::json& j, const ReceiverModelCard& c);
void from_json(const nlohmann::json& j, ReceiverModelCard& card);
