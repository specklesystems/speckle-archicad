#ifndef _INVERSION_HPP_
#define _INVERSION_HPP_
#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "Line2D.hpp"
#include "Circle2DData.h"
#include "Base2DFormation.hpp"

// =====================================================================================================================

namespace Geometry {

class GEOMETRY_DLL_EXPORT Inversion2D
{
public:
	Inversion2D (const Point2D& origo, double radius);
	Inversion2D (const Circle2D& circ);
	~Inversion2D ();

	Point2D			GetOrigo () const;
	double			GetRadius () const;
	Circle2D		GetCircle () const;

	Base2DFormationType		Transform (const Point2D& point, Base2DFormation& result) const;
	Base2DFormationType		Transform (const Line2D& line,   Base2DFormation& result) const;
	Base2DFormationType		Transform (const Circle2D& circ, Base2DFormation& result) const;


private:
	Inversion2D () = default;
	Base2DFormationType		Transform (const Point2D& point, Point2D& resPoint) const;

	Circle2D m_circle;
};

}
#endif
