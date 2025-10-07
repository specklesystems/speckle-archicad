#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

#include <iostream>

/*std::vector<std::string> HostToSpeckleConverter::GetElementListByLayer(const std::vector<int>& layerIndices)
{	
    std::vector<std::string> elementList;

    std::cout << layerIndices.size();

    try
    {
        GS::Array<API_Guid> elemGuids;
        CHECK_ERROR(ACAPI_Element_GetElemList(API_ZombieElemID, &elemGuids));
        for (const auto& apiGuid : elemGuids)
        {
            std::string guid = APIGuidToString(apiGuid).ToCStr().Get();
            elementList.push_back(guid);
        }
    }
    catch (const std::exception&)
    {
        // continue
    }
	
	return elementList;
}*/
