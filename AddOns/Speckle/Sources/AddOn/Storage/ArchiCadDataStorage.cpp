#include "APIEnvir.h"
#include "ACAPinc.h"
#include <MemoryOChannel32.hpp>
#include <MemoryIChannel32.hpp>
#include "CheckError.h"
#include "ArchiCadDataStorage.h"
#include "Utils.h"

#include <iostream>

static API_Guid GetApiObjectGuidByName(const std::string& dataName)
{
	API_Guid apiGuid{};
	CHECK_ERROR(ACAPI_AddOnObject_GetUniqueObjectGuidFromName(dataName.c_str(), &apiGuid));

	if (apiGuid == APINULLGuid)
		CHECK_ERROR(ACAPI_AddOnObject_CreateUniqueObject(dataName.c_str(), &apiGuid));

	if (apiGuid == APINULLGuid)
		throw "Could not find ApiObjec guid by name";

	return apiGuid;
}

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

	//auto dataString = data.dump().c_str();
	std::string dataString = data.dump();
	//dataString = "Apple";
	GS::MemoryOChannel32 memChannel(GS::MemoryOChannel32::BMAllocation);
	CHECK_ERROR(GS::UniString(dataString).Write(memChannel));
	GSHandle content = nullptr;
	CHECK_ERROR(BMPtrToHandle(memChannel.GetDestination(), &content, memChannel.GetDataSize()));
	CHECK_ERROR(ACAPI_AddOnObject_ModifyObject(apiGuid, nullptr, &content));
	BMKillHandle(&content);
}

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
	
	

	try
	{
		auto jsonData = nlohmann::json::parse(stdDataString);
		Utils::WriteJsonToFile(jsonData, "C:\\tmp\\modelCards.json");
		return jsonData;
	}
	catch (nlohmann::json::parse_error& e)
	{
		std::cout << e.what();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	catch (...)
	{
		// wtf
	}

	return {};
}
