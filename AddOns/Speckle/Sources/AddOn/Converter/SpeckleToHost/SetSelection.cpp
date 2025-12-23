#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

static bool ElementExists(const API_Guid& guid)
{
	API_Element element;
	BNZeroMemory(&element, sizeof(API_Element));
	element.header.guid = guid;

	GSErrCode err = ACAPI_Element_Get(&element);
	return (err == NoError);
}

void SpeckleToHostConverter::SetSelection(std::vector<std::string> guids)
{
	CHECK_ERROR(ACAPI_Selection_DeselectAll());
	GS::Array<API_Neig> selNeigs;
	for (const auto& id : guids)
	{
		auto guid = APIGuidFromString(id.c_str());
		if (ElementExists(guid))
		{
			API_Neig neig(guid);
			selNeigs.Push(neig);
		}
	}
	CHECK_ERROR(ACAPI_Selection_Select(selNeigs, true));
}
