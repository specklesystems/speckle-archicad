#pragma once

#include "json.hpp"
#include "CategoryData.h"

struct ArchicadLayerFilter
{
    std::string typeDiscriminator = "ArchicadLayerFilter";
    std::vector<std::string> selectedObjectIds;
    std::string name = "Layers";
    // revitCategories was first implemented on UI
    // it will be used in Archicad as well for element type filters
    std::string id = "archicadLayers";
    std::string summary;
    bool isDefault = false;
    std::vector<std::string> selectedCategories;
    std::vector<CategoryData> availableCategories;

    void UpdateSelectedObjectIds();
};

void to_json(nlohmann::json& j, const ArchicadLayerFilter& filter);
void from_json(const nlohmann::json& j, ArchicadLayerFilter& filter);
