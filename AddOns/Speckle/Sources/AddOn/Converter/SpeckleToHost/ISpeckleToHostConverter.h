#pragma once

#include <string>
#include <vector>
#include "Material.h"
#include "ColorProxy.h"
#include "Mesh.h"

class ISpeckleToHostConverter
{
public:
	virtual ~ISpeckleToHostConverter() = default;

	virtual void SetSelection(std::vector<std::string> guids) = 0;
	virtual void ShowAllIn3D() = 0;
	virtual int CreateMaterial(const Material& material, const std::string& baseGroupName) = 0;
	virtual int CreateMaterial(const ColorProxy& color, const std::string& baseGroupName) = 0;
	virtual std::string CreateMorph(const Mesh& mesh, const int materialIndex, const std::string& baseGroupName) = 0;
	virtual std::string CreateGroup(const std::vector<std::string>& memberIds) = 0;
};
