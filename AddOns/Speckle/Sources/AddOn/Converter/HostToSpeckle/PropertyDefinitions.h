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
    // Returned by reference — API_PropertyDefinition arrays are heavy and this
    // is called once per element (the reference stays valid; entries are only
    // ever added to the cache, never removed). GS::Array so the result feeds
    // ACAPI_Element_GetPropertyValues without a per-element conversion.
    const GS::Array<API_PropertyDefinition>& GetDefinitions(API_ElemTypeID elemType);

private:
    PropertyDefinitions() = default;
    ~PropertyDefinitions() = default;

    // Delete copy & move operations
    PropertyDefinitions(const PropertyDefinitions&) = delete;
    PropertyDefinitions& operator=(const PropertyDefinitions&) = delete;
    PropertyDefinitions(PropertyDefinitions&&) = delete;
    PropertyDefinitions& operator=(PropertyDefinitions&&) = delete;

    static const std::unordered_map<API_ElemTypeID, std::vector<std::string>> propertyDefinitionIds;
    std::unordered_map<API_ElemTypeID, GS::Array<API_PropertyDefinition>> cache;
};
