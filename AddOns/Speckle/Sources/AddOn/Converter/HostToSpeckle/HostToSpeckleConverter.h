#pragma once

#include "IHostToSpeckleConverter.h"

class HostToSpeckleConverter : public IHostToSpeckleConverter
{
public:
	HostToSpeckleConverter() = default;

	std::vector<std::string> GetSelection() override;
	ElementBody GetElementBody(const std::string& elemId) override;
	Material GetModelMaterial(int materialIndex) override;
	std::string GetElementName(const std::string& elemId) override;
	std::string GetElementLevel(const std::string& elemId) override;
	std::string GetElementType(const std::string& elemId) override;
	std::map<std::string, std::string> GetElementClassifications(const std::string& elemId) override;
	ProjectInfo GetProjectInfo() override;
	std::string GetHostAppReleaseInfo() override;
	nlohmann::json GetElementMaterialQuantities(const std::string& elemId) override;
	nlohmann::json GetElementPropertiesByPropertyType(const std::string& elemId, const ArchicadPropertyType propertyType) override;
	nlohmann::json GetElementPropertiesByPropertyFilter(const std::string& elemId, const PropertyFilter filter) override;
	nlohmann::json GetElementProperties(const std::string& elemId) override;
	nlohmann::json GetWorkingUnits() override;
	std::string GetResourceString(short resourceId) override;
};
