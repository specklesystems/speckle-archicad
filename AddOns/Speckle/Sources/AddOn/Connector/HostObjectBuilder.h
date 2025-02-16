#pragma once

#include "json.hpp"

class HostObjectBuilder 
{
public:
	HostObjectBuilder() = default;
	void Build(const nlohmann::json& rootObject, const std::string& projectName, const std::string& modelName);

private:
	void BakeObjects(const nlohmann::json& rootObject);
};
