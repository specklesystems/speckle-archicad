#pragma once

#include "json.hpp"

struct Material
{
    std::string speckle_type = "Objects.Other.RenderMaterial";
    std::string name = "RenderMaterial";
    std::string applicationId = "D2417E06-1AA5-1714-D29A-1EC8F0830654"; //TODO: remove default
    uint32_t diffuse = 0;
    double opacity = 1.0;
    double emissive = 0.0;
    double metalness = 0.0;
    double roughness = 1.0;
};

void to_json(nlohmann::json& j, const Material& material);
void from_json(const nlohmann::json& j, Material& material);
