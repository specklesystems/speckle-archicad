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
    // Packed ARGB emission colour. 0 = no emission; the bundle writes NULL for it,
    // per the spec's "producers normalize black RGB to NULL" contract.
    uint32_t emissive = 0;
    double metalness = 0.0;
    double roughness = 1.0;
};
