#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"
#include "WorkingUnits.h"

namespace
{
	bool HasMaterialOverride(const API_OverriddenAttribute& material)
	{
#if defined(AC26)
		return material.overridden;
#else
		return material.hasValue;
#endif
	}

	API_AttributeIndex GetMaterialOverrideIndex(const API_OverriddenAttribute& material)
	{
#if defined(AC26)
		return material.attributeIndex;
#else
		return material.value;
#endif
	}

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

	// Quantity values ride as {name, value, units} parameter dicts — the shape the
	// Speckle EAV flattener turns into one typed row with the units column set
	// (matching the Revit connector's Material Quantities convention).
	nlohmann::json MakeQuantityParam(const char* name, double value, const std::string& units)
	{
		return { { "name", name }, { "value", value }, { "units", units } };
	}

	void SetQuantity(nlohmann::json& quantities, const std::string& materialName, double area, double volume, const WorkingUnits& workingUnits)
	{
		quantities[materialName]["area"] = MakeQuantityParam("area", area, workingUnits.calculatedAreaUnits);
		quantities[materialName]["volume"] = MakeQuantityParam("volume", volume, workingUnits.calculatedVolumeUnits);
	}

	void AddSurfaceQuantity(nlohmann::json& quantities, const std::string& materialName, const double area, const WorkingUnits& workingUnits)
	{
		if (quantities.contains(materialName))
		{
			double originalArea = quantities[materialName]["area"]["value"];
			quantities[materialName]["area"]["value"] = originalArea + area;
		}
		else
		{
			quantities[materialName]["area"] = MakeQuantityParam("area", area, workingUnits.calculatedAreaUnits);
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
			SetQuantity(quantities, materialName, totalSurface, elementQuantity.wall.volume, workingUnits);
		}

		if (HasMaterialOverride(apiElem.wall.sidMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.wall.sidMat)), elementQuantity.wall.surface3, workingUnits);
		}

		if (HasMaterialOverride(apiElem.wall.refMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.wall.refMat)), elementQuantity.wall.surface1, workingUnits);
		}

		if (HasMaterialOverride(apiElem.wall.oppMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.wall.oppMat)), elementQuantity.wall.surface2, workingUnits);
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
			SetQuantity(quantities, materialName, totalSurface, elementQuantity.slab.volume, workingUnits);
		}

		if (HasMaterialOverride(apiElem.slab.topMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.slab.topMat)), elementQuantity.slab.topSurface, workingUnits);
		}

		if (HasMaterialOverride(apiElem.slab.botMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.slab.botMat)), elementQuantity.slab.bottomSurface, workingUnits);
		}

		if (HasMaterialOverride(apiElem.slab.sideMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.slab.sideMat)), elementQuantity.slab.edgeSurface, workingUnits);
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
			SetQuantity(quantities, materialName, totalSurface, elementQuantity.beamSegment.volume, workingUnits);
		}

		// this is needed because if the materials have been overridden on the basic structure settings page
		// then the hasValue will return true even if the Beam is set as profiled structure
		if (apiElem.beamSegment.assemblySegmentData.modelElemStructureType == API_BasicStructure)
		{
			if (HasMaterialOverride(apiElem.beamSegment.topMaterial))
			{
				AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.beamSegment.topMaterial)), elementQuantity.beamSegment.topSurface, workingUnits);
			}

			if (HasMaterialOverride(apiElem.beamSegment.bottomMaterial))
			{
				AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.beamSegment.bottomMaterial)), elementQuantity.beamSegment.bottomSurface, workingUnits);
			}

			if (HasMaterialOverride(apiElem.beamSegment.rightMaterial))
			{
				AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.beamSegment.rightMaterial)), elementQuantity.beamSegment.rightSurface, workingUnits);
			}
		}

		if (HasMaterialOverride(apiElem.beamSegment.leftMaterial))
		{
			double leftSurface = elementQuantity.beamSegment.leftSurface;
#if defined(AC27)
			if (apiElem.beamSegment.assemblySegmentData.modelElemStructureType == API_ProfileStructure)
			{
				// AC27 hack to get the extrusion surface
				// in AC 27 only HasMaterialOverride(apiElem.beamSegment.leftMaterial) will be true if we have a profiled structure
				leftSurface = elementQuantity.beamSegment.topSurface + elementQuantity.beamSegment.bottomSurface + elementQuantity.beamSegment.leftSurface + elementQuantity.beamSegment.rightSurface;
			}
#endif
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.beamSegment.leftMaterial)), leftSurface, workingUnits);
		}

		if (HasMaterialOverride(apiElem.beamSegment.endsMaterial))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.beamSegment.endsMaterial)), elementQuantity.beamSegment.endSurface, workingUnits);
		}
#if defined(AC29)
		if (HasMaterialOverride(apiElem.beamSegment.extrusionMaterial))
		{
			double extrusionSurface = elementQuantity.beamSegment.topSurface + elementQuantity.beamSegment.bottomSurface + elementQuantity.beamSegment.leftSurface + elementQuantity.beamSegment.rightSurface;
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.beamSegment.extrusionMaterial)), extrusionSurface, workingUnits);
		}
#endif

#if defined(AC28)
		if (HasMaterialOverride(apiElem.beamSegment.extrusionMaterial))
		{
			double extrusionSurface = elementQuantity.beamSegment.topSurface + elementQuantity.beamSegment.bottomSurface + elementQuantity.beamSegment.leftSurface + elementQuantity.beamSegment.rightSurface;
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.beamSegment.extrusionMaterial)), extrusionSurface, workingUnits);
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
			SetQuantity(quantities, materialName, sideSurface + topAndBottomSurface, volume, workingUnits);
		}

		if (HasMaterialOverride(apiElem.columnSegment.extrusionSurfaceMaterial))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.columnSegment.extrusionSurfaceMaterial)), sideSurface, workingUnits);
		}

		if (HasMaterialOverride(apiElem.columnSegment.endsMaterial))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.columnSegment.endsMaterial)), topAndBottomSurface, workingUnits);
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
			SetQuantity(quantities, materialName, elementQuantity.roof.contourArea, elementQuantity.roof.volume, workingUnits);
		}

		if (HasMaterialOverride(apiElem.roof.shellBase.topMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.roof.shellBase.topMat)), elementQuantity.roof.topSurface, workingUnits);
		}

		if (HasMaterialOverride(apiElem.roof.shellBase.botMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.roof.shellBase.botMat)), elementQuantity.roof.bottomSurface, workingUnits);
		}

		if (HasMaterialOverride(apiElem.roof.shellBase.sidMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.roof.shellBase.sidMat)), elementQuantity.roof.edgeSurface, workingUnits);
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
			SetQuantity(quantities, materialName, elementQuantity.shell.floorplanArea, elementQuantity.shell.volume, workingUnits);
		}

		if (HasMaterialOverride(apiElem.shell.shellBase.topMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.shell.shellBase.topMat)), elementQuantity.shell.grossOppositeSurf, workingUnits);
		}

		if (HasMaterialOverride(apiElem.shell.shellBase.botMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.shell.shellBase.botMat)), elementQuantity.shell.grossReferenceSurf, workingUnits);
		}

		if (HasMaterialOverride(apiElem.shell.shellBase.sidMat))
		{
			AddSurfaceQuantity(quantities, GetMaterialName(GetMaterialOverrideIndex(apiElem.shell.shellBase.sidMat)), elementQuantity.shell.grossEdgeSurf, workingUnits);
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
			SetQuantity(quantities, materialName, elementQuantity.morph.floorPlanArea, elementQuantity.morph.volume, workingUnits);
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
