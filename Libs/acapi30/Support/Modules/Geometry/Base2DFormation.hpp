#ifndef _BASE2DFORMATION_HPP_
#define _BASE2DFORMATION_HPP_
#pragma once

// === Includes ========================================================================================================

// from Geometry
#include "GeometricDefinitions.h"
#include "Point2D.hpp"
#include "Line2D.hpp"
#include "Circle2DData.h"

// =====================================================================================================================

namespace Geometry {

enum Base2DFormationType {
	BASE2D_INVALID,		// No result
	BASE2D_Point,		// A single point (Coord)
	BASE2D_Line,		// A line
	BASE2D_Circle		// A circle
};

class GEOMETRY_DLL_EXPORT Base2DFormation
{

public:
	Base2DFormation ();
	Base2DFormation (const Point2D& point);
	Base2DFormation (const Line2D& line);
	Base2DFormation (const Circle2D& circle);
	~Base2DFormation ();

	void SetPoint  (const Point2D& point);
	void SetLine   (const Line2D& line);
	void SetCircle (const Circle2D& circle);

	Base2DFormationType			GetType () const;
	Base2DFormationType			GetPoint  (Point2D& point) const;
	Base2DFormationType			GetLine   (Line2D& line) const;
	Base2DFormationType			GetCircle (Circle2D& circle) const;

private:

	Base2DFormationType  m_type;
	Point2D				 m_point;
	GS::Optional<Line2D> m_line;
	Circle2D			 m_circle;
};

}

#endif
