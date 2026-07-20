#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <unordered_map>

namespace
{
	// Classification item/system names are invariant during a send and shared by
	// many elements — cache them per SendCacheScope, keyed by the raw GUID bytes.
	std::string GuidKey(const API_Guid& guid)
	{
		return std::string(reinterpret_cast<const char*>(&guid), sizeof(API_Guid));
	}

	template <typename Fetch>
	std::string CachedName(std::unordered_map<std::string, std::string>& cache, unsigned& cachedGeneration,
		const API_Guid& guid, Fetch&& fetch)
	{
		const unsigned generation = ConverterUtils::SendCacheGeneration();
		if (generation == 0)
			return fetch();
		if (generation != cachedGeneration)
		{
			cache.clear();
			cachedGeneration = generation;
		}
		const auto [it, isNew] = cache.try_emplace(GuidKey(guid));
		if (isNew)
			it->second = fetch();
		return it->second;
	}

	std::string GetClassifictaionName(const API_Guid& classificationId)
	{
		static std::unordered_map<std::string, std::string> cache;
		static unsigned cachedGeneration = 0;
		return CachedName(cache, cachedGeneration, classificationId, [&]
		{
			API_ClassificationItem classification{};
			classification.guid = classificationId;
			ACAPI_Classification_GetClassificationItem(classification);
			std::string classificationName = classification.id.ToCStr().Get();

			return classificationName;
		});
	}

	std::string GetClassifictaionSystemName(const API_Guid& classificationSystemId)
	{
		static std::unordered_map<std::string, std::string> cache;
		static unsigned cachedGeneration = 0;
		return CachedName(cache, cachedGeneration, classificationSystemId, [&]
		{
			API_ClassificationSystem system{};
			system.guid = classificationSystemId;
			ACAPI_Classification_GetClassificationSystem(system);
			std::string systemName = system.name.ToCStr().Get();
			std::string systemEdition = system.editionVersion.ToCStr().Get();

			return systemName + " - " + systemEdition;
		});
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
