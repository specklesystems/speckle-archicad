#pragma once

#include "ISpeckleToHostConverter.h"

class SpeckleToHostConverter : public ISpeckleToHostConverter
{
public:
	SpeckleToHostConverter() = default;

	void SetSelection(std::vector<std::string> guids) override;
	void ShowAllIn3D() override;
	void ShowIn3D() override;
	void SetView(const std::string& viewName) override;
	int CreateMaterial(const Material& material, const std::string& materialName) override;
	int CreateMaterial(const ColorProxy& color, const std::string& materialName) override;
	std::string CreateMorph(const Mesh& mesh, const int materialIndex, const std::string& baseGroupName) override;
	std::string CreateGroup(const std::vector<std::string>& memberIds) override;
};
