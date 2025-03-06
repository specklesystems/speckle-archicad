#pragma once

#include "json.hpp"
#include "Mesh.h"

struct UnpackedMesh
{
    Mesh mesh;
    std::string materialName;
};
