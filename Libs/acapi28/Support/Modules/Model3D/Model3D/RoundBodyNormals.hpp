// *********************************************************************************************************************
// Description:		Calculates the normals of the body
//
// Module:			Model3D
// Namespace:		Modeler
// Contact person:	FGY, BA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_ROUNDBODYNORMALS_HPP)
#define GS_MODELER_ROUNDBODYNORMALS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"Array.hpp"

// from Geometry
#include	"Vector3D.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {
	class MeshBody;
}

namespace Modeler {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

enum EdgeVertexPolygonConfiguration {
	Vert1Pgon1 = 0,
	Vert2Pgon1 = 1,
	Vert1Pgon2 = 2,
	Vert2Pgon2 = 3
};


void GenerateOneBodyNormalVectors (const MeshBody* abody, GS::Array<Vector3D>& vectArray);

} // Modeler
#endif  // GS_MODELER_ROUNDBODYNORMALS_HPP
