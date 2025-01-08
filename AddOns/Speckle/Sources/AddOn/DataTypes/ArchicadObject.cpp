#include "ArchicadObject.h"

void to_json(nlohmann::json& j, const ArchicadObject& elem)
{
    j["name"] = elem.name;
    j["type"] = elem.type;
    j["level"] = elem.level;
    j["speckle_type"] = elem.speckle_type;
    j["applicationId"] = elem.applicationId;
    j["units"] = elem.units;
    j["@displayValue"] = elem.displayValue;
    j["properties"] = elem.properties;
}
