// *********************************************************************************************************************
// Description:		Base class of filtering rule implementations used in @PointCloud::Walker.
//
// Module:			PointCloudManager
// Namespace:		PointCloud
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (POINTCLOUDFILTER_HPP)
#define POINTCLOUDFILTER_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Ref.hpp"

// from Geometry
#include "Vector3D.hpp"

// from PointCloud
#include "PCMatrix.hpp"

// from PointCloudManager
#include "PointCloudManagerDefinitions.hpp"

#include "PointCloudFilterFwd.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PointCloud {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------------
// Base class of filtering rule used in @PointCloud::Walker. A filtering rule describes that a region (node)
// of the point tree or a specific point must or must not be included in the result.
// ---------------------------------------------------------------------------------------------------------------------
class POINTCLOUDMANAGER_DLL_EXPORT Filter
{
public:
	enum NodeResult
	{
		NodeFullHidden,
		NodeFullVisible,
		NodeUndetermined
	};

	enum PointResult
	{
		PointHidden,
		PointVisible
	};

	Filter ()
	{
		 // do nothing
	}
    
    virtual ~Filter ();

	// Returns if the points in the given spheric region (node) must all be kept (NodeFullVisible), all removed (NodeFullHidden)
	// or further testing is needed on smaller regions (NodeUndetermined).
	// If the @newFilter parameter is not a @nullptr, a new instance of @Filter is returned through it that can safely
	// be used on nodes and points that are inside the currently tested node, in replacement of the current instance. 
	// This gives the ability to give back a new filter that can produce the same result with less calculations on the
	// contained nodes and points.
	virtual NodeResult	TestNode	(const Geometry::Coord3D& center, const float radius, Filter** newFilter = nullptr) const = 0;

	// Returns if the given point must be kept (PointVisible) or removed (PointHidden).
	virtual PointResult	TestPoint	(const Geometry::Coord3D& point) const = 0;	
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

}	// namespace PointCloud

#endif // POINTCLOUDFILTER_HPP
