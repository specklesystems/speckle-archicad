#pragma once

#include <string>

// The layer attribute an element sits on, resolved from API_Elem_Head::layer.
//
// Archicad layers are FLAT — there is no layer hierarchy (Layer Combinations are a
// separate, orthogonal concept) — so the bundle CONTAINER built from this never gets
// a parent. id is empty when the element carries no valid layer
// (APIInvalidAttributeIndex == 0), which is the signal to emit no IN_COLLECTION edge.
struct ArchicadLayer
{
    std::string id = "";   // layer attribute index as text (matches LayerData::id)
    std::string name = "";
};
