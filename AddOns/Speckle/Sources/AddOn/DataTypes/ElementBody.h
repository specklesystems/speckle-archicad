#pragma once

#include "json.hpp"
#include <map>
#include "Mesh.h"

struct ElementBody
{
    // the int value refers to an Archicad materialIndex
    // we store 1 Mesh for each Material in the Body
    std::map<int, Mesh> meshes;

    void AddFace(std::vector<double> vertices, int materialIndex);
};

void to_json(nlohmann::json& j, const ElementBody& body);
