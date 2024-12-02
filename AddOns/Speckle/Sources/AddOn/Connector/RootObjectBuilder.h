#pragma once

#include "RootObject.h"
#include "SendConversionResult.h"

class RootObjectBuilder 
{
public:
	RootObjectBuilder() = default;
	RootObject GetRootObject(const std::vector<std::string>& elementIds, std::vector<SendConversionResult>& conversionResults);
};
