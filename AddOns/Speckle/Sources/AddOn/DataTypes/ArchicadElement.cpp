#include "ArchicadElement.h"

ArchicadElement::ArchicadElement(const std::vector<Mesh>& meshes)
{
	for (const auto& m : meshes)
	{
		archicadMeshes.emplace_back(ArchicadMesh(m));
	}
}