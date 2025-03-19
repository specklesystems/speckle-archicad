#pragma once

#include "RenderMaterialProxy.h"
#include "Mesh.h"
#include "UnpackedElement.h"
#include "InstanceProxy.h"
#include "InstanceDefinitionProxy.h"
#include "Node.h"

#include <vector>
#include <map>
#include <set>

class RootObjectUnpacker
{
private:
	const Node* rootNode;
	const std::string baseGroupName;
	std::map<std::string, std::string> materialTable;
	std::map<std::string, const Node*> nodes;
	std::map<std::string, const Node*> nodesByAppId;

	std::map<std::string, Mesh> meshes;
	std::map<std::string, InstanceProxy> instanceProxies;
	std::map<std::string, InstanceDefinitionProxy> instanceDefinitionProxies;
	std::vector<RenderMaterialProxy> renderMaterialProxies;
	std::vector<const Node*> meshNodes;
	std::set<std::string> proxyDefinitionObjects;
	
	int jsonSize = 0;
	int traversed = 0;
	int meshCountAfterTraversal = 0;

	std::vector<std::string> errors;

public:
	RootObjectUnpacker(const Node* rootNode, const std::string& baseGroupName);
	void Unpack();

	std::map<std::string, std::vector<Mesh>> unpackedMeshes;
	std::vector<UnpackedElement> unpackedElements;

private:
	void Traverse(const Node* node);
	void Deserialize();
	void BakeMaterials();
	void ExpandInstances();
	void ExpandInstance(const Node* node, bool addNew = true);
	void ProcessNodes();
	void ProcessNode(const Node* node);
	void UnpackElements();
};
