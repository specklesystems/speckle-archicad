#pragma warning(push)           // Save the current warning state
#pragma warning(disable : 4996) // Disable warning C4996

#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <iostream>
#include <codecvt>
#include <locale>


namespace 
{
	std::string WstringToString(const std::wstring& wideString) 
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(wideString);
	}
}

// TODO cachce level names before send
static GSErrCode GetStorySettings(API_StoryInfo* storyInfo)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_ProjectSetting_GetStorySettings(storyInfo);
#elif defined(AC27)
	err = ACAPI_ProjectSetting_GetStorySettings(storyInfo);
#elif defined(AC26)
	err = ACAPI_Environment(APIEnv_GetStorySettingsID, storyInfo, nullptr);
#elif defined(AC25)
	err = ACAPI_Environment(APIEnv_GetStorySettingsID, storyInfo, nullptr);
#endif

	return err;
}

std::string HostToSpeckleConverter::GetElementLevel(const std::string& elemId)
{
	std::string floorName = "";
	auto apielem = ConverterUtils::GetElement(elemId);
	auto floorInd = apielem.header.floorInd;
	
	API_StoryInfo storyInfo{};
	CHECK_ERROR(GetStorySettings(&storyInfo));
	auto storyCount = storyInfo.lastStory - storyInfo.firstStory + 1;
	for (auto i = 0; i < storyCount; i++)
	{
		if ((storyInfo.data) != nullptr)
		{
			auto storyData = (*storyInfo.data)[i];
			if (storyData.index == floorInd)
			{
				std::wstring fn = storyData.uName;
				floorName = WstringToString(fn);
				break;
			}
		}
	}

	return floorName;
}

#pragma warning(pop) // Restore the previous warning state
