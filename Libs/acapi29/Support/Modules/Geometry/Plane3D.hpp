#ifndef PLANE3D_HPP_
#define PLANE3D_HPP_
#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "GeometricDefinitions.h"
#include "UnitVector3D.hpp"
#include "Optional.hpp"

// === Predeclarations =================================================================================================

struct PlaneEq;

namespace Geometry {
	class Plane;
	class Transformation3D;
	class OrthogonalTransformation3D;
}

// =====================================================================================================================

namespace Geometry {

class GEOMETRY_DLL_EXPORT Plane3D
{
public:
	Plane3D (const UnitVector_3D& planeNormal, const Point3D& onPlanePoint);
	Plane3D (const PlaneEq& planeEq);

	static GS::Optional<Plane3D> CreateFromPoints (const Point3D& p1, const Point3D& p2, const Point3D& p3, const DistanceTolerance& tol = {});

	Point3D			GetAnOnPlanePoint	() const;
	UnitVector_3D	GetPlaneNormal		() const;
	PlaneEq			GetPlaneEq_Deprecated	() const;

	bool			ContainsPoint		(const Point3D& p, const DistanceTolerance& tol = {}) const;
	Point3D			ProjectToPlane		(const Point3D& p) const;
	Vector3D		ProjectToPlane_V	(const Vector3D& v) const;
	double			GetDistance			(const Point3D& p) const;

	bool			IsParallelWith		(const Plane3D& other, const AngleTolerance& tol = {}) const;
	bool			IsCoplanarWith		(const Plane3D& other, const Tolerance& tol = {}) const;		// normal vectors may be opposite
	bool			IsEqualWith			(const Plane3D& other, const Tolerance& tol = {}) const;		// coplanar and normals point to same direction

	Plane3D					Transform	(const OrthogonalTransformation3D& trafo) const;
	GS::Optional<Plane3D>	Transform	(const Transformation3D& trafo) const;

private:
	Plane3D ();

	UnitVector_3D planeNormal;
	double pD;					// for on plane points : planeNormal * point + pD = 0
};


GEOMETRY_DLL_EXPORT Plane3D GetPlaneWithReversedNormal (const Plane3D& originalPlane);	//#KiP_GeometryRefactor ez lehetne member?

GEOMETRY_DLL_EXPORT Plane3D ToPlane3D (const Plane& plane);

}

#endif
