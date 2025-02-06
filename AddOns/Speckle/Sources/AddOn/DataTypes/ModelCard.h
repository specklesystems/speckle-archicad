#pragma once

#include "SendFilter.h"
#include "SenderModelCard.h"
#include "ReceiverModelCard.h"

struct ModelCard
{
    std::string typeDiscriminator;
    std::string modelCardId;
    nlohmann::json data;

    bool IsSenderModelCard();
    bool IsReceiverModelCard();
    SenderModelCard AsSenderModelCard();
    ReceiverModelCard AsReceiverModelCard();

};

void to_json(nlohmann::json& j, const ModelCard& c);
void from_json(const nlohmann::json& j, ModelCard& card);
