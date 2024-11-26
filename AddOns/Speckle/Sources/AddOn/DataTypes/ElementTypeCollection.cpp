#include "ElementTypeCollection.h"

void to_json(nlohmann::json& j, const ElementTypeCollection& elementType)
{
    j["speckle_type"] = elementType.speckle_type;
    j["name"] = elementType.name;
    j["elements"] = elementType.elements;
}
