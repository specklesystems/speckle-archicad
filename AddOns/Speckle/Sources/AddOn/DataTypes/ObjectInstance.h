#pragma once

#include <array>
#include <string>

#include "ElementBody.h"

// Instancing payload for a GDL / library-part "Object" element.
//
// Archicad places every object from a library-part definition through a
// local->world transform; the Modeler exposes BOTH the untransformed (ElemLocal)
// geometry and that transform directly (MeshBody::GetVertex with
// CoordinateSystem::ElemLocal, and Element::GetElemLocalToWorldTransformation).
// We hash the local geometry into a stable definitionId so identical placements
// collapse to one shared DEFINITION, and store the per-placement transform on the
// INSTANCE. Rendering is exact by construction: world == transform * local.
struct ObjectInstance
{
    // false -> not an instanceable object (wrong type, grid element, or empty/failed
    // extraction); the caller bakes world-coordinate geometry instead.
    bool valid = false;

    // Geometry-hash identity: SHA-256 hex of the quantized ElemLocal meshes + material
    // indices. Two placements of the same shape share this id -> one DEFINITION, N INSTANCEs.
    std::string definitionId;

    // Row-major 4x4 local->world transform (last row 0 0 0 1) in the exact layout the
    // bundle's nodes.transform CSV expects (16 doubles, M11..M44).
    std::array<double, 16> transform{};

    // Untransformed definition geometry (ElemLocal coordinate system).
    ElementBody localBody;
};
