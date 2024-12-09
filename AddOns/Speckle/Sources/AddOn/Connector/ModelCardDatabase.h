#pragma once

#include "IModelCardDatabase.h"
#include "IDataStorage.h"
#include <map>

class ModelCardDatabase : public IModelCardDatabase
{
public:
    ModelCardDatabase(std::unique_ptr<IDataStorage> storage);

    nlohmann::json GetModelsAsJson() override;
    void LoadModelsFromJson(const nlohmann::json j) override;
    void StoreModels() override;
    void LoadModelsFromStorage() override;

    std::vector<SendModelCard> GetModels() const override;
    SendModelCard GetModelCard(const std::string& modelCardId) const override;
    void AddModel(const SendModelCard& modelCard) override;
    void UpdateModel(const SendModelCard& modelCard) override;
    void RemoveModel(const std::string& modelCardId) override;
    void ClearModels() override;

private:
    std::unique_ptr<IDataStorage> dataStorage;
    std::map<std::string, SendModelCard> modelCards;
};
