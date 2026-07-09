#include "ReceiverModelCard.h"

void from_json(const nlohmann::json& j, ReceiverModelCard& card)
{
    card.projectName = j.at("projectName").get<std::string>();
    card.modelName = j.at("modelName").get<std::string>();
    card.typeDiscriminator = j.at("typeDiscriminator").get<std::string>();
    card.modelId = j.at("modelId").get<std::string>();
    card.projectId = j.at("projectId").get<std::string>();
    card.accountId = j.at("accountId").get<std::string>();
    card.serverUrl = j.at("serverUrl").get<std::string>();
    card.expired = j.at("expired").get<bool>();
    card.modelCardId = j.at("modelCardId").get<std::string>();
    card.selectedVersionId = j.at("selectedVersionId").get<std::string>();
    if (j.contains("bakedObjectIds")) 
    {
        card.bakedObjectIds = j.at("bakedObjectIds").get<std::vector<std::string>>();
    }
}
