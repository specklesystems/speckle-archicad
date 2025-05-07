#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"
#include "ConverterUtils.h"
#include "CheckError.h"

namespace
{
	std::string GetIfcPropertyValue(const API_IFCProperty& prop)
	{
		if (prop.head.propertyType == API_IFCPropertyType::API_IFCPropertySingleValueType)
		{
			if (prop.singleValue.nominalValue.value.primitiveType == API_IFCPropertyValuePrimitiveType::API_IFCPropertyAnyValueRealType)
			{
				return std::to_string(prop.singleValue.nominalValue.value.doubleValue);
			}

			if (prop.singleValue.nominalValue.value.primitiveType == API_IFCPropertyValuePrimitiveType::API_IFCPropertyAnyValueIntegerType)
			{
				return std::to_string(prop.singleValue.nominalValue.value.intValue);
			}

			if (prop.singleValue.nominalValue.value.primitiveType == API_IFCPropertyValuePrimitiveType::API_IFCPropertyAnyValueStringType)
			{
				return prop.singleValue.nominalValue.value.stringValue.ToCStr().Get();
			}
		}

		return "none";
	}
}

nlohmann::json HostToSpeckleConverter::GetElementIfcProperties(const std::string& elemId)
{
	nlohmann::json properties;
	auto apiGuid = APIGuidFromString(elemId.c_str());
	GS::Array<API_IFCProperty> ifcProperties;
	CHECK_ERROR(ACAPI_Element_GetIFCProperties(apiGuid, false, &ifcProperties));

	for (const auto& property : ifcProperties)
	{
		std::string propertyName = property.head.propertyName.ToCStr().Get();
		std::string propertySetName = property.head.propertySetName.ToCStr().Get();
		std::string propertyValue = GetIfcPropertyValue(property);

		properties[propertySetName][propertyName] = propertyValue;
	}

	return properties;
}
