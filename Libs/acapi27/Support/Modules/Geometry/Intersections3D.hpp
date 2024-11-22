// contact person : KiP
#ifndef INTERSECTIONS_3D_HPP
#define INTERSECTIONS_3D_HPP
#pragma once

// === Includes ========================================================================================================

#include "Optional.hpp"
#include "Line3D.hpp"
#include "Plane3D.hpp"

// =====================================================================================================================

namespace Geometry {

class GEOMETRY_DLL_EXPORT RelativePositions3D
{
public:
	struct GEOMETRY_DLL_EXPORT LineLine
	{
		enum Type { Disjuct_Parallel, Disjunct_Skew, IntersectInOnePoint, Colinear };

		Type type;
		GS::Optional<Point3D> intersectionPoint;
	};

	struct GEOMETRY_DLL_EXPORT LinePlane
	{
		enum Type { Disjunct, IntersectInOnePoint, LineIsOnPlane };

		Type type;
		GS::Optional<Point3D> intersectionPoint;
	};

	struct GEOMETRY_DLL_EXPORT PlanePlane
	{
		enum Type { Coplanar, Disjunct, IntersectInLine };

		Type type;
		GS::Optional<Line3D> intersectionLine;
	};

	static LineLine Calculate (const Line3D& line1, const Line3D& line2);
	static LinePlane Calculate (const Line3D& line, const Plane3D& plane);
	static PlanePlane Calculate (const Plane3D& plane1, const Plane3D& plane2);
};


class GEOMETRY_DLL_EXPORT Intersections3D
{
public:
	static GS::Optional<Point3D> Calculate (const Line3D& line1, const Line3D& line2);
	static GS::Optional<Point3D> Calculate (const Line3D& line, const Plane3D& plane);
	static GS::Optional<Line3D> Calculate (const Plane3D& plane1, const Plane3D& plane2);
};

}

#endif
