#include "Mesh.h"

void to_json(nlohmann::json& j, const Mesh& mesh)
{
    j["speckle_type"] = mesh.speckle_type;
    j["applicationId"] = mesh.applicationId;
    j["units"] = mesh.units;
    j["vertices"] = mesh.vertices;
    j["faces"] = mesh.faces;
    j["colors"] = mesh.colors;
}

void from_json(const nlohmann::json& j, Mesh& mesh)
{
    try
    {
        mesh.speckle_type = j.at("speckle_type").get<std::string>();
    }
    catch (const std::exception&)
    {
        mesh.speckle_type = "Objects.Geometry.Mesh";
    }

    try
    {
        mesh.applicationId = j.at("applicationId").get<std::string>();
    }
    catch (const std::exception&)
    {
        mesh.applicationId = "0";
    }

    try
    {
        mesh.units = j.at("units").get<std::string>();
    }
    catch (const std::exception&)
    {
        mesh.units = "m";
    }
    
    mesh.vertices = j.at("vertices").get<std::vector<double>>();
    mesh.faces = j.at("faces").get<std::vector<int>>();
    try
    {
        mesh.colors = j.at("colors").get<std::vector<int>>();
    }
    catch (const std::exception&)
    {
        mesh.colors = std::vector<int>();
    }
}

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
