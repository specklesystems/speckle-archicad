#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::string HostToSpeckleConverter::GetResourceString(short resourceId)
{
	char resourceString[256];
	bool succ;
	
	succ = ACAPI_Resource_GetLocStr(resourceString, resourceId, 1, ACAPI_GetOwnResModule());

	if (succ) 
	{
		return resourceString;
	}
	else
	{
		return "";
	}
}
