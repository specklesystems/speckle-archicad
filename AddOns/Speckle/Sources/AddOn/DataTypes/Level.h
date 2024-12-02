#pragma once

#include "json.hpp"
#include "ElementTypeCollection.h"
#include "RenderMaterialProxy.h"

struct Level
{
    std::string speckle_type = "Speckle.Core.Models.Collections.Collection";
    std::string name = "";
    std::map<std::string, ElementTypeCollection> elements;
};

void to_json(nlohmann::json& j, const Level& level);
