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
#include	"Model3D/model.h"

namespace Modeler {
	class MeshBody;
}

namespace Modeler {

	/********************************************************************************/
	/*																				*/
	/*		DIVIDE A CONCAVE POLYGON (OR POL. WITH A HOLE) TO CONVEX POLYGONS		*/
	/*																				*/
	/*				convexIverts[0]:  (-) Number of convex polygons					*/
	/*				convexIverts[1]:  (-) Number of nodes of the 1st convex pol.	*/
	/*				convexIverts[2]:  index of 1st vertex of 1st convex pol.		*/
	/*				convexIverts[3]:  index of 2nd vertex of 1st convex pol.		*/
	/*				...																*/
	/*				convexIverts[.]:  (-) Number of nodes of the 2nd convex pol.	*/
	/*				...																*/
	/*																				*/
	/********************************************************************************/
	MODEL3D_DLL_EXPORT
	void	MODEL3D_CALL	DecomposePolygonToConvexIverts (const MeshBody& body, const PGON& pgon, GS::PagedArray<Int32>& convexIverts);

}	// namespace Modeler


#endif	// CONVEXDECOMPOSITION_HPP
