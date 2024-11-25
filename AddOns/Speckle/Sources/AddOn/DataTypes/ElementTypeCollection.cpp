#include "ElementTypeCollection.h"

void to_json(nlohmann::json& j, const ElementTypeCollection& elementType)
{
    j["speckle_type"] = elementType.speckle_type;
    j["name"] = elementType.name;
    j["elements"] = elementType.elements;
}

void from_json(const nlohmann::json& j, ElementTypeCollection& elementType)
{
    elementType.speckle_type = j.at("speckle_type").get<std::string>();
    elementType.name = j.at("name").get<std::string>();
    elementType.elements = j.at("elements").get<std::vector<ModelElement>>();
}
