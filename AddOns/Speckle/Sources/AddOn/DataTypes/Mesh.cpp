#include "Mesh.h"

void Mesh::AddFace(std::vector<double> verticesToAdd)
{
    int faceSize = static_cast<int>(verticesToAdd.size() / 3);
    int lastVertexCount = static_cast<int>(vertices.size() / 3);
    faces.push_back(faceSize);

    for (const auto& v : verticesToAdd)
    {
        // rounding doubles to 4 decimals to lower the JSON size
        // it saves about 10-15% on large models
        // it can be critical if we try to parse large JSON cunks on the JS side
        // remove the rounding if the precision is needed
        double d = std::round(v * 10000.0) * 0.0001;;
        vertices.push_back(d);
    }

    for (int i = 0; i < faceSize; i++)
        faces.push_back(lastVertexCount + i);
}

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
    mesh.speckle_type = j.at("speckle_type").get<std::string>();
    mesh.applicationId = j.at("applicationId").get<std::string>();
    mesh.units = j.at("units").get<std::string>();
    mesh.vertices = j.at("vertices").get<std::vector<double>>();
    mesh.faces = j.at("faces").get<std::vector<int>>();
    mesh.colors = j.at("colors").get<std::vector<int>>();
}
