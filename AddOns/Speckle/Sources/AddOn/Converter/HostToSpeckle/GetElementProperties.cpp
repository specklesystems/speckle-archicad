#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"

#include <iostream>

static const std::vector<std::string> generalRatingsPropertyFilter = 
{
	"E480E81E-EDE3-43FC-9C52-B55A4CA1A85C", // Fire Resistance Rating
	"13A61253-66A9-4494-9393-9E8F2E19D55E"  // Combustible
};

static const std::vector<std::string> ifcPropertyFilter =
{
	"3B402C48-23D3-4A04-8BDF-E63E81318DAE", // External IFC ID
	"84A027A9-F2F1-40B4-A900-70A422B10829"  // Archicad IFC ID
};

static const std::vector<std::string> dimensionalPropertyFilter =
{
	// Wall
	"C1C47616-2BDD-49BF-92FB-CAC1206BF171", // Wall Height (Archicad 20)
	"41D36190-E3B6-4504-BF4F-1B7EBD02CBA2", // Wall Width (Archicad 20)
	"57597878-A6E8-4D43-BF52-CB4E157DBFE4", // Average length of the Wall

	// Slab
	"A40FD114-CDA3-4554-8831-29FF73151153", // Surface Area of the Slab Top (Gross)
	"AD5116E3-95D9-42E3-A41A-D7155ADF0C5F", // Slab Perimeter (Archicad 21)
	"A824A045-80D7-4E3D-82A8-C82BD15EF0E5", // Slab Thickness (Archicad 20)

	// Beam
	"DADCDFC6-3AFF-415B-98ED-FDF9EF4B1807", // Beam Height (Archicad 20)
	"D8707463-22C1-412B-8146-AD7DCEF17E49", // Beam Width (Archicad 20)
	"BA0E29BD-A795-4A93-A33F-C2C17B46C33A", // 3D Length
	"CCC9ED1E-32D6-410C-9928-EF4C629AFAFB", // Beam Slant Angle

	// Column
	"2E32E96D-6220-4AE2-86C2-FEDB45450DC2", // Column Core Width
	"C9D4DA15-A7A7-4B5D-8E48-854F3D2A7053", // Column Core Height / Diameter
	"F4FEE28D-16B9-4801-B2F2-672CCCD872B0", // Column Length (Archicad 21)
	"7EDA68CA-D646-4180-B840-4327181C3E62", // Profile Height
	"A69ECF2A-DFEE-4B64-A1CF-C562F57FB503", // Profile Width
	"98E22B3A-C663-4249-8D85-BC5C4F32D487", // Veneer Thickness

	// Roof
	"544ED0A0-0C04-4DCA-9F9A-82871C34C03E", // Surface Area of the Roof Bottom (Conditional)
	"D39090EB-5A07-4E2E-8521-FA60E8907592", // Surface Area of the Roof Top (Conditional)
	"48706EB0-152A-47A0-8963-AD00AA7CC11D", // Thickness
	"C4B62357-1289-4D43-A3F6-AB02B192864C", // Height
	"5BF6931F-82EB-40B8-B184-F51D20EC9D17", // Elevation to Project Zero

	// Stair
	"F914EBCF-B012-4DDC-976A-5BFFB5BD301A", // Default Going Depth
	"CD511852-FB66-426B-AC5B-DDAC12817792", // Default Riser Height
	"1C31D9CE-273B-4868-A891-103DC24FE7C8", // Default Riser Slant Angle
	"55F9F389-C7CF-4661-B603-5B3A0591CB21", // Default Stair Width
	"8EC256D5-C747-4778-A4BF-99047C25F4AF", // Required Headroom Height
	"4FFCB82F-1D60-4262-85B9-EC6FEC785D40", // Number Of Risers (total)
	"1108D4D8-BDFB-491D-B527-C1779EE03209", // Number Of Treads (total)
	"C58C7FC2-CBFC-4998-93D1-0A40A0D0681E"  // Walking Line Length
};

namespace
{
	const std::vector<std::string> GetPropertyFilter(const PropertyFilter filter)
	{
		switch (filter)
		{
		case PropertyFilter::GeneralRatings:
			return generalRatingsPropertyFilter;
		case PropertyFilter::IFC:
			return ifcPropertyFilter;
		case PropertyFilter::Dimensional:
			return dimensionalPropertyFilter;

		default:
			return {};
		}
	}

	std::string bool_to_string(bool b)
	{
		return b ? "True" : "False";
	}

