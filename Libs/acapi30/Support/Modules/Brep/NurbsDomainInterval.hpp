// *********************************************************************************************************************
// Represents a slice of the domain of a NURBS curve or of one of the 1D domains of a NURBS surface.
// *********************************************************************************************************************

#if !defined(NURBSDOMAININTERVAL_HPP)
#define NURBSDOMAININTERVAL_HPP

#pragma once

// from Geometry
#include "Vector3D.hpp"

namespace Brep {


struct Interval {
	double begin;
	double end;
	Interval () :
		begin (BiggestDouble),
		end (-BiggestDouble)
	{ }
	Interval (double b, double e) :
		begin (b),
		end (e)
	{
	}
	bool Equals (const Interval& other, double eps = SmallEps) const
	{
		return (Geometry::IsNear (begin, other.begin, eps)
				&& Geometry::IsNear (end, other.end, eps));
	}
};

}		// namespace Brep

#endif	// NURBSDOMAININTERVAL_HPP
