#pragma once

#include "json.hpp"

struct ArchicadLevel
{
    std::string speckle_type = "Objects.Data.DataObject";
    std::string name = "";
    std::string units = "m";
    double elevation = 0.0;
    short floorId = 0;
};

void to_json(nlohmann::json& j, const ArchicadLevel& level);
void from_json(const nlohmann::json& j, ArchicadLevel& level);
