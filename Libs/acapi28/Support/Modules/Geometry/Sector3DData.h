// *****************************************************************************
// C style struct for 3D Line, Sector and their operations
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (SECTOR3DDATA_H)
#define SECTOR3DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point3DData.h"
#include "Box3DData.h"
#include "PagedArray.hpp"
#include "Tolerance.hpp"
#include "Line3D.hpp"

/* 3D line segment	*/ /* 48 bytes */

struct GEOMETRY_DLL_EXPORT Sector3D {
	Point3D	c1;
	Point3D	c2;
	Sector3D () : c1 (0., 0., 0.), c2 (0., 0., 0.) {}
	Sector3D (const Point3D& c1, const Point3D& c2) : c1 (c1), c2 (c2) {}
	Sector3D (const Point3D& begPoint, const UnitVector_3D& direction, double length) : c1 { begPoint }, c2 { begPoint + direction * length } {}

public:
	inline double 	GetLength () const;

	// Extensions to match Line3D, Ray3D-s methods

	Point3D							BegPoint () const;
	Point3D							EndPoint () const;
	Point3D							GetMidPoint () const;

	double							GetDistance (const Point3D& point, const Geometry::DistanceTolerance& zeroLengthCriterion = Geometry::DistanceTolerance { SmallEps }) const;
	GS::Optional<UnitVector_3D>		GetDirection (const Geometry::DistanceTolerance& zeroLengthCriterion = Geometry::DistanceTolerance { SmallEps }) const;

	bool							IsZeroLength (const Geometry::DistanceTolerance& zeroLengthCriterion = Geometry::DistanceTolerance { SmallEps }) const;

	GS::Optional<Point3D>			ProjectPoint (const Point3D& point, const Geometry::DistanceTolerance& zeroLengthCriterion = Geometry::DistanceTolerance { SmallEps }) const;
	bool							ContainsPoint (const Point3D& point, const Geometry::DistanceTolerance& tol = {}) const;
	Point3D							GetNearestPointTo (const Point3D& toPoint, const Geometry::DistanceTolerance& zeroLengthCriterion = Geometry::DistanceTolerance { SmallEps }) const;

	GS::Optional<Geometry::Line3D>	AsLine (const Geometry::DistanceTolerance& zeroLengthCriterion = Geometry::DistanceTolerance { SmallEps }) const;

	Sector3D						InvertDirection () const;

	Sector3D						Transform (const Geometry::OrthogonalTransformation3D& transformation) const;
	GS::Optional<Sector3D>			Transform (const Geometry::Transformation3D& transformation) const;
};

// forward declarations
typedef GS::PagedArray<Sector3D>	GSPagedArray_Sector3D;
typedef GS::PagedArray<Int32>		GSPagedArray_int;

namespace Geometry {

using Segment3D = Sector3D;  // Used in LineUtils3D, Intersection3D

GEOMETRY_DLL_EXPORT Sector3D	SetSector3D (const Vector3D& v1, const Vector3D& v2);

GEOMETRY_DLL_EXPORT Vector3D	SectorVector3D (const Sector3D& s);

GEOMETRY_DLL_EXPORT Point3D		CoordProjSector3D (const Point3D& c, const Sector3D& s);

GEOMETRY_DLL_EXPORT double		CoordProjSector3DParam (const Point3D& c, const Sector3D& s);

GEOMETRY_DLL_EXPORT double		CoordSectorDist3D (const Point3D& point, const Sector3D& sector);

GEOMETRY_DLL_EXPORT bool		AreSector3DEndPointsNear (const Sector3D& s1, const Sector3D& s2);

GEOMETRY_DLL_EXPORT bool		IsCoord3DInSector (const Point3D& wc, const Sector3D& s);

GEOMETRY_DLL_EXPORT bool		IsLineCoord3D (const Point3D* wc, const Sector3D* s);

GEOMETRY_DLL_EXPORT bool		XLines3D (const Sector3D* s1, const Sector3D* s2, Point3D* ccc,
										  double* xt1 = nullptr, double* xt2 = nullptr);

GEOMETRY_DLL_EXPORT bool		XLine3DsEps  (
										const Sector3D*		s1,
										const Sector3D*		s2,
										Point3D*			xc,
										double				eps,
										double				radEps,
										double*				xt1 = nullptr,
										double*				xt2 = nullptr);

GEOMETRY_DLL_EXPORT bool		MinDistanceLine3Ds (
															const Vector3D	& p0, 
															const Vector3D	& t0, 
															const Vector3D	& p1, 
															const Vector3D	& t1, 
															double			& alpha_0, 
															double			& alpha_1);

GEOMETRY_DLL_EXPORT bool		XSectors3D (const Sector3D* s1, const Sector3D* s2, Point3D* ccc,
											double* xt1 = nullptr, double* xt2 = nullptr);

//		Intersection with epsilon
GEOMETRY_DLL_EXPORT bool		XSector3DsEps (
						const Sector3D&	s1,
						const Sector3D&	s2,
						Boundary		sectorBoundaries,
						Point3D*		xc,
						double			eps,
						double*			xt1 = nullptr,
						double*			xt2 = nullptr);		/* mi46 */

GEOMETRY_DLL_EXPORT bool		XSectors3DOverLapByDist  (const Sector3D&	s1,
														  const Sector3D&	s2,
														  Sector3D*			xs = nullptr,
														  const Tolerance&	tol = {});

GEOMETRY_DLL_EXPORT Int32		XSector3DOverLap  (	const Sector3D*	s1,
													const Sector3D*	s2,
													double			eps,
													Point3D*		xc1,
													Point3D*		xc2);

GEOMETRY_DLL_EXPORT Box3D		Sector3DBox3D (const Sector3D *s);

GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLSector3D	(GS::XMLIChannel& ic, Sector3D& sec);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLSector3D	(GS::XMLOChannel& oc, const Sector3D& sec);
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Sector3D& sec)	{ return Geometry::WriteXMLSector3D (oc, sec); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Sector3D& sec)	{ return Geometry::ReadXMLSector3D (ic, sec); }
}

// Inline method definitions
inline double 	Sector3D::GetLength () const
{
	return (c1 - c2).GetLength ();
}

#endif
