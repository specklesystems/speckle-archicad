#pragma once

#include "ElementBody.h"
#include "Material.h"
#include "ProjectInfo.h"
#include "WorkingUnits.h"
#include "ArchicadObject.h"
#include "SendConversionResult.h"
#include "PropertyFilters.h"
#include "NavigatorView.h"
#include "ArchicadLevel.h"
#include "ArchicadRoomTopology.h"
#include "LayerData.h"

class IHostToSpeckleConverter 
{
public:
	virtual ~IHostToSpeckleConverter() = default;

	virtual std::vector<std::string> GetSelection() = 0;
	virtual std::vector<std::string> GetElementList(const std::vector<std::string>& elementTypes) = 0;
	virtual std::vector<std::string> GetElementListByLayer(const std::vector<std::string>& layerIndices) = 0;
	virtual std::vector<std::string> GetElementListAllVisibleIn3D() = 0;
	virtual std::vector<std::string> GetElementTypeList() = 0;
	virtual ElementBody GetElementBody(const std::string& elemId) = 0;
	virtual ObjectInstance GetObjectInstance(const std::string& elemId) = 0;
	virtual Material GetModelMaterial(int materialIndex) = 0;
	virtual std::string GetElementName(const std::string& elemId) = 0;
	virtual ArchicadLevel GetElementLevel(const std::string& elemId) = 0;
	virtual ArchicadLayer GetElementLayer(const std::string& elemId) = 0;
	// Guid of the element this one is hosted on (door/window -> wall, skylight ->
	// roof/shell); empty when the element is not an opening.
	virtual std::string GetElementHost(const std::string& elemId) = 0;
	// Guid of the group the element belongs to; empty when ungrouped.
	virtual std::string GetElementGroup(const std::string& elemId) = 0;
	// Synthetic display label for a group (Archicad groups carry no name).
	virtual std::string GetGroupDisplayName(const std::string& groupId) = 0;
	// Zone occupancy/boundary, or the two zones an opening connects. Empty otherwise.
	virtual ArchicadRoomTopology GetElementRoomTopology(const std::string& elemId) = 0;
	virtual std::string GetElementType(const std::string& elemId) = 0;
	virtual std::map<std::string, std::string> GetElementClassifications(const std::string& elemId) = 0;
	virtual ProjectInfo GetProjectInfo() = 0;
	virtual std::string GetApplicationFolder() = 0;
	virtual std::string GetHostAppReleaseInfo() = 0;
	virtual nlohmann::json GetElementMaterialQuantities(const std::string& elemId) = 0;
	virtual nlohmann::json GetElementCompositeStructure(const std::string& elemId) = 0;
	virtual nlohmann::json GetElementPropertiesByPropertyType(const std::string& elemId, const ArchicadPropertyTypeFilter propertyType) = 0;
	virtual nlohmann::json GetElementBuiltInProperties(const std::string& elemId) = 0;
	virtual nlohmann::json GetElementIfcProperties(const std::string& elemId) = 0;
	// Pre-flattened EAV leaves (see EavLeaf.h) — the nested-json intermediate
	// tree was removed from the send path.
	virtual EavLeaves GetElementProperties(const std::string& elemId) = 0;
	virtual WorkingUnits GetWorkingUnits() = 0;
	virtual ArchicadObject GetArchicadObject(const std::string& elemId, SendConversionResult& conversionResult, bool includeProperties) = 0;
	virtual std::vector<ArchicadObject> GetElementChildren(const std::string& elemId, bool includeProperties) = 0;
	// Drops elements whose hierarchical parent is also in the list — they ship as
	// SUBELEMENT children of that parent instead of duplicating at top level.
	virtual std::vector<std::string> FilterOutHierarchicalChildren(const std::vector<std::string>& elementIds) = 0;
	virtual std::string GetResourceString(short resourceId) = 0;
	virtual std::vector<NavigatorView> GetNavigatorViews() = 0;
	virtual std::vector<LayerData> GetLayers() = 0;
};
