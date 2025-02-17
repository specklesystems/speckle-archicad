#pragma once

#include "json.hpp"
#include "HostObjectBuilderResult.h"

class HostObjectBuilder
{
public:
	HostObjectBuilder() = default;
	HostObjectBuilderResult Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName);

private:
	HostObjectBuilderResult BakeObjects(const nlohmann::json& rootObject, const std::string& baseGroupName);
	void GroupObjects(const std::vector<std::string>& objectIds);
};
