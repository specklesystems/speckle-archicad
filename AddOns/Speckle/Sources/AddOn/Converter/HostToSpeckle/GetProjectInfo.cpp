#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

ProjectInfo HostToSpeckleConverter::GetProjectInfo()
{
	ProjectInfo projectInfo{};
	API_ProjectInfo apiProjectInfo{};
	// TODO handle errors locally?
	CHECK_ERROR(ACAPI_ProjectOperation_Project(&apiProjectInfo));

	// TODO TeamWork
	projectInfo.location = apiProjectInfo.projectPath->ToCStr().Get();
	projectInfo.name = apiProjectInfo.projectName->ToCStr().Get();

	return projectInfo;
}
