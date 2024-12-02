#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

void SpeckleToHostConverter::ShowAllIn3D()
{
	CHECK_ERROR(ACAPI_View_ShowAllIn3D());
}