	std::string GetSingleCollectionTypePropertyValue(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));
		std::string propertyValue = "";

		switch (propertyDefinition.valueType)
		{
		case API_PropertyStringValueType:
			propertyValue = prop.value.singleVariant.variant.uniStringValue.ToCStr().Get();
			break;
		case API_PropertyIntegerValueType:
			propertyValue = std::to_string(prop.value.singleVariant.variant.intValue);
			break;
		case API_PropertyRealValueType:
			propertyValue = std::to_string(prop.value.singleVariant.variant.doubleValue);
			break;
		case API_PropertyBooleanValueType:
			propertyValue = bool_to_string(prop.value.singleVariant.variant.boolValue);
			break;

		default:
			throw SpeckleConversionException("Invalid property value type");
		}

		if (propertyValue.empty())
			throw SpeckleConversionException("Property value was empty");

		return propertyValue;
	}

	std::vector<std::string> GetListCollectionTypePropertyValue(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));
		std::vector<std::string> propertyValues;

		auto variants = prop.value.listVariant.variants;

		for (const auto& variant : variants)
		{
			switch (propertyDefinition.valueType)
			{
			case API_PropertyStringValueType:
				propertyValues.push_back(variant.uniStringValue.ToCStr().Get());
				break;
			case API_PropertyIntegerValueType:
				propertyValues.push_back(std::to_string(variant.intValue));
				break;
			case API_PropertyRealValueType:
				propertyValues.push_back(std::to_string(variant.doubleValue));
				break;
			case API_PropertyBooleanValueType:
				propertyValues.push_back(bool_to_string(variant.boolValue));
				break;

			default:
				continue;
			}
		}

		if (propertyValues.empty())
			throw SpeckleConversionException("Property value was empty");

		return propertyValues;
	}

	std::string GetSingleChoiceEnumerationCollectionTypePropertyValue(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));
		std::string propertyValue = "";

		auto selectedValueGuid = prop.value.singleVariant.variant.guidValue;
		for (const auto& variant : propertyDefinition.possibleEnumValues)
		{
			if (variant.keyVariant.guidValue == selectedValueGuid)
			{
				switch (propertyDefinition.valueType)
				{
				case API_PropertyStringValueType:
					propertyValue = variant.displayVariant.uniStringValue.ToCStr().Get();
					break;
				case API_PropertyIntegerValueType:
					propertyValue = std::to_string(variant.displayVariant.intValue);
					break;
				case API_PropertyRealValueType:
					propertyValue = std::to_string(variant.displayVariant.doubleValue);
					break;
				case API_PropertyBooleanValueType:
					propertyValue = bool_to_string(variant.displayVariant.boolValue);
					break;

				default:
					throw SpeckleConversionException("Invalid property value type");
				}

				break;
			}
		}

		if (propertyValue.empty())
			throw SpeckleConversionException("Property value was empty");

		return propertyValue;
	}

	std::vector<std::string> GetMultipleChoiceEnumerationCollectionTypePropertyValue(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));
		std::vector<std::string> propertyValues;
		auto variants = prop.value.listVariant.variants;

		for (const auto& variant : propertyDefinition.possibleEnumValues)
		{
			for (const auto& selectedVariant : variants)
			{
				if (variant.keyVariant.guidValue == selectedVariant.guidValue)
				{
					switch (propertyDefinition.valueType)
					{
					case API_PropertyStringValueType:
						propertyValues.push_back(variant.displayVariant.uniStringValue.ToCStr().Get());
						break;
					case API_PropertyIntegerValueType:
						propertyValues.push_back(std::to_string(variant.displayVariant.intValue));
						break;
					case API_PropertyRealValueType:
						propertyValues.push_back(std::to_string(variant.displayVariant.doubleValue));
						break;
					case API_PropertyBooleanValueType:
						propertyValues.push_back(bool_to_string(variant.displayVariant.boolValue));
						break;

					default:
						continue;
					}
				}
			}
		}

		if (propertyValues.empty())
			throw SpeckleConversionException("Property value was empty");

		return propertyValues;
	}

	std::string GetPropertyName(const API_PropertyDefinition& propertyDefinition)
	{
		return propertyDefinition.name.ToCStr().Get();
	}

	std::string GetPropertyGroupName(const API_PropertyDefinition& propertyDefinition)
	{
		API_PropertyGroup group;
		group.guid = propertyDefinition.groupGuid;
		CHECK_ERROR(ACAPI_Property_GetPropertyGroup(group));
		return group.name.ToCStr().Get();
	}

	nlohmann::json GetElementPropertyValueAsJson(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		switch (propertyDefinition.collectionType)
		{
		case API_PropertySingleCollectionType:
			return GetSingleCollectionTypePropertyValue(elemId, propertyDefinition);
		case API_PropertyListCollectionType:
			return GetListCollectionTypePropertyValue(elemId, propertyDefinition);
		case API_PropertySingleChoiceEnumerationCollectionType:
			return GetSingleChoiceEnumerationCollectionTypePropertyValue(elemId, propertyDefinition);
		case API_PropertyMultipleChoiceEnumerationCollectionType:
			return GetMultipleChoiceEnumerationCollectionTypePropertyValue(elemId, propertyDefinition);

		default:
			throw SpeckleConversionException("Invalid property collection type.");
		}
	}

	nlohmann::json GetElementPropertiesAsJson(const API_Guid& elemId, const std::vector<API_PropertyDefinition>& propertyDefinitions)
	{
		nlohmann::json propertyJson;

		for (const auto& definition : propertyDefinitions)
		{
			try
			{
				nlohmann::json propertyValue = GetElementPropertyValueAsJson(elemId, definition);
				std::string propertyName = GetPropertyName(definition);
				std::string propertyGroupName = GetPropertyGroupName(definition);
				propertyJson[propertyGroupName][propertyName] = propertyValue;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what();
			}
		}

		return propertyJson;
	}
}

