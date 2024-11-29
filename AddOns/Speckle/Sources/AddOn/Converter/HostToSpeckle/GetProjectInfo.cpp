#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

static GSErrCode ApiProjectInfo(API_ProjectInfo* projectInfo)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_ProjectOperation_Project(projectInfo);
#elif defined(AC27)
	err = ACAPI_ProjectOperation_Project(projectInfo);
#elif defined(AC26)
	err = ACAPI_Environment(APIEnv_ProjectID, projectInfo);
#elif defined(AC25)
	err = ACAPI_Environment(APIEnv_ProjectID, projectInfo);
#endif

	return err;
}

ProjectInfo HostToSpeckleConverter::GetProjectInfo()
{
	ProjectInfo projectInfo{};
	API_ProjectInfo apiProjectInfo{};
	// TODO handle errors locally?
	CHECK_ERROR(ApiProjectInfo(&apiProjectInfo));
	
	// TODO TeamWork
	projectInfo.location = apiProjectInfo.projectPath->ToCStr().Get();
	projectInfo.name = apiProjectInfo.projectName->ToCStr().Get();

	return projectInfo;
}
