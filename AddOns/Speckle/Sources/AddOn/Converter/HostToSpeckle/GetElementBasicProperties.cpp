#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ConverterUtils.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"

#include <iostream>

namespace
{
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

nlohmann::json HostToSpeckleConverter::GetElementPropertiesByPropertyType(const std::string& elemId, const ArchicadPropertyTypeFilter propertyType)
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

nlohmann::json HostToSpeckleConverter::GetElementPropertiesByPropertyFilter(const std::string& elemId, const PropertyCollectionFilter filter)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	std::vector<API_PropertyDefinition> definitions;

	for (const auto& propertyId : PropertyFilters::Get(filter))
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
