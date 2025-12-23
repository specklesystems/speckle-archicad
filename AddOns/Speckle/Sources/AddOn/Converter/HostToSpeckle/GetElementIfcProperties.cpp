#pragma warning(disable : 4996) // Disable warning C4996

#if defined(AC29)
#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ACAPI/IFCObjectAccessor.hpp"
#include "ACAPI/IFCObjectID.hpp"
#include "ACAPI/IFCProperty.hpp"
#include "ACAPI/IFCPropertyAccessor.hpp"
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

	std::string ifc_logical_to_string(int value)
	{
		switch (value)
		{
		case 0:
			return "False";
		case 1:
			return "Unknown";
		case 2:
			return "True";
		default:
			return "Invalid";
		}
	}

	std::string GetIfcPropertyValue(const IFCAPI::Value& propertyValue)
	{
		auto anyValue = propertyValue.GetAnyValue();
		if (anyValue.has_value())
		{
			auto value = anyValue.value();
			if (std::holds_alternative<GS::UniString>(value))
			{
				return std::get<GS::UniString>(value).ToCStr().Get();
			}
			else if (std::holds_alternative<bool>(value))
			{
				return bool_to_string(std::get<bool>(value));
			}
			else if (std::holds_alternative<double>(value))
			{
				return std::to_string(std::get<double>(value));
			}
			else if (std::holds_alternative<Int64>(value))
			{
				return std::to_string(std::get<Int64>(value));
			}
			else if (std::holds_alternative<IFCAPI::IfcLogical>(value))
			{
				return ifc_logical_to_string(static_cast<int>(std::get<IFCAPI::IfcLogical>(value)));
			}
		}
	}

	std::string GetIfcSinglePropertyValue(const IFCAPI::PropertySingleValue& propertySingleValue)
	{
		return GetIfcPropertyValue(propertySingleValue.GetNominalValue());
	}

	std::vector<std::string> GetIfcListPropertyValue(const IFCAPI::PropertyListValue& propertyListValue)
	{
		std::vector<std::string> values;
		for (const auto& val : propertyListValue.GetListValues())
		{
			values.push_back(GetIfcPropertyValue(val));
		}

		return values;
	}

	std::pair<std::string, std::string> GetIfcBoundedPropertyValue(const IFCAPI::PropertyBoundedValue& propertyBoundedValue)
	{
		std::pair<std::string, std::string> values;
		values.first = GetIfcPropertyValue(propertyBoundedValue.GetLowerBoundValue());
		values.second = GetIfcPropertyValue(propertyBoundedValue.GetUpperBoundValue());

		return values;
	}

	std::vector<std::string> GetIfcEnumeratedPropertyValue(const IFCAPI::PropertyEnumeratedValue& propertyEnumeratedValue)
	{
		std::vector<std::string> values;
		for (const auto& val : propertyEnumeratedValue.GetEnumerationValues())
		{
			values.push_back(GetIfcPropertyValue(val));
		}

		return values;
	}

	std::map<std::string, std::string> GetIfcTablePropertyValue(const IFCAPI::PropertyTableValue& propertyTableValue)
	{
		std::map<std::string, std::string> values;

		std::vector<std::string> definingValues;
		for (const auto& val : propertyTableValue.GetDefiningValues())
		{
			definingValues.push_back(GetIfcPropertyValue(val));
		}

		std::vector<std::string> definedValues;
		for (const auto& val : propertyTableValue.GetDefinedValues())
		{
			definedValues.push_back(GetIfcPropertyValue(val));
		}

		size_t count = std::min(definingValues.size(), definedValues.size());
		for (size_t i = 0; i < count; ++i)
		{
			values[definingValues[i]] = definedValues[i];
		}

		return values;
	}
	
	nlohmann::json GetElementIfcPropertyValueAsJson(const IFCAPI::Property& property)
	{
		auto propertyVariant = property.GetTyped();
		if (std::holds_alternative<IFCAPI::PropertySingleValue>(propertyVariant)) 
		{
			return GetIfcSinglePropertyValue(std::get<IFCAPI::PropertySingleValue>(propertyVariant));
		}
		else if (std::holds_alternative<IFCAPI::PropertyListValue>(propertyVariant)) 
		{
			return GetIfcListPropertyValue(std::get<IFCAPI::PropertyListValue>(propertyVariant));
		}
		else if (std::holds_alternative<IFCAPI::PropertyBoundedValue>(propertyVariant)) 
		{
			return GetIfcBoundedPropertyValue(std::get<IFCAPI::PropertyBoundedValue>(propertyVariant));
		}
		else if (std::holds_alternative<IFCAPI::PropertyEnumeratedValue>(propertyVariant)) 
		{
			return GetIfcEnumeratedPropertyValue(std::get<IFCAPI::PropertyEnumeratedValue>(propertyVariant));
		}
		else if (std::holds_alternative<IFCAPI::PropertyTableValue>(propertyVariant))
		{
			return GetIfcTablePropertyValue(std::get<IFCAPI::PropertyTableValue>(propertyVariant));
		}
		else
		{
			// TODO throw
		}
	}
}

