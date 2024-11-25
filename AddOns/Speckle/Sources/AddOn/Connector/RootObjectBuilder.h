#pragma once

#include "RootObject.h"

class RootObjectBuilder 
{
public:
	RootObjectBuilder() = default;
	RootObject GetRootObject(const std::vector<std::string>& elementIds);
};
