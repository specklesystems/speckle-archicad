#pragma once

#include "IHostToSpeckleConverter.h"

class HostToSpeckleConverter : public IHostToSpeckleConverter
{
public:
	HostToSpeckleConverter() = default;

	std::vector<std::string> GetSelection() override;
	ElementBody GetElementBody(const std::string& elemId) override;
	Material GetModelMaterial(int materialIndex) override;
	std::string GetElementLevel(const std::string& elemId) override;
	std::string GetElementType(const std::string& elemId) override;
	ProjectInfo GetProjectInfo() override;
	std::string GetHostAppReleaseInfo() override;
};
