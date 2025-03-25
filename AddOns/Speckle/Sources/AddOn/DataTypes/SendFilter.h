#pragma once

#include "json.hpp"
#include "ArchicadSelectionFilter.h"
#include "ArchicadElementTypeFilter.h"

struct SendFilter
{
    std::string typeDiscriminator;
    nlohmann::json data;

    bool IsArchicadSelectionFilter();
    bool IsArchicadElementTypeFilter();
    ArchicadSelectionFilter AsArchicadSelectionFilter();
    ArchicadElementTypeFilter AsArchicadElementTypeFilter();

    std::vector<std::string> GetSelectedObjectIds();
};

void to_json(nlohmann::json& j, const SendFilter& filter);
void from_json(const nlohmann::json& j, SendFilter& filter);
