// *****************************************************************************
// Obsolete functions in Geometry
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (GEOMETRICOBSOLETES_H)
#define GEOMETRICOBSOLETES_H

#pragma once

#include "GeometricDefinitions.h"
#include "Box2DData.h"

struct PolyArcRec;

namespace Geometry {
namespace Deprecated {

inline bool		CoordInBox (const Point2D& c, const Box2DData& b, double eps)
{
	return IsBoxPointIntersect (b, c, Geometry::Boundary_Closed, (eps));
}

GEOMETRY_DLL_EXPORT void	MatProdVect (Int32 n, double* mat, double* vect, double* newv);


GEOMETRY_DLL_EXPORT bool	CUClipPoly (Box2DData *clip,
										Int32 ipa, Int32 *parts,
										Int32 ipb, UInt32 *pends,
										Int32 ipc, double *pcoos,
										Int32 *jpa, Int32 **cparts,
										Int32 *jpb, UInt32 **cpends,
										Int32 *jpc, double **cpcoos,
										Int32 *wrcode);

#define OutsidePoly		0		/* CoordInPoly Return values	*/
#define InsidePoly		1
#define OnPolyEdge		2

GEOMETRY_DLL_EXPORT void	GetOriandAngle (						/* RJ003 */
		const	PolyArcRec*	arcP,	/* fgy032 */
		Int32				arcInd,
		const Point2D*		c1,
		const Point2D*		c2,
		Point2D*				ori,
		double*				fi);

GEOMETRY_DLL_EXPORT void	Arc_Extent_Dir (const Point2D   *origo,
											const Point2D	*firstP,
											const Point2D	*lastP,
											double  angle,
											double  radius,
											double	*miny,
											double	*maxy,
											double	*minx,
											double	*maxx,
											char    *arcFirstDir,
											char    *arcSecondDir);

GEOMETRY_DLL_EXPORT short	Check_CoordInPoly (Int32			nSubPolys,
											   Int32			nArcs,
											   const Point2D	*myPolyCoordsPtr,
											   const Int32		*mySubPolyEndsPtr,
											   const PolyArcRec	*myPolyArcsPtr,
											   const Point2D	*theCoord,
											   Int32			*coordIndex);

GEOMETRY_DLL_EXPORT GSErr	InvMat (short n, double *a, double *inva);
GEOMETRY_DLL_EXPORT void	TMPoint (const TRANMAT *tran, double *x, double *y, double *z);

GEOMETRY_DLL_EXPORT inline void	TMPoint0 (const double *tran, double *x, double *y, double *z)

{	double	x1, y1, z1;

	x1 = tran[0] * *x + tran[1] * *y + tran[2] * *z;
	y1 = tran[3] * *x + tran[4] * *y + tran[5] * *z;
	z1 = tran[6] * *x + tran[7] * *y + tran[8] * *z;
	*x = x1;
	*y = y1;
	*z = z1;
}

}	// namespace Deprecated
}	// namespace Geometry

#endif
