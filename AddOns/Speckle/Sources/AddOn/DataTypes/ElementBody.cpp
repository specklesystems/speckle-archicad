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
	{
		displayValue.push_back(m.second);
	}
	j = displayValue;

	// this reference wrapper did not help much to lower the memory footprint but chcek it again
	/*std::vector<std::reference_wrapper<const Mesh>> values;
	for (const auto& pair : body.meshes) 
	{
		values.push_back(std::cref(pair.second));
	}

	j = values;*/
}
