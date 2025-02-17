#pragma once

#include "json.hpp"
#include "HostObjectBuilderResult.h"

class HostObjectBuilder
{
public:
	HostObjectBuilder() = default;
	HostObjectBuilderResult Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName);

private:
	std::map<std::string, int> BakeMaterials(const nlohmann::json& rootObject, const std::string& baseGroupName);
	HostObjectBuilderResult BakeObjects(const nlohmann::json& rootObject, const std::string& baseGroupName, const std::map<std::string, int>& materialTable);
	void GroupObjects(const std::vector<std::string>& objectIds);
};
