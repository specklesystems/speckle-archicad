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

#include "HostObjectBuilderResult.h"
#include "LibpartBuilder.h"

class RootObjectUnpacker
{
private:
	const std::shared_ptr<Node> rootNode;
	const std::string baseGroupName;
	LibpartBuilder libPartBuilder;

	std::map<std::string, std::string> materialTable;
	std::map<std::string, std::shared_ptr<Node>> nodes;
	std::map<std::string, std::shared_ptr<Node>> nodesByAppId;

	std::map<std::string, Mesh> meshes;
	std::map<std::string, InstanceProxy> instanceProxies;
	std::map<std::string, InstanceDefinitionProxy> instanceDefinitionProxies;
	std::vector<RenderMaterialProxy> renderMaterialProxies;
	std::vector<std::shared_ptr<Node>> meshNodes;
	std::set<std::string> proxyDefinitionObjects;
	
	int jsonSize = 0;
	int traversed = 0;
	int meshCountAfterTraversal = 0;

	std::vector<std::string> errors;

public:
	RootObjectUnpacker(const std::shared_ptr<Node>, const std::string& baseGroupName);
	void Unpack();
	HostObjectBuilderResult GetHostObjectBuilderResult();

	std::map<std::string, std::vector<Mesh>> unpackedMeshes;
	std::vector<UnpackedElement> unpackedElements;

private:
	void Traverse(const std::shared_ptr<Node>& node);
	void Deserialize();
	void BakeMaterials();
	void ExpandInstances();
	void ExpandInstance(const std::shared_ptr<Node>& node, bool addNew = true);
	void ProcessNodes();
	void ProcessNode(const std::shared_ptr<Node>& node);
	void UnpackElements();
};
