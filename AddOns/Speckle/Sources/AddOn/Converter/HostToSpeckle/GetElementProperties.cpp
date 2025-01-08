#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include "SpeckleConversionException.h"

#include <fstream>
#include <iostream>

static const std::vector<std::string> generalRatingsPropertyFilter = 
{
	"Apple",
	"Banana"
};

static const std::vector<std::string> ifcPropertyFilter =
{
	"Apple",
	"Banana"
};

static const std::vector<std::string> dimensionalPropertyFilter =
{
	"30B6B10B-B0ED-46EA-8BA0-04230BF038D0",
	"B58729AB-7F80-46FD-BE5E-477563DCFD96"
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
	std::ofstream outputFile("C:\\temp\\property_names.txt");

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

			outputFile << APIGuidToString(propertyDefinition.guid).ToCStr().Get();
			outputFile << " - ";
			outputFile << propertyDefinition.name.ToCStr().Get();
			outputFile << std::endl;
		}
		catch (const SpeckleConversionException& /*ex*/)
		{
			// TODO handle this
		}
	}

	outputFile.close();
	return propertyListJson;
}

nlohmann::json HostToSpeckleConverter::GetElementProperties(const std::string& elemId, const PropertyFilter filter)
{
	nlohmann::json propertyListJson;
	auto apiElem = ConverterUtils::GetElement(elemId);
	auto propertyFilter = GetPropertyFilter(filter);

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
