#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::vector<std::string> HostToSpeckleConverter::GetSelection()
{
	API_SelectionInfo selectionInfo{};
	GS::Array<API_Neig> selection;
	CHECK_ERROR(ACAPI_Selection_Get(&selectionInfo, &selection, true));
	
	std::vector<std::string> selectedElements;
	for (const auto& item : selection)
	{
		std::string guid = APIGuidToString(item.guid).ToCStr().Get();
		selectedElements.push_back(guid);
	}
	return selectedElements;
}
