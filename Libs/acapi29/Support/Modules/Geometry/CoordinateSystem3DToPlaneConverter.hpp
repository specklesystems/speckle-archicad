#ifndef COORDINATESYSTEM3D_TO_PLANE_CONVERTER_HPP 
#define COORDINATESYSTEM3D_TO_PLANE_CONVERTER_HPP
#pragma once

#include "GeometricDefinitions.h"
#include "Optional.hpp"

namespace Geometry {

class Plane;
class CoordinateSystem3D;
class GeneralCoordinateSystem3D;
class OrthonormalizedCoordinateSystem3D;


GEOMETRY_DLL_EXPORT	Plane CoordinateSystem3DToPlane (const CoordinateSystem3D& coordSys);

GEOMETRY_DLL_EXPORT	GeneralCoordinateSystem3D PlaneToGeneralCoordinateSystem3D (const Plane& plane);

GEOMETRY_DLL_EXPORT	GS::Optional<OrthonormalizedCoordinateSystem3D> PlaneToOrthonormalizedCoordinateSystem3D (const Plane& plane);

}

#endif