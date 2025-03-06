#pragma once

#include <vector>
#include "RenderMaterialProxy.h"
#include "Mesh.h"
#include "UnpackedElement.h"

class RootObjectUnpacker
{
public:
	RootObjectUnpacker() = default;
	std::vector<RenderMaterialProxy> UnpackRenderMaterialProxies(const nlohmann::json& rootObject);
	std::vector<Mesh> UnpackMeshesFlat(const nlohmann::json& rootObject);
	std::vector<std::vector<Mesh>> UnpackMeshes(const nlohmann::json& rootObject);
	std::vector<UnpackedElement> UnpackElements(const nlohmann::json& rootObject, const std::map<std::string, std::string>& materialTable);
};
