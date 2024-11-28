#ifndef _LINE_3D_HPP_
#define _LINE_3D_HPP_
#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "GeometricDefinitions.h"
#include "Tolerance.hpp"
#include "UnitVector3D.hpp"
#include "Transformation3D.hpp"
#include "OrthogonalTransformation3D.hpp"

// =====================================================================================================================

namespace Geometry {

class GEOMETRY_DLL_EXPORT Line3D
{
public:
	static Line3D CreateFromPoints (const Point3D& c1, const Point3D& c2, const DistanceTolerance& tol = DistanceTolerance { SmallEps });
	
	Line3D (const Point3D& linePoint, const UnitVector_3D& direction);
	virtual ~Line3D ();

	Point3D			GetAnOnLinePoint	() const;
	UnitVector_3D	GetDirection		() const;
	double			GetDistance			(const Point3D& c) const;

	bool			ContainsPoint		(const Point3D& c, const DistanceTolerance& tol = {}) const;
	Point3D			ProjectPoint		(const Point3D& c) const;
	Point3D			GetNearestPointTo	(const Point3D& c) const;

	Line3D			InvertDirection		() const;
	

	bool			IsParallelWith		(const Line3D& other, const AngleTolerance& tol = {}) const;
	bool			IsColinearWith		(const Line3D& other, const Tolerance& tol = {}) const;					// directions may be opposite
	bool			IsEqualWith			(const Line3D& other, const Tolerance& tol = {}) const;					// colinear and directions point to same direction

	static bool		AreParallel			(const Line3D& line1, const Line3D& line2, const AngleTolerance& tol = {});
	static bool		AreColinear			(const Line3D& line1, const Line3D& line2, const Tolerance& tol = {});		// directions may be opposite
	static bool		AreEqual			(const Line3D& line1, const Line3D& line2, const Tolerance& tol = {});		// colinear and directions point to same direction

	GS::Optional<Line3D>	Transform (const Transformation3D&) const;
	Line3D					Transform (const OrthogonalTransformation3D&) const;

	//#KiP_Note ide meg kellhetenek muveletek

	static Point3D ProjectToLine (const Point3D& coord, const Vector3D& lineDir, const Point3D& linePoint);	//#KiP_Note ez megmaradt, mert sokat hasznaltak kivulrol

private:
	Point3D m_linePoint;
	UnitVector_3D m_direction;
};

GEOMETRY_DLL_EXPORT bool IsHorizontalLine (const Geometry::Line3D& line, const AngleTolerance& tol = {});
GEOMETRY_DLL_EXPORT bool IsVerticalLine (const Geometry::Line3D& line, const AngleTolerance& tol = {});

}
#endif
