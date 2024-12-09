#include "ElementBody.h"

void ElementBody::AddFace(std::vector<double> vertices, int materialIndex)
{
	if (meshes.find(materialIndex) == meshes.end())
	{
		Mesh mesh;
		mesh.materialIndex = materialIndex;
		meshes[materialIndex] = mesh;
	}

	meshes[materialIndex].AddFace(vertices);
}

void to_json(nlohmann::json& j, const ElementBody& body)
{
	std::vector<Mesh> displayValue;
	for (const auto& m : body.meshes)
		displayValue.push_back(m.second);

	j = displayValue;
}
