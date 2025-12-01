// Contact person: PR

#ifndef CUBICBEZIERCURVE3D_HPP
#define CUBICBEZIERCURVE3D_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "Vector3D.hpp"
#include "Box3DData.h"


struct Sector3D;
namespace Geometry { class Plane; }
namespace Geometry { class Transformation3D; }
namespace Math { class Interval; }


namespace Geometry {


class GEOMETRY_DLL_EXPORT CubicBezierCurve3D
{
public:
	enum BezierSegmentMode {
		FirstSegment	= 1,
		NormalSegment	= 2,
		LastSegment		= 3
	};

private:
	Point3D		m_startPoint;
	Point3D		m_endPoint;
	Vector3D	m_startHandle;
	Vector3D	m_endHandle;

	Point3D		m_startControl;		// control = point + handle
	Point3D		m_endControl;

public:
	static CubicBezierCurve3D	CreateFromPolylineSegment (const Point3D& beforeStartPoint, const Point3D& segmentStartPoint, const Point3D& segmentEndPoint, const Point3D& afterEndPoint, BezierSegmentMode segmentMode);

	CubicBezierCurve3D		() = default;
	CubicBezierCurve3D		(const Point3D& startPoint, const Vector3D& startHandle, const Point3D& endPoint, const Vector3D& endHandle);
	
	const Point3D&			GetStartPoint	(void) const					{ return m_startPoint;	 }
	const Point3D&			GetEndPoint		(void) const					{ return m_endPoint;	 }
	const Vector3D&			GetStartHandle	(void) const					{ return m_startHandle;	 }
	const Vector3D&			GetEndHandle	(void) const					{ return m_endHandle;	 }
	const Point3D&			GetStartControl	(void) const					{ return m_startControl; }
	const Point3D&			GetEndControl	(void) const					{ return m_endControl;	 }

	void					SetStartPoint	(const Point3D& startPoint)		{ m_startPoint	 = startPoint;		m_startHandle  = m_startControl - m_startPoint;  }
	void					SetEndPoint		(const Point3D& endPoint)		{ m_endPoint	 = endPoint;		m_endHandle    = m_endControl   - m_endPoint;    }
	void					SetStartHandle	(const Vector3D& startHandle)	{ m_startHandle	 = startHandle;		m_startControl = m_startPoint   + m_startHandle; }
	void					SetEndHandle	(const Vector3D& endHandle)		{ m_endHandle	 = endHandle;		m_endControl   = m_endPoint     + m_endHandle;	 }
	void					SetStartControl	(const Point3D& startControl)	{ m_startControl = startControl;	m_startHandle  = m_startControl - m_startPoint;	 }
	void					SetEndControl	(const Point3D& endControl)		{ m_endControl	 = endControl;		m_endHandle    = m_endControl   - m_endPoint;	 }

	Box3D					GetBoundingBox	(void) const;	// Not a tight bounding box
	Box3D					GetBoundingBox	(const Math::Interval&) const;

	bool					GetPoint	(double param, Point3D& result) const;

	Point3D					GetPoint	(double param) const;
	GS::Optional<double>	GetParam	(const Point3D& point, double distEps) const;

	double					GetClosestPoint (const Point3D& point, double startParam = 0.0, double endParam = 1.0) const;
	double					GetClosestPoint (const Point3D& point, const Math::Interval& ival) const;

	Vector3D				GetTangent (double param) const;

	double					GetLength (double startParam = 0.0, double endParam = 1.0) const;

	GS::Array<double>		Intersect (const CubicBezierCurve3D& other) const;

	bool					Split			(double param, CubicBezierCurve3D& startCurveOut, CubicBezierCurve3D& endCurveOut) const;
	bool					GetSubCurve		(double startParam, double endParam, CubicBezierCurve3D& subCurveOut, double paramEpsilon = SmallEps) const;
	double					EstimateError	(void) const;									// Crude estimation of the maximum deviation of a cubic Bezier curve from it's base segment.
	double					EstimateSegmentationError (UInt32 numSegments) const;

	bool					IsFlat			(double epsilonDistance = EPS) const;

	void					Transform		(const Transformation3D&);
	CubicBezierCurve3D		GetTransformed	(const Transformation3D&) const;

	static GS::Array<double>	Intersect	(const CubicBezierCurve3D&, const Sector3D&);
	static GS::Array<double>	Intersect	(const CubicBezierCurve3D&, const Plane&);
	static GS::Array<double>	Intersect	(const CubicBezierCurve3D&, double r);
};


}	// namespace Geometry

#endif
