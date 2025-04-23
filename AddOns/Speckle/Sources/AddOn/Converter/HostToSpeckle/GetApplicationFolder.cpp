#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"


std::string HostToSpeckleConverter::GetApplicationFolder()
{
	IO::Location loc;
	API_SpecFolderID specFolderId = API_ApplicationFolderID;
	ACAPI_ProjectSettings_GetSpecFolder(&specFolderId, &loc);
	std::string folderPath = loc.ToDisplayText().ToCStr().Get();
	return folderPath;
}
