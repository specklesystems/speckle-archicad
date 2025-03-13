#include "UnpackedElement.h"

UnpackedElement::UnpackedElement(const std::vector<Mesh>& meshes, const std::map<std::string, std::string>& materialTable)
{
    std::unordered_map<int, int> vertexMap;

    for (const auto& mesh : meshes)
    {
        int vertexOffset = static_cast<int>(vertices.size());

        for (size_t i = 0; i < mesh.vertices.size(); i += 3)
        {
            vertices.push_back({ mesh.vertices[i], mesh.vertices[i + 1], mesh.vertices[i + 2] });
        }

        size_t i = 0;
        while (i < mesh.faces.size())
        {
            int polySize = mesh.faces[i++];

            if (polySize < 3)
            {
                polySize += 3;
            }

            std::vector<int> newIndices;
            std::vector<Edge> edges;

            for (int j = 0; j < polySize; ++j)
            {
                int oldIndex = mesh.faces[i++];
                newIndices.push_back(oldIndex + vertexOffset);
            }

            std::string materialName = "speckle_default_material";
            auto it = materialTable.find(mesh.applicationId);
            if (it != materialTable.end())
            {
                materialName = it->second;
            }

            if (polySize == 3)
            {
                // Directly add triangles
                faces.push_back({ 3, {newIndices[0], newIndices[1], newIndices[2]},
                                  { {newIndices[0], newIndices[1]}, {newIndices[1], newIndices[2]}, {newIndices[2], newIndices[0]} },
                                  materialName });
            }
            else
            {
                // Fan triangulation for n-gons
                for (int j = 1; j < polySize - 1; ++j)
                {
                    faces.push_back({ 3, {newIndices[0], newIndices[j], newIndices[j + 1]},
                                      { {newIndices[0], newIndices[j]}, {newIndices[j], newIndices[j + 1]}, {newIndices[j + 1], newIndices[0]} },
                                      materialName });
                }
            }
        }
    }
}

void UnpackedElement::ApplyScaling(const double scale)
{
    for (auto& vertex : vertices)
    {
        vertex.x *= scale;
        vertex.y *= scale;
        vertex.z *= scale;
    }
}
