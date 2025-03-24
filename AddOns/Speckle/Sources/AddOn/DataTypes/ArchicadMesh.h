#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include "Mesh.h"

// TODO move the belov helper classes to their own files
// use API classes if possible
struct ArchicadVertex 
{
    double x, y, z;
};

struct ArchicadEdge 
{
    int start, end;
    int poly1 = -1, poly2 = -1;
    double polyAngle = 0.0;
    std::string visibilityType; // smoothBodyEdge/hiddenBodyEdge/visibleBodyEdge, TODO should be enum

    bool Equals(const ArchicadEdge& other) const
    {
        return (start == other.start) && (end == other.end);
    }

    bool Opposite(const ArchicadEdge& other) const
    {
        return (end == other.start) && (start == other.end);
    }
};

struct ArchicadPoly
{
    int size;
    std::vector<int> edges;
    std::string materialName;
    ArchicadVertex normal;
    bool isCoplanar = false;
};

class ArchicadMesh 
{
public:
    explicit ArchicadMesh(const Mesh& mesh);

    std::vector<ArchicadVertex> vertices;
    std::vector<ArchicadEdge> edges;
    std::vector<ArchicadPoly> polys;
    std::unordered_map<size_t, int> vertexMap;

    size_t ArchicadVertexHash(const ArchicadVertex& vertex) const;
    void CreateMesh(const Mesh& mesh);
    void CalculatePolyNormals();
    void ComputeEdgeVisibility();
};
