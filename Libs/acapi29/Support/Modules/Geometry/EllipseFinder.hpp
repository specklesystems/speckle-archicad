#ifndef ELLIPSE_FINDER_HPP
#define ELLIPSE_FINDER_HPP
#pragma once

#include "GeometricDefinitions.h"
#include "Point2D.hpp"

namespace Geometry {
	class Ellipse;
}

struct Sector;



namespace Geometry {

class GEOMETRY_DLL_EXPORT GRDebugger //Ebbol kellene csinalni egy Visual Debug-ert akar 3D-hez is. Ez egy onallo ablakos mini app lenne, visualization control-al, debug-control-al, ugy hogy unit tesztekhez is mukodne, de AC - n belul is. Szivesen megterveznem. AACS
{
public:
	virtual ~GRDebugger (); 
	virtual void AddPoint (const Point2D& p, const char* color) = 0;
	virtual void AddLineSegment (const Sector& s, const char* color) = 0;
	virtual void AddEllipse (const Geometry::Ellipse& e, const char* color) = 0;

	virtual void ZoomToPoints (const GS::Array<Point2D>& pointSet) = 0;
	virtual void AddMargin (const double percentX, const double percentY) = 0;
};

//Usage note: 
// FitEllipseToPoints tries to fit an ellipse exactly, while
// RegressionEllipseToPoints tries to find an ellipse, that is best approximating the points (regression)

//For both functions:
//1. For 5 points expect exact fit within EPS error (unless you are clustering some of the points)
//2. For less than 5 point, there will be no result.

//FitEllipseToPoints may fail (no result) if the points are not lying on an ellipse (e.g. due to noise)
//RegressionEllipseToPoints may fail when the points are too noisy and/or not lying on an ellipse.

GEOMETRY_DLL_EXPORT
GS::Optional<Ellipse>	FitEllipseToPoints (const GS::Array<Point2D>& points, GRDebugger* GRDbg = nullptr); // Fits ellipse to EPS tolerance.

GEOMETRY_DLL_EXPORT
GS::Optional<Ellipse>	RegressionEllipseToPoints (const GS::Array<Point2D>& points, double& regressionError /*unit is meter*/, GRDebugger* GRDbg = nullptr);

}

#endif

