#include "APIdefs.h"
#include "ElementTypeToStringConverter.h"
#include "ACAPI/MEPAdapter.hpp"
#include <unordered_map>

static const std::unordered_map<API_ElemTypeID, std::string> elementTypeToStringMap = {
    {API_ZombieElemID, "ZombieElem"},
    {API_WallID, "Wall"},
    {API_ColumnID, "Column"},
    {API_BeamID, "Beam"},
    {API_WindowID, "Window"},
    {API_DoorID, "Door"},
    {API_ObjectID, "Object"},
    {API_LampID, "Lamp"},
    {API_SlabID, "Slab"},
    {API_RoofID, "Roof"},
    {API_MeshID, "Mesh"},
    {API_DimensionID, "Dimension"},
    {API_RadialDimensionID, "RadialDimension"},
    {API_LevelDimensionID, "LevelDimension"},
    {API_AngleDimensionID, "AngleDimension"},
    {API_TextID, "Text"},
    {API_LabelID, "Label"},
    {API_ZoneID, "Zone"},
    {API_HatchID, "Hatch"},
    {API_LineID, "Line"},
    {API_PolyLineID, "PolyLine"},
    {API_ArcID, "Arc"},
    {API_CircleID, "Circle"},
    {API_SplineID, "Spline"},
    {API_HotspotID, "Hotspot"},
    {API_CutPlaneID, "CutPlane"},
    {API_CameraID, "Camera"},
    {API_CamSetID, "CamSet"},
    {API_GroupID, "Group"},
    {API_SectElemID, "SectElem"},
    {API_DrawingID, "Drawing"},
    {API_PictureID, "Picture"},
    {API_DetailID, "Detail"},
    {API_ElevationID, "Elevation"},
    {API_InteriorElevationID, "InteriorElevation"},
    {API_WorksheetID, "Worksheet"},
    {API_HotlinkID, "Hotlink"},
    {API_CurtainWallID, "CurtainWall"},
    {API_CurtainWallSegmentID, "CurtainWallSegment"},
    {API_CurtainWallFrameID, "CurtainWallFrame"},
    {API_CurtainWallPanelID, "CurtainWallPanel"},
    {API_CurtainWallJunctionID, "CurtainWallJunction"},
    {API_CurtainWallAccessoryID, "CurtainWallAccessory"},
    {API_ShellID, "Shell"},
    {API_SkylightID, "Skylight"},
    {API_MorphID, "Morph"},
    {API_ChangeMarkerID, "ChangeMarker"},
    {API_StairID, "Stair"},
    {API_RiserID, "Riser"},
    {API_TreadID, "Tread"},
    {API_StairStructureID, "StairStructure"},
    {API_RailingID, "Railing"},
    {API_RailingToprailID, "RailingToprail"},
    {API_RailingHandrailID, "RailingHandrail"},
    {API_RailingRailID, "RailingRail"},
    {API_RailingPostID, "RailingPost"},
    {API_RailingInnerPostID, "RailingInnerPost"},
    {API_RailingBalusterID, "RailingBaluster"},
    {API_RailingPanelID, "RailingPanel"},
    {API_RailingSegmentID, "RailingSegment"},
    {API_RailingNodeID, "RailingNode"},
    {API_RailingBalusterSetID, "RailingBalusterSet"},
    {API_RailingPatternID, "RailingPattern"},
    {API_RailingToprailEndID, "RailingToprailEnd"},
    {API_RailingHandrailEndID, "RailingHandrailEnd"},
    {API_RailingRailEndID, "RailingRailEnd"},
    {API_RailingToprailConnectionID, "RailingToprailConnection"},
    {API_RailingHandrailConnectionID, "RailingHandrailConnection"},
    {API_RailingRailConnectionID, "RailingRailConnection"},
    {API_RailingEndFinishID, "RailingEndFinish"},
    {API_BeamSegmentID, "BeamSegment"},
    {API_ColumnSegmentID, "ColumnSegment"},
    {API_OpeningID, "Opening"},
#ifndef AC25
    {API_ExternalElemID, "ExternalElem"}
#endif
};

std::string ElementTypeToStringConverter::ElementTypeToString(API_ElemTypeID type) 
{
    auto it = elementTypeToStringMap.find(type);
    if (it != elementTypeToStringMap.end()) 
    {
        return it->second;
    }
    return "Unknown Element Type";
}

const std::map<API_Guid, std::string>& ElementTypeToStringConverter::GetMepElementTypes()
{
    using namespace ACAPI::MEP;
    static const std::map<API_Guid, std::string> types = {
#if defined(AC27)
        {VentilationRoutingID, "DuctRoute"},
        {PipingRoutingID, "PipeRoute"},
        {CableCarrierRoutingID, "CableCarrierRoute"},
#else
        {VentilationRoutingElementID, "DuctRoute"},
        {PipingRoutingElementID, "PipeRoute"},
        {CableCarrierRoutingElementID, "CableCarrierRoute"},
#endif
        {VentilationFittingID, "DuctFitting"},
        {PipingFittingID, "PipeFitting"},
        {CableCarrierFittingID, "CableCarrierFitting"},
        {VentilationBranchID, "DuctBranch"},
        {PipingBranchID, "PipeBranch"},
        {CableCarrierBranchID, "CableCarrierBranch"},
        {VentilationTerminalID, "DuctTerminal"},
        {PipingTerminalID, "PipeTerminal"},
        {VentilationAccessoryID, "DuctAccessory"},
        {PipingAccessoryID, "PipeAccessory"},
        {EquipmentID, "Equipment"},
        {VentilationRoutingSegmentID, "DuctRoutingSegment"},
        {PipingRoutingSegmentID, "PipeRoutingSegment"},
        {CableCarrierRoutingSegmentID, "CableCarrierRoutingSegment"},
        {VentilationRoutingNodeID, "DuctRoutingNode"},
        {PipingRoutingNodeID, "PipeRoutingNode"},
        {CableCarrierRoutingNodeID, "CableCarrierRoutingNode"},
        {VentilationRigidSegmentID, "DuctSegment"},
        {PipingRigidSegmentID, "PipeSegment"},
        {CableCarrierRigidSegmentID, "CableCarrierSegment"},
#if defined(AC29)
        {VentilationElbowID, "DuctElbow"},
        {PipingElbowID, "PipeElbow"},
        {CableCarrierElbowID, "CableCarrierElbow"},
#else
        {VentilationBendID, "DuctElbow"},
        {PipingBendID, "PipeElbow"},
        {CableCarrierBendID, "CableCarrierElbow"},
#endif
        {VentilationTransitionID, "DuctTransition"},
        {PipingTransitionID, "PipeTransition"},
        {CableCarrierTransitionID, "CableCarrierTransition"},
        {VentilationFlexibleSegmentID, "DuctFlexibleSegment"},
#if !defined(AC27)
        {PipingFlexibleSegmentID, "PipeFlexibleSegment"},
        {VentilationTakeOffID, "DuctTakeOff"},
#endif
    };
    return types;
}

std::string ElementTypeToStringConverter::ElementTypeToString(const API_ElemType& type)
{
    if (type.typeID == API_ExternalElemID)
    {
        const auto& types = GetMepElementTypes();
        auto it = types.find(type.classID);
        if (it != types.end())
            return it->second;
    }
    return ElementTypeToString(type.typeID);
}
