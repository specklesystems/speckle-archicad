#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"
#include "WorkingUnits.h"

namespace
{
	std::string GetMaterialName(API_AttributeIndex materialId)
	{
		return ConverterUtils::GetAttributeName(materialId, API_MaterialID);
	}

	std::string GetBuildingMaterialName(API_AttributeIndex materialId)
	{
		return ConverterUtils::GetAttributeName(materialId, API_BuildingMaterialID);
	}

	std::string GetCompositeMaterialName(API_AttributeIndex materialId)
	{
		return ConverterUtils::GetAttributeName(materialId, API_CompWallID);
	}

	std::string GetProfileName(API_AttributeIndex materialId)
	{
		return ConverterUtils::GetAttributeName(materialId, API_ProfileID);
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
		{
			throw SpeckleConversionException("Could not get Element Quantities");
		}

		return quantity;
	}

	void AddSurfaceQuantity(nlohmann::json& quantities, const std::string& materialName, const double area, const WorkingUnits& workingUnits)
	{
		if (quantities.contains(materialName))
		{
			double originalArea = quantities[materialName]["area"];
			quantities[materialName]["area"] = originalArea + area;
		}
		else
		{
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["area"] = area;
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}
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
		else if (apiElem.wall.modelElemStructureType == API_ProfileStructure)
		{
			materialName = GetCompositeMaterialName(apiElem.wall.profileAttr);
		}

		if (!materialName.empty())
		{
			double totalSurface = elementQuantity.wall.surface1 + elementQuantity.wall.surface2 + elementQuantity.wall.surface3;
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = elementQuantity.wall.volume;
			quantities[materialName]["area"] = totalSurface;
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.wall.sidMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.wall.sidMat.value), elementQuantity.wall.surface3, workingUnits);
		}

		if (apiElem.wall.refMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.wall.refMat.value), elementQuantity.wall.surface1, workingUnits);
		}

		if (apiElem.wall.oppMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.wall.oppMat.value), elementQuantity.wall.surface2, workingUnits);
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
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.slab.topMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.slab.topMat.value), elementQuantity.slab.topSurface, workingUnits);
		}

		if (apiElem.slab.botMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.slab.botMat.value), elementQuantity.slab.bottomSurface, workingUnits);
		}

		if (apiElem.slab.sideMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.slab.sideMat.value), elementQuantity.slab.edgeSurface, workingUnits);
		}

		return quantities;
	}

	nlohmann::json GetBeamSegmentQuantity(const API_Element& apiElem, const WorkingUnits& workingUnits)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;
		std::string materialName = "";

		if (apiElem.beamSegment.assemblySegmentData.modelElemStructureType == API_BasicStructure)
		{
			materialName = GetBuildingMaterialName(apiElem.beamSegment.assemblySegmentData.buildingMaterial);
		}
		else if (apiElem.beamSegment.assemblySegmentData.modelElemStructureType == API_ProfileStructure)
		{
			materialName = GetProfileName(apiElem.beamSegment.assemblySegmentData.profileAttr);
		}

		if (!materialName.empty())
		{
			double totalSurface = elementQuantity.beamSegment.bottomSurface + elementQuantity.beamSegment.topSurface + elementQuantity.beamSegment.leftSurface + elementQuantity.beamSegment.rightSurface + elementQuantity.beamSegment.endSurface;
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = elementQuantity.beamSegment.volume;
			quantities[materialName]["area"] = totalSurface;
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		// this is needed because if the materials have been overridden on the basic structure settings page
		// then the hasValue will return true even if the Beam is set as profiled structure
		if (apiElem.beamSegment.assemblySegmentData.modelElemStructureType == API_BasicStructure)
		{
			if (apiElem.beamSegment.topMaterial.hasValue)
			{
				AddSurfaceQuantity(quantities, GetMaterialName(apiElem.beamSegment.topMaterial.value), elementQuantity.beamSegment.topSurface, workingUnits);
			}

			if (apiElem.beamSegment.bottomMaterial.hasValue)
			{
				AddSurfaceQuantity(quantities, GetMaterialName(apiElem.beamSegment.bottomMaterial.value), elementQuantity.beamSegment.bottomSurface, workingUnits);
			}

			if (apiElem.beamSegment.rightMaterial.hasValue)
			{
				AddSurfaceQuantity(quantities, GetMaterialName(apiElem.beamSegment.rightMaterial.value), elementQuantity.beamSegment.rightSurface, workingUnits);
			}
		}

		if (apiElem.beamSegment.leftMaterial.hasValue)
		{
			double leftSurface = elementQuantity.beamSegment.leftSurface;
#if defined(AC27)
			if (apiElem.beamSegment.assemblySegmentData.modelElemStructureType == API_ProfileStructure)
			{
				// AC27 hack to get the extrusion surface
				// in AC 27 only apiElem.beamSegment.leftMaterial.hasValue will be true if we have a profiled structure
				leftSurface = elementQuantity.beamSegment.topSurface + elementQuantity.beamSegment.bottomSurface + elementQuantity.beamSegment.leftSurface + elementQuantity.beamSegment.rightSurface;
			}
#endif
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.beamSegment.leftMaterial.value), leftSurface, workingUnits);
		}

		if (apiElem.beamSegment.endsMaterial.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.beamSegment.endsMaterial.value), elementQuantity.beamSegment.endSurface, workingUnits);
		}
