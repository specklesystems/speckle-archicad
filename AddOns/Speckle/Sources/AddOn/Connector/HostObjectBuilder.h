#pragma once

#include "json.hpp"

class HostObjectBuilder 
{
public:
	HostObjectBuilder() = default;
	void Build(const nlohmann::json& rootObject);
};
