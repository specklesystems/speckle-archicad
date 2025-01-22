#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::string HostToSpeckleConverter::GetElementName(const std::string& elemId)
{
	auto apiGuid = APIGuidFromString(elemId.c_str());
	GS::UniString infoString;
	CHECK_ERROR(ACAPI_Element_GetElementInfoString(&apiGuid, &infoString));
	std::string elementName = infoString.ToCStr().Get();

	return elementName;
}
