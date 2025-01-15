#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"

namespace
{
	std::string GetMaterialName(API_AttributeIndex materialId)
	{
		API_Attribute attr;
		BNZeroMemory(&attr, sizeof(attr));
		attr.header.typeID = API_MaterialID;
		attr.header.index = materialId;
		ACAPI_Attribute_Get(&attr);

		return attr.header.name;
	}

	std::string GetBuildingMaterialName(API_AttributeIndex materialId)
	{
		API_Attribute attr;
		BNZeroMemory(&attr, sizeof(attr));
		attr.header.typeID = API_BuildingMaterialID;
		attr.header.index = materialId;
		ACAPI_Attribute_Get(&attr);

		return attr.header.name;
	}

	std::string GetCompositeMaterialName(API_AttributeIndex materialId)
	{
		API_Attribute attr;
		BNZeroMemory(&attr, sizeof(attr));
		attr.header.typeID = API_CompWallID;
		attr.header.index = materialId;
		ACAPI_Attribute_Get(&attr);

		return attr.header.name;
	}

	std::string GetWorkingUnits()
	{
		API_WorkingUnitPrefs prefs{};
		ACAPI_ProjectSetting_GetPreferences(&prefs, APIPrefs_WorkingUnitsID);

		if (prefs.lengthUnit == API_LengthTypeID::Meter)
		{
			return "m";
		}
		else
		{
			return "m";
		}
	}

	API_ElementQuantity GetElementQuantity(const API_Guid apiGuid)
	{
		API_ElementQuantity quantity{};
		API_Quantities quantities{};
		API_QuantitiesMask mask{};
		API_QuantityPar params{};

		ACAPI_ELEMENT_QUANTITY_MASK_SETFULL(mask);

		quantities.elements = &quantity;
		GSErrCode error = ACAPI_Element_GetQuantities(apiGuid, &params, &quantities, &mask);

		if (error)
			throw SpeckleConversionException("Could not get Element Quantities");

		return quantity;
	}

	nlohmann::json GetWallQuantity(const API_Element& apiElem)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;

		std::string materialName = "";

		if (apiElem.wall.modelElemStructureType == API_BasicStructure)
		{
			materialName = GetBuildingMaterialName(apiElem.wall.buildingMaterial);

		}
		else if (apiElem.wall.modelElemStructureType == API_CompositeStructure)
		{
			materialName = GetCompositeMaterialName(apiElem.wall.composite);
		}

		if (!materialName.empty())
		{
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = elementQuantity.wall.volume;
			quantities[materialName]["area"] = elementQuantity.wall.area;
			quantities[materialName]["units"] = "m";
		}

		if (apiElem.wall.sidMat.hasValue)
		{
			std::string sideMatName = GetMaterialName(apiElem.wall.sidMat.value);
			quantities[sideMatName]["materialName"] = sideMatName;
			quantities[sideMatName]["area"] = elementQuantity.wall.surface3;
			quantities[sideMatName]["units"] = "m";
		}

		if (apiElem.wall.refMat.hasValue)
		{
			std::string refMatName = GetMaterialName(apiElem.wall.refMat.value);
			quantities[refMatName]["materialName"] = refMatName;
			quantities[refMatName]["area"] = elementQuantity.wall.surface1;
			quantities[refMatName]["units"] = "m";
		}

		if (apiElem.wall.oppMat.hasValue)
		{
			std::string oppMatName = GetMaterialName(apiElem.wall.oppMat.value);
			quantities[oppMatName]["materialName"] = oppMatName;
			quantities[oppMatName]["area"] = elementQuantity.wall.surface2;
			quantities[oppMatName]["units"] = "m";
		}

		return quantities;
	}

	nlohmann::json GetSlabQuantity(const API_Element& apiElem)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;

		quantities["area"] = elementQuantity.slab.bottomSurface;
		quantities["volume"] = elementQuantity.slab.volume;

		if (apiElem.slab.modelElemStructureType == API_BasicStructure)
		{
			quantities["materialName"] = GetBuildingMaterialName(apiElem.slab.buildingMaterial);

		}
		else if (apiElem.slab.modelElemStructureType == API_CompositeStructure)
		{
			quantities["materialName"] = GetCompositeMaterialName(apiElem.slab.composite);
		}

		return quantities;
	}

	// TODO: change this when we export beams as segmented elements
	nlohmann::json GetBeamQuantity(const API_Element& apiElem)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;

		//quantities["area"] = (elementQuantity.beam.bottomSurface + elementQuantity.beam.topSurface + elementQuantity.beam.edgeSurface);
		quantities["area"] = elementQuantity.beam.area;
		quantities["volume"] = elementQuantity.beam.volume;

		return quantities;
	}

	// TODO: change this when we export columns as segmented elements
	nlohmann::json GetColumnQuantity(const API_Element& apiElem)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;

		quantities["area"] = elementQuantity.column.coreSurface;
		quantities["volume"] = (elementQuantity.column.coreGrossVolume + elementQuantity.column.veneGrossVolume);

		return quantities;
	}

	nlohmann::json GetRoofQuantity(const API_Element& apiElem)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;

		quantities["area"] = elementQuantity.roof.contourArea;
		quantities["volume"] = elementQuantity.roof.volume;

		return quantities;
	}

	nlohmann::json GetShellQuantity(const API_Element& apiElem)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;

		quantities["area"] = elementQuantity.shell.floorplanArea;
		quantities["volume"] = elementQuantity.shell.volume;

		if (apiElem.shell.shellBase.modelElemStructureType == API_BasicStructure)
		{
			quantities["materialName"] = GetBuildingMaterialName(apiElem.shell.shellBase.buildingMaterial);

		}
		else if (apiElem.shell.shellBase.modelElemStructureType == API_CompositeStructure)
		{
			quantities["materialName"] = GetCompositeMaterialName(apiElem.shell.shellBase.composite);
		}

		return quantities;
	}

	nlohmann::json GetMorphQuantity(const API_Element& apiElem)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;

		quantities["area"] = elementQuantity.morph.floorPlanArea;
		quantities["volume"] = elementQuantity.morph.volume;

		quantities["materialName"] = GetBuildingMaterialName(apiElem.morph.buildingMaterial);

		return quantities;
	}
}

nlohmann::json HostToSpeckleConverter::GetElementMaterialQuantities(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);

	switch (apiElem.header.type.typeID)
	{
	case API_WallID:
		return GetWallQuantity(apiElem);
	case API_SlabID:
		return GetSlabQuantity(apiElem);
	case API_BeamID:
		return GetBeamQuantity(apiElem);
	case API_ColumnID:
		return GetColumnQuantity(apiElem);
	case API_RoofID:
		return GetRoofQuantity(apiElem);
	case API_ShellID:
		return GetShellQuantity(apiElem);
	case API_MorphID:
		return GetMorphQuantity(apiElem);

	default:
		return {};
	}
}
