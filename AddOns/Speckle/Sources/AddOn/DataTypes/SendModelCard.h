#pragma once

#include "SendFilter.h"

struct SendModelCard
{
    std::string typeDiscriminator;
    SendFilter sendFilter;
    std::string modelId;
    std::string projectId;
    std::string accountId;
    std::string serverUrl;
    bool expired;
    std::string modelCardId;
};

void to_json(nlohmann::json& j, const SendModelCard& c);
void from_json(const nlohmann::json& j, SendModelCard& card);
