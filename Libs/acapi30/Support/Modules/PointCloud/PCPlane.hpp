// *********************************************************************************************************************
// Description:		Simple plane (or half space) representation for the PointCloud module.
//
// Module:			PointCloud
// Namespace:		PC
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (PCPLANE_HPP)
#define PCPLANE_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include "PointCloudDefinitions.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PC {
	class Matrix;
	class DMatrix;
}

namespace PC {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------------
// Represents the 3D plane described by the equation: pa * x + pb * y + pc * z + pd = 0
// ---------------------------------------------------------------------------------------------------------------------
struct	POINTCLOUD_DLL_EXPORT	Plane
{
	Plane ()
		: a (0.0)
		, b (0.0)
		, c (0.0)
		, d (0.0)
	{
		// do nothing
	}

	Plane (double aIn, double bIn, double cIn, double dIn)
		: a (aIn)
		, b (bIn)
		, c (cIn)
		, d (dIn)
	{
		// do nothing
	}

	~Plane ();

	void Normalize ();
	
	// member values
	double	a, b, c, d;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

}	// namespace PC

PC::Plane operator* (const PC::DMatrix& traf, const PC::Plane& p);

#endif // PCPLANE_HPP
