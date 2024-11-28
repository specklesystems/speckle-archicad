#ifndef GS_ACAPI_MEP_RIGID_SEGMENT_HPP
#define GS_ACAPI_MEP_RIGID_SEGMENT_HPP

#include "MEPAPIExport.hpp"
#include "MEPElementBase.hpp"
#include "MEPUniqueID.hpp"
#include "MEPEnums.hpp"

// ACAPI
#include "ACAPI/Result.hpp"

#include <optional>

namespace ACAPI::MEP {

namespace v1 {


class RigidSegmentDefault;


/**
 * @brief The RigidSegment is placed in RoutingSegments.
 * @details This type of element is placed automatically, it is used to fill a RoutingSegment.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test/New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp RigidSegment-Getters-Example
 * 		Labeling @snippet LabelingElements.cpp RigidSegment-Labeling-Example
 */
class MEPAPI_EXPORT RigidSegment final : public ElementBase {
	RigidSegment (const UniqueID& uniqueId);

public:
	~RigidSegment ();
	
	/**
	 * @brief Returns a RigidSegment.
	 * @param uniqueId The UniqueID of the requested RigidSegment.
	 * @return If the uniqueId belongs to a RigidSegment, returns the object associated to it, otherwise Error.
	 */
	static Result<RigidSegment> Get (const UniqueID& uniqueId);

	/** @return Returns the insulation thickness if the RigidSegment has insulation, otherwise std::nullopt. RigidSegment of cable carrier domain cannot have insulation. */
	std::optional<double>	GetInsulationThickness () const;
	
	/** @return Returns the length of the RigidSegment. */
	double		GetLength () const;

	/** @return Returns the width of the RigidSegment. */
	double		GetWidth () const;

	/** @return Returns the height of the RigidSegment. */
	double		GetHeight () const;

	/** @return Returns the UniqueID of the RoutingSegment that it belongs to. */
	UniqueID	GetRoutingSegmentId () const;
	
	/** @return Returns the domain of the RigidSegment. */
	Domain		GetDomain () const;

	/**
	 * @brief Picks up and returns the Default of the RigidSegment.
	 * @return Returns a RigidSegmentDefault with the parameters of the object it was called for.
	 */
	RigidSegmentDefault			PickUpDefault () const;
};


} // v1

using v1::RigidSegment;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_RIGID_SEGMENT_HPP*/