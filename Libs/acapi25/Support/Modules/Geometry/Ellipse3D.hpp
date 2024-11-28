#ifndef ELLIPSE_3D_HPP
#define ELLIPSE_3D_HPP
#pragma once

#include "Ellipse2DData.h"
#include "CoordinateSystem3D.hpp"

namespace Geometry {
	class Plane3D;
}


namespace Geometry {

class GEOMETRY_DLL_EXPORT Ellipse3D
{
public:
	Ellipse3D (const Ellipse& ellipse2D, const OrthonormalizedCoordinateSystem3D& coordSys);
		
	Ellipse								GetEllipse2D () const;
	Plane3D								GetPlane () const;
	OrthonormalizedCoordinateSystem3D	GetCoordSys () const;

	//#KiP_Note_GeometryRefactor ide jonnek meg muveletek, de ezt az interface-t a tobbi iv jellegu osztaly (GanArc, Circle 2D/3D) interface-evel egyutt at kell gondolni

private:
	Ellipse ellipse2D; 
	OrthonormalizedCoordinateSystem3D coordSys;
};

}

#endif
