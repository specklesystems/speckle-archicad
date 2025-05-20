#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

void SpeckleToHostConverter::ShowAllIn3D()
{
	CHECK_ERROR(ACAPI_View_ShowAllIn3D());
}

void SpeckleToHostConverter::ShowIn3D()
{
	API_WindowInfo currentWindowInfo = {};
	ACAPI_Window_GetCurrentWindow(&currentWindowInfo);
	if (currentWindowInfo.typeID != APIWind_3DModelID)
	{
		API_WindowInfo newWindowInfo = {};
		newWindowInfo.typeID = APIWind_3DModelID;
		CHECK_ERROR(ACAPI_Window_ChangeWindow(&newWindowInfo));
	}
}
