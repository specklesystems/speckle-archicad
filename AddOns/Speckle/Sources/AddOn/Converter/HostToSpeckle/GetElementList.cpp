#include "HostToSpeckleConverter.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"
#include <unordered_map>

// one to one mapping from string to api element types
/*static const std::unordered_map<std::string, std::vector<API_ElemTypeID>> stringToElementTypeMap = {
    {"ZombieElem", {API_ZombieElemID}},
    {"Wall", {API_WallID}},
    {"Column", {API_ColumnID}},
    {"Beam", {API_BeamID}},
    {"Window", {API_WindowID}},
    {"Door", {API_DoorID}},
    {"Object", {API_ObjectID}},
    {"Lamp", {API_LampID}},
    {"Slab", {API_SlabID}},
    {"Roof", {API_RoofID}},
    {"Mesh", {API_MeshID}},
    {"Zone", {API_ZoneID}},
    {"CurtainWall", {API_CurtainWallID}},
    {"CurtainWallSegment", {API_CurtainWallSegmentID}},
    {"CurtainWallFrame", {API_CurtainWallFrameID}},
    {"CurtainWallPanel", {API_CurtainWallPanelID}},
    {"CurtainWallJunction", {API_CurtainWallJunctionID}},
    {"CurtainWallAccessory", {API_CurtainWallAccessoryID}},
    {"Shell", {API_ShellID}},
    {"Skylight", {API_SkylightID}},
    {"Morph", {API_MorphID}},
    {"Stair", {API_StairID}},
    {"Riser", {API_RiserID}},
    {"Tread", {API_TreadID}},
    {"StairStructure", {API_StairStructureID}},
    {"Railing", {API_RailingID}},
    {"RailingToprail", {API_RailingToprailID}},
    {"RailingHandrail", {API_RailingHandrailID}},
    {"RailingRail", {API_RailingRailID}},
    {"RailingPost", {API_RailingPostID}},
    {"RailingInnerPost", {API_RailingInnerPostID}},
    {"RailingBaluster", {API_RailingBalusterID}},
    {"RailingPanel", {API_RailingPanelID}},
    {"RailingSegment", {API_RailingSegmentID}},
    {"RailingNode", {API_RailingNodeID}},
    {"RailingBalusterSet", {API_RailingBalusterSetID}},
    {"RailingPattern", {API_RailingPatternID}},
    {"RailingToprailEnd", {API_RailingToprailEndID}},
    {"RailingHandrailEnd", {API_RailingHandrailEndID}},
    {"RailingRailEnd", {API_RailingRailEndID}},
    {"RailingToprailConnection", {API_RailingToprailConnectionID}},
    {"RailingHandrailConnection", {API_RailingHandrailConnectionID}},
    {"RailingRailConnection", {API_RailingRailConnectionID}},
    {"RailingEndFinish", {API_RailingEndFinishID}},
    {"BeamSegment", {API_BeamSegmentID}},
    {"ColumnSegment", {API_ColumnSegmentID}},
    {"Opening", {API_OpeningID}},
};*/

// composite elements are converted as groups
static const std::unordered_map<std::string, std::vector<API_ElemTypeID>> stringToElementTypesMap = {
    {"Wall", {API_WallID}},
    {"Column", {API_ColumnID, API_ColumnSegmentID}},
    {"Beam", {API_BeamID, API_BeamSegmentID}},
    {"Window", {API_WindowID}},
    {"Door", {API_DoorID}},
    {"Object", {API_ObjectID}},
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

std::vector<std::string> HostToSpeckleConverter::GetElementList(const std::vector<std::string>& elementTypes)
{	
    std::vector<std::string> elementList;

    for (const auto& elementType : elementTypes)
    {
        auto it = stringToElementTypesMap.find(elementType);
        if (it != stringToElementTypesMap.end())
        {
            auto types = it->second;
            for (const auto& t : types)
            {
                try
                {
                    GS::Array<API_Guid> elemGuids;
                    CHECK_ERROR(ACAPI_Element_GetElemList(t, &elemGuids));
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

std::vector<std::string> HostToSpeckleConverter::GetElementTypeList()
{
    return {
        "Wall", "Column", "Beam", "Window", "Door", "Object", "Slab", "Roof", "Mesh",
        "Zone", "CurtainWall", "Shell", "Skylight", "Morph", "Stair", "Railing", "Opening"
    };
}
