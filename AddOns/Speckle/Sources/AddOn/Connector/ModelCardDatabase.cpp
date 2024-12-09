#include "ModelCardDatabase.h"

const static std::string MODELCARD_ADDONOBJECT_NAME = "SpeckleModelCardAddOnObjectName_v123";

ModelCardDatabase::ModelCardDatabase(std::unique_ptr<IDataStorage> storage)
    : dataStorage(std::move(storage)) {}


void ModelCardDatabase::LoadModelsFromJson(const nlohmann::json j)
{
    ClearModels();

    if (j.empty() || !j.contains("models"))
        return;

    for (const SendModelCard& modelCard : j["models"])
        modelCards[modelCard.modelCardId] = modelCard;
}

nlohmann::json ModelCardDatabase::GetModelsAsJson()
{
    nlohmann::json j;
    j["models"] = GetModels();
    return j;
}

void ModelCardDatabase::StoreModels()
{
    if (!dataStorage)
        throw std::runtime_error("DataStorage not initialized");

    dataStorage->SaveData(GetModelsAsJson(), MODELCARD_ADDONOBJECT_NAME);
}

void ModelCardDatabase::LoadModelsFromStorage()
{
    if (!dataStorage)
        throw std::runtime_error("DataStorage not initialized");

    auto data = dataStorage->LoadData(MODELCARD_ADDONOBJECT_NAME);
    LoadModelsFromJson(data);
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
    //StoreModels();
}

void ModelCardDatabase::UpdateModel(const SendModelCard& modelCard)
{
    modelCards[modelCard.modelCardId] = modelCard;
    //StoreModels();
}

void ModelCardDatabase::RemoveModel(const std::string& modelCardId)
{
    modelCards.erase(modelCardId);
    //StoreModels();
}

void ModelCardDatabase::ClearModels()
{
    modelCards.clear();
}
