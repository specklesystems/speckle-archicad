#pragma once

#include <string>
#include <vector>

// Flat geometry carrier for the send path: vertices are x,y,z triplets, faces
// are [n, i0..in-1] polygon runs (Speckle mesh layout), consumed by
// SgeoEncoder / ComputeDefinitionId.
struct Mesh
{
    std::string units = "m"; // default to meters
    std::vector<double> vertices;
    std::vector<int> faces;
    std::vector<int> colors;
    int materialIndex = 0;
};