#if defined(AC28)
		if (apiElem.beamSegment.extrusionMaterial.hasValue)
		{
			double extrusionSurface = elementQuantity.beamSegment.topSurface + elementQuantity.beamSegment.bottomSurface + elementQuantity.beamSegment.leftSurface + elementQuantity.beamSegment.rightSurface;
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.beamSegment.extrusionMaterial.value), extrusionSurface, workingUnits);
		}
#endif

		return quantities;
	}

	nlohmann::json GetColumnSegmentQuantity(const API_Element& apiElem, const WorkingUnits& workingUnits)
	{
		auto elementQuantity = GetElementQuantity(apiElem.header.guid);
		nlohmann::json quantities;
		std::string materialName = "";

		double sideSurface = 0.0;
		if (apiElem.columnSegment.venThick > 0.001)
		{
			sideSurface = elementQuantity.columnSegment.veneerSideSurface;
		}
		else
		{
			sideSurface = elementQuantity.columnSegment.coreGrossSurface;
		}

		double topAndBottomSurface = elementQuantity.columnSegment.coreGrossBottomSurface + elementQuantity.columnSegment.coreGrossTopSurface;
		if (apiElem.columnSegment.venThick > 0.001)
		{
			topAndBottomSurface += (elementQuantity.columnSegment.veneerGrossBottomSurface + elementQuantity.columnSegment.veneerGrossTopSurface);
		}

		double volume = elementQuantity.columnSegment.coreGrossVolume;
		if (apiElem.columnSegment.venThick > 0.001)
		{
			volume += elementQuantity.columnSegment.veneerGrossVolume;
		}

		if (apiElem.columnSegment.assemblySegmentData.modelElemStructureType == API_BasicStructure)
		{
			materialName = GetBuildingMaterialName(apiElem.columnSegment.assemblySegmentData.buildingMaterial);
		}
		else if (apiElem.columnSegment.assemblySegmentData.modelElemStructureType == API_ProfileStructure)
		{
			materialName = GetProfileName(apiElem.columnSegment.assemblySegmentData.profileAttr);
		}

		if (!materialName.empty())
		{
			quantities[materialName]["materialName"] = materialName;
			quantities[materialName]["volume"] = volume;
			quantities[materialName]["area"] = (sideSurface + topAndBottomSurface);
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.columnSegment.extrusionSurfaceMaterial.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.columnSegment.extrusionSurfaceMaterial.value), sideSurface, workingUnits);
		}

		if (apiElem.columnSegment.endsMaterial.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.columnSegment.endsMaterial.value), topAndBottomSurface, workingUnits);
		}

		return quantities;
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
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.roof.shellBase.topMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.roof.shellBase.topMat.value), elementQuantity.roof.topSurface, workingUnits);
		}

		if (apiElem.roof.shellBase.botMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.roof.shellBase.botMat.value), elementQuantity.roof.bottomSurface, workingUnits);
		}

		if (apiElem.roof.shellBase.sidMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.roof.shellBase.sidMat.value), elementQuantity.roof.edgeSurface, workingUnits);
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
			quantities[materialName]["units"] = workingUnits.calculatedAreaUnits;
		}

		if (apiElem.shell.shellBase.topMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.shell.shellBase.topMat.value), elementQuantity.shell.grossOppositeSurf, workingUnits);
		}

		if (apiElem.shell.shellBase.botMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.shell.shellBase.botMat.value), elementQuantity.shell.grossReferenceSurf, workingUnits);
		}

		if (apiElem.shell.shellBase.sidMat.hasValue)
		{
			AddSurfaceQuantity(quantities, GetMaterialName(apiElem.shell.shellBase.sidMat.value), elementQuantity.shell.grossEdgeSurf, workingUnits);
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
	case API_BeamSegmentID:
		return GetBeamSegmentQuantity(apiElem, workingUnits);
	case API_ColumnSegmentID:
		return GetColumnSegmentQuantity(apiElem, workingUnits);
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
