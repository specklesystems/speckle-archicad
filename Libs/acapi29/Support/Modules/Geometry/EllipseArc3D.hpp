#ifndef ELLIPSE_ARC_3D_HPP
#define ELLIPSE_ARC_3D_HPP
#pragma once

#include "GenArc2DData.h"
#include "CoordinateSystem3D.hpp"

namespace Geometry {
	class Plane3D;
}


namespace Geometry {

class GEOMETRY_DLL_EXPORT EllipseArc3D
{
public:
	EllipseArc3D (const GenArc& arc2D, const OrthonormalizedCoordinateSystem3D& coordSys);
		
	GenArc								GetArc2D () const;
	Plane3D								GetPlane () const;
	OrthonormalizedCoordinateSystem3D	GetCoordSys () const;

	//#KiP_Note_GeometryRefactor ide jonnek meg muveletek, de ezt az interface-t a tobbi iv jellegu osztaly (GanArc, Circle 2D/3D) interface-evel egyutt at kell gondolni

private:
	GenArc arc2D;
	OrthonormalizedCoordinateSystem3D coordSys;
};

}

#endif
