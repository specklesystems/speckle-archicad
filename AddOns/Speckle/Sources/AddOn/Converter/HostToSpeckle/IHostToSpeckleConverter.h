#pragma once

#include "ElementBody.h"
#include "Material.h"

class IHostToSpeckleConverter 
{
public:
	virtual ~IHostToSpeckleConverter() = default;

	virtual std::vector<std::string> GetSelection() = 0;
	virtual ElementBody GetElementBody(const std::string& elemId) = 0;
	virtual Material GetModelMaterial(int materialIndex) = 0;
};
