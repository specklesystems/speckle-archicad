#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"


void SpeckleToHostConverter::ShowAllIn3D()
{
#if defined(AC28)
	CHECK_ERROR(ACAPI_View_ShowAllIn3D());
#elif defined(AC27)
	CHECK_ERROR(ACAPI_View_ShowAllIn3D());
#elif defined(AC26)
	CHECK_ERROR(ACAPI_View_ShowAllIn3D());
#elif defined(AC25)
	CHECK_ERROR(ACAPI_Automate(APIDo_ShowAllIn3DID));
#endif
}
