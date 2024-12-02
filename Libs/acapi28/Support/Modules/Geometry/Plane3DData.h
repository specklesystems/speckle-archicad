/****************************************************************************/
/*																			*/
/*					3D Plane and its operations								*/
/*																			*/
/****************************************************************************/


#if !defined (PLANE3DDATA_H)
#define PLANE3DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Circle2DData.h"

#include "Point3DData.h"
#include "Sector3DData.h"

/* 3D plane equation (pa*x + pb*y + pc*z + pd = 0) */
struct GEOMETRY_DLL_EXPORT PlaneEq {
	double		pa;
	double		pb;
	double		pc;
	double		pd;

	PlaneEq () : pa (0.0), pb (0.0), pc (0.0), pd (0.0) {}
	PlaneEq (double a, double b, double c, double d) : pa (a), pb (b), pc (c), pd (d) {}
	
	PlaneEq (const Vector3D& normalVector, const Point3D& pointOnPlane)
		: pa (normalVector.x)
		, pb (normalVector.y)
		, pc (normalVector.z)
		, pd (-(normalVector * pointOnPlane))
	{ /* do nothing */ }

	bool	IsValid () const
	{
		return pa != 0.0 || pb != 0.0 || pc != 0.0 || pd != 0.0;
	}

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;
};


inline PlaneEq	operator-(PlaneEq plane)
{
	plane.pa *= -1.0;
	plane.pb *= -1.0;
	plane.pc *= -1.0;
	plane.pd *= -1.0;

	return plane;
}