nlohmann::json HostToSpeckleConverter::GetElementIfcProperties(const std::string& elemId)
{
	nlohmann::json properties;
	auto apiGuid = APIGuidFromString(elemId.c_str());
	API_Elem_Head head{};
	head.guid = apiGuid;

	auto objectID = IFCAPI::GetObjectAccessor().CreateElementObjectID(head);
	if (objectID.IsErr())
		return {};

	auto previewProperties = IFCAPI::PropertyAccessor(*objectID).GetPreviewProperties();
	if (previewProperties.IsErr())
		return {};

	for (const auto& property : *previewProperties)
	{
		std::string propertyName = property.GetName().ToCStr().Get();
		std::string propertySetName = property.GetPropertySetName().ToCStr().Get();
		nlohmann::json propertyValue = GetElementIfcPropertyValueAsJson(property);

		properties[propertySetName][propertyName] = propertyValue;
	}

	return properties;
}

#else
#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ConverterUtils.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"

namespace
{
	std::string bool_to_string(bool b)
	{
		return b ? "True" : "False";
	}

	std::string ifc_logical_to_string(int value)
	{
		switch (value)
		{
		case 0:
			return "False";
		case 1:
			return "Unknown";
		case 2:
			return "True";
		default:
			return "Invalid";
		}
	}

	std::string GetIfcPropertyValue(const API_IFCPropertyValue& propertyValue)
	{
		switch (propertyValue.value.primitiveType)
		{
		case API_IFCPropertyAnyValueRealType:
			return std::to_string(propertyValue.value.doubleValue);
		case API_IFCPropertyAnyValueIntegerType:
			return std::to_string(propertyValue.value.intValue);
		case API_IFCPropertyAnyValueStringType:
			return propertyValue.value.stringValue.ToCStr().Get();
		case API_IFCPropertyAnyValueBooleanType:
			return bool_to_string(propertyValue.value.boolValue);
		case API_IFCPropertyAnyValueLogicalType:
			return ifc_logical_to_string(static_cast<int>(propertyValue.value.intValue));

		default:
			throw SpeckleConversionException("Invalid IFC property value type.");
		}
	}

	std::string GetIfcSinglePropertyValue(const API_IFCProperty& property)
	{
		return GetIfcPropertyValue(property.singleValue.nominalValue);
	}

	std::vector<std::string> GetIfcListPropertyValue(const API_IFCProperty& property)
	{
		std::vector<std::string> values;
		for (const auto& val : property.listValue.listValues)
		{
			values.push_back(GetIfcPropertyValue(val));
		}

		return values;
	}

	std::pair<std::string, std::string> GetIfcBoundedPropertyValue(const API_IFCProperty& property)
	{
		std::pair<std::string, std::string> values;
		values.first = GetIfcPropertyValue(property.boundedValue.lowerBoundValue);
		values.second = GetIfcPropertyValue(property.boundedValue.upperBoundValue);

		return values;
	}

	std::vector<std::string> GetIfcEnumeratedPropertyValue(const API_IFCProperty& property)
	{
		std::vector<std::string> values;
		for (const auto& val : property.enumeratedValue.enumerationValues)
		{
			values.push_back(GetIfcPropertyValue(val));
		}

		return values;
	}

	std::map<std::string, std::string> GetIfcTablePropertyValue(const API_IFCProperty& property)
	{
		std::map<std::string, std::string> values;

		std::vector<std::string> definingValues;
		for (const auto& val : property.tableValue.definingValues)
		{
			definingValues.push_back(GetIfcPropertyValue(val));
		}

		std::vector<std::string> definedValues;
		for (const auto& val : property.tableValue.definedValues)
		{
			definedValues.push_back(GetIfcPropertyValue(val));
		}

		size_t count = std::min(definingValues.size(), definedValues.size());
		for (size_t i = 0; i < count; ++i)
		{
			values[definingValues[i]] = definedValues[i];
		}

		return values;
	}

	nlohmann::json GetElementIfcPropertyValueAsJson(const API_IFCProperty& property)
	{
		switch (property.head.propertyType)
		{
		case API_IFCPropertySingleValueType:
			return GetIfcSinglePropertyValue(property);
		case API_IFCPropertyListValueType:
			return GetIfcListPropertyValue(property);
		case API_IFCPropertyBoundedValueType:
			return GetIfcBoundedPropertyValue(property);
		case API_IFCPropertyEnumeratedValueType:
			return GetIfcEnumeratedPropertyValue(property);
		case API_IFCPropertyTableValueType:
			return GetIfcTablePropertyValue(property);

		default:
			throw SpeckleConversionException("Invalid IFC property type.");
		}
	}
}

nlohmann::json HostToSpeckleConverter::GetElementIfcProperties(const std::string& elemId)
{
	nlohmann::json properties;
	auto apiGuid = APIGuidFromString(elemId.c_str());
	GS::Array<API_IFCProperty> ifcProperties;
	GSErrCode err = NoError;
	err = ACAPI_Element_GetIFCProperties(apiGuid, false, &ifcProperties);

	if (err != NoError)
	{
		return {};
	}

	for (const auto& property : ifcProperties)
	{
		std::string propertyName = property.head.propertyName.ToCStr().Get();
		std::string propertySetName = property.head.propertySetName.ToCStr().Get();
		nlohmann::json propertyValue = GetElementIfcPropertyValueAsJson(property);

		properties[propertySetName][propertyName] = propertyValue;
	}

	return properties;
}
#endif