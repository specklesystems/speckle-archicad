#pragma once

#include "json.hpp"
#include "ModelElement.h"
#include "RenderMaterialProxy.h"

struct ElementTypeCollection
{
    std::string speckle_type = "Speckle.Core.Models.Collections.Collection";
    std::string name = "ElementType";
    std::vector<ModelElement> elements;
};

void to_json(nlohmann::json& j, const ElementTypeCollection& elementType);
