// *****************************************************************************
// 2D Angle, Direction, Deflection and their operations.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************
#if !defined (ANGLEDATA_H)
#define ANGLEDATA_H

#include "GeometricDefinitions.h"


constexpr double	RadEps = 1E-07;			/* Eps for angles in radians; 0.1 mm error through 1 km 										*/
											/* Draw.c:			DrawPictObj()																*/
											/* DrawExt.c:		DivideArcToCo(), DivideEllArcToCo()											*/
											/* DrHatch.c:		ReCalcFill()																*/
											/* GeomElem.cpp:	NormFi02Pi(), ComputeFiPtr()												*/
											/* Group.c:			MakeDefPlaceTran(), Set_HLMSets(), SetChGroupTrafo()						*/
											/* ListSel.c:		WLinAreaTconns()															*/
											/* TM.c:			TranDecompose()																*/
											/* WBUti.c:			GetFactors_WD2(), ElemCrossPoint()											*/
											/* XColumn.c:		CutCmpCmp(), ColumnCutWall(), ColumnCutArcWall(), CalcSectBSectE(),			*/
											/*					CalcWall2Lines(), ColumnLineCutWall(), WrkColumnLines()						*/
											/* XWall2.c:		GetCrossInd(), StoreCoAndAc()												*/

constexpr double	PI     = 3.141592653589793;		/* The Ludolph's constant	*/
constexpr double	RADDEG = 57.29577951308232;		/* Radian->degree conversion ( 180.0/PI ) */
constexpr double	DEGRAD = 0.017453292519943295;	/* Degree->radian conversion ( PI/180.0 ) */


namespace Geometry {

	GEOMETRY_DLL_EXPORT double	NormFi02Pi (double angle, double radEps = RadEps);

	GEOMETRY_DLL_EXPORT double	ArcSin (double a);

	GEOMETRY_DLL_EXPORT double	ArcCos (double a);

	GEOMETRY_DLL_EXPORT double	ArcTan (double y, double x);

	GEOMETRY_DLL_EXPORT double	AddAngle (double a, double b);

	GEOMETRY_DLL_EXPORT double	SubAngle (double a, double b);

	GEOMETRY_DLL_EXPORT double	MidAngle (double alfa, double beta);

						bool	IsInsideAngle (double alfa, double beta, double x);

	GEOMETRY_DLL_EXPORT bool	IsLessThanAngle (double alfa, double beta, double gamma);

	GEOMETRY_DLL_EXPORT bool	NegativeArc (double a, double b);

	GEOMETRY_DLL_EXPORT void	TMDirCoeffs (double x, double y, double z, double *coz, double *siz, double *coxy, double *sixy);

	GEOMETRY_DLL_EXPORT void	TMDir2Angles (double x, double y, double z, double *yangle, double *xangle);

	GEOMETRY_DLL_EXPORT void	AdjustAngle (double* io_angle);
	GEOMETRY_DLL_EXPORT void	AdjustAngles (double* io_angle1, double* io_angle2);
}

/****************************************************************************************************/
/* alfa-beta positively oriented arc; is the x angle between alfa-beta? [all angles between 0..2PI] */
/****************************************************************************************************/

inline bool Geometry::IsInsideAngle (double alfa, double beta, double x)
{
	if (alfa < beta)
		return (alfa < x && x < beta);
	else
		return (alfa < x || x < beta);

// Conversions between angle and direction form
// is too expensive so we use the old fast way

//	DirectionSector2D dirSector = DirectionSector2D (alfa, beta);
//	return dirSector.HasIntersectionWith (Direction2D (x), 0.0);
}


#endif
