#pragma once

#include "ElementBody.h"
#include "Material.h"
#include "ProjectInfo.h"

enum class ArchicadPropertyType
{
	UserDefined,
	FundamentalBuiltIn,
	UserLevelBuiltIn,
	All
};

class IHostToSpeckleConverter 
{
public:
	virtual ~IHostToSpeckleConverter() = default;

	virtual std::vector<std::string> GetSelection() = 0;
	virtual ElementBody GetElementBody(const std::string& elemId) = 0;
	virtual Material GetModelMaterial(int materialIndex) = 0;
	virtual std::string GetElementLevel(const std::string& elemId) = 0;
	virtual std::string GetElementType(const std::string& elemId) = 0;
	virtual ProjectInfo GetProjectInfo() = 0;
	virtual std::string GetHostAppReleaseInfo() = 0;
	virtual nlohmann::json GetElementMaterialQuantities(const std::string& elemId) = 0;
	virtual nlohmann::json GetElementUserDefinedProperties(const std::string& elemId) = 0;
	virtual nlohmann::json GetElementBuiltInProperties(const std::string& elemId) = 0;
	virtual nlohmann::json GetElementIfcProperties(const std::string& elemId) = 0;
	virtual nlohmann::json GetElementProperties(const std::string& elemId, const ArchicadPropertyType propertyType) = 0;
};
