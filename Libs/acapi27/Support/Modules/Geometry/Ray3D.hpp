#pragma once

#ifndef RAY_3D_HPP_
#define RAY_3D_HPP_

#include "Line3D.hpp"


namespace Geometry {

	class GEOMETRY_DLL_EXPORT Ray3D
	{
	public:
		Ray3D (const Point3D& basePoint, const UnitVector_3D& direction);

		Point3D					BasePoint () const;
		UnitVector_3D			GetDirection () const;
		double					GetDistance (const Point3D& point) const;
		
		bool					ContainsPoint (const Point3D& point, const DistanceTolerance& tol = {}) const;
		GS::Optional<Point3D>	ProjectPoint (const Point3D& point) const;
		Point3D					GetNearestPointTo (const Point3D& toPoint) const;

		Line3D					AsLine () const;

		Ray3D					InvertDirection () const;

		GS::Optional<Ray3D>		Transform (const Transformation3D& transformation) const;
		Ray3D					Transform (const OrthogonalTransformation3D& transformation) const;

	private:
		Point3D m_basePoint;
		UnitVector_3D m_direction;
	};

}

#endif
