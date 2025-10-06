#include "ArchicadLevel.h"

void to_json(nlohmann::json& j, const ArchicadLevel& level)
{
    j["speckle_type"] = level.speckle_type;
    j["name"] = level.name;
    j["units"] = level.units;
    j["elevation"] = level.elevation;
}

void from_json(const nlohmann::json& j, ArchicadLevel& level)
{
    level.speckle_type = j.at("speckle_type").get<std::string>();
    level.name = j.at("name").get<std::string>();
    level.units = j.at("units").get<std::string>();
    level.elevation = j.at("elevation").get<double>();
}
