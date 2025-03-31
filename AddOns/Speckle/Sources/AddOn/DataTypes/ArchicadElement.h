#pragma once

#include "ArchicadMesh.h"

class ArchicadElement 
{
public:
    explicit ArchicadElement(const std::vector<Mesh>& meshes);
    std::vector<ArchicadMesh> archicadMeshes;
};
