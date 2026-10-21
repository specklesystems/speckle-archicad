#ifndef _CIRCLEARC2D_HPP_
#define _CIRCLEARC2D_HPP_
#pragma once

#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "SignedAngle.hpp"

namespace Geometry {
	class GenArc;
}


namespace Geometry {

DECLARE_EXCEPTION_CLASS (CircleArc2DCreationError, GeometryException, Error, GEOMETRY_DLL_EXPORT)

class GEOMETRY_DLL_EXPORT CircleArc2D
{
public:
	static CircleArc2D CreateFromBeginEnd (const Point2D& begPoint, const Point2D& endPoint, double arcAngle);
	static CircleArc2D CreateFromBeginEnd (const Point2D& begPoint, const Point2D& endPoint, SignedAngle arcAngle);
	static CircleArc2D CreateByOrigo (const Point2D& origo, const Point2D& begPoint, double arcAngle);
	static CircleArc2D CreateByOrigo (const Point2D& origo, const Point2D& begPoint, SignedAngle arcAngle);

	static GS::Optional<CircleArc2D> Create (const Point2D& origo, const Point2D& begPoint, const Point2D& endPoint, bool reflected);

	Point2D GetOrigo () const;
	Point2D GetBegPoint () const;
	Point2D GetEndPoint () const;
	double	GetRadius () const;
	bool	IsReflected () const;
	double	GetArcAngle () const;

	GenArc	ToGenArc () const;

private:
	CircleArc2D () = default;

	Point2D beg;
	Point2D end;
	Point2D origo;
	double angle;
};

}

#endif
