// *****************************************************************************
// C style struct for 2D Vectors and Points
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (POINT2DDATA_H)
#define POINT2DDATA_H

#pragma once

#include "Point2D.hpp"
#include "AngleData.h"


namespace GS {
	class IChannel;
	class OChannel;
}

namespace Geometry {

	GEOMETRY_DLL_EXPORT Point2D	PolarCoord (const Point2D& origo, double r, double a);

	GEOMETRY_DLL_EXPORT Point2D	ToGlobalCoords (const Point2D& localOrigo, const Vector2D& localDirection, const Point2D& localRep);

	inline				bool	IsEqualCoord (const Point2D& c1, const Point2D& c2, double epsilon);

	GEOMETRY_DLL_EXPORT bool	IsColinVectors (const Vector2D& v1, const Vector2D& v2, double radEps = RadEps, double minLengthEps = EPS);

	GEOMETRY_DLL_EXPORT void	IVCoord (GS::PlatformSign inplatform, Point2D *c);
	GEOMETRY_DLL_EXPORT void	IVCoord (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Point2D *c);
	GEOMETRY_DLL_EXPORT void	IVVector (GS::PlatformSign inplatform, Vector2D *v);
	GEOMETRY_DLL_EXPORT void	IVVector (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Vector2D *v);

	GEOMETRY_DLL_EXPORT Point2D	GrowCoord (const Point2D& origo, const Point2D& c, double factor);

	GEOMETRY_DLL_EXPORT Point2D	RotCoord (const Point2D& oc, const Point2D& wc, double si, double co);
	GEOMETRY_DLL_EXPORT Point2D	RotCoord0 (const Point2D& wc, double si, double co);

	inline				double	Dist (const Point2D&	c1, const Point2D& c2);
	inline				double	DistSqr (const Point2D& c1, const Point2D& c2);

	GEOMETRY_DLL_EXPORT double	ComputeFi (const Point2D& c1, const Point2D& c2);
	GEOMETRY_DLL_EXPORT double	CalcRotFi (double 	a1, double	a2, bool	negArc);
	GEOMETRY_DLL_EXPORT double	ComputeRotFi (const Point2D& o, const Point2D& c1, const Point2D& c2, bool negArc);

	GEOMETRY_DLL_EXPORT double	GetVectorsRelAngle (const Vector2D& a1, const Vector2D& a2);
	GEOMETRY_DLL_EXPORT double	GetCornerAngle (const Point2D& o, const Point2D& c1, const Point2D& c2);
	GEOMETRY_DLL_EXPORT bool		IsVectBetweenTwoVect (Vector v1, Vector v2, Vector vectToTest);

	GEOMETRY_DLL_EXPORT Vector2D	UnitVector (const Vector2D& v);

	GEOMETRY_DLL_EXPORT Vector2D	Rot90CW (const Vector2D& v);	//clockwise rotation with 90 degree
	GEOMETRY_DLL_EXPORT Vector2D	Rot90ACW (const Vector2D& v);	//anti clockwise rotation with 90 degree

	GEOMETRY_DLL_EXPORT double	MulsVectors (const Vector2D& v1, const Vector2D& v2);
	GEOMETRY_DLL_EXPORT Vector2D	MulVector (const Vector2D& v, double r);

	GEOMETRY_DLL_EXPORT Point2D	MiddleCoord (const Point2D& a, const Point2D& b);

	GEOMETRY_DLL_EXPORT Vector2D	SubPoint (const Point2D& p1, const Point2D& p2);

	GEOMETRY_DLL_EXPORT Point2D	InterpolateCoord (const Point2D& a, const Point2D& b, double ratio);

	inline double DistSqr (const Point2D& c1, const Point2D& c2)
	{
		const double dx = c1.x - c2.x;
		const double dy = c1.y - c2.y;
		return dx * dx + dy * dy;
	}


	inline double Dist (const Point2D& c1, const Point2D& c2)
	{
		return sqrt (DistSqr (c1, c2));
	}


	inline bool IsEqualCoord (const Point2D& c1, const Point2D& c2, double epsilon)
	{
		return IsNearZero (DistSqr (c1, c2), epsilon * epsilon);
	}

	inline bool IsLessByXY(const Coord& c1, const Coord& c2)
	{
		return IsLess(c1.x, c2.x) || (IsNear(c1.x, c2.x) && IsLess(c1.y, c2.y));
	}
	inline bool IsGreaterByXY(const Coord& c1, const Coord c2)
	{
		return IsLessByXY(c2, c1);
	}
	inline bool IsLessOrNearByXY(const Coord& c1, const Coord& c2)
	{
		return !IsLessByXY(c2, c1);
	}
	inline bool IsGreaterOrNearByXY(const Coord& c1, const Coord& c2)
	{
		return !IsLessByXY(c1, c2);
	}

	inline Coord MINByXY(const Coord& c1, const Coord& c2)
	{
		return IsLessByXY(c1, c2) ? c1 : c2;
	}
	inline Coord MAXByXY(const Coord& c1, const Coord& c2)
	{
		return IsLessByXY(c1, c2) ? c2 : c1;
	}

	GEOMETRY_DLL_EXPORT void	IVF_Coord (GS::PlatformSign inplatform, Point2f *c);
	GEOMETRY_DLL_EXPORT void	IVF_Coord (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Point2f *c);

	GEOMETRY_DLL_EXPORT void	IVF_Vector (GS::PlatformSign inplatform, Vector2f *v);
	GEOMETRY_DLL_EXPORT void	IVF_Vector (GS::PlatformSign inplatform, GS::PlatformSign toplatform, Vector2f *v);

	GEOMETRY_DLL_EXPORT void	F_CoordToCoord (Point2D* dCo, const Point2f* fCo);

	GEOMETRY_DLL_EXPORT void	CoordToF_Coord (Point2f* fCo, const Point2D* dCo);

	GEOMETRY_DLL_EXPORT void	GetExtremePointsOfPointSetByDir (const GS::Array<Point2D>& pointSet, const Vector2D& direction, GS::Array<Point2D>& minima, GS::Array<Point2D>& maxima);

}

#endif