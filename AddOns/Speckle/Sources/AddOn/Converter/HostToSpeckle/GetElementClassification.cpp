#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

namespace
{
	std::string GetClassifictaionName(const API_Guid& classificationId)
	{
		API_ClassificationItem classification{};
		classification.guid = classificationId;
		ACAPI_Classification_GetClassificationItem(classification);
		std::string classificationName = classification.id.ToCStr().Get();

		return classificationName;
	}

	std::string GetClassifictaionSystemName(const API_Guid& classificationSystemId)
	{
		API_ClassificationSystem system{};
		system.guid = classificationSystemId;
		ACAPI_Classification_GetClassificationSystem(system);
		std::string systemName = system.name.ToCStr().Get();
		std::string systemEdition = system.editionVersion.ToCStr().Get();

		return systemName + " - " + systemEdition;
	}
}

std::map<std::string, std::string> HostToSpeckleConverter::GetElementClassifications(const std::string& elemId)
{
	std::map<std::string, std::string> classifications;

	auto apiGuid = APIGuidFromString(elemId.c_str());

	GS::Array<GS::Pair<API_Guid, API_Guid>> classificationItems;
	ACAPI_Element_GetClassificationItems(apiGuid, classificationItems);

	for (const auto& item : classificationItems)
	{
		auto classificationSystemName = GetClassifictaionSystemName(item.first);
		auto classificationName = GetClassifictaionName(item.second);
		classifications[classificationSystemName] = classificationName;
	}

	return classifications;
}
