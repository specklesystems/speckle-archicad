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

    j["elements"] = levels;
    j["renderMaterialProxies"] = rootObject.renderMaterialProxies;
}
