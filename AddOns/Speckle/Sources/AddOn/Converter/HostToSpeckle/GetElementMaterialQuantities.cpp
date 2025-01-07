#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"

namespace
{
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

		quantities["area"] = elementQuantity.wall.surface1;
		quantities["volume"] = elementQuantity.wall.volume;

		if (apiElem.wall.modelElemStructureType == API_BasicStructure)
		{
			quantities["materialName"] = GetBuildingMaterialName(apiElem.wall.buildingMaterial);
			
		}
		else if (apiElem.wall.modelElemStructureType == API_CompositeStructure)
		{
			quantities["materialName"] = GetCompositeMaterialName(apiElem.wall.composite);
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

	default:
		return {};
	}
}
