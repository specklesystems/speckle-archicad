#pragma once

#include <vector>
#include <map>
#include "RenderMaterialProxy.h"
#include "Mesh.h"
#include "UnpackedElement.h"
#include "UnpackedObject.h"
#include "InstanceProxy.h"
#include "InstanceDefinitionProxy.h"

class Node
{
private:
	bool isSpeckleType = false;

public:
	const nlohmann::json* data;
	const Node* parent = nullptr;
	std::string id = "";
	std::string appId = "";
	std::string speckle_type = "";

	Node(const nlohmann::json& j, const Node* parent);
	bool IsObject() const;
	bool IsArray() const;
	bool IsSpeckleType() const;
	bool IsMesh() const;
	bool IsColorProxy() const;
	bool IsMaterialProxy() const;
	bool IsInstanceProxy() const;
	bool IsInstanceDefinitionProxy() const;
	bool IsCollection() const;
};
