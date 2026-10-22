#ifndef TRANSFORMATION_CONVERTER
#define TRANSFORMATION_CONVERTER

#pragma once

#include "GeometricDefinitions.h"

namespace Geometry {

class Transformation2D;
class Transformation3D;

GEOMETRY_DLL_EXPORT	Transformation2D ConvertTransformation3DTo2D (const Transformation3D& transformation);
GEOMETRY_DLL_EXPORT	Transformation3D ConvertTransformation2DTo3D (const Transformation2D& transformation);

}

#endif