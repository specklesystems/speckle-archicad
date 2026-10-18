// *********************************************************************************************************************
// Description:		Geometry structures on the unit sphere
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	CsetA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (SPHERICALPOLYGON_HPP)
#define SPHERICALPOLYGON_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Array.hpp"

// from Geometry
#include	"GeometricDefinitions.h"
#include	"Vector3D.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Geometry {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

typedef	enum	{
	ShorterSphericalSegment	= 0,
	HalfSphericalSegment	= 1,
	LongerSphericalSegment	= 2
} SphericalSegmentType;

// Spherical segment as part of spherical line on the unit sphere
// A spherical line is cut into two spherical segments by two points on it
// Identifying one of them is done by describing being larger or smaller than a half great circle
// the only problematic case is when the two point are antipodal, in this case the normal vector determines which segment it is about
class	GEOMETRY_DLL_EXPORT	SphericalSegment {
private:
	Vector3D				m_begPoint;			// Unit vector !
	Vector3D				m_endPoint;			// Unit vector !
	Vector3D				m_normalVec;		// Unit vector ! Determines the plane of the line as a great circle (with orientation)
	SphericalSegmentType	m_segmentType;		// if the segment is the longer or the shorter one among the two segments defined by the two endpoints
	double					m_tolerance;		// for checking coincidence, etc.

public:
	SphericalSegment					();
	SphericalSegment					(const Vector3D& begPt, const Vector3D& endPt, const Vector3D* normal = nullptr, double toler = EPS);
	void		inline	SetPoints		(const Vector3D& begPt, const Vector3D& endPt, const Vector3D* normal = nullptr);
	void		inline	SetNormalDir	(const Vector3D& normal);
	void		inline	SetTolerance	(double toler);
	Vector3D	inline	GetBegPoint		()	const	{	return m_begPoint;	}
	Vector3D	inline	GetEndPoint		()	const	{	return m_endPoint;	}
	Vector3D	inline	GetNormalVec	()	const	{	return m_normalVec;	}

	bool	ContainsExtended		(const Vector3D& pt)	const;
	bool	Contains				(const Vector3D& pt)	const;
	bool	IntersectionExtended	(const SphericalSegment& other, Vector3D* result)	const;
	bool	Intersection			(const SphericalSegment& other, bool* multipleResult = nullptr, Vector3D* result= nullptr)	const;
	bool	IsOppositeDir			(const SphericalSegment& other)	const;

};	// class SphericalSegment


// Polygon on unit sphere
// Edges are spherical segments, with the ambiguity of being one of the two spherical segments defined by the two endpoints
// It is generally a closed polygon, with the omit array special edges can be masked out
class	GEOMETRY_DLL_EXPORT	SphericalPolygon {
private:
	GS::Array<Vector3D>	m_vertices;
	GS::Array<Vector3D>	m_outerVects;	// Directions determining outer side of polygon for each edge (as a normal vector),
										// and by this these determine the "larger than half" states also
	GS::Array<bool>		m_omitSides;	// For masking out specific edges

	mutable	GS::Array<SphericalSegment>	m_cachedSides;	// Filled only if needed !

public:
	SphericalPolygon		(const Int32& size);
	SphericalPolygon		(const GS::Array<Vector3D>& vertices, const GS::Array<Vector3D>* outerVects = nullptr, GS::Array<bool>* omitSides = nullptr);
	void				Add	(const Vector3D& vertex, const Vector3D* outerVect = nullptr, bool* omitSide = nullptr);
	GS::Array<Vector3D>	GetVertexVects		()	const	{	return m_vertices;	}
	void				SetupSides			()	const;
	bool				IsSelfIntersecting	()	const;
	bool				HasTurnaround		()	const;

};	// class SphericalPolygon


// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Geometry

#endif
