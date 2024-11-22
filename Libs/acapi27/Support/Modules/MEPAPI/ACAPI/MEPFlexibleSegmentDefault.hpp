#ifndef GS_ACAPI_MEP_FLEXIBLE_SEGMENT_DEFAULT_HPP
#define GS_ACAPI_MEP_FLEXIBLE_SEGMENT_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"


namespace ACAPI::MEP {

namespace Impl { class IFlexibleSegmentDefaultImpl; }

inline namespace v1 {


/** @brief The FlexibleSegmentDefault contains the necessary non-geometric data for creating a FlexibleSegment element.
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test / New MEP
		Pickup and Getters @snippet QueryElementsAndDefaults.cpp FlexibleSegmentDefault-Pickup-and-Getters-Example
		Placement @snippet PlaceElements.cpp FlexibleSegment-Placement-Example
*/
class MEPAPI_EXPORT FlexibleSegmentDefault final : public ElementDefault {
	FlexibleSegmentDefault (std::shared_ptr<Impl::IFlexibleSegmentDefaultImpl>);
	static Result<FlexibleSegmentDefault>	Create (const API_Token&);

public:
	friend class FlexibleSegment;
	friend Result<FlexibleSegmentDefault>	CreateFlexibleSegmentDefault ();

	/** @brief Places a FlexibleSegment element based on this Default.
	
		@details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
		When someone would like to group the placement of several routes and/or MEP elements together, it is recommended to create a single Command Scope.
		Doing this prevents the opening and closing of a Command Scope for every single created route and/or MEP element, therefore the performance should be improved.
	
		@param controlPoints The control points the FlexibleSegment will be placed with.
		@param startOrientation The orientation of the start point of the FlexibleSegment, which is based on a direction vector and a rotation vector.
		@param endOrientation The orientation of the end point of the FlexibleSegment, which is based on a direction vector and a rotation vector.
		@param requiredId The guid to be set for the FlexibleSegment - optional parameter
		@return If executed with success, returns the newly placed FlexibleSegment's uniqueId, otherwise Error.
	*/
	Result<UniqueID> Place (const std::vector<API_Coord3D>& controlPoints, const Orientation& startOrientation, const Orientation& endOrientation, const std::optional<API_Guid>& requiredId = std::nullopt) const;

	/** @return Returns the width of the FlexibleSegment. */
	double	GetWidth () const;

	/** @return Returns the height of the FlexibleSegment. */
	double	GetHeight () const;

	/** @return Returns the shape of the FlexibleSegment. */
	ConnectorShape			GetShape () const;
};


/** @brief Creates a FlexibleSegmentDefault.
	@ingroup MEP
	@return If able, returns a copy of Archicad's current Default of the Duct (Ventilation) FlexibleSegment tool, otherwise Error.
*/
inline Result<FlexibleSegmentDefault> CreateFlexibleSegmentDefault ()
{
	return FlexibleSegmentDefault::Create (ACAPI_GetToken ());
}


} // v1

} // ACAPI::MEP

#endif /* GS_ACAPI_MEP_FLEXIBLE_SEGMENT_DEFAULT_HPP */