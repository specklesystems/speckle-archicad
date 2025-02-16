#include "ReceiverModelCard.h"

void to_json(nlohmann::json& j, const ReceiverModelCard& card)
{
    j["projectName"] = card.projectName;
    j["modelName"] = card.modelName;
    j["typeDiscriminator"] = card.typeDiscriminator;
    j["modelId"] = card.modelId;
    j["projectId"] = card.projectId;
    j["accountId"] = card.accountId;
    j["serverUrl"] = card.serverUrl;
    j["expired"] = card.expired;
    j["modelCardId"] = card.modelCardId;
    j["selectedVersionId"] = card.selectedVersionId;
    j["bakedObjectIds"] = card.bakedObjectIds;
}

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
    if (j.contains("bakedObjecIds")) 
    {
        card.bakedObjectIds = j.at("bakedObjectIds").get<std::vector<std::string>>();
    }
}
