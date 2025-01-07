#include "ArchicadObject.h"

void to_json(nlohmann::json& j, const ArchicadObject& elem)
{
    j["name"] = elem.name;
    j["type"] = elem.type;
    j["level"] = elem.level;
    j["classifications"] = elem.classifications;
    j["speckle_type"] = elem.speckle_type;
    j["applicationId"] = elem.applicationId;
    j["units"] = elem.units;
    j["@displayValue"] = elem.displayValue;
    j["properties"] = elem.properties;
}

/*void from_json(const nlohmann::json& j, ArchicadObject& elem)
{
    elem.speckle_type = j.at("speckle_type").get<std::string>();
    elem.applicationId = j.at("applicationId").get<std::string>();
    elem.units = j.at("units").get<std::string>();
}*/
