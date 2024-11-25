#pragma once

#include "json.hpp"
#include <map>
#include "ModelElement.h"
#include "Level.h"
#include "RenderMaterialProxy.h"

struct RootObject
{
    std::string speckle_type = "Speckle.Core.Models.Collections.Collection";
    std::string name = "RootObject";
    std::map<std::string, Level> elements;
    std::vector<RenderMaterialProxy> renderMaterialProxies;
};

void to_json(nlohmann::json& j, const RootObject& rootObject);
void from_json(const nlohmann::json& j, RootObject& rootObject);
