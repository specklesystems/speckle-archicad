#include "SpeckleToHostConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

static GSErrCode DeselectAll()
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_Selection_DeselectAll();
#elif defined(AC27)
	err = ACAPI_Selection_DeselectAll();
#elif defined(AC26)
	err = ACAPI_Element_DeselectAll();
#elif defined(AC25)
	err = ACAPI_Element_DeselectAll();
#endif

	return err;
}

static GSErrCode Select(const GS::Array<API_Neig>& selNeigs, bool add)
{
	GSErrCode err = NoError;

#if defined(AC28)
	err = ACAPI_Selection_Select();
#elif defined(AC27)
	err = ACAPI_Selection_Select();
#elif defined(AC26)
	err = ACAPI_Element_Select(selNeigs, add);
#elif defined(AC25)
	err = ACAPI_Element_Select();
#endif

	return err;
}

void SpeckleToHostConverter::SetSelection(std::vector<std::string> guids)
{
	CHECK_ERROR(DeselectAll());
	GS::Array<API_Neig> selNeigs;
	for (const auto& id : guids)
	{
		auto guid = APIGuidFromString(id.c_str());
		API_Neig neig(guid);
		selNeigs.Push(neig);
	}
	CHECK_ERROR(Select(selNeigs, true));
}
