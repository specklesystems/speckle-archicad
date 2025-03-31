#include "RootObject.h"

void to_json(nlohmann::json& j, const RootObject& rootObject)
{
    j["speckle_type"] = rootObject.speckle_type;
    j["name"] = rootObject.name;

    std::vector<Level> levels;
    for (const auto& e : rootObject.elements)
    {
        levels.push_back(e.second);
    }

    j["@elements"] = levels;
    j["renderMaterialProxies"] = rootObject.renderMaterialProxies;
}

void from_json(const nlohmann::json& j, RootObject& rootObject)
{
    rootObject.speckle_type = j.at("speckle_type").get<std::string>();
    rootObject.name = j.at("name").get<std::string>();
    std::vector<Level> levels = j.at("elements").get<std::vector<Level>>();

    for (const auto& level : levels)
    {
        rootObject.elements[level.name] = level;
    }
}
