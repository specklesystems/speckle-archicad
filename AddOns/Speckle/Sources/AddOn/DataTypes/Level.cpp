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
}
