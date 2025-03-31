#pragma once

#include "json.hpp"
#include "Material.h"
#include "GuidGenerator.h"

struct ColorProxy
{
    std::string speckle_type = "Objects.Other.RenderMaterialProxy";
    std::string applicationId = GuidGenerator::NewGuid();
    uint32_t value;
    std::vector<std::string> objects;
};

void to_json(nlohmann::json& j, const ColorProxy& proxy);
void from_json(const nlohmann::json& j, ColorProxy& proxy);
