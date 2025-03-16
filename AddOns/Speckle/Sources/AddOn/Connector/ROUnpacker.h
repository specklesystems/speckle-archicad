#pragma once

#include <vector>
#include <map>
#include "RenderMaterialProxy.h"
#include "Mesh.h"
#include "UnpackedElement.h"
#include "UnpackedObject.h"
#include "InstanceProxy.h"
#include "InstanceDefinitionProxy.h"
#include "Node.h"

class ROUnpacker
{
private:
	const Node* rootNode;
	const std::string baseGroupName;
	const std::map<std::string, std::string>* materialTable;
	std::map<std::string, const Node*> nodes;

	std::map<std::string, Mesh> meshes;
	std::map<std::string, InstanceProxy> instanceProxies;
	std::map<std::string, InstanceDefinitionProxy> instanceDefinitionProxies;
	std::vector<RenderMaterialProxy> renderMaterialProxies;
	std::vector<const Node*> meshNodesAfterTraversal;
	
	int jsonSize = 0;
	int traversed = 0;

	int instanceCount = 0;
	int meshCountAfterTraversal = 0;

	std::vector<std::string> errors;

public:
	ROUnpacker(const Node* rootNode, const std::map<std::string, std::string>* materialTable, const std::string& baseGroupName); 
	void Unpack();

	std::map<std::string, std::vector<Mesh>> unpackedMeshes;
	std::vector<UnpackedElement> unpackedElements;

private:
	void Traverse(const Node* node);
	void Deserialize();
	void ExpandInstances();
	void ExpandInstance(const Node* node);
	void ProcessNodes();
	void ProcessNode(const Node* node);
	void UnpackElements();
	//void CreateElements();
	//void PlaceElements();
};
