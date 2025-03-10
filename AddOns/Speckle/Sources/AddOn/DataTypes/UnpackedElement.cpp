#include "UnpackedElement.h"

UnpackedElement::UnpackedElement(const std::vector<Mesh>& meshes, const std::map<std::string, std::string>& materialMap)
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
            int vertexCount = mesh.faces[i++];
            std::vector<int> newIndices;
            std::vector<Edge> edges;

            int firstIndex = mesh.faces[i] + vertexOffset;
            int prevIndex = firstIndex;

            for (int j = 0; j < vertexCount; ++j)
            {
                int oldIndex = mesh.faces[i++];
                int newIndex = oldIndex + vertexOffset;
                newIndices.push_back(newIndex);

                if (j > 0)
                {
                    edges.push_back({ prevIndex, newIndex });
                }
                prevIndex = newIndex;
            }

            edges.push_back({ prevIndex, firstIndex });

            std::string materialName = "";
            auto it = materialMap.find(mesh.applicationId);
            if (it != materialMap.end())
            {
                materialName = it->second;
            }

            faces.push_back({ vertexCount, newIndices, edges, materialName });
        }
    }
}

void UnpackedElement::ApplyTransform(const std::vector<double>& transform)
{
    if (transform.size() != 16) 
    {
        throw std::invalid_argument("Transform matrix must have 16 elements.");
    }

    for (auto& vertex : vertices) 
    {
        double x = vertex.x;
        double y = vertex.y;
        double z = vertex.z;
        double w = 1.0;

        vertex.x = transform[0] * x + transform[1] * y + transform[2] * z + transform[3] * w;
        vertex.y = transform[4] * x + transform[5] * y + transform[6] * z + transform[7] * w;
        vertex.z = transform[8] * x + transform[9] * y + transform[10] * z + transform[11] * w;
    }
}

void UnpackedElement::Scale(const double scale)
{
    for (auto& vertex : vertices)
    {
        vertex.x *= scale;
        vertex.y *= scale;
        vertex.z *= scale;
    }
}
