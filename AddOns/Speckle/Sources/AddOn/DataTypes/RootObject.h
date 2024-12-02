#pragma once

#include "json.hpp"
#include <map>
#include "Level.h"
#include "RenderMaterialProxy.h"

struct RootObject
{
    std::string speckle_type = "Speckle.Core.Models.Collections.Collection";
    std::string name = "";
    std::map<std::string, Level> elements;
    std::vector<RenderMaterialProxy> renderMaterialProxies;
};

void to_json(nlohmann::json& j, const RootObject& rootObject);
