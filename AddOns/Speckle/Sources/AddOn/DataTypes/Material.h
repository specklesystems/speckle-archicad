#pragma once

#include "json.hpp"
#include "GuidGenerator.h"

struct Material
{
    std::string speckle_type = "Objects.Other.RenderMaterial";
    std::string name = "";
    std::string applicationId = GuidGenerator::NewGuid();
    uint32_t diffuse = 0;
    double opacity = 1.0;
    double emissive = 0.0;
    double metalness = 0.0;
    double roughness = 1.0;
};

void to_json(nlohmann::json& j, const Material& material);
void from_json(const nlohmann::json& j, Material& material);
