#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

static GSErrCode ApiProjectInfo(void* par)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_ProjectOperation_Project(par);
#elif defined(AC27)
	err = ACAPI_ProjectOperation_Project(par);
#elif defined(AC26)
	err = ACAPI_Environment(APIEnv_ProjectID, par);
#elif defined(AC25)
	err = ACAPI_Environment(APIEnv_ProjectID, par);
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
