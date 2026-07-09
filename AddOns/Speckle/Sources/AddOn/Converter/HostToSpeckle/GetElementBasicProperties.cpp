#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ConverterUtils.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"
#include "PropertyDefinitions.h"

#include <iostream>

namespace
{
	// Typed value from a property variant: real JSON numbers/booleans/strings
	// (the historical std::to_string/"True" stringification lost the type, which
	// broke EAV typing downstream and rendered numbers as "0.600000").
	nlohmann::json GetVariantValue(const API_Variant& variant, API_VariantType valueType)
	{
		switch (valueType)
		{
		case API_PropertyStringValueType:
			return std::string(variant.uniStringValue.ToCStr().Get());
		case API_PropertyIntegerValueType:
			return variant.intValue;
		case API_PropertyRealValueType:
			return variant.doubleValue;
		case API_PropertyBooleanValueType:
			return variant.boolValue;

		default:
			throw SpeckleConversionException("Invalid property value type");
		}
	}

	void ThrowIfEmptyString(const nlohmann::json& value)
	{
		if (value.is_string() && value.get<std::string>().empty())
			throw SpeckleConversionException("Property value was empty");
	}

	nlohmann::json GetSingleCollectionTypePropertyValue(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));

		nlohmann::json propertyValue = GetVariantValue(prop.value.singleVariant.variant, propertyDefinition.valueType);
		ThrowIfEmptyString(propertyValue);
		return propertyValue;
	}

	std::vector<nlohmann::json> GetListCollectionTypePropertyValue(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));
		std::vector<nlohmann::json> propertyValues;

		auto variants = prop.value.listVariant.variants;

		for (const auto& variant : variants)
		{
			try
			{
				propertyValues.push_back(GetVariantValue(variant, propertyDefinition.valueType));
			}
			catch (const SpeckleConversionException&)
			{
				continue;
			}
		}

		if (propertyValues.empty())
			throw SpeckleConversionException("Property value was empty");

		return propertyValues;
	}

	nlohmann::json GetSingleChoiceEnumerationCollectionTypePropertyValue(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));

		auto selectedValueGuid = prop.value.singleVariant.variant.guidValue;
		for (const auto& variant : propertyDefinition.possibleEnumValues)
		{
			if (variant.keyVariant.guidValue == selectedValueGuid)
			{
				nlohmann::json propertyValue = GetVariantValue(variant.displayVariant, propertyDefinition.valueType);
				ThrowIfEmptyString(propertyValue);
				return propertyValue;
			}
		}

		throw SpeckleConversionException("Property value was empty");
	}

	std::vector<nlohmann::json> GetMultipleChoiceEnumerationCollectionTypePropertyValue(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));
		std::vector<nlohmann::json> propertyValues;
		auto variants = prop.value.listVariant.variants;

		for (const auto& variant : propertyDefinition.possibleEnumValues)
		{
			for (const auto& selectedVariant : variants)
			{
				if (variant.keyVariant.guidValue == selectedVariant.guidValue)
				{
					try
					{
						propertyValues.push_back(GetVariantValue(variant.displayVariant, propertyDefinition.valueType));
					}
					catch (const SpeckleConversionException&)
					{
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

	// Unit label for a measured property. API property values are Archicad-internal
	// SI (meters and powers thereof), so the labels are the SI names regardless of
	// the user's display-unit preferences.
	const char* GetMeasureUnitName(API_PropertyMeasureType measureType)
	{
		switch (measureType)
		{
		case API_PropertyLengthMeasureType:
			return "Meter";
		case API_PropertyAreaMeasureType:
			return "Square Meter";
		case API_PropertyVolumeMeasureType:
			return "Cubic Meter";
		case API_PropertyAngleMeasureType:
			return "Radian";

		default:
			return nullptr;
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

				// Measured single-real properties ride as {name, value, units} parameter
				// dicts, which the Speckle EAV flattener stores as one typed row with the
				// units column set (matching the Revit connector's parameter shape).
				const char* unitName = GetMeasureUnitName(definition.measureType);
				if (unitName != nullptr && propertyValue.is_number())
				{
					propertyJson[propertyGroupName][propertyName] = {
						{ "name", propertyName },
						{ "value", propertyValue },
						{ "units", unitName }
					};
				}
				else
				{
					propertyJson[propertyGroupName][propertyName] = propertyValue;
				}
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

nlohmann::json HostToSpeckleConverter::GetElementBuiltInProperties(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);
	auto definitions = PropertyDefinitions::Instance().GetDefinitions(apiElem.header.type.typeID);

	return GetElementPropertiesAsJson(apiElem.header.guid, definitions);
}
