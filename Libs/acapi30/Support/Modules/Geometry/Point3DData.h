/****************************************************************************/
/*																			*/
/*					3D Point, Vector and their operations					*/
/*																			*/
/****************************************************************************/


#if !defined (POINT3DDATA_H)
#define POINT3DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point2DData.h"
#include "Vector3D.hpp"
#include "AngleData.h"


namespace Geometry {
	template <class CoordinateType>	class CustomUnitVector3D;
	typedef CustomUnitVector3D<double> UnitVector_3D;
}


namespace Geometry {

/* coord */
GEOMETRY_DLL_EXPORT void	IVCoord3D (GS::PlatformSign inplatform, Point3D *c3);

GEOMETRY_DLL_EXPORT Point3D	SetCoord3D (const Point2D& c, const double z = 0);

GEOMETRY_DLL_EXPORT Point2D	SetCoord2D (const Point3D& pC);

GEOMETRY_DLL_EXPORT double	Dist3D (const Point3D& c1, const Point3D& c2);

GEOMETRY_DLL_EXPORT double	TetraVolume (const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4);

/* vector */
GEOMETRY_DLL_EXPORT Vector3D	SetVector3D (const Vector2D& c, const double z = 0);

GEOMETRY_DLL_EXPORT Vector3D	AddVector3D (const Vector3D& v1, const Vector3D& v2);

GEOMETRY_DLL_EXPORT Vector3D	SubVector3D (const Vector3D& v1, const Vector3D& v2);

GEOMETRY_DLL_EXPORT double		LenVector3D (const Vector3D& v);

GEOMETRY_DLL_EXPORT double		LenSqrVector3D (const Vector3D& v);

GEOMETRY_DLL_EXPORT bool		IsUnitVector3D (const Vector3D& v);

GEOMETRY_DLL_EXPORT bool		StrictUnitVector3D (Vector3D* v);

GEOMETRY_DLL_EXPORT bool		StrictUnitVector3D (Vector3D& v, double lenEps);

inline				double		MulsVectors3D (const Vector3D& v1, const Vector3D& v2);

GEOMETRY_DLL_EXPORT Vector3D	MulVector3D (const Vector3D& v, double r);

GEOMETRY_DLL_EXPORT Vector3D	MulvVectors3D (const Vector3D& a, const Vector3D& b);

GEOMETRY_DLL_EXPORT double		UnitVectorPtr3D (const Vector3D *v, Vector3D *w);

GEOMETRY_DLL_EXPORT Point3D		MiddleCoord3D (const Point3D& a, const Point3D& b);

inline				Vector3D*	LinePt3D (const Point3D& r0, const Vector3D& e, double lambda, Point3D *pp);

GEOMETRY_DLL_EXPORT bool		IsColinVectors3D (const Vector3D& v1, const Vector3D& v2, double radEps = RadEps, double minLengthEps = EPS);

GEOMETRY_DLL_EXPORT Vector3D	PolarCoord3D (double r, double fi, double theta);

GEOMETRY_DLL_EXPORT double		GetVector3DAngle (const Vector3D& v1);
GEOMETRY_DLL_EXPORT double		GetVectors3DAngle (const Vector3D& v1, const Vector3D& v2);
GEOMETRY_DLL_EXPORT double		CalcRTAngleAndRTAxis (Vector3D a, Vector3D b, Vector3D & rtAxis); //angle for rotating a to b

GEOMETRY_DLL_EXPORT double		CalcSignedRotAngleOfPlanes (const Geometry::UnitVector_3D& rotAxisDir,
															const Vector3D& srcPlaneDir,
															const Vector3D& destPlaneDir);

GEOMETRY_DLL_EXPORT Vector3D	GetOrthogonalVector3D (const Vector3D& in_vect);

GEOMETRY_DLL_EXPORT Point3D		InterpolateCoord3D (const Point3D& a, const Point3D& b, double ratio);

GEOMETRY_DLL_EXPORT Point3D		RotCoord3D (const Point3D& oc, const Point3D& wc, double si, double co);

GEOMETRY_DLL_EXPORT bool		NormVectorUnitPtr3D (const Vector3D *p1, Vector3D *p2, Vector3D *pp);

GEOMETRY_DLL_EXPORT void		TMRotateVect (
											double rx, double ry, double rz, double alpha,
											double *x, double *y, double *z);

GEOMETRY_DLL_EXPORT void		TMRotatePoint (double vx, double vy, double vz,
												double rx, double ry, double rz, double alpha,
												double *px, double *py, double *pz);

GEOMETRY_DLL_EXPORT void	IVF_Coord3D (GS::PlatformSign inplatform, F_Coord3D *c);
GEOMETRY_DLL_EXPORT void	IVF_Coord3D (GS::PlatformSign inplatform, GS::PlatformSign toplatform, F_Coord3D *c);

GEOMETRY_DLL_EXPORT bool	IsEqualCoord3D (const Point3D& c1, const Point3D& c2);
GEOMETRY_DLL_EXPORT bool	IsEqualCoord3D (const Point3D& c1, const Point3D& c2, double epsilon);
GEOMETRY_DLL_EXPORT double	Dist3DSqr (const Point3D& c1, const Point3D& c2);

GEOMETRY_DLL_EXPORT bool	AreParallelVectors (const Vector3D& v1, const Vector3D& v2, double givenEps = EPS);

}

inline double Geometry::MulsVectors3D (const Vector3D& v1, const Vector3D& v2)
{
	return v1 * v2;
}

inline Vector3D* Geometry::LinePt3D (const Point3D& r0, const Vector3D& e, double lambda, Point3D *pp)
{
	pp->x = r0.x + lambda * e.x;
	pp->y = r0.y + lambda * e.y;
	pp->z = r0.z + lambda * e.z;
	return pp;
}

#endif
