#pragma once

#include <string>
#include <vector>

// Spatial topology read off an element via ACAPI_Element_GetRelations. Only one half is
// ever populated: the zone half for API_ZoneID elements, the opening half for
// doors/windows/skylights.
//
// Guids only — they are resolved to bundle relations after the whole selection has been
// emitted, since an endpoint may not be a sent object.
struct ArchicadRoomTopology
{
    // ── zone side (API_RoomRelation) ──────────────────────────────────────
    // Elements that OCCUPY the zone (furniture, lamps, openings, stairs, ...) -> IN_ROOM.
    std::vector<std::string> occupantElementIds;
    // Wall parts that BORDER the zone polygon -> BOUNDS.
    std::vector<std::string> boundingElementIds;

    // ── opening side (API_CWPanelRelation) ────────────────────────────────
    // The two zones a door/window/skylight connects. Either may be empty (an opening on an
    // exterior wall has only one side inside a zone). -> CONNECTS_TO, scoped by the opening.
    std::string fromRoomId = "";
    std::string toRoomId = "";
};
