#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

void SpeckleToHostConverter::SetSelection(std::vector<std::string> guids)
{
	CHECK_ERROR(ACAPI_Selection_DeselectAll());
	GS::Array<API_Neig> selNeigs;
	for (const auto& id : guids)
	{
		auto guid = APIGuidFromString(id.c_str());
		API_Neig neig(guid);
		selNeigs.Push(neig);
	}
	CHECK_ERROR(ACAPI_Selection_Select(selNeigs, true));
}
