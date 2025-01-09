#pragma once

#include "FaceVertex.h"
#include <vector>

struct MeshFace
{
    std::vector<FaceVertex> vertices;
    int size;
};
