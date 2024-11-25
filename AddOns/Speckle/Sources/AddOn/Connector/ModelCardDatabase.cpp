#include "ModelCardDatabase.h"


void ModelCardDatabase::LoadModelsFromJson(const nlohmann::json j)
{
    if (!j.empty() && j.contains("models"))
    {
        for (const auto& model : j["models"])
            AddModel(nlohmann::json(model));
    }
    else
    {
        // TODO
    }
}

nlohmann::json ModelCardDatabase::GetModelsAsJson()
{
    nlohmann::json j;
    j["models"] = GetModels();
    return j;
}

std::vector<SendModelCard> ModelCardDatabase::GetModels() const
{
    std::vector<SendModelCard> cards;
    for (const auto& [id, card] : modelCards)
        cards.push_back(card);

    return cards;
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
        return {};
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
