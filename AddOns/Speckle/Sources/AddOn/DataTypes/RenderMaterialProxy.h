#pragma once

#include "json.hpp"
#include "Material.h"
#include "GuidGenerator.h"

struct RenderMaterialProxy
{
    std::string speckle_type = "Objects.Other.RenderMaterialProxy";
    std::string applicationId = GuidGenerator::NewGuid();
    Material value;
    std::vector<std::string> objects;
};

void to_json(nlohmann::json& j, const RenderMaterialProxy& proxy);
