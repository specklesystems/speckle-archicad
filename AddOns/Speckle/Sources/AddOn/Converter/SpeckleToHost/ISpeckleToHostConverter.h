#pragma once

#include <string>
#include <vector>
#include "Material.h"
#include "Mesh.h"

class ISpeckleToHostConverter
{
public:
	virtual ~ISpeckleToHostConverter() = default;

	virtual void SetSelection(std::vector<std::string> guids) = 0;
	virtual void ShowAllIn3D() = 0;
	virtual int CreateMaterial(const std::string& materialName, const Material& material) = 0;
	virtual std::string CreateMorph(const Mesh& mesh, const int materialIndex) = 0;
	virtual std::string CreateGroup(const std::vector<std::string>& memberIds) = 0;
};
