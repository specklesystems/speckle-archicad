#include "ElementTypeToStringConverter.h"
#include "ACAPI/MEPAdapter.hpp"
#include <iostream>
#include <vector>
#include <utility>
int main()
{
    using namespace ACAPI::MEP;
    const std::vector<std::pair<API_Guid, std::string>> expected = {
#if defined(AC27)
        {VentilationRoutingID, "DuctRoute"}, {PipingRoutingID, "PipeRoute"}, {CableCarrierRoutingID, "CableCarrierRoute"},
#else
        {VentilationRoutingElementID, "DuctRoute"}, {PipingRoutingElementID, "PipeRoute"}, {CableCarrierRoutingElementID, "CableCarrierRoute"},
#endif
        {VentilationFittingID, "DuctFitting"}, {PipingFittingID, "PipeFitting"}, {CableCarrierFittingID, "CableCarrierFitting"},
        {VentilationBranchID, "DuctBranch"}, {PipingBranchID, "PipeBranch"}, {CableCarrierBranchID, "CableCarrierBranch"},
        {VentilationTerminalID, "DuctTerminal"}, {PipingTerminalID, "PipeTerminal"},
        {VentilationAccessoryID, "DuctAccessory"}, {PipingAccessoryID, "PipeAccessory"}, {EquipmentID, "Equipment"},
        {VentilationRoutingSegmentID, "DuctRoutingSegment"}, {PipingRoutingSegmentID, "PipeRoutingSegment"}, {CableCarrierRoutingSegmentID, "CableCarrierRoutingSegment"},
        {VentilationRoutingNodeID, "DuctRoutingNode"}, {PipingRoutingNodeID, "PipeRoutingNode"}, {CableCarrierRoutingNodeID, "CableCarrierRoutingNode"},
        {VentilationRigidSegmentID, "DuctSegment"}, {PipingRigidSegmentID, "PipeSegment"}, {CableCarrierRigidSegmentID, "CableCarrierSegment"},
#if defined(AC29)
        {VentilationElbowID, "DuctElbow"}, {PipingElbowID, "PipeElbow"}, {CableCarrierElbowID, "CableCarrierElbow"},
#else
        {VentilationBendID, "DuctElbow"}, {PipingBendID, "PipeElbow"}, {CableCarrierBendID, "CableCarrierElbow"},
#endif
        {VentilationTransitionID, "DuctTransition"}, {PipingTransitionID, "PipeTransition"}, {CableCarrierTransitionID, "CableCarrierTransition"},
        {VentilationFlexibleSegmentID, "DuctFlexibleSegment"},
#if !defined(AC27)
        {PipingFlexibleSegmentID, "PipeFlexibleSegment"}, {VentilationTakeOffID, "DuctTakeOff"}
#endif
    };
    auto check = [](const API_ElemType& type, const std::string& expectedName) {
        auto actual = ElementTypeToStringConverter::ElementTypeToString(type);
        if (actual != expectedName) {
            std::cerr << "FAIL: expected " << expectedName << ", got " << actual << '\n';
            return false;
        }
        return true;
    };
    for (const auto& [guid, name] : expected)
        if (!check(API_ElemType(guid), name)) return 1;
    if (!check(API_ElemType(APIGuidFromString("{00000000-1111-2222-3333-444444444444}")), "ExternalElem")) return 1;
    if (!check(API_ElemType(API_ExternalElemID), "ExternalElem")) return 1;
    for (int i = API_ZombieElemID; i < API_ExternalElemID; ++i) {
        API_ElemType type(static_cast<API_ElemTypeID>(i));
        type.classID = expected.front().first;
        if (!check(type, ElementTypeToStringConverter::ElementTypeToString(type.typeID))) return 1;
    }
    if (!check(API_ElemType(API_WallID), "Wall") || !check(API_ElemType(API_ObjectID), "Object") || !check(API_ElemType(API_LampID), "Lamp")) return 1;
    if (ElementTypeToStringConverter::GetMepElementTypes().size() != expected.size()) return 1;
    std::cout << "PASS: " << expected.size() << " MEP classes, unknown/null external fallbacks, and all non-MEP enum types\n";
}
