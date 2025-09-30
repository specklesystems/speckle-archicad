#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ConverterUtils.h"

nlohmann::json HostToSpeckleConverter::GetElementProperties(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	nlohmann::json properties;

	auto elemType = apiElem.header.type.typeID;

	std::vector<API_ElemTypeID> systemTypes = { API_WallID, API_SlabID, API_BeamID, API_BeamSegmentID, API_ColumnID, API_ColumnSegmentID, API_RoofID, API_ShellID, API_MorphID };
	bool isSystemType = std::find(systemTypes.begin(), systemTypes.end(), elemType) != systemTypes.end();

	std::vector<API_ElemTypeID> doorWindowStairZoneObject = { API_DoorID, API_WindowID, API_StairID, API_ZoneID, API_ObjectID };
	bool isDoorWindowStairZoneObject = std::find(doorWindowStairZoneObject.begin(), doorWindowStairZoneObject.end(), elemType) != doorWindowStairZoneObject.end();

	std::vector<API_ElemTypeID> compositeTypes = { API_WallID, API_SlabID, API_BeamID, API_RoofID, API_ShellID };
	bool canBeComposite = std::find(compositeTypes.begin(), compositeTypes.end(), elemType) != compositeTypes.end();

	if (canBeComposite)
	{
		nlohmann::json compositeStructure = GetElementCompositeStructure(elemId);
		if (!compositeStructure.empty())
			properties["Composite Structure"] = compositeStructure;
	}

	if (isSystemType) 
	{
		nlohmann::json materialQuantities = GetElementMaterialQuantities(elemId);
		if (!materialQuantities.empty())
			properties["Material Quantities"] = materialQuantities;
	}

	if (isSystemType || isDoorWindowStairZoneObject)
	{
		nlohmann::json dimensionalProperties = GetElementBuiltInProperties(elemId);
		if (!dimensionalProperties.empty())
			properties["Element Properties"]["Dimensional Properties"] = dimensionalProperties;
	}
	
	nlohmann::json classifications = GetElementClassifications(elemId);
	if (!classifications.empty())
		properties["Element Properties"]["Classifications"] = classifications;

	nlohmann::json userDefinedProperties = GetElementPropertiesByPropertyType(elemId, ArchicadPropertyTypeFilter::UserDefined);
	if (!userDefinedProperties.empty())
		properties["User Defined Properties"] = userDefinedProperties;

	nlohmann::json ifcProperties = GetElementIfcProperties(elemId);
	if (!ifcProperties.empty())
		properties["IFC Properties"] = ifcProperties;

	return properties;
}
