#pragma once

#include "IModelCardDatabase.h"
#include <map>

class ModelCardDatabase : public IModelCardDatabase
{
public:
    ModelCardDatabase();

    std::vector<SendModelCard> GetModels() const override;
    std::map<std::string, SendModelCard> GetModelsMap() const;
    SendModelCard GetModelCard(const std::string& modelCardId) const override;
    void AddModel(const SendModelCard& modelCard) override;
    void UpdateModel(const SendModelCard& modelCard) override;
    void RemoveModel(const std::string& modelCardId) override;

private:
    void InitData();
    std::map<std::string, SendModelCard> modelCards;
};
