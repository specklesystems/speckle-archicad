#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::vector<std::string> HostToSpeckleConverter::GetSelection()
{
	API_SelectionInfo selectionInfo{};
	GS::Array<API_Neig> selection;
	
	try
	{
		CHECK_ERROR(ACAPI_Selection_Get(&selectionInfo, &selection, true));
	}
	catch (const std::exception&)
	{
		// could not get selection
		// it has to be handled locally to return an empty list 
		// instead of a toast error in the SelectionBridge OnRunMethod
	}
	
	std::vector<std::string> selectedElements;
	for (const auto& item : selection)
	{
		std::string guid = APIGuidToString(item.guid).ToCStr().Get();
		selectedElements.push_back(guid);
	}
	return selectedElements;
}
