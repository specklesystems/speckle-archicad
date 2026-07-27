#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"

#include "APIEnvir.h"
#include "ACAPinc.h"

namespace
{
	// Which element types count as OCCUPYING a zone rather than bounding or intersecting it.
	//
	// API_RoomRelation::elementsGroupedByType returns everything related to the room —
	// including the walls, slabs, roofs and shells that ENCLOSE it. Emitting IN_ROOM for
	// those would say a wall "occupies" the room, which is wrong: enclosure is what BOUNDS
	// is for. So occupancy is an explicit allowlist rather than a denylist, and it lands on
	// roughly the same set Revit's FamilyInstance.Room covers (furniture / lamps / openings),
	// plus the free-standing element types.
	const API_ElemTypeID s_occupantTypes[] = {
		API_ObjectID,
		API_LampID,
		API_WindowID,
		API_DoorID,
		API_StairID,
		API_RailingID,
		API_MorphID,
		API_ColumnID,
	};

	void AppendGuids(const GS::Array<API_Guid>& guids, std::vector<std::string>& out)
	{
		for (const auto& guid : guids)
			out.push_back(APIGuidToString(guid).ToCStr().Get());
	}

	// Owns the room-relation handles; the struct carries handle-backed arrays that the API
	// requires us to release through its own disposer.
	struct RoomRelationGuard
	{
		API_RoomRelation relation{};
		~RoomRelationGuard() { ACAPI_DisposeRoomRelationHdls(&relation); }
	};

	ArchicadRoomTopology GetZoneTopology(const API_Guid& zoneGuid)
	{
		ArchicadRoomTopology topology;

		RoomRelationGuard guard;
		// API_ZombieElemID = "every related type", so one call returns occupants AND the
		// bordering wall parts.
		if (ACAPI_Element_GetRelations(zoneGuid, API_ZombieElemID, &guard.relation) != NoError)
			return topology;

		for (const API_ElemTypeID typeID : s_occupantTypes)
		{
			if (const GS::Array<API_Guid>* guids = guard.relation.elementsGroupedByType.GetPtr(typeID))
				AppendGuids(*guids, topology.occupantElementIds);
		}

		// wallPart holds the wall segments that border the zone polygon. cwSegmentPart is
		// deliberately NOT read: it identifies curtain wall SEGMENTS, which are not emitted as
		// objects (see GetElementChildren — segments carry no body and have no back-reference
		// from frames/panels), so such an edge could never resolve to a sent object.
		for (const auto& wallPart : guard.relation.wallPart)
			topology.boundingElementIds.push_back(APIGuidToString(wallPart.guid).ToCStr().Get());

		return topology;
	}

	// Doors, windows and skylights report the zones on either side directly — the exact
	// analogue of Revit's FamilyInstance.FromRoom / .ToRoom. No derivation from wall
	// adjacency needed.
	ArchicadRoomTopology GetOpeningTopology(const API_Guid& openingGuid)
	{
		ArchicadRoomTopology topology;

		// API_WindowRelation / API_DoorRelation / API_SkylightRelation are all aliases of
		// API_CWPanelRelation: two plain guids, no handles, so nothing to dispose.
		API_CWPanelRelation relation{};
		if (ACAPI_Element_GetRelations(openingGuid, API_ZoneID, &relation) != NoError)
			return topology;

		if (relation.fromRoom != APINULLGuid)
			topology.fromRoomId = APIGuidToString(relation.fromRoom).ToCStr().Get();
		if (relation.toRoom != APINULLGuid)
			topology.toRoomId = APIGuidToString(relation.toRoom).ToCStr().Get();

		return topology;
	}
}

// Spatial topology for one element: what a zone contains and what bounds it, or which two
// zones an opening connects. Empty for every other element type.
ArchicadRoomTopology HostToSpeckleConverter::GetElementRoomTopology(const std::string& elemId)
{
	auto apiElem = ConverterUtils::GetElement(elemId);

	switch (apiElem.header.type.typeID)
	{
	case API_ZoneID:
		return GetZoneTopology(apiElem.header.guid);
	case API_WindowID:
	case API_DoorID:
	case API_SkylightID:
		return GetOpeningTopology(apiElem.header.guid);
	default:
		return {};
	}
}
