#include "WorkingUnits.h"

void to_json(nlohmann::json& j, const WorkingUnits& units)
{
    j["calculatedLengthUnits"] = units.calculatedLengthUnits;
    j["calculatedAreaUnits"] = units.calculatedAreaUnits;
    j["calculatedVolumeUnits"] = units.calculatedVolumeUnits;
    j["workingLengthUnits"] = units.workingLengthUnits;
    j["workingAreaUnits"] = units.workingAreaUnits;
    j["workingVolumeUnits"] = units.workingVolumeUnits;
}

void from_json(const nlohmann::json& j, WorkingUnits& units)
{
    units.calculatedLengthUnits = j.at("calculatedLengthUnits").get<std::string>();
    units.calculatedAreaUnits = j.at("calculatedAreaUnits").get<std::string>();
    units.calculatedVolumeUnits = j.at("calculatedVolumeUnits").get<std::string>();
    units.workingLengthUnits = j.at("workingLengthUnits").get<std::string>();
    units.workingAreaUnits = j.at("workingAreaUnits").get<std::string>();
    units.workingVolumeUnits = j.at("workingVolumeUnits").get<std::string>();
}
