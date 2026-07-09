#include "Mesh.h"

void Mesh::ApplyTransform(const std::vector<double>& transform)
{
    if (transform.size() != 16)
    {
        throw std::invalid_argument("Transform matrix must have 16 elements.");
    }

    for (int i = 0; i < vertices.size(); i += 3)
    {
        double x = vertices[i];
        double y = vertices[i + 1];
        double z = vertices[i + 2];
        double w = 1.0;

        vertices[i] = transform[0] * x + transform[1] * y + transform[2] * z + transform[3] * w;
        vertices[i + 1] = transform[4] * x + transform[5] * y + transform[6] * z + transform[7] * w;
        vertices[i + 2] = transform[8] * x + transform[9] * y + transform[10] * z + transform[11] * w;
    }
}

void Mesh::ApplyScaling(const double scaling)
{
    for (auto& v : vertices)
    {
        v *= scaling;
    }
}
