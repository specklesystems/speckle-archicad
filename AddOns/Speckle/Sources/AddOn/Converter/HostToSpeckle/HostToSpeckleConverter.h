#pragma once

#include "IHostToSpeckleConverter.h"

class HostToSpeckleConverter : public IHostToSpeckleConverter
{
public:
	HostToSpeckleConverter() = default;

	std::vector<std::string> GetSelection() override;
	std::vector<std::string> GetElementList(const std::vector<std::string>& elementTypes) override;
	std::vector<std::string> GetElementTypeList() override;
	ElementBody GetElementBody(const std::string& elemId) override;
	Material GetModelMaterial(int materialIndex) override;
	std::string GetElementName(const std::string& elemId) override;
	std::string GetElementLevel(const std::string& elemId) override;
	std::string GetElementType(const std::string& elemId) override;
	std::map<std::string, std::string> GetElementClassifications(const std::string& elemId) override;
	ProjectInfo GetProjectInfo() override;
	std::string GetApplicationFolder() override;
	std::string GetHostAppReleaseInfo() override;
	nlohmann::json GetElementMaterialQuantities(const std::string& elemId) override;
	nlohmann::json GetElementPropertiesByPropertyType(const std::string& elemId, const ArchicadPropertyTypeFilter propertyType) override;
	nlohmann::json GetElementPropertiesByPropertyFilter(const std::string& elemId, const PropertyCollectionFilter filter) override;
	nlohmann::json GetElementIfcProperties(const std::string& elemId) override;
	nlohmann::json GetElementProperties(const std::string& elemId) override;
	WorkingUnits GetWorkingUnits() override;
	ArchicadObject GetArchicadObject(const std::string& elemId, SendConversionResult& conversionResult) override;
	std::vector<ArchicadObject> GetElementChildren(const std::string& elemId) override;
	std::string GetResourceString(short resourceId) override;
};
