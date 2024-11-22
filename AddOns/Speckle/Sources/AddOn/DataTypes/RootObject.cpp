#include "RootObject.h"

void to_json(nlohmann::json& j, const RootObject& elem)
{
    j["speckle_type"] = elem.speckle_type;
    j["name"] = elem.name;
    j["elements"] = elem.elements;
    j["renderMaterialProxies"] = elem.renderMaterialProxies;
}

void from_json(const nlohmann::json& j, RootObject& elem)
{
    elem.speckle_type = j.at("speckle_type").get<std::string>();
    elem.name = j.at("name").get<std::string>();
    elem.elements = j.at("elements").get<std::vector<ModelElement>>();
    // TODO: renderMaterialProxies
}
