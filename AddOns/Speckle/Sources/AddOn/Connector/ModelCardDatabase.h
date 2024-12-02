#pragma once

#include "IModelCardDatabase.h"
#include <map>

class ModelCardDatabase : public IModelCardDatabase
{
public:
    ModelCardDatabase() = default;

    void LoadModelsFromJson(const nlohmann::json j) override;
    nlohmann::json GetModelsAsJson() override;

    std::vector<SendModelCard> GetModels() const override;
    SendModelCard GetModelCard(const std::string& modelCardId) const override;
    void AddModel(const SendModelCard& modelCard) override;
    void UpdateModel(const SendModelCard& modelCard) override;
    void RemoveModel(const std::string& modelCardId) override;
    void ClearModels() override;

private:
    std::map<std::string, SendModelCard> modelCards;
};
