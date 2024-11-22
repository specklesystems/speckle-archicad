#pragma once

#include "json.hpp"
#include "Utils.h"
#include "Material.h"

struct RenderMaterialProxy
{
    std::string speckle_type = "Objects.Other.RenderMaterialProxy";
    std::string applicationId = Utils::GenerateGUID();
    Material value;
    std::vector<std::string> objects;
};

void to_json(nlohmann::json& j, const RenderMaterialProxy& proxy);
