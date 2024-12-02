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
std::string HostToSpeckleConverter::GetElementLevel(const std::string& elemId)
{
	std::string floorName = "";
	auto apielem = ConverterUtils::GetElement(elemId);
	auto floorInd = apielem.header.floorInd;
	
	API_StoryInfo storyInfo{};
	CHECK_ERROR(ACAPI_ProjectSetting_GetStorySettings(&storyInfo));
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
