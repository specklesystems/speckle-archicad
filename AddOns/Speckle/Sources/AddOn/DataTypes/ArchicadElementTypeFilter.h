#pragma once

#include "json.hpp"
#include "CategoryData.h"

struct ArchicadElementTypeFilter
{
    std::string typeDiscriminator = "ArchicadElementTypeFilter";
    std::vector<std::string> selectedObjectIds;
    std::string name = "Element Types";
    // TODO change id
    std::string id = "revitCategories";
    //std::string id = "archicadElementTypes";
    std::string summary;
    bool isDefault = false;
    std::vector<std::string> selectedCategories;
    std::vector<CategoryData> availableCategories;

    void UpdateSelectedObjectIds();
};

void to_json(nlohmann::json& j, const ArchicadElementTypeFilter& filter);
void from_json(const nlohmann::json& j, ArchicadElementTypeFilter& filter);
