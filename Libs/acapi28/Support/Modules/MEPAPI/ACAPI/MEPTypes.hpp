#ifndef GS_ACAPI_MEP_TYPES_HPP
#define GS_ACAPI_MEP_TYPES_HPP

#include "MEPEnums.hpp"
#include "MEPUniqueID.hpp"

// from ARCHICADAPI
#include "APIdefs_Base.h"
#include "ACAPI/Object.hpp"

// from std
#include <optional>
#include <vector>
#include <variant>


namespace ACAPI::MEP {


/**
 * @brief Defines the orientation with the help of a direction and rotation vector.
 * @struct Orientation
 * @ingroup MEP
 */
struct Orientation {
	/** @brief Direction of the Orientation. */
	API_Vector3D direction;

	/** @brief Rotation of the Orientation. */
	API_Vector3D rotation;
};


/**
 * @brief Defines the necessary data for placing RectangularRoutingSegments of a RoutingElement.
 * @struct RoutingSegmentRectangularCrossSectionData
 * @ingroup MEP
 */
struct RoutingSegmentRectangularCrossSectionData {
	/** @brief Width of the cross section. */
	double width;

	/** @brief Height of the cross section. */
	double height;

	/**
	 * @brief Constructs a RoutingSegmentRectangularCrossSectionData.
	 * @param width The width of the RectangularRoutingSegment.
	 * @param height The height of the RectangularRoutingSegment.
	 */
	RoutingSegmentRectangularCrossSectionData (double width, double height) 
		: width (width), height (height)
	{
	}
};


/**
 * @brief Defines the necessary data for placing CircularRoutingSegments of a RoutingElement.
 * @struct RoutingSegmentCircularCrossSectionData
 * @ingroup MEP
 */
struct RoutingSegmentCircularCrossSectionData {
	/** @brief ReferenceId of the cross section. */
	UInt32 referenceId;

	/**
	 * @brief Constructs a RoutingSegmentCircularCrossSectionData.
	 * @param referenceId The referenceId of the CircularRoutingSegment.
	 */
	RoutingSegmentCircularCrossSectionData (UInt32 referenceId)
		: referenceId (referenceId)
	{
	}
};


/**
 * @brief Defines the changes regarding Ids after a RoutingElement-RoutingElement connection.
 * @struct RouteConnectionResult
 * @ingroup MEP
 */
struct RouteConnectionResult {
	/** @brief If there was a merge, it contains the id of the deleted RoutingElement. */
	std::optional<UniqueID>	deletedRoutingElementId;

	/** @brief If there was a splitting, it contains the id of the newly created RoutingElement. */
	std::optional<UniqueID>	splittedRoutingElementId;

	/** @brief If there was a splitting, it contains the id of the newly created branch. */
	std::optional<UniqueID>	createdBranchId;
};


/**
 * @brief Defines a single line segment of a polyline FlexibleSegment.
 * @struct FlexibleSegmentPolylineLinePart
 * @ingroup MEP
 */
struct FlexibleSegmentPolylineLinePart {
	/** @brief World coordinate of starting point of the line. */
	API_Coord3D begin;

	/** @brief World coordinate of ending point of the line. */
	API_Coord3D end;
};


/**
 * @brief Defines a single spline segment of a polyline FlexibleSegment.
 * @struct FlexibleSegmentPolylineSplinePart
 * @ingroup MEP
 */
struct FlexibleSegmentPolylineSplinePart {
	/** @brief World coordinates of control points. */
	std::vector<API_Coord3D> controlPoints;
};


/**
 * @brief Defines a polyline FlexibleSegment geometry. Must contain alternating line and spline segments.
 * @ingroup MEP
 */
using FlexibleSegmentPolyline = std::vector<std::variant<FlexibleSegmentPolylineLinePart, FlexibleSegmentPolylineSplinePart>>;


} // ACAPI::MEP


#endif