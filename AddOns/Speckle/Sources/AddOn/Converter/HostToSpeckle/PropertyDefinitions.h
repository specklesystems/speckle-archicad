#pragma once

#include "APIEnvir.h"
#include "ACAPinc.h"

#include <unordered_map>
#include <vector>
#include <string>

class PropertyDefinitions
{
public:
    static PropertyDefinitions& Instance();

    std::vector<std::string> GetDefinitionIds(API_ElemTypeID elemType) const;
    std::vector<API_PropertyDefinition> GetDefinitions(API_ElemTypeID elemType);

private:
    PropertyDefinitions() = default;
    ~PropertyDefinitions() = default;

    // Delete copy & move operations
    PropertyDefinitions(const PropertyDefinitions&) = delete;
    PropertyDefinitions& operator=(const PropertyDefinitions&) = delete;
    PropertyDefinitions(PropertyDefinitions&&) = delete;
    PropertyDefinitions& operator=(PropertyDefinitions&&) = delete;

    static const std::unordered_map<API_ElemTypeID, std::vector<std::string>> propertyDefinitionIds;
    std::unordered_map<API_ElemTypeID, std::vector<API_PropertyDefinition>> cache;
};
