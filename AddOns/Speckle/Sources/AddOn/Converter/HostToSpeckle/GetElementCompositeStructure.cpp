#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"
#include "WorkingUnits.h"

namespace
{
	struct CompositeQuantity
	{
		std::string materialName = "";
		double volume = 0.0;
		double thickness = 0.0;
	};

	std::string GetBuildingMaterialName(API_AttributeIndex materialId)
	{
		return ConverterUtils::GetAttributeName(materialId, API_BuildingMaterialID);
	}

	void setMask(void* field) 
	{
		*(reinterpret_cast<unsigned char*>(field)) = 0xFF;
	}

	std::vector<double> GetSkinThicknesses(const API_AttributeIndex& compositeIndex)
	{
		std::vector<double> thicknesses;

		API_AttributeDef defs;
		GSErrCode err = ACAPI_Attribute_GetDef(API_CompWallID, compositeIndex, &defs);

		API_Attribute attr;
		BNZeroMemory(&attr, sizeof(attr));
		attr.header.typeID = API_CompWallID;
		attr.header.index = compositeIndex;
		err = ACAPI_Attribute_Get(&attr);

		if (err != NoError)
		{
			return thicknesses;
		}

		for (short j = 0; j < attr.compWall.nComps; j++)
		{
			thicknesses.push_back((*defs.cwall_compItems)[j].fillThick);
		}

		return thicknesses;
	}

	std::vector<CompositeQuantity> GetElementCompositeQuantities(const API_Guid apiGuid)
	{
		API_ElementQuantity quantity{};
		GS::Array <API_CompositeQuantity> compositeQuantities{};
		API_Quantities quantities{};
		API_QuantitiesMask mask{};
		API_QuantityPar params{};

		setMask(&mask.composites.buildMatIndices);
		setMask(&mask.composites.volumes);
		setMask(&mask.composites.projectedArea);

		quantities.elements = &quantity;
		quantities.composites = &compositeQuantities;
		GSErrCode err = ACAPI_Element_GetQuantities(apiGuid, &params, &quantities, &mask);

		if (err != NoError)
		{
			return {};
		}

		std::vector<CompositeQuantity> composites;
		for (const auto& q : compositeQuantities)
		{
			auto mat = GetBuildingMaterialName(q.buildMatIndices);
			composites.push_back({ mat, q.volumes });
		}

		return composites;
	}

	nlohmann::json GetCompositeStructure(const API_Guid& apiGuid, const API_AttributeIndex& compositeIndex)
	{
		auto composites = GetElementCompositeQuantities(apiGuid);
		auto thicknesses = GetSkinThicknesses(compositeIndex);

		nlohmann::json structure;

		int i = 0;
		for (const auto& c : composites)
		{
			// Format index with leading zero and concatenate with material name
			// this is needed to keep the skin order in the viewer
			std::ostringstream oss;
			oss << std::setw(2) << std::setfill('0') << (i + 1) << " - " << c.materialName;
			std::string materialName = oss.str();

			double thickness = (i < thicknesses.size()) ? thicknesses[i] : 0.0;

			structure[materialName]["material"] = c.materialName;
			structure[materialName]["volume"] = c.volume;
			structure[materialName]["thickness"] = thickness;
			structure[materialName]["units"] = "Meter";
			i++;
		}

		return structure;
	}

	nlohmann::json GetWallCompositeStructure(const API_Element& apiElem)
	{
		return apiElem.wall.modelElemStructureType == API_CompositeStructure 
			? GetCompositeStructure(apiElem.header.guid, apiElem.wall.composite) : nlohmann::json{};
	}

	nlohmann::json GetSlabCompositeStructure(const API_Element& apiElem)
	{
		return apiElem.slab.modelElemStructureType == API_CompositeStructure 
			? GetCompositeStructure(apiElem.header.guid, apiElem.slab.composite) : nlohmann::json{};
	}

	nlohmann::json GetRoofCompositeStructure(const API_Element& apiElem)
	{
		return apiElem.roof.shellBase.modelElemStructureType == API_CompositeStructure 
			? GetCompositeStructure(apiElem.header.guid, apiElem.roof.shellBase.composite) : nlohmann::json{};
	}

	nlohmann::json GetShellCompositeStructure(const API_Element& apiElem)
	{
		return apiElem.shell.shellBase.modelElemStructureType == API_CompositeStructure 
			? GetCompositeStructure(apiElem.header.guid, apiElem.shell.shellBase.composite) : nlohmann::json{};
	}
}

nlohmann::json HostToSpeckleConverter::GetElementCompositeStructure(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	WorkingUnits workingUnits = GetWorkingUnits();

	switch (apiElem.header.type.typeID)
	{
	case API_WallID:
		return GetWallCompositeStructure(apiElem);
	case API_SlabID:
		return GetSlabCompositeStructure(apiElem);
	case API_RoofID:
		return GetRoofCompositeStructure(apiElem);
	case API_ShellID:
		return GetShellCompositeStructure(apiElem);

	default:
		return {};
	}
}
