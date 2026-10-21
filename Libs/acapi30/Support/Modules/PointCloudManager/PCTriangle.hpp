// *********************************************************************************************************************
// Description:		Simple 2D (XY) triangle representation for point clouds.
//
// Module:			PointCloudManager
// Namespace:		PC
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (PCTRIANGLE_HPP)
#define PCTRIANGLE_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from PointCloudManager
#include "PointCloudManagerDefinitions.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PC {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

struct	POINTCLOUDMANAGER_DLL_EXPORT	Triangle
{
	Triangle () 
		: x1 (0.0f) 
		, y1 (0.0f)
		, x2 (0.0f) 
		, y2 (0.0f)
		, x3 (0.0f) 
		, y3 (0.0f)
	{
		// do nothing
	}

	Triangle (float x1In, float y1In, float x2In, float y2In, float x3In, float y3In)
		: x1 (x1In) 
		, y1 (y1In)
		, x2 (x2In) 
		, y2 (y2In)
		, x3 (x3In) 
		, y3 (y3In)
	{
		// do nothing
	}

	~Triangle ();

	float x1, y1, x2, y2, x3, y3;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------



}	// namespace PC

#endif // PCTRIANGLE_HPP
