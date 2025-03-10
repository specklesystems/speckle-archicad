#pragma once

#include <vector>
#include <map>
#include "RenderMaterialProxy.h"
#include "Mesh.h"
#include "UnpackedElement.h"
#include "UnpackedObject.h"
#include "InstanceProxy.h"
#include "InstanceDefinitionProxy.h"

class RootObjectUnpacker
{
public:
	RootObjectUnpacker() = default;
	std::vector<RenderMaterialProxy> UnpackRenderMaterialProxies(const nlohmann::json& rootObject);
	std::vector<Mesh> UnpackMeshesFlat(const nlohmann::json& rootObject);
	std::vector<std::vector<Mesh>> UnpackMeshes(const nlohmann::json& rootObject);
	std::vector<UnpackedElement> UnpackElements(const nlohmann::json& rootObject, const std::map<std::string, std::string>& materialTable);

	std::map<std::string, UnpackedObject> UnpackObjects(const nlohmann::json& rootObject);
	std::map<std::string, InstanceProxy> RootObjectUnpacker::UnpackInstanceProxies(const nlohmann::json& rootObject);
	std::map<std::string, InstanceDefinitionProxy> RootObjectUnpacker::UnpackInstanceDefinitionProxies(const nlohmann::json& rootObject);
};
