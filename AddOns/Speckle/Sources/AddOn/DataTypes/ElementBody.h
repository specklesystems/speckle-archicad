#pragma once

#include "json.hpp"
#include <map>
#include "Mesh.h"

struct ElementBody
{
    std::vector<Mesh> meshes;
};

void to_json(nlohmann::json& j, const ElementBody& body);
