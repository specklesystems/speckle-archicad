#ifndef GS_ACAPI_MEP_FLEXIBLE_SEGMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_FLEXIBLE_SEGMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"


namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class IFlexibleSegmentDefaultImpl; }

namespace v1 {


/**
 * @brief The FlexibleSegmentDefault contains the necessary non-geometric data for creating a FlexibleSegment element.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Pickup and Getters @snippet QueryElementsAndDefaults.cpp FlexibleSegmentDefault-Pickup-and-Getters-Example
 * 		Placement @snippet PlaceElements.cpp FlexibleSegment-Placement-Example
 * 		Polyline Placement @snippet PlacePolylineFlexibleSegments.cpp FlexibleSegment-Polyline-Placement-Example
 */
class MEPAPI_EXPORT FlexibleSegmentDefault final : public ElementDefault {
	FlexibleSegmentDefault (std::shared_ptr<Impl::IFlexibleSegmentDefaultImpl>);
	static Result<FlexibleSegmentDefault>	Create (const API_Token&, Domain);

protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<FlexibleSegmentDefault>	CreateFlexibleSegmentDefault (Domain domain);

	/**
	 * @brief Places a FlexibleSegment element defined by a spline geometry based on this Default.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param controlPoints The control points the FlexibleSegment will be placed with.
	 * @param startOrientation The orientation of the start point of the FlexibleSegment, which is based on a direction vector and a rotation vector.
	 * @param endOrientation The orientation of the end point of the FlexibleSegment, which is based on a direction vector and a rotation vector.
	 * @param requiredId The guid to be set for the FlexibleSegment - optional parameter.
	 * @return If executed with success, returns the newly placed FlexibleSegment's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const std::vector<API_Coord3D>& controlPoints, const Orientation& startOrientation, const Orientation& endOrientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;
	
	/**
	 * @brief Places a FlexibleSegment element defined by a polyline based on this Default. Only supported domain is Piping.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param polyline The polyline geometry the FlexibleSegment will be placed with. The polyline must include alternating types of segments, either a
	 * 				   straight line (defined by its begin and end coordinates), or a spline (defined by its control points). Adjacent segments must connect at their starting/ending points.
	 * @param startDirectionVector The direction vector of the start point of the FlexibleSegment. Must be nullopt when the first segment is a line.
	 * @param endDirectionVector The direction vector of the end point of the FlexibleSegment. Must be nullopt when the last segment is a line.
	 * @param requiredId The guid to be set for the FlexibleSegment - optional parameter.
	 * @return If executed with success, returns the newly placed FlexibleSegment's uniqueId, otherwise Error.
	 */
	Result<UniqueID> PlacePolyline (const FlexibleSegmentPolyline& polyline, const std::optional<API_Vector3D>& startDirectionVector, const std::optional<API_Vector3D>& endDirectionVector, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/** @return Returns the width of the FlexibleSegment. */
	double	GetWidth () const;

	/** @return Returns the height of the FlexibleSegment. */
	double	GetHeight () const;

	/** @return Returns the shape of the FlexibleSegment. */
	ConnectorShape GetShape () const;
};


/**
 * @brief Creates a FlexibleSegmentDefault.
 * @ingroup MEP
 * @param domain The domain determines whether the Default will be Duct or Pipe FlexibleSegment tool.
 * @return If able, returns a copy of Archicad's current Default of the Duct (Ventilation) or Pipe (Piping) FlexibleSegment tool, otherwise Error.
 */
inline Result<FlexibleSegmentDefault> CreateFlexibleSegmentDefault (Domain domain)
{
	return FlexibleSegmentDefault::Create (ACAPI_GetToken (), domain);
}


} // v1

using v1::FlexibleSegmentDefault;
using v1::CreateFlexibleSegmentDefault;

} // ACAPI::MEP

#endif /* GS_ACAPI_MEP_FLEXIBLE_SEGMENT_DEFAULT_HPP */