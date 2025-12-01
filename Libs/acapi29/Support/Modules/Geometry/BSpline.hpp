// *********************************************************************************************************************
// Description:		BSpline class
//
// Module:			Geometry
// Namespace:		Geometry
//
// SG compatible
// *********************************************************************************************************************

#ifndef BSPLINE_HPP
#define BSPLINE_HPP

// from Geometry
#include "GeometricDefinitions.h"

namespace Geometry {
	
class KnotVector;

class GEOMETRY_DLL_EXPORT BSpline {
private:
	const Geometry::KnotVector& knotVector;

	BSpline ();								// disabled
	BSpline (const BSpline&);				// disabled
	BSpline& operator= (const BSpline&);	// disabled

public:
	static const USize AssumedMaxDegree = 16;	// A reasonable common upper bound of the degree of a BSpline.
												// Used for optimization purposes only, does not restrict any calculations.
	
	BSpline (const Geometry::KnotVector& knotVector_) : knotVector (knotVector_)
	{
		// do nothing
	}

	UIndex GetEffectiveBSplineValues	(GS::Array<double>& values, const double t) const;

//	double GetValue						(UInt32 i, double t) const;
//	double GetDerivate					(Int32 i, double t) const;
};

}		// namespace Geometry

#endif	// BSPLINE_HPP