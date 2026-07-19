#pragma once

#include "json.hpp"

struct Mesh
{
    std::string speckle_type = "Objects.Geometry.Mesh";
    std::string units = "m"; // default to meters
    std::vector<double> vertices;
    std::vector<int> faces;
    std::vector<int> colors;
    int materialIndex = 0;
    std::string materialName = "";

    void ApplyTransform(const std::vector<double>& transform);
    void ApplyScaling(const double scaling);
};
