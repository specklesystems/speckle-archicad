#include "APIEnvir.h"
#include "ACAPinc.h"
#include <MemoryOChannel32.hpp>
#include <MemoryIChannel32.hpp>
#include "CheckError.h"
#include "ArchiCadDataStorage.h"

namespace
{
	// this function should always be called in a try-catch block
	API_Guid GetApiObjectGuidByName(const std::string& dataName)
	{
		API_Guid apiGuid{};
		CHECK_ERROR(ACAPI_AddOnObject_GetUniqueObjectGuidFromName(dataName.c_str(), &apiGuid));

		if (apiGuid == APINULLGuid)
			CHECK_ERROR(ACAPI_AddOnObject_CreateUniqueObject(dataName.c_str(), &apiGuid));

		if (apiGuid == APINULLGuid)
			throw "Could not find ApiObject guid by name";

		return apiGuid;
	}
}

// TODO handle exceptions from CHECK_ERROR somewhere
void ArchiCadDataStorage::SaveData(const nlohmann::json& data, const std::string& dataName)
{
	API_Guid apiGuid{};
	try
	{
		apiGuid = GetApiObjectGuidByName(dataName);
	}
	catch (...)
	{
		// An error occured when getting ApiObject guid by name
		return;
	}

	std::string dataString = data.dump();
	GS::MemoryOChannel32 memChannel(GS::MemoryOChannel32::BMAllocation);
	CHECK_ERROR(GS::UniString(dataString).Write(memChannel));
	GSHandle content = nullptr;
	CHECK_ERROR(BMPtrToHandle(memChannel.GetDestination(), &content, memChannel.GetDataSize()));
	CHECK_ERROR(ACAPI_AddOnObject_ModifyObject(apiGuid, nullptr, &content));
	BMKillHandle(&content);
}

// TODO handle exceptions from CHECK_ERROR somewhere
nlohmann::json ArchiCadDataStorage::LoadData(const std::string& dataName)
{
	API_Guid apiGuid{};
	try
	{
		apiGuid = GetApiObjectGuidByName(dataName);
	}
	catch (...)
	{
		// An error occured when getting ApiObject guid by name
		return {};
	}

	GSHandle content = nullptr;
	GS::UniString name;
	CHECK_ERROR(ACAPI_AddOnObject_GetObjectContent(apiGuid, &name, &content));

	if (content == nullptr)
		return {};

	GS::UniString dataString;
	GS::MemoryIChannel32 mic(*content, BMhGetSize(content));
	CHECK_ERROR(dataString.Read(mic));

	std::string stdDataString = dataString.ToCStr().Get();
	
	auto jsonData = nlohmann::json::parse(stdDataString);
	return jsonData;
}
