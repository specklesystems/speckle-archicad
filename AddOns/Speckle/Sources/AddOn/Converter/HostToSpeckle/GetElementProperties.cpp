#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"


namespace
{
	nlohmann::json GetElementProperty(const API_Guid& elemId, const API_PropertyDefinition& propertyDefinition)
	{
		nlohmann::json propertyJson;

		std::string propertyGuid = APIGuidToString(propertyDefinition.guid).ToCStr();
		std::string propertyName = propertyDefinition.name.ToLowerCase().ToCStr();
		std::string propertyValue = "";
		std::string propertyValueType = "";

		API_Property  prop = {};
		CHECK_ERROR(ACAPI_Element_GetPropertyValue(elemId, propertyDefinition.guid, prop));

		if (propertyDefinition.valueType == API_PropertyStringValueType && propertyDefinition.collectionType == API_PropertySingleCollectionType)
		{
			propertyValueType = "string";
			propertyValue = prop.value.singleVariant.variant.uniStringValue.ToCStr();
		}
		else if (propertyDefinition.valueType == API_PropertyIntegerValueType && propertyDefinition.collectionType == API_PropertySingleCollectionType)
		{
			propertyValueType = "integer";
			propertyValue = std::to_string(prop.value.singleVariant.variant.intValue);
		}
		else if (propertyDefinition.valueType == API_PropertyRealValueType && propertyDefinition.collectionType == API_PropertySingleCollectionType)
		{
			propertyValueType = "real";
			propertyValue = std::to_string(prop.value.singleVariant.variant.doubleValue);
		}
		else
		{
			// TODO implement other cases
			throw SpeckleConversionException("Converting property type is not supported.");
		}

		API_PropertyGroup group;
		group.guid = propertyDefinition.groupGuid;
		CHECK_ERROR(ACAPI_Property_GetPropertyGroup(group));
		std::string propertyGroupName = group.name.ToCStr();

		if (propertyValue != "")
		{
			propertyJson["guid"] = propertyGuid;
			propertyJson["name"] = propertyName;
			propertyJson["groupName"] = propertyGroupName;
			propertyJson["value"] = propertyValue;
			propertyJson["value type"] = propertyValueType;
		}

		return propertyJson;
	}
}

nlohmann::json HostToSpeckleConverter::GetElementProperties(const std::string& elemId, const ArchicadPropertyType propertyType)
{
	nlohmann::json propertyListJson;

	auto apiElem = ConverterUtils::GetElement(elemId);
	GS::Array<API_PropertyDefinition> definitions;
	CHECK_ERROR(ACAPI_Element_GetPropertyDefinitions(apiElem.header.guid, static_cast<API_PropertyDefinitionFilter>(propertyType), definitions));

	for (const auto& propertyDefinition : definitions)
	{
		try
		{
			const auto& propertyJson = GetElementProperty(apiElem.header.guid, propertyDefinition);
			if (!propertyJson.empty())
			{
				propertyListJson.push_back(propertyJson);
			}
		}
		catch (const SpeckleConversionException& /*ex*/)
		{
			// TODO handle this
		}
	}

	return propertyListJson;
}
