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
    std::string applicationId = "";
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    UnpackedElement(const std::vector<Mesh>& meshes, const std::map<std::string, std::string>& materialTable);
    void ApplyScaling(const double scale);
};