nlohmann::json HostToSpeckleConverter::GetElementPropertiesByPropertyType(const std::string& elemId, const ArchicadPropertyType propertyType)
{
	nlohmann::json propertyListJson;

	auto apiElem = ConverterUtils::GetElement(elemId);
	GS::Array<API_PropertyDefinition> propertyDefinitions;
	CHECK_ERROR(ACAPI_Element_GetPropertyDefinitions(apiElem.header.guid, static_cast<API_PropertyDefinitionFilter>(propertyType), propertyDefinitions));

	std::vector<API_PropertyDefinition> definitions;
	for (const auto& d : propertyDefinitions)
		definitions.push_back(d);

	return GetElementPropertiesAsJson(apiElem.header.guid, definitions);
}

nlohmann::json HostToSpeckleConverter::GetElementPropertiesByPropertyFilter(const std::string& elemId, const PropertyFilter filter)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	auto propertyFilter = GetPropertyFilter(filter);
	std::vector<API_PropertyDefinition> definitions;

	for (const auto& propertyId : propertyFilter)
	{
		auto propertyGuid = APIGuidFromString(propertyId.c_str());

		bool isPropertyAvailable = ACAPI_Element_IsPropertyDefinitionAvailable(apiElem.header.guid, propertyGuid);
		if (!isPropertyAvailable)
			continue;

		API_PropertyDefinition propertyDefinition{};
		propertyDefinition.guid = propertyGuid;
		GSErrCode error = ACAPI_Property_GetPropertyDefinition(propertyDefinition);

		if (error != NoError)
			continue;

		definitions.push_back(propertyDefinition);
	}

	return GetElementPropertiesAsJson(apiElem.header.guid, definitions);
}

nlohmann::json HostToSpeckleConverter::GetElementProperties(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	nlohmann::json properties;

	auto elemType = apiElem.header.type.typeID;
	std::vector<API_ElemTypeID> systemTypes = { API_WallID, API_SlabID, API_BeamID, API_BeamSegmentID, API_ColumnID, API_ColumnSegmentID, API_RoofID, API_ShellID, API_MorphID };
	bool isSystemType = std::find(systemTypes.begin(), systemTypes.end(), elemType) != systemTypes.end();

	if (isSystemType) 
	{
		nlohmann::json materialQuantities = GetElementMaterialQuantities(elemId);
		if (!materialQuantities.empty())
			properties["Material Quantities"] = materialQuantities;

		nlohmann::json classifications = GetElementClassifications(elemId);
		if (!classifications.empty())
			properties["Element Properties"]["Classifications"] = classifications;

		nlohmann::json dimensionalProperties = GetElementPropertiesByPropertyFilter(elemId, PropertyFilter::Dimensional);
		if (!dimensionalProperties.empty())
			properties["Element Properties"]["Dimensional Properties"] = dimensionalProperties;
		
		nlohmann::json userDefinedProperties = GetElementPropertiesByPropertyType(elemId, ArchicadPropertyType::UserDefined);
		if (!userDefinedProperties.empty())
			properties["User Defined Properties"] = userDefinedProperties;
	}
	else 
	{
		nlohmann::json classifications = GetElementClassifications(elemId);
		if (!classifications.empty())
			properties["Element Properties"]["Classifications"] = classifications;
	}

	return properties;
}
