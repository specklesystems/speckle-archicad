#ifndef GS_ACAPI_MEP_TAKE_OFF_DEFAULT_HPP
#define GS_ACAPI_MEP_TAKE_OFF_DEFAULT_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"
#include "MEPElementDefault.hpp"

namespace ACAPI::Impl { class ObjectCreator; }

namespace ACAPI::MEP {

namespace Impl { class ITakeOffDefaultImpl; }

namespace v1 {


/**
 * @brief The TakeOffDefault contains the necessary non-geometric data for creating a Take-off element.
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Placement @snippet PlaceElements.cpp Take-Off-Placement-Example
 * 		Modification @snippet ModifyElements.cpp Take-Off-Modification-Example
 */
class MEPAPI_EXPORT TakeOffDefault final : public ElementDefault {
	TakeOffDefault (std::shared_ptr<Impl::ITakeOffDefaultImpl>);
	static Result<TakeOffDefault> Create (const API_Token&, Domain);
protected:
	friend class ACAPI::Impl::ObjectCreator;

public:
	friend Result<TakeOffDefault> CreateTakeOffDefault (Domain);

	/**
	 * @brief Places an Take-off element on the given segment based on this Default.
	 *
	 * @details The implementation creates an Undoable Command Scope before executing the placement. This Command Scope is automatically closed after execution.
	 * 			When someone would like to group the placement of several RoutingElements and/or MEP elements together, it is recommended to create a single Command Scope.
	 * 			Doing this prevents the opening and closing of a Command Scope for every single created RoutingElement and/or MEP element, therefore the performance should be improved.
	 *
	 * @param associatedSegmentId The UniqueID representing the RoutingSegment on which the Take-off will be placed
	 * @param distanceFromBeginning The distance along the segment where the Take-off will be placed, measured from the beginning coordinate of the associated segment
	 * @param rotationAroundMainAxis The rotation of the Take-off with the associated segment's direction vector as an axis - optional parameter, the default value of 0.0 will place the Take-off facing left relative to the segment's direction
	 * @param requiredId The guid to be set for the Take-off - optional parameter
	 * @return If executed with success, returns the newly placed Take-off's uniqueId, otherwise Error.
	 */
	Result<UniqueID> Place (const UniqueID& associatedSegmentId, const double distanceFromBeginning, const double rotationAroundMainAxis = 0.0, const std::optional<API_Guid>& requiredId = std::nullopt) const;
};


/**
 * @brief Creates a TakeOffDefault
 * @ingroup MEP
 * @param domain The domain of the requested TakeOffDefault. Currently it can only be ventilation.
 * @return If able, returns a copy of Archicad's current Default of the TakeOff tool for the domain defined by the parameter, otherwise Error (for ex. if domain is cable carrier).
 */
inline Result<TakeOffDefault> CreateTakeOffDefault (Domain domain)
{
	return TakeOffDefault::Create (ACAPI_GetToken (), domain);
}


} // v1

using v1::TakeOffDefault;
using v1::CreateTakeOffDefault;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_TAKE_OFF_DEFAULT_HPP */