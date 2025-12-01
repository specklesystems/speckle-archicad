// *****************************************************************************
// TMB routines.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#ifndef	_TMB_H_
#define	_TMB_H_

#pragma once

#include "GeometricDefinitions.h"
#include "Point3DData.h"
#include "UnitVector3DClassDeclaration.hpp"


typedef struct BASTRAN {
	double	tmx[9];
} BASTRAN;				/* 72 */

namespace Geometry {

	GEOMETRY_DLL_EXPORT void	TMBSet (BASTRAN *bastran, const Point3D *e1, const Point3D *e2, const Point3D *e3);

	GEOMETRY_DLL_EXPORT void	TMBVect (const BASTRAN *bastran, const Point3D *r, Point3D *rr);

	GEOMETRY_DLL_EXPORT void	TMBCalcRottran (const UnitVector_3D& axis, double angle, BASTRAN* resultTran);
}

#endif
