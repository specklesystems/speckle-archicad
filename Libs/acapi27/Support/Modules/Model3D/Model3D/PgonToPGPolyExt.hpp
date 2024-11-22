// *********************************************************************************************************************
// Convert a Modeler::Polygon to a PGPOLYEXT.
// *********************************************************************************************************************

#if !defined(PGONTOPGPOLYEXT_HPP)
#define PGONTOPGPOLYEXT_HPP
#pragma once

#include "Definitions.hpp"

#include "Model3DExport.h"

#include "Polygon2DOperations.h"
#include "Vector3D.hpp"

struct TRANMAT;

namespace Modeler {
	class Elem;
	class MeshBody;
}

namespace Modeler {

enum SignificantCoordinate { SigCoord_X, SigCoord_Y, SigCoord_Z };

struct MODEL3D_DLL_EXPORT PgonEdgeExtData
{

	const TRANMAT*				tran;
	const Modeler::MeshBody*		body;
	UIndex						pgonIdx;
	SignificantCoordinate		significantCoordinate;
};


MODEL3D_DLL_EXPORT
void	CalcPGPolyBBox (Geometry::PGPOLYEXT& pgPoly);

MODEL3D_DLL_EXPORT
Coord ProjectCoord3DWithSignificantCoord (const Coord3D& c,
										  const Modeler::SignificantCoordinate significantCoordinate);

MODEL3D_DLL_EXPORT
void	InitPGPoly (Geometry::PGPOLYEXT& pgPoly);


enum PGPolyBoxCalculation { PGPoly_CalcBBox, PGPoly_DontCalcBBox, PGPoly_FillInfiniteBBox };

MODEL3D_DLL_EXPORT
void	FillPGPolyExtFromPgon (Geometry::PGPOLYEXT&			pgPoly,
							   PgonEdgeExtData*				data,
							   const Modeler::Elem&			elem,
							   const Modeler::MeshBody&		body,
							   const UIndex					polygonIndex,
							   const PGPolyBoxCalculation	bboxCalc);

} // namespace Modeler




#endif // PGONTOPGPOLYEXT_HPP