namespace Geometry {

class Plane;
class Ellipse;

struct Triangle3D {
	Point3D		c1;
	Point3D		c2;
	Point3D		c3;
};

GEOMETRY_DLL_EXPORT	Point3D		GetAnOnPlanePoint (const PlaneEq& plane);

GEOMETRY_DLL_EXPORT PlaneEq		SetPlaneEq (const Point3D& onPlanePoint, const Vector3D& planeNormal);

GEOMETRY_DLL_EXPORT Triangle3D	SetTriangle (const Point3D& c1, const Point3D& c2, const Point3D& c3);

GEOMETRY_DLL_EXPORT void		SetUpGenPlane (PlaneEq* plane, const Point3D* c0, const Vector3D* nn);		/*vv124*/

GEOMETRY_DLL_EXPORT PlaneEq		HorizontalPlane (double zlev);		/*vv121*/

GEOMETRY_DLL_EXPORT Point3D		ProjectAlongZ (const Point2D	*wc, const PlaneEq* p);		/*vv72*/

GEOMETRY_DLL_EXPORT Point3D		ProjectAlongZ (const Point2D	&wc, const PlaneEq& p);		/*vv72*/

GEOMETRY_DLL_EXPORT Point3D		UnsafeProjectAlongZ (const Point2D& point, const PlaneEq& plane);

GEOMETRY_DLL_EXPORT Point3D		ProjCoord3DToPlane (const Point3D* wc, const PlaneEq* p);	/*vv120*/

GEOMETRY_DLL_EXPORT Point3D		ProjCoord3DToPlane (const Point3D& wc, const PlaneEq& p);	/*vv120*/

GEOMETRY_DLL_EXPORT Vector3D	ProjVector3DToPlane (const Vector3D& wc, const Vector3D& pNormal);	/*AACS*/

GEOMETRY_DLL_EXPORT bool		IsPlaneCoord3D (const Point3D* wc, const PlaneEq* p);	/*vv72*/

GEOMETRY_DLL_EXPORT bool		IsPlaneCoord3D (const Point3D& wc, const PlaneEq& p);	/*vv72*/

GEOMETRY_DLL_EXPORT double		DistPlaneCoord3D (const Point3D &wc,const PlaneEq &p);

GEOMETRY_DLL_EXPORT bool		IsCoord3DAbovePlane (const Point3D& wc, const PlaneEq& p);	

GEOMETRY_DLL_EXPORT bool		ArePlanesEqual (const PlaneEq& eq1, const PlaneEq& eq2, const double eps = Eps);

GEOMETRY_DLL_EXPORT bool		IsCoplanar (const Point3D* p1, const Point3D* p2, const Point3D* p3, const Point3D* p4);

GEOMETRY_DLL_EXPORT Vector3D   	NormVector3D (const Triangle3D& p);

GEOMETRY_DLL_EXPORT bool		ArePointsOnPlane (
									Int32			n,
									const double*	x,
									const double*	y,
									const double*	z,
									PlaneEq*		pl = nullptr);

GEOMETRY_DLL_EXPORT bool		ArePointsOnPlane (const GS::Array<Point3D>& points, PlaneEq* pl = nullptr);

GEOMETRY_DLL_EXPORT bool		XSectorNormalizedPlane (const Sector3D& s,
														const PlaneEq& p,
														Point3D* intersectionPoint,
														double* intersectionParam);

GEOMETRY_DLL_EXPORT bool		XSectorPlane (const Sector3D& s,
											  const PlaneEq& p,
											  Point3D* intersectionPoint,
											  double* intersectionParam);

GEOMETRY_DLL_EXPORT Point3D		XSectorPlane (const Sector3D& s, const Triangle3D& p, bool& exist);

GEOMETRY_DLL_EXPORT bool		XPlanes (const PlaneEq& p1, const PlaneEq& p2, Sector3D& s);

GEOMETRY_DLL_EXPORT char		XCylarcLine3D (
									const Ellipse&	el,
									const Plane&	plane,
									const Sector3D&	s,
									Sector3D&		xs);	/*vv72*/

GEOMETRY_DLL_EXPORT char		XCylarcSector3D (
									const Ellipse&	el,
									const Plane&	plane,
									const Sector3D&	s,
									Sector3D&		xs);	/*vv72*/

GEOMETRY_DLL_EXPORT char		XCylarcs (
									const Ellipse&	el1,
									const Plane&	plane1,
									const Ellipse&	el2,
									const Plane&	plane2,
									Point3D			xs[4]);

GEOMETRY_DLL_EXPORT PlaneEq		PlaneEqFromTriangle (const Triangle3D& plane);

// creates a plane from the points and returns true if all points are coplanar
GEOMETRY_DLL_EXPORT bool		CreatePlaneEq (
											const GS::PagedArray<Point3D>& in_pointArray,
											PlaneEq& out_p);

// creates the regression plane to the given points and returns true if the plane is created
GEOMETRY_DLL_EXPORT bool		GetRegressionPlane (
									const GS::PagedArray<Point3D>&	points,
									PlaneEq&						plane,
									Point3D							*basePoint = nullptr);

// creates least squares plane to the given points (orthogonal regression in 3d)
GEOMETRY_DLL_EXPORT PlaneEq		GetLeastSquaresPlane (
									Int32			n,
									const double*	x,
									const double*	y,
									const double*	z);

// creates least squares plane to the given points (orthogonal regression in 3d)
GEOMETRY_DLL_EXPORT PlaneEq		GetLeastSquaresPlane (const GS::Array<Point3D>& inputCoords);

GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLTriangle3D (GS::XMLIChannel& ic, Triangle3D& t);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLTriangle3D (GS::XMLOChannel& oc, const Triangle3D& t);

GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLPlaneEq (GS::XMLIChannel& ic, PlaneEq& p);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLPlaneEq (GS::XMLOChannel& oc, const PlaneEq& p);

inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Geometry::Triangle3D& t)	{ return Geometry::ReadXMLTriangle3D (ic, t); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Geometry::Triangle3D& t)	{ return Geometry::WriteXMLTriangle3D (oc, t); }

inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const PlaneEq& p)	{ return Geometry::WriteXMLPlaneEq (oc, p); }
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, PlaneEq& p)	{ return Geometry::ReadXMLPlaneEq (ic, p); }
}


#endif
