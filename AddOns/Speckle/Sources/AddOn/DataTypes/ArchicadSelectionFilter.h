#pragma once

#include "json.hpp"

struct ArchicadSelectionFilter
{
    std::string typeDiscriminator = "ArchicadSelectionFilter";
    std::vector<std::string> selectedObjectIds;
    std::string name = "Selection";
    std::string summary;
    bool isDefault = true;
};

void to_json(nlohmann::json& j, const ArchicadSelectionFilter& filter);
void from_json(const nlohmann::json& j, ArchicadSelectionFilter& filter);
