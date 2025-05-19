#pragma once

#include "json.hpp"
#include "CategoryData.h"

struct ArchicadViewsFilter
{
    std::string typeDiscriminator = "ArchicadViewsFilter";
    std::vector<std::string> selectedObjectIds;
    std::string name = "Views";
    // revitViews was first implemented on UI
    // it will be used in Archicad as well for views filter
    std::string id = "revitViews";
    std::string type = "Custom";
    std::string summary;
    bool isDefault = false;
    std::string selectedView;
    std::vector<std::string> availableViews;

    void UpdateSelectedObjectIds();
};

void to_json(nlohmann::json& j, const ArchicadViewsFilter& filter);
void from_json(const nlohmann::json& j, ArchicadViewsFilter& filter);
