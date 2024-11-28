#define COORDINATE_SYSTEM_UTILS_3D_HPP
#pragma once

#include "GeometricDefinitions.h"
#include "Vector3D.hpp"

namespace Geometry {
class OrthonormalizedCoordinateSystem3D;
class GeneralCoordinateSystem3D;

GEOMETRY_DLL_EXPORT
OrthonormalizedCoordinateSystem3D CreateCoordinateSystem (const Point3D& origo, const Vector3D& zAxis);

GEOMETRY_DLL_EXPORT
GeneralCoordinateSystem3D CreateCoordinateSystem (const Point3D& origo, const Vector3D& zAxis, const Vector3D& xAxis);
}