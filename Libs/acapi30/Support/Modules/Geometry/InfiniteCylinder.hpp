#ifndef INFINITE_CYLINDER_HPP
#define INFINITE_CYLINDER_HPP
#pragma once

#include "Line3D.hpp"


namespace Geometry {

DECLARE_EXCEPTION_CLASS (InfiniteCylinderCreationError, GeometryException, Error, GEOMETRY_DLL_EXPORT);

class GEOMETRY_DLL_EXPORT InfiniteCylinder
{
public:
	InfiniteCylinder (const Line3D& axis, double radius);
	virtual ~InfiniteCylinder ();
	
	Line3D					GetAxis () const;
	double					GetRadius () const;

	bool					IsOnSurface (const Point3D& point, const DistanceTolerance& tol = {}) const;
	bool					IsInside (const Point3D& point, const DistanceTolerance& tol = {}) const;
	bool					IsOutside (const Point3D& point, const DistanceTolerance& tol = {}) const;
	bool					IsAxisPoint (const Point3D& point, const DistanceTolerance& tol = {}) const;
	GS::Optional<Point3D>	GetClosestPointTo (const Point3D& point) const;										// NoValue result for axis points
	double					GetDistanceFrom (const Point3D& point) const;

private:
	Line3D axis;
	double radius;
};

}
#endif
