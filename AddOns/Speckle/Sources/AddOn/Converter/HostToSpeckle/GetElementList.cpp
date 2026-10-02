#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include <algorithm>

struct ElementTypeCategory
{
    std::string name;
    std::vector<API_ElemTypeID> types;
};

// composite elements are converted as groups
static const std::vector<ElementTypeCategory> elementTypeCategories = {
    {"Wall", {API_WallID}},
    {"Column", {API_ColumnID, API_ColumnSegmentID}},
    {"Beam", {API_BeamID, API_BeamSegmentID}},
    {"Window", {API_WindowID}},
    {"Door", {API_DoorID}},
    {"Object", {API_ObjectID}},
    {"Lamp", {API_LampID}},
    {"Slab", {API_SlabID}},
    {"Roof", {API_RoofID}},
    {"Mesh", {API_MeshID}},
    {"Zone", {API_ZoneID}},
    {"CurtainWall", {API_CurtainWallID, API_CurtainWallSegmentID, API_CurtainWallFrameID, 
        API_CurtainWallPanelID, API_CurtainWallJunctionID, API_CurtainWallAccessoryID}},
    {"Shell", {API_ShellID}},
    {"Skylight", {API_SkylightID}},
    {"Morph", {API_MorphID}},
    {"Stair", {API_StairID, API_RiserID, API_TreadID, API_StairStructureID}},
    {"Railing", {API_RailingID, API_RailingToprailID, API_RailingHandrailID, API_RailingRailID, API_RailingPostID, 
        API_RailingInnerPostID, API_RailingBalusterID, API_RailingPanelID, API_RailingSegmentID, API_RailingNodeID,
        API_RailingBalusterSetID, API_RailingPatternID, API_RailingToprailEndID, API_RailingHandrailEndID, API_RailingRailEndID,
        API_RailingToprailConnectionID, API_RailingHandrailConnectionID, API_RailingRailConnectionID, API_RailingEndFinishID}},
    {"Opening", {API_OpeningID}},
};

static const std::vector<API_ElemTypeID>* FindElementTypes(const std::string& category)
{
    auto it = std::find_if(elementTypeCategories.begin(), elementTypeCategories.end(),
        [&](const ElementTypeCategory& entry) { return entry.name == category; });
    return it != elementTypeCategories.end() ? &it->types : nullptr;
}

// Marker symbols of sections, elevations, details, worksheets and changes are API_ObjectID
// sub-elements with no name or geometry; only independent Objects are placed library parts (ENG-10270).
static API_ElemFilterFlags GetElemListFilter(API_ElemTypeID type)
{
    return type == API_ObjectID ? APIFilt_IsIndependent : APIFilt_None;
}

std::vector<std::string> HostToSpeckleConverter::GetElementList(const std::vector<std::string>& elementTypes)
{	
    std::vector<std::string> elementList;

    for (const auto& elementType : elementTypes)
    {
        if (const auto* types = FindElementTypes(elementType))
        {
            for (const auto& t : *types)
            {
                try
                {
                    GS::Array<API_Guid> elemGuids;
                    CHECK_ERROR(ACAPI_Element_GetElemList(t, &elemGuids, GetElemListFilter(t)));
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
            }
        }
    }
	
	return elementList;
}

std::vector<std::string> HostToSpeckleConverter::GetElementListByLayer(const std::vector<std::string>& layerIndices)
{
    std::vector<std::string> elementList;

    for (const auto& category : elementTypeCategories)
    {
        for (const auto& t : category.types)
        {
            try
            {
                GS::Array<API_Guid> elemGuids;
                CHECK_ERROR(ACAPI_Element_GetElemList(t, &elemGuids, GetElemListFilter(t)));
                for (const auto& apiGuid : elemGuids)
                {
                    API_Element element = {};
                    element.header.guid = apiGuid;

                    if (ACAPI_Element_GetHeader(&element.header) == NoError)
                    {
#if defined(AC26)
                        std::string layerIndex = std::to_string(element.header.layer);
#else
                        std::string layerIndex = element.header.layer.ToUniString().ToCStr().Get();
#endif

                        if (std::find(layerIndices.begin(), layerIndices.end(), layerIndex) != layerIndices.end())
                        {
                            std::string guid = APIGuidToString(apiGuid).ToCStr().Get();
                            elementList.push_back(guid);
                        }
                    }
                }
            }
            catch (const std::exception&)
            {
                // continue
            }
        }
    }

    return elementList;
}

std::vector<std::string> HostToSpeckleConverter::GetElementTypeList()
{
    std::vector<std::string> names;
    for (const auto& category : elementTypeCategories)
    {
        names.push_back(category.name);
    }
    return names;
}
