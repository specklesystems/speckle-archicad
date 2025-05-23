#pragma once

#include "SendFilter.h"
#include "SendSetting.h"

struct SenderModelCard
{
    std::string typeDiscriminator;
    SendFilter sendFilter;
    std::string modelId;
    std::string projectId;
    std::string accountId;
    std::string serverUrl;
    bool expired;
    std::string modelCardId;
    std::vector<SendSetting> settings;
};

void to_json(nlohmann::json& j, const SenderModelCard& c);
void from_json(const nlohmann::json& j, SenderModelCard& card);
