#pragma once

#include "RootObject.h"
#include <vector>
#include <stack>
#include <string>
#include <map>

#include "json.hpp"

class BaseObjectSerializer 
{
public:
	BaseObjectSerializer() = default;

	std::string Serialize(RootObject root);
	std::vector<nlohmann::json> GetObjects();
	std::vector<std::string> BatchObjects();

private:
	std::stack<bool> detachLineage;
	std::vector<std::string> lineage;
	std::map<std::string, nlohmann::json> familyTree;
	// familyTreeRelation
	std::map<std::string, nlohmann::json> objects;

	
	std::pair<std::string, nlohmann::json> TraverseBase(const nlohmann::json& base);
	void TraverseBaseProps(const nlohmann::json& base, nlohmann::json& traversedBase);
	nlohmann::json TraverseValue(const nlohmann::json& value, bool isDetach = false);
	nlohmann::json DetachHelper(const std::string& referenceId);
	
};
