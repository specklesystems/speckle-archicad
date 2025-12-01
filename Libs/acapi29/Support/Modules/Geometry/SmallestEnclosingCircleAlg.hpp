#if !defined (GS_SMALLEST_ENCLOSING_CIRCLE_ALG_HPP)
#define GS_SMALLEST_ENCLOSING_CIRCLE_ALG_HPP

#pragma once

#include "GeometricDefinitions.h"

//from GSRoot
#include "Definitions.hpp"
#include "PagedArray.hpp"
#include "Point2D.hpp"

namespace Geometry {

class Circle2D;

//Use this algorithm to find the smallest circle/disk encapsulating all the points in the plane given as input.
//!This is a recursive algorithm, so the length of the input is practically limited!
//resultCirc is your circle, except if the radius is negative (in case you should also get error code as the return value
GEOMETRY_DLL_EXPORT GSErrCode CalcSmallestEnclosingCircle (const GS::PagedArray<Point2D>& pointsToEnclose, Circle2D& resultCirc);
}

#endif

