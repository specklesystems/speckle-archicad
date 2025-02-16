#pragma once

#include <vector>
#include "Mesh.h"

class RootObjectUnpacker
{
public:
	RootObjectUnpacker() = default;
	std::vector<Mesh> UnpackMeshes(const nlohmann::json& rootObject);
};
