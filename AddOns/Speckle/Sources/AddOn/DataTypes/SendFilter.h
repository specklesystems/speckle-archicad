#pragma once

#include "json.hpp"
#include "ArchicadSelectionFilter.h"
#include "ArchicadElementTypeFilter.h"
#include "ArchicadViewsFilter.h"
#include "ArchicadLayerFilter.h"

struct SendFilter
{
    std::string typeDiscriminator;
    nlohmann::json data;

    bool IsArchicadSelectionFilter();
    bool IsArchicadElementTypeFilter();
    bool IsArchicadViewsFilter();
    bool IsArchicadLayerFilter();
    ArchicadSelectionFilter AsArchicadSelectionFilter();
    ArchicadElementTypeFilter AsArchicadElementTypeFilter();
    ArchicadViewsFilter AsArchicadViewsFilter();
    ArchicadLayerFilter AsArchicadLayerFilter();

    std::vector<std::string> GetSelectedObjectIds();
};

void to_json(nlohmann::json& j, const SendFilter& filter);
void from_json(const nlohmann::json& j, SendFilter& filter);
