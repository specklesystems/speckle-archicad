#pragma once

#include "json.hpp"

struct WorkingUnits
{
    std::string calculatedLengthUnits = "";
    std::string calculatedAreaUnits = "";
    std::string calculatedVolumeUnits = "";
    std::string workingLengthUnits = "";
    std::string workingAreaUnits = "";
    std::string workingVolumeUnits = "";
};

void to_json(nlohmann::json& j, const WorkingUnits& units);
void from_json(const nlohmann::json& j, WorkingUnits& units);
