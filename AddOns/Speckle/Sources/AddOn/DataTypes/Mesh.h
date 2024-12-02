#pragma once

#include "json.hpp"
#include "GuidGenerator.h"

struct Mesh
{
    std::string speckle_type = "Objects.Geometry.Mesh";
    std::string applicationId = GuidGenerator::NewGuid();
    std::string units = "m"; // default to meters
    std::vector<double> vertices;
    std::vector<int> faces;
    std::vector<int> colors;
    int materialIndex = 0;

    // if face size is 4 you have to provide 12 double values in the vertices array 
    // x, y, z values for each vertex
    void AddFace(std::vector<double> verticesToAdd);
};

void to_json(nlohmann::json& j, const Mesh& mesh);
void from_json(const nlohmann::json& j, Mesh& mesh);
