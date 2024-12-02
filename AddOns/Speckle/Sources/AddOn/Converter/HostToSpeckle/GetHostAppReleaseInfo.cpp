#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"


std::string HostToSpeckleConverter::GetHostAppReleaseInfo()
{
	API_ServerApplicationInfo info{};
	ACAPI_GetReleaseNumber(&info);
	int mainVersion = info.mainVersion;
	int releaseVersion = info.releaseVersion;
	int buildNum = info.buildNum;
	std::string releaseInfo = std::to_string(mainVersion) + "." + std::to_string(releaseVersion) + "." + std::to_string(buildNum);
	return releaseInfo;
}
