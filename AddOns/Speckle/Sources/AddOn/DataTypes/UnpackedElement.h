#pragma once

#include "json.hpp"
#include "Mesh.h"

struct Vertex 
{
    double x, y, z;
};

struct Edge 
{
    int start, end;
};

struct Face 
{
    int vertexCount;
    std::vector<int> vertexIndices;
    std::vector<Edge> edges;
    std::string materialName;
};

class UnpackedElement
{
public:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    std::string id = "";

    UnpackedElement(const std::vector<Mesh>& meshes, const std::map<std::string, std::string>& materialMap);
};
