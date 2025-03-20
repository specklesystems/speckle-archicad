#include "ArchicadMesh.h"
#include <unordered_set>
#include <cmath>

size_t ArchicadMesh::ArchicadVertexHash(const ArchicadVertex& vertex) const 
{
    std::hash<double> hasher;
    return hasher(vertex.x) ^ (hasher(vertex.y) << 1) ^ (hasher(vertex.z) << 2);
}

ArchicadMesh::ArchicadMesh(const std::vector<Mesh>& meshes) 
{
    CreateMesh(meshes);
}

void ArchicadMesh::CreateMesh(const std::vector<Mesh>& meshes)
{
    int vertexIndex = 1;

    for (const auto& mesh : meshes)
    {
        for (size_t i = 0; i < mesh.faces.size(); )
        {
            int polySize = mesh.faces[i++];
            std::vector<int> faceVertices;

            for (int j = 0; j < polySize; ++j)
            {
                int originalIndex = mesh.faces[i++];
                ArchicadVertex vertex = { mesh.vertices[originalIndex * 3], mesh.vertices[originalIndex * 3 + 1], mesh.vertices[originalIndex * 3 + 2] };
                //size_t hash = ArchicadVertexHash(vertex);
                size_t hash = static_cast<size_t>(vertexIndex);

                if (vertexMap.find(hash) == vertexMap.end())
                {
                    vertices.push_back(vertex);
                    faceVertices.push_back(vertexIndex);
                    vertexMap[hash] = vertexIndex++;
                }
                else
                {
                    faceVertices.push_back(vertexMap[hash]);
                }
            }

            std::vector<int> polyEdges;

            for (size_t j = 0; j < faceVertices.size(); ++j)
            {
                ArchicadEdge acEdge;
                acEdge.start = faceVertices[j];
                acEdge.end = faceVertices[(j + 1) % faceVertices.size()];

                bool newEdge = true;
                int foundEdgeIndex = 1;
                /*for (const auto& e : edges)
                {
                    if (acEdge.Equals(e))
                    {
                        polyEdges.push_back(foundEdgeIndex);
                        newEdge = false;
                        break;
                    }

                    if (acEdge.Opposite(e))
                    {
                        polyEdges.push_back(-foundEdgeIndex);
                        newEdge = false;
                        break;
                    }

                    foundEdgeIndex++;
                }*/
                if (newEdge)
                {
                    edges.push_back(acEdge);
                    foundEdgeIndex = static_cast<int>(edges.size());
                    polyEdges.push_back(foundEdgeIndex);
                }
            }

            polys.push_back({ polySize, polyEdges, mesh.materialName });
        }
    }
}
