#include "SenderModelCard.h"

void from_json(const nlohmann::json& j, SenderModelCard& card)
{
    card.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    card.sendFilter = j.at("sendFilter").get<SendFilter>();
    card.modelId = j.at("modelId").get<std::string>();
    card.projectId = j.at("projectId").get<std::string>();
    card.accountId = j.at("accountId").get<std::string>();
    card.serverUrl = j.at("serverUrl").get<std::string>();
    card.expired = j.value("expired", false);
    card.modelCardId = j.at("modelCardId").get<std::string>();
    // Optional: cards created before the send-settings feature (persisted in the
    // Archicad document) and cards from UI flows that never opened the settings
    // panel have no "settings" key. Default = empty (sendProperties defaults true).
    if (j.contains("settings") && j["settings"].is_array())
    {
        card.settings = j["settings"].get<std::vector<SendSetting>>();
    }
    else
    {
        card.settings.clear();
    }
}
