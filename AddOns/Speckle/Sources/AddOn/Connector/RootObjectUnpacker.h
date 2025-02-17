#pragma once

#include <vector>
#include "RenderMaterialProxy.h"
#include "Mesh.h"

class RootObjectUnpacker
{
public:
	RootObjectUnpacker() = default;
	std::vector<RenderMaterialProxy> UnpackRenderMaterialProxies(const nlohmann::json& rootObject);
	std::vector<Mesh> UnpackMeshes(const nlohmann::json& rootObject);
};
