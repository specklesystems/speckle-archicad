#pragma once

#include <unordered_map>
#include <vector>
#include <string>

enum class ArchicadPropertyTypeFilter
{
    UserDefined,
    FundamentalBuiltIn,
    UserLevelBuiltIn,
    All
};

enum class PropertyCollectionFilter
{
    GeneralRatings,
    IFC,
    Dimensional
};

class PropertyFilters
{
public:
    static const std::unordered_map<PropertyCollectionFilter, std::vector<std::string>> propertyFilters;
    static std::vector<std::string> Get(PropertyCollectionFilter filter);

private:
    PropertyFilters() = delete;
};
