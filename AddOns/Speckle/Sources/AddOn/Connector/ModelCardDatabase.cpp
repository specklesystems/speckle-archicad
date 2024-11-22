#include "ModelCardDatabase.h"
#include "LoggerFactory.h"

ModelCardDatabase::ModelCardDatabase()
{
    InitData();
}

void ModelCardDatabase::InitData()
{
    auto modelsData = R"({"models":[
        {"typeDiscriminator":"SenderModelCard","sendFilter":{"typeDiscriminator":"ArchicadSelectionFilter","selectedObjectIds":["CC867F9B-1CE7-45ED-8F9A-DD067E6D0FB3","585EC9CE-A763-44FB-899A-17FBAB31CE30"],"name":"Selection","summary":"2 objects selected."},"modelId":"4914109801","projectId":"41a66a8a84","accountId":"56CEDA5BBD148EA03214D2E8A59B3EB8","serverUrl":"https:\/\/app.speckle.systems","settings":[],"expired":false,"modelCardId":"5b868cf89df45bdcf78b"},
        {"typeDiscriminator":"SenderModelCard","sendFilter":{"typeDiscriminator":"ArchicadSelectionFilter","selectedObjectIds":["4C0D259B-F659-4AF8-9DCE-FAADB5C68D8E","1A6ADCA1-B01F-49E7-AA26-62EA1F78D096"],"name":"Selection","summary":"2 objects selected."},"modelId":"7a90ebbec2","projectId":"41a66a8a84","accountId":"56CEDA5BBD148EA03214D2E8A59B3EB8","serverUrl":"https:\/\/app.speckle.systems","settings":[],"expired":false,"modelCardId":"e35af2f3ff8cee8254a6"},
        {"typeDiscriminator":"SenderModelCard","sendFilter":{"typeDiscriminator":"ArchicadSelectionFilter","selectedObjectIds":["B302E999-96A7-45A6-9033-594CDBB9C499"],"name":"Selection","summary":"1 objects selected."},"modelId":"2339ef9cd1","projectId":"41a66a8a84","accountId":"56CEDA5BBD148EA03214D2E8A59B3EB8","serverUrl":"https:\/\/app.speckle.systems","settings":[],"expired":false,"modelCardId":"f6cf26219e1c1b2620d2"},
        {"typeDiscriminator":"SenderModelCard","sendFilter":{"typeDiscriminator":"ArchicadSelectionFilter","selectedObjectIds":["4C0D259B-F659-4AF8-9DCE-FAADB5C68D8E","B302E999-96A7-45A6-9033-594CDBB9C499"],"name":"Selection","summary":"2 objects selected."},"modelId":"7133a374ec","projectId":"41a66a8a84","accountId":"56CEDA5BBD148EA03214D2E8A59B3EB8","serverUrl":"https:\/\/app.speckle.systems","settings":[],"expired":false,"modelCardId":"f64a806a51bcefcdd522"}
    ]})";

    try
    {
        auto jsonModels = nlohmann::json::parse(modelsData)["models"];
        for (const auto& model : jsonModels)
        {
            AddModel(nlohmann::json(model));
        }
    }
    catch (...)
    {
        // TODO
    }
}

std::vector<SendModelCard> ModelCardDatabase::GetModels() const
{
    std::vector<SendModelCard> cards;
    for (const auto& [id, card] : modelCards)
        cards.push_back(card);

    return cards;
}

std::map<std::string, SendModelCard> ModelCardDatabase::GetModelsMap() const
{
    return modelCards;
}

SendModelCard ModelCardDatabase::GetModelCard(const std::string& modelCardId) const
{
    try
    {
        return modelCards.at(modelCardId);
    }
    catch (...)
    {
        // TODO
        return SendModelCard{};
    }
}

void ModelCardDatabase::AddModel(const SendModelCard& modelCard)
{
    modelCards[modelCard.modelCardId] = modelCard;
}

void ModelCardDatabase::UpdateModel(const SendModelCard& modelCard)
{
    modelCards[modelCard.modelCardId] = modelCard;
}

void ModelCardDatabase::RemoveModel(const std::string& modelCardId)
{
    modelCards.erase(modelCardId);
}
