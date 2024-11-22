#pragma once

#include "SendFilter.h"
#include "SendModelCard.h"

class IModelCardDatabase 
{
public:
    virtual ~IModelCardDatabase() = default;

    virtual std::vector<SendModelCard> GetModels() const = 0;
    virtual SendModelCard GetModelCard(const std::string& modelCardId) const = 0;
    virtual void AddModel(const SendModelCard& modelCard) = 0;
    virtual void UpdateModel(const SendModelCard& modelCard) = 0;
    virtual void RemoveModel(const std::string& modelCardId) = 0;
};
