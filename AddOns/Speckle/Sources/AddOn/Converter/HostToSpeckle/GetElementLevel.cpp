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

// TODO cachce level names before sending
ArchicadLevel HostToSpeckleConverter::GetElementLevel(const std::string& elemId)
{
	ArchicadLevel level;
	std::string floorName = "";
	auto apiElem = ConverterUtils::GetElement(elemId);
	auto floorInd = apiElem.header.floorInd;
	
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
				level.elevation = storyData.level;
				level.floorId = storyData.floorId;
				break;
			}
		}
	}

	std::ostringstream oss;
	oss << floorInd << ". " << (floorName.empty() ? "Story" : floorName);
	level.name = oss.str();
	return level;
}

#pragma warning(pop) // Restore the previous warning state
