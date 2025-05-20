#include "HostToSpeckleConverter.h"
#include "APIEnvir.h"
#include "ACAPinc.h"

std::vector<std::string> HostToSpeckleConverter::GetElementListAllVisibleIn3D()
{
    std::vector<std::string> elementList;
    GS::Array<API_Guid> elemGuids;
    ACAPI_Element_GetElemList(API_ZombieElemID, &elemGuids, APIFilt_OnVisLayer | APIFilt_In3D);
    for (const auto& apiGuid : elemGuids)
    {
        std::string guid = APIGuidToString(apiGuid).ToCStr().Get();
        elementList.push_back(guid);
    }

    return elementList;
}
