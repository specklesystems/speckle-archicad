#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"
#include "WorkingUnits.h"

namespace
{
	// TODO: move this to converter utils
	std::string GetAttributeName(API_AttributeIndex attributeIndex, API_AttrTypeID attributeType)
	{
		API_Attribute attr;
		BNZeroMemory(&attr, sizeof(attr));
		attr.header.typeID = attributeType;
		attr.header.index = attributeIndex;
		ACAPI_Attribute_Get(&attr);

		return attr.header.name;
	}

	std::string GetMaterialName(API_AttributeIndex materialId)
	{
		return GetAttributeName(materialId, API_MaterialID);
	}

	std::string GetBuildingMaterialName(API_AttributeIndex materialId)
	{
		return GetAttributeName(materialId, API_BuildingMaterialID);
	}

	std::string GetCompositeMaterialName(API_AttributeIndex materialId)
	{
		return GetAttributeName(materialId, API_CompWallID);
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

	nlohmann::json GetWallQuantity(const API_Element& apiElem, const WorkingUnits& workingUnits)
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
			double totalSurface = elementQuantity.wall.surface1 + elementQuantity.wall.surface2 + elementQuantity.wall.surface3;
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = elementQuantity.wall.volume;
			quantities[materialName]["area"] = totalSurface;
			// TODO this is centimeters while area is square meters and volume is cubic meters
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.wall.sidMat.hasValue)
		{
			std::string sideMatName = GetMaterialName(apiElem.wall.sidMat.value);
			quantities[sideMatName]["materialName"] = sideMatName;
			quantities[sideMatName]["area"] = elementQuantity.wall.surface3;
			quantities[sideMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.wall.refMat.hasValue)
		{
			std::string refMatName = GetMaterialName(apiElem.wall.refMat.value);
			quantities[refMatName]["materialName"] = refMatName;
			quantities[refMatName]["area"] = elementQuantity.wall.surface1;
			quantities[refMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.wall.oppMat.hasValue)
		{
			std::string oppMatName = GetMaterialName(apiElem.wall.oppMat.value);
			quantities[oppMatName]["materialName"] = oppMatName;
			quantities[oppMatName]["area"] = elementQuantity.wall.surface2;
			quantities[oppMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		return quantities;
	}

	nlohmann::json GetSlabQuantity(const API_Element& apiElem, const WorkingUnits& workingUnits)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;
		std::string materialName = "";

		if (apiElem.slab.modelElemStructureType == API_BasicStructure)
		{
			materialName = GetBuildingMaterialName(apiElem.slab.buildingMaterial);
		}
		else if (apiElem.slab.modelElemStructureType == API_CompositeStructure)
		{
			materialName = GetCompositeMaterialName(apiElem.slab.composite);
		}

		if (!materialName.empty())
		{
			double totalSurface = elementQuantity.slab.bottomSurface + elementQuantity.slab.topSurface + elementQuantity.slab.edgeSurface;
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = elementQuantity.slab.volume;
			quantities[materialName]["area"] = totalSurface;
			// TODO this is centimeters while area is square meters and volume is cubic meters
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.slab.topMat.hasValue)
		{
			std::string topMatName = GetMaterialName(apiElem.slab.topMat.value);
			quantities[topMatName]["materialName"] = topMatName;
			quantities[topMatName]["area"] = elementQuantity.slab.topSurface;
			quantities[topMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.slab.botMat.hasValue)
		{
			std::string bottomMatName = GetMaterialName(apiElem.slab.botMat.value);
			quantities[bottomMatName]["materialName"] = bottomMatName;
			quantities[bottomMatName]["area"] = elementQuantity.slab.bottomSurface;
			quantities[bottomMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.slab.sideMat.hasValue)
		{
			std::string sideMatName = GetMaterialName(apiElem.slab.sideMat.value);
			quantities[sideMatName]["materialName"] = sideMatName;
			quantities[sideMatName]["area"] = elementQuantity.slab.edgeSurface;
			quantities[sideMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		return quantities;
	}

	nlohmann::json GetBeamQuantity(const API_Element& /*apiElem*/, const WorkingUnits& /*workingUnits*/)
	{
		// TODO: change this when we export beams as segmented elements
		return {};
	}

	nlohmann::json GetColumnQuantity(const API_Element& /*apiElem*/, const WorkingUnits& /*workingUnits*/)
	{
		// TODO: change this when we export beams as segmented elements
		return {};
	}

	nlohmann::json GetRoofQuantity(const API_Element& apiElem, const WorkingUnits& workingUnits)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;
		std::string materialName = "";

		if (apiElem.roof.shellBase.modelElemStructureType == API_BasicStructure)
		{
			materialName = GetBuildingMaterialName(apiElem.roof.shellBase.buildingMaterial);
		}
		else if (apiElem.roof.shellBase.modelElemStructureType == API_CompositeStructure)
		{
			materialName = GetCompositeMaterialName(apiElem.roof.shellBase.composite);
		}

		if (!materialName.empty())
		{
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = elementQuantity.roof.volume;
			quantities[materialName]["area"] = elementQuantity.roof.contourArea;
			// TODO this is centimeters while area is square meters and volume is cubic meters
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.roof.shellBase.topMat.hasValue)
		{
			std::string topMatName = GetMaterialName(apiElem.roof.shellBase.topMat.value);
			quantities[topMatName]["materialName"] = topMatName;
			quantities[topMatName]["area"] = elementQuantity.roof.topSurface;
			quantities[topMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.roof.shellBase.botMat.hasValue)
		{
			std::string bottomMatName = GetMaterialName(apiElem.roof.shellBase.botMat.value);
			quantities[bottomMatName]["materialName"] = bottomMatName;
			quantities[bottomMatName]["area"] = elementQuantity.roof.bottomSurface;
			quantities[bottomMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.roof.shellBase.sidMat.hasValue)
		{
			std::string sideMatName = GetMaterialName(apiElem.roof.shellBase.sidMat.value);
			quantities[sideMatName]["materialName"] = sideMatName;
			quantities[sideMatName]["area"] = elementQuantity.roof.edgeSurface;
			quantities[sideMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		return quantities;
	}

	nlohmann::json GetShellQuantity(const API_Element& apiElem, const WorkingUnits& workingUnits)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;
		std::string materialName = "";

		if (apiElem.shell.shellBase.modelElemStructureType == API_BasicStructure)
		{
			materialName = GetBuildingMaterialName(apiElem.shell.shellBase.buildingMaterial);
		}
		else if (apiElem.shell.shellBase.modelElemStructureType == API_CompositeStructure)
		{
			materialName = GetCompositeMaterialName(apiElem.shell.shellBase.composite);
		}

		if (!materialName.empty())
		{
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = elementQuantity.shell.volume;
			quantities[materialName]["area"] = elementQuantity.shell.floorplanArea;
			// TODO this is centimeters while area is square meters and volume is cubic meters
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.shell.shellBase.topMat.hasValue)
		{
			std::string topMatName = GetMaterialName(apiElem.shell.shellBase.topMat.value);
			quantities[topMatName]["materialName"] = topMatName;
			quantities[topMatName]["area"] = elementQuantity.shell.grossOppositeSurf;
			quantities[topMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.shell.shellBase.botMat.hasValue)
		{
			std::string bottomMatName = GetMaterialName(apiElem.shell.shellBase.botMat.value);
			quantities[bottomMatName]["materialName"] = bottomMatName;
			quantities[bottomMatName]["area"] = elementQuantity.shell.grossReferenceSurf;
			quantities[bottomMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.shell.shellBase.sidMat.hasValue)
		{
			std::string sideMatName = GetMaterialName(apiElem.shell.shellBase.sidMat.value);
			quantities[sideMatName]["materialName"] = sideMatName;
			quantities[sideMatName]["area"] = elementQuantity.shell.grossEdgeSurf;
			quantities[sideMatName]["units"] = workingUnits.calculatedAreaUnits;
		}

		return quantities;
	}

	nlohmann::json GetMorphQuantity(const API_Element& apiElem, const WorkingUnits& workingUnits)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;
		std::string materialName = GetBuildingMaterialName(apiElem.shell.shellBase.buildingMaterial);

		if (!materialName.empty())
		{
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = elementQuantity.morph.volume;
			quantities[materialName]["area"] = elementQuantity.morph.floorPlanArea;
			// TODO this is centimeters while area is square meters and volume is cubic meters
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		return quantities;
	}
}

nlohmann::json HostToSpeckleConverter::GetElementMaterialQuantities(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	WorkingUnits workingUnits = GetWorkingUnits();

	switch (apiElem.header.type.typeID)
	{
	case API_WallID:
		return GetWallQuantity(apiElem, workingUnits);
	case API_SlabID:
		return GetSlabQuantity(apiElem, workingUnits);
	case API_BeamID:
		return GetBeamQuantity(apiElem, workingUnits);
	case API_ColumnID:
		return GetColumnQuantity(apiElem, workingUnits);
	case API_RoofID:
		return GetRoofQuantity(apiElem, workingUnits);
	case API_ShellID:
		return GetShellQuantity(apiElem, workingUnits);
	case API_MorphID:
		return GetMorphQuantity(apiElem, workingUnits);

	default:
		return {};
	}
}
