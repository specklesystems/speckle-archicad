#include "WorkingUnits.h"

void to_json(nlohmann::json& j, const WorkingUnits& units)
{
    j["lengthUnits"] = units.lengthUnits;
    j["areaUnits"] = units.areaUnits;
    j["volumeUnits"] = units.volumeUnits;
}
