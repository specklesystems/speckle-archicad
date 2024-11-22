#include "SendModelCard.h"

void to_json(nlohmann::json& j, const SendModelCard& card)
{
    j["typeDiscriminator"] = card.typeDiscriminator;
    j["sendFilter"] = nlohmann::json(card.sendFilter);
    j["modelId"] = card.modelId;
    j["projectId"] = card.projectId;
    j["accountId"] = card.accountId;
    j["serverUrl"] = card.serverUrl;
    j["expired"] = card.expired;
    j["modelCardId"] = card.modelCardId;
}

void from_json(const nlohmann::json& j, SendModelCard& card)
{
    card.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    card.sendFilter = j.at("sendFilter").get<SendFilter>();
    card.modelId = j.at("modelId").get<std::string>();
    card.projectId = j.at("projectId").get<std::string>();
    card.accountId = j.at("accountId").get<std::string>();
    card.serverUrl = j.at("serverUrl").get<std::string>();
    card.expired = j.at("expired").get<bool>();
    card.modelCardId = j.at("modelCardId").get<std::string>();
}
