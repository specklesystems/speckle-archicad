#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

std::string SpeckleToHostConverter::CreateGroup(const std::vector<std::string>& memberIds)
{
	GS::Array<API_Guid> group;
	for (const auto& id : memberIds)
	{
		auto guid = APIGuidFromString(id.c_str());
		group.Push(guid);
	}

	//API_Guid groupGuid = APINULLGuid;
	//CHECK_ERROR(ACAPI_Grouping_CreateGroup(group, &groupGuid));
	CHECK_ERROR(ACAPI_CallUndoableCommand("Create Group",
		[&]() -> GSErrCode {
			return ACAPI_Grouping_CreateGroup(group);
		}));

	//return APIGuidToString(groupGuid).ToCStr().Get();
	return "asd";
}
