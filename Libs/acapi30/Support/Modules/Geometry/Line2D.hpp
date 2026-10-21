#ifndef _LINE_2D_HPP_
#define _LINE_2D_HPP_
#pragma once

// === Includes ========================================================================================================

// from Geometry

#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "UnitVector2D.hpp"
#include "Tolerance.hpp"
#include "Transformation2D.hpp"
#include "OrthogonalTransformation2D.hpp"

// =====================================================================================================================

namespace Geometry {

class GEOMETRY_DLL_EXPORT Line2D
{
public:
	static Line2D CreateFromPoints (const Point2D& linePoint1, const Point2D& linePoint2, const DistanceTolerance& tol = DistanceTolerance { SmallEps });

	Line2D (const Point2D& linePoint, const UnitVector_2D& direction);
	virtual ~Line2D ();

	Point2D			GetAnOnLinePoint () const;
	UnitVector_2D	GetDirection () const;
	double			GetDistance (const Point2D& point) const;

	bool			ContainsPoint (const Point2D& point, const DistanceTolerance& tol = {}) const;	
	Point2D			ProjectPoint (const Point2D& point) const;
	Point2D			GetNearestPointTo (const Point2D& point) const;

	bool			IsParallelWith (const Line2D& other, const AngleTolerance& tol = {}) const;
	bool			IsColinearWith (const Line2D& other, const Tolerance& tol = {}) const;					// directions may be opposite
	bool			IsEqualWith (const Line2D& other, const Tolerance& tol = {}) const;					// colinear and directions point to same direction

	static bool		AreParallel (const Line2D& line1, const Line2D& line2, const AngleTolerance& tol = {});
	static bool		AreColinear (const Line2D& line1, const Line2D& line2, const Tolerance& tol = {});		// directions may be opposite
	static bool		AreEqual (const Line2D& line1, const Line2D& line2, const Tolerance& tol = {});		// colinear and directions point to same direction

	Line2D			InvertDirection () const;

	GS::Optional<Line2D>	Transform (const Transformation2D& transformation) const;
	Line2D					Transform (const OrthogonalTransformation2D& transformation) const;
	
private:
	Point2D m_linePoint;
	UnitVector_2D m_direction;
};

GEOMETRY_DLL_EXPORT bool IsHorizontalLine (const Geometry::Line2D& line, const AngleTolerance& tol = {});
GEOMETRY_DLL_EXPORT bool IsVerticalLine (const Geometry::Line2D& line, const AngleTolerance& tol = {});


}

#endif
