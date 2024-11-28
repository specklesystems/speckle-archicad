// *****************************************************************************
// Convex decomposition of a polygon
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          FGY
//
// SG compatible
// *****************************************************************************

#if !defined(CONVEXDECOMPOSITION_HPP)
#define CONVEXDECOMPOSITION_HPP

#pragma once

#include	"Model3D/Model3DExport.h"
#include	"Definitions.hpp"
#include	"QuickTriangulation.h"
#include	"Model3D/model.h"

namespace Modeler {
	class MeshBody;
	class CandidateMeshBody;
}

namespace Modeler {

	MODEL3D_DLL_EXPORT
	void	MODEL3D_CALL	DecomposePolygon (const MeshBody& body, const PGON& pgon, DecArray& convexdp);

	MODEL3D_DLL_EXPORT
	void	MODEL3D_CALL	DecomposePgon (const CandidateMeshBody& body, UInt32 polygonIndex, Int32** cpols);

}	// namespace Modeler


#endif	// CONVEXDECOMPOSITION_HPP
