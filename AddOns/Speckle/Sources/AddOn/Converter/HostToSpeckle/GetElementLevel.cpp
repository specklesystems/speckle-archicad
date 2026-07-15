#ifdef _MSC_VER
#pragma warning(push)           // Save the current warning state
#pragma warning(disable : 4996) // Disable warning C4996
#endif

#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <iostream>

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
				floorName = GS::UniString(storyData.uName).ToCStr(CC_UTF8).Get();
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

#ifdef _MSC_VER
#pragma warning(pop) // Restore the previous warning state
#endif
