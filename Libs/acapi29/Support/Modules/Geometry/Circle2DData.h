#ifndef CIRCLE2DDATA_H
#define CIRCLE2DDATA_H
#pragma once

#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "UnitVector2DClassDeclaration.hpp"


struct Sector;


namespace Geometry {

class GEOMETRY_DLL_EXPORT Circle2D 
{
public:
	Circle2D ();
	Circle2D (const Point2D& origo, double radius);

	Point2D Origo () const;
	double	Radius () const;

	void SetOrigo (const Point2D& newOrigo);
	void SetRadius (double newRadius);

	//#KiP_Note_GeometryRefactor ide meg kellenek muveletek

private:
	Point2D	origo;
	double radius;
};



class Direction2D;

GEOMETRY_DLL_EXPORT UnitVector_2D GetCircleTangent (
						const Circle2D&		circle,
						const Point2D&		tangentPoint);		/* always counter-clockwise direction on the circle */


GEOMETRY_DLL_EXPORT void Circle_3Pt (
						const Point2D&		c1,
						const Point2D&		c2,
						const Point2D&		c3,
						Point2D*			origo,
						bool*				exist);

GEOMETRY_DLL_EXPORT GS::Optional<Point2D>	Circle_3Pt (const Point2D& p1,
														const Point2D& p2,
														const Point2D& p3);

GEOMETRY_DLL_EXPORT void Circle_2Pt1Lin (const Point2D&		c1,
										 const Point2D&		c2,
										 const Sector&		s,
										 const Point2D&		refCo,
										 Point2D*			origo,
										 bool 				*exist);

GEOMETRY_DLL_EXPORT void Circle_1Pt2Lin (const Point2D&		c,
										 const Sector&		s1,
										 const Sector&		s2,
										 const Point2D&		refCo,
										 Point2D*			origo,
										 bool 				*exist);

GEOMETRY_DLL_EXPORT void Circle_3Lin (const Sector&		s1,
									  const Sector&		s2,
									  const Sector&		s3,
									  const Point2D&	refCo,
									  Point2D*			origo,
									  bool 				*exist);

GEOMETRY_DLL_EXPORT double ChordAngle (double	len,				/* sm014... */
									   double	radius);

GEOMETRY_DLL_EXPORT char XCircleLine	(const Circle2D	*c,
										 const Sector	*s,
										 Sector			*xs);

GEOMETRY_DLL_EXPORT char XCircleLineEps (const Circle2D	*c,
										 const Sector	*s,
										 Sector			*xs,
										 double			eps);

GEOMETRY_DLL_EXPORT char XCircleSector (const Circle2D	*c,
										const Sector	*s,
										Sector			*xs);

GEOMETRY_DLL_EXPORT char XCircleSectorEps (const Circle2D	*c,
										   const Sector	*s,
										   Sector		*xs,
										   double		eps);

GEOMETRY_DLL_EXPORT char XCircleRayEps (const Circle2D	*c,
										const Sector	*s,
										Sector			*xs,
										double			eps);

GEOMETRY_DLL_EXPORT bool XCircles (const Circle2D	*c1,
								   const Circle2D	*c2,
								   Sector		*xs);

GEOMETRY_DLL_EXPORT bool XCirclesEps (const Circle2D	*c1,
									  const Circle2D	*c2,
									  Sector		*xs,
									  double		eps);

GEOMETRY_DLL_EXPORT	bool IsPointOnCircle (const Point2D& point, const Circle2D& circle);

GEOMETRY_DLL_EXPORT GS::Array<Point2D> CalcCircleLineIntersections (const Circle2D& circle, const Point2D& lineCoord, const Vector2D& lineDir);


// class for calculating outer common tangent lines to two circles and touch points of circles and tangent lines
// Outer means: the two input circles are on the same side of tangent line
// Right (resp. left) tangent line is which has touch points on the right (resp. left) side of the central line of the two circle
// viewed from center of circle1 towards the center of circle2
class GEOMETRY_DLL_EXPORT CircleOuterCommonTangentCalculator {
private:
	// input:
	const Circle2D&	mCircle1;
	const Circle2D&	mCircle2;

	// calculated:
	UInt32	mTangentNum;			// number of outer tangents: 0, 1 or 2 (for identical circles we set 0, not infinity)
	Vector2D	mLeftTangentDirUnit;	// unit direction of left tangent line (orientation same as central line from circle1 to circle2)
	Vector2D	mRightTangentDirUnit;	// unit direction of right tangent line (orientation same as central line from circle1 to circle2)
	Vector2D	mLeftRadialDirUnit;		// unit direction radial vector from circle center to touch point on left tangent line (same for the two circles)
	Vector2D	mRightRadialDirUnit;	// unit direction radial vector from circle center to touch point on right tangent line (same for the two circles)

public:
	CircleOuterCommonTangentCalculator (const Circle2D& circle1, const Circle2D& circle2);
	UInt32	GetNumberOfOuterTangents () const;
	Vector2D	GetLeftTangentDir		() const;
	Vector2D	GetRightTangentDir		() const;
	Vector2D	GetRadialToLeftTangent	() const;
	Vector2D	GetRadialToRightTangent	() const;
	Point2D	GetLeftTangentTouchOn1	() const;
	Point2D	GetLeftTangentTouchOn2	() const;
	Point2D	GetRightTangentTouchOn1	() const;
	Point2D	GetRightTangentTouchOn2	() const;
#if defined (DEBUVERS)
	void	DumpGDL () const;
#endif
};


GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLCircle (GS::XMLIChannel& ic, Circle2D& c);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLCircle (GS::XMLOChannel& oc, const Circle2D& c);
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Circle2D& c)	{ return Geometry::ReadXMLCircle (ic, c); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Circle2D& c)	{ return Geometry::WriteXMLCircle (oc, c); }

}

#endif
