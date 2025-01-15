#pragma once

#include "json.hpp"

struct WorkingUnits
{
    std::string lengthUnits = "";
    std::string areaUnits = "";
    std::string volumeUnits = "";
};

void to_json(nlohmann::json& j, const WorkingUnits& units);
