#pragma once

#include "IHostToSpeckleConverter.h"

class HostToSpeckleConverter : public IHostToSpeckleConverter
{
public:
	HostToSpeckleConverter() = default;

	std::vector<std::string> GetSelection() override;
	ElementBody GetElementBody(const std::string& elemId) override;
	Material GetModelMaterial(int materialIndex) override;
};
