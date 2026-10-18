#pragma once

#ifndef RAY_2D_HPP_
#define RAY_2D_HPP_

#include "Line2D.hpp"


namespace Geometry {

	class GEOMETRY_DLL_EXPORT Ray2D
	{
	public:
		Ray2D (const Point2D& basePoint, const UnitVector_2D& direction);

		Point2D					BasePoint () const;
		UnitVector_2D			GetDirection () const;
		double					GetDistance (const Point2D& point) const;
		
		bool					ContainsPoint (const Point2D& point, const DistanceTolerance& tol = {}) const;
		GS::Optional<Point2D>	ProjectPoint (const Point2D& point) const;
		Point2D					GetNearestPointTo (const Point2D& toPoint) const;

		Line2D					AsLine () const;

		Ray2D					InvertDirection () const;

		GS::Optional<Ray2D>		Transform (const Transformation2D& transformation) const;
		Ray2D					Transform (const OrthogonalTransformation2D& transformation) const;

	private:
		Point2D m_basePoint;
		UnitVector_2D m_direction;
	};

}

#endif
