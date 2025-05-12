#pragma warning(disable : 4996) // Disable warning C4996

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
