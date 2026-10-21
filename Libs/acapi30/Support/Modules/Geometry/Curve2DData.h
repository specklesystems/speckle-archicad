#if !defined (CURVE2DDATA_H)
#define CURVE2DDATA_H

#pragma once
// Geometry internal!!!

#include	"GeometricDefinitions.h"
#include	"RealNumber.h"
#include	"AngleData.h"

#include	"Point2DData.h"
#include	"Vector2D.hpp"

#include	"Direction2D.hpp"
#include	"Sector2DData.h"
#include	"GenArc2DData.h"
#include	"BezierDetails.hpp"

namespace Geometry {

	enum Curve2DDataType {
		CURVE2D_NULL,		// The invalid state
		CURVE2D_Point,		// A single point (Coord)
		CURVE2D_Sector,		// A sector of a straight line
		CURVE2D_Ray,		// A straight line limited only at the first end, but unlimited to the other
		CURVE2D_Line,		// A straight line

		CURVE2D_Circle,		// circle
		CURVE2D_GenArc,		// Circle, Arc, Ellipse, Ellipse Arc

		CURVE2D_Spline,		// sm405 used by CutElems
		CURVE2D_PolyLine,	// VBElems::Polygondata.GeomData-like, considered as a curve (even if closed)
		CURVE2D_2DPolygon	// Geometry-like (Polygon2DData), considered as a shpape
	};

	struct Curve2DData {
		Curve2DDataType	type;
		double			epsilon;
		double			angleEpsilon;

		// only one of them valid - was union
		Point2D	point;
		Sector	sector;
		GenArc	genArc;

		BezierDetails spline;
	};

	inline void		InitCurve2DData (Curve2DData* curve, double eps = Eps, double angEps = RadEps);

	GEOMETRY_DLL_EXPORT void	InitCurve2DData (Curve2DData* curve, const Point2D&  point, double eps = Eps, double angEps = RadEps);
	GEOMETRY_DLL_EXPORT void	InitCurve2DData (Curve2DData* curve, const Sector& sector, Curve2DDataType type, double eps = Eps, double angEps = RadEps);
	GEOMETRY_DLL_EXPORT void	InitCurve2DData (Curve2DData* curve, const Circle2D& circle, double eps = Eps, double angEps = RadEps);
	GEOMETRY_DLL_EXPORT void	InitCurve2DData (Curve2DData* curve, const GenArc& genArc, double eps = Eps, double angEps = RadEps);
	GEOMETRY_DLL_EXPORT void	InitCurve2DData (Curve2DData* curve, const BezierDetails& spline, double eps = Eps, double angEps = RadEps);

	inline bool		IsCurve2DDataStraight (const Curve2DData& curve);

	GEOMETRY_DLL_EXPORT Point2D	GetCurve2DDataBegPosition (const Curve2DData& curve);
	GEOMETRY_DLL_EXPORT Point2D	GetCurve2DDataEndPosition (const Curve2DData& curve);

	GEOMETRY_DLL_EXPORT Box2DData	GetCurve2DDataBoundingBox (const Curve2DData& curve);

	GEOMETRY_DLL_EXPORT UnitVector_2D GetCurve2DDataBegDirection (const Curve2DData& curve);
	GEOMETRY_DLL_EXPORT UnitVector_2D GetCurve2DDataEndDirection (const Curve2DData& curve);

	GEOMETRY_DLL_EXPORT bool	OffsetCurve2DData (
				const Curve2DData&	curveIn,
				double				offset,
				Curve2DData*		curveOut,
				Point2D*				refPt = nullptr);	/* [in, out], can be nullptr */

	GEOMETRY_DLL_EXPORT GSErrCode	GetMaxOffsetValue (
				const Curve2DData&	curve1In,
				const Curve2DData&	curve2In,
				double				triedOffset,
				double*				maxOffset);

	enum NeighbourCircleCenter {
		FixNeighbourCircleCenter,
		MovingNeighbourCircleCenter
	};

	GEOMETRY_DLL_EXPORT void		LimitOffsetForArc (
						const Curve2DData&	prevEdgeCurve,
						const Curve2DData&	nextEdgeCurve,
						const Curve2DData&	originalCurve,
						double				offset,
						double*				maxBegOffset,
						double*				maxEndOffset,
						NeighbourCircleCenter	neighbourCircleCenter = MovingNeighbourCircleCenter);

	GEOMETRY_DLL_EXPORT double		LimitOffsetToXNeigEdges (
						const Curve2DData&	begXEdgeCurve,
						const Curve2DData&	endXEdgeCurve,
						const Curve2DData&	originalCurve,
						double				offset);

	/* return value: number of valid intersections */
	GEOMETRY_DLL_EXPORT Int32	IntersectCurve2DData (const Curve2DData& curve1, const Curve2DData& curve2, Point2D result[4]);

	enum GetGivenDistantPointResult {
		DistantPointError,
		DistantPointNoIntersection,
		DistantPointSuccess
	};
	GEOMETRY_DLL_EXPORT GetGivenDistantPointResult	GetGivenDistantPoint (					/* RJ003 */
																const Curve2DData&	curvePrev,
																double				offset1,
																const Curve2DData&	curveNext,
																double				offset2,
																const Point2D&		refPt,
																Point2D*				result,
																Curve2DData*		offsetedCurve1 = nullptr,
																Curve2DData*		offsetedCurve2 = nullptr);

	typedef const std::function<void (const Point2D&)>& CoordResultFn;

	GEOMETRY_DLL_EXPORT void	IntersectCurve2DData (const Curve2DData& curve1, const Curve2DData& curve2, CoordResultFn resultCallback);
	GEOMETRY_DLL_EXPORT void	IntersectCurve2DData (const Curve2DData& curve1, const Curve2DData& curve2, GS::Array<Point2D>& result);

	GEOMETRY_DLL_EXPORT void	ExtendCurveLine		(Curve2DData& curve);

	GEOMETRY_DLL_EXPORT Curve2DData	ToCurve2DData (const GenArc& arc);
	GEOMETRY_DLL_EXPORT Curve2DData	ToCurve2DDataLine (const Sector& s);
	GEOMETRY_DLL_EXPORT Curve2DData	ToCurve2DData (const BezierDetails& bez);

	GEOMETRY_DLL_EXPORT	Curve2DData	Line (const Point2D& a, double alfa);
	GEOMETRY_DLL_EXPORT	Curve2DData	Line (const Point2D& a, const Point2D& b);

} // namespace Geometry

inline void Geometry::InitCurve2DData (Curve2DData* curve, double eps, double angEps)
{
	BNZeroMemory (&curve->point, sizeof (Point2D));
	BNZeroMemory (&curve->sector, sizeof (Sector));
	curve->genArc = GenArc ();
	// don't BNZeroMemory the BezierDetails!

	curve->type			= CURVE2D_NULL;
	curve->epsilon		= eps;
	curve->angleEpsilon = angEps;
}


inline bool Geometry::IsCurve2DDataStraight (const Curve2DData& curve)
{
	return (curve.type != CURVE2D_Circle && curve.type != CURVE2D_GenArc);
}

#endif
