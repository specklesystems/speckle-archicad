#pragma once

#include "json.hpp"
#include "ModelElement.h"
#include "RenderMaterialProxy.h"

struct RootObject
{
    std::string speckle_type = "Speckle.Core.Models.Collections.Collection";
    std::string name = "RootObject";
    std::vector<ModelElement> elements;
    std::vector<RenderMaterialProxy> renderMaterialProxies;
};

void to_json(nlohmann::json& j, const RootObject& mesh);
void from_json(const nlohmann::json& j, RootObject& mesh);
