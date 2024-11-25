#include "Level.h"

void to_json(nlohmann::json& j, const Level& level)
{
    j["speckle_type"] = level.speckle_type;
    j["name"] = level.name;

    std::vector<ElementTypeCollection> elementTypes;
    for (const auto& e : level.elements)
    {
        elementTypes.push_back(e.second);
    }

    j["elements"] = elementTypes;
    //j["elements"] = level.elements;
}

void from_json(const nlohmann::json& j, Level& level)
{
    level.speckle_type = j.at("speckle_type").get<std::string>();
    level.name = j.at("name").get<std::string>();
    //level.elements = j.at("elements").get<std::vector<ModelElement>>();
}
