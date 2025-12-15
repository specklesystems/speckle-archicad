#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ConverterUtils.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"
#include "PropertyDefinitions.h"
#include "JsonFileWriter.h"

#include "StopWatch.h"

#include <iostream>
#include <variant>

using PropertyOwner = std::variant<API_Guid, API_ElemComponentID>;

namespace
{
	std::string bool_to_string(bool b)
	{
		return b ? "True" : "False";
	}

	GSErrCode GetPropertyValue(
		const PropertyOwner& owner,
		const API_PropertyDefinition& propertyDef,
		API_Property& outProp)
	{
		return std::visit([&](auto&& id) -> GSErrCode {
			return ACAPI_Element_GetPropertyValue(id, propertyDef.guid, outProp);
			}, owner);
	}

	std::string GetSingleCollectionTypePropertyValue(const PropertyOwner& propertyOwner, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(GetPropertyValue(propertyOwner, propertyDefinition, prop));
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

	std::vector<std::string> GetListCollectionTypePropertyValue(const PropertyOwner& propertyOwner, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(GetPropertyValue(propertyOwner, propertyDefinition, prop)); CHECK_ERROR(GetPropertyValue(propertyOwner, propertyDefinition, prop));
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

	std::string GetSingleChoiceEnumerationCollectionTypePropertyValue(const PropertyOwner& propertyOwner, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(GetPropertyValue(propertyOwner, propertyDefinition, prop));
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

	std::vector<std::string> GetMultipleChoiceEnumerationCollectionTypePropertyValue(const PropertyOwner& propertyOwner, const API_PropertyDefinition& propertyDefinition)
	{
		API_Property  prop = {};
		CHECK_ERROR(GetPropertyValue(propertyOwner, propertyDefinition, prop));
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

	nlohmann::json GetElementPropertyValueAsString(const PropertyOwner& propertyOwner, const API_PropertyDefinition& propertyDefinition)
	{
		switch (propertyDefinition.collectionType)
		{
		case API_PropertySingleCollectionType:
			return GetSingleCollectionTypePropertyValue(propertyOwner, propertyDefinition);
		case API_PropertyListCollectionType:
			return GetListCollectionTypePropertyValue(propertyOwner, propertyDefinition);
		case API_PropertySingleChoiceEnumerationCollectionType:
			return GetSingleChoiceEnumerationCollectionTypePropertyValue(propertyOwner, propertyDefinition);
		case API_PropertyMultipleChoiceEnumerationCollectionType:
			return GetMultipleChoiceEnumerationCollectionTypePropertyValue(propertyOwner, propertyDefinition);

		default:
			throw SpeckleConversionException("Invalid property collection type.");
		}
	}

	nlohmann::json GetElementPropertiesAsJson(const PropertyOwner& propertyOwner, const std::vector<API_PropertyDefinition>& propertyDefinitions)
	{
		nlohmann::json propertyJson;

		for (const auto& definition : propertyDefinitions)
		{
			try
			{
				nlohmann::json propertyValueString = GetElementPropertyValueAsString(propertyOwner, definition);
				std::string propertyName = GetPropertyName(definition);
				std::string propertyGroupName = GetPropertyGroupName(definition);
				propertyJson[propertyGroupName][propertyName] = propertyValueString;

				// TODO add property structure similar to Revit
				/*nlohmann::json propertyValue;
				propertyValue["name"] = propertyName;
				propertyValue["value"] = propertyValueString;
				propertyValue["units"] = "m";
				propertyJson[propertyGroupName].push_back(propertyValue);*/

				// only for finding property definition ids
				// add lines after GetElementPropertiesByPropertyType(elemId, ArchicadPropertyTypeFilter::UserDefined)
				// in GetElementProperties.cpp as needed to print props into a json file
				//std::string propertyId = APIGuidToString(definition.guid).ToCStr().Get();
				//propertyJson[propertyGroupName][propertyName] = propertyId;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what();
			}
		}
		//JsonFileWriter::WriteJsonToFile(propertyJson, "C:\\t\\pro.json");
		return propertyJson;
	}

	std::string GetComponentBuildingMaterialName(const API_ElemComponentID& componentId)
	{
		try
		{
			API_Property prop = {};
			auto buildingMatPropertyDefinition = PropertyDefinitions::Instance().GetComponentBuildingMaterialDefinition();
			CHECK_ERROR(GetPropertyValue(componentId, buildingMatPropertyDefinition, prop));
			int index = prop.value.singleVariant.variant.intValue;
			auto materialName = ConverterUtils::GetAttributeName(ACAPI_CreateAttributeIndex(index), API_BuildingMaterialID);

			return materialName;
		}
		catch (...)
		{
			return "No Material";
		}
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

nlohmann::json HostToSpeckleConverter::GetElementComponentProperties(const std::string& elemId)
{
	nlohmann::json componentProperties;

	auto apiElem = ConverterUtils::GetElement(elemId);

	GS::Array<API_ElemComponentID> elemComponents;
	if (ACAPI_Element_GetComponents(apiElem.header.guid, elemComponents) == NoError)
	{
		auto componentDefinitions = PropertyDefinitions::Instance().GetComponentDefinitions();

		int i = 0;
		for (const auto& component : elemComponents)
		{	
			auto propsJson = GetElementPropertiesAsJson(component, componentDefinitions);
			auto materialName = GetComponentBuildingMaterialName(component);
			auto value = propsJson.at("ComponentProperties");
			value["Component Building Material Name"] = materialName;
			// TODO add proper units for each value type
			value["Units"] = "Meters";
			
			// Format index with leading zero and concatenate with material name
			// this is needed to keep the skin order in the viewer
			std::ostringstream oss;
			oss << std::setw(2) << std::setfill('0') << (i + 1) << " - " << materialName;
			std::string componentName = oss.str();
			componentProperties[componentName] = value;
			i++;
		}
	}

	return componentProperties;
}
