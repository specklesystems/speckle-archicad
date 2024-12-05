#include "ModelElement.h"

void to_json(nlohmann::json& j, const ModelElement& elem)
{
    j["speckle_type"] = elem.speckle_type;
    j["applicationId"] = elem.applicationId;
    j["units"] = elem.units;
    j["@displayValue"] = elem.displayValue;
}

void from_json(const nlohmann::json& j, ModelElement& elem)
{
    elem.speckle_type = j.at("speckle_type").get<std::string>();
    elem.applicationId = j.at("applicationId").get<std::string>();
    elem.units = j.at("units").get<std::string>();
    //elem.displayValue = j.at("displayValue").get<std::vector<Mesh>>();
}
