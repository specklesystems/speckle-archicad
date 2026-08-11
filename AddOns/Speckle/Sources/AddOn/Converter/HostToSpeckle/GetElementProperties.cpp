#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ConverterUtils.h"

namespace
{
	constexpr int MAX_DEPTH = 10;

	bool IsScalar(const nlohmann::json& v)
	{
		return v.is_boolean() || v.is_string() || v.is_number();
	}

	// Exact port of the old BundleWriter::WalkProperties, emitting flat leaves
	// instead of re-walking a merged tree later: depth-first, per-level
	// alphabetical key order (nlohmann objects are sorted maps), {name, value}
	// parameter dicts collapsed to one leaf with units/internalDefinitionName,
	// arrays forwarded whole (joined at EAV-write time), nulls and other
	// non-scalars skipped. `depth` counts from the old tree's root so the
	// MAX_DEPTH cap trips at the same nesting level as before.
	void FlattenSubtree(const nlohmann::json& obj, const std::string& prefix, int depth, EavLeaves& out)
	{
		if (depth >= MAX_DEPTH || !obj.is_object())
			return;

		for (auto it = obj.begin(); it != obj.end(); ++it)
		{
			const std::string& key = it.key();
			const nlohmann::json& val = it.value();
			if (val.is_null())
				continue;

			const std::string path = prefix + "." + key;

			if (val.is_object())
			{
				// Parameter pattern { name, value } -> a single leaf at this path.
				if (val.contains("name") && val.contains("value"))
				{
					const nlohmann::json& paramVal = val["value"];
					if (!IsScalar(paramVal))
						continue;
					EavLeaf leaf;
					leaf.path = path;
					leaf.value = paramVal;
					if (val.contains("units") && val["units"].is_string())
						leaf.units = val["units"].get<std::string>();
					if (val.contains("internalDefinitionName") && val["internalDefinitionName"].is_string())
						leaf.internalDefinitionName = val["internalDefinitionName"].get<std::string>();
					out.push_back(std::move(leaf));
					continue;
				}
				FlattenSubtree(val, path, depth + 1, out);
				continue;
			}

			if (IsScalar(val) || val.is_array())
			{
				out.push_back({ path, val, std::nullopt, std::nullopt });
				continue;
			}
			// remaining non-scalars are skipped
		}
	}
}

EavLeaves HostToSpeckleConverter::GetElementProperties(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	EavLeaves leaves;

	auto elemType = apiElem.header.type.typeID;

	std::vector<API_ElemTypeID> systemTypes = { API_WallID, API_SlabID, API_BeamID, API_BeamSegmentID, API_ColumnID, API_ColumnSegmentID, API_RoofID, API_ShellID, API_MorphID };
	bool isSystemType = std::find(systemTypes.begin(), systemTypes.end(), elemType) != systemTypes.end();

	std::vector<API_ElemTypeID> doorWindowStairZoneObject = { API_DoorID, API_WindowID, API_StairID, API_ZoneID, API_ObjectID };
	bool isDoorWindowStairZoneObject = std::find(doorWindowStairZoneObject.begin(), doorWindowStairZoneObject.end(), elemType) != doorWindowStairZoneObject.end();

	std::vector<API_ElemTypeID> compositeTypes = { API_WallID, API_SlabID, API_BeamID, API_RoofID, API_ShellID };
	bool canBeComposite = std::find(compositeTypes.begin(), compositeTypes.end(), elemType) != compositeTypes.end();

	// Subtrees are flattened in the alphabetical top-level-key order the old
	// merged tree iterated in ("Composite Structure" < "Element Properties"
	// {"Classifications" < "Dimensional Properties"} < "IFC Properties" <
	// "Material Quantities" < "User Defined Properties"), with the same start
	// depths, so the emitted rows keep their exact previous order.
	if (canBeComposite)
	{
		nlohmann::json compositeStructure = GetElementCompositeStructure(elemId);
		FlattenSubtree(compositeStructure, "properties.Composite Structure", 1, leaves);
	}

	{
		nlohmann::json classifications = GetElementClassifications(elemId);
		FlattenSubtree(classifications, "properties.Element Properties.Classifications", 2, leaves);
	}

	if (isSystemType || isDoorWindowStairZoneObject)
	{
		nlohmann::json dimensionalProperties = GetElementBuiltInProperties(elemId);
		FlattenSubtree(dimensionalProperties, "properties.Element Properties.Dimensional Properties", 2, leaves);
	}

	{
		nlohmann::json ifcProperties = GetElementIfcProperties(elemId);
		FlattenSubtree(ifcProperties, "properties.IFC Properties", 1, leaves);
	}

	if (isSystemType)
	{
		nlohmann::json materialQuantities = GetElementMaterialQuantities(elemId);
		FlattenSubtree(materialQuantities, "properties.Material Quantities", 1, leaves);
	}

	{
		nlohmann::json userDefinedProperties = GetElementPropertiesByPropertyType(elemId, ArchicadPropertyTypeFilter::UserDefined);
		FlattenSubtree(userDefinedProperties, "properties.User Defined Properties", 1, leaves);
	}

	return leaves;
}
