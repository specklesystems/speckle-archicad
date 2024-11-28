#ifndef GS_ACAPI_MEP_TRANSITION_HPP
#define GS_ACAPI_MEP_TRANSITION_HPP

#include "MEPAPIExport.hpp"
#include "MEPEnums.hpp"
#include "MEPUniqueID.hpp"
#include "MEPElementBase.hpp"

// ACAPI
#include "ACAPI/Result.hpp"

#include <optional>


namespace ACAPI::MEP {

namespace v1 {


class TransitionDefault;


/**
 * @brief The Transition is an element that connects two different Routing Segments.
 * @details Routing Segments can differ from each other in size or shape.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test/New MEP
 * 		Getters @snippet QueryElementsAndDefaults.cpp Transition-Getters-Example
 * 		Labeling @snippet LabelingElements.cpp Transition-Labeling-Example
 */
class MEPAPI_EXPORT Transition final : public ElementBase {
private:
	Transition (const UniqueID&);

public:
	~Transition ();

	/**
	 * @brief Returns a Transition.
	 * @param uniqueId The UniqueID of the requested Transition.
	 * @return If the uniqueId belongs to a Transition, returns the object associated to it, otherwise Error.
	 */
	static Result<Transition> Get (const UniqueID& uniqueId);

	/** @return Returns the insulation thickness if the Transition has insulation, otherwise std::nullopt. Transition of cable carrier domain cannot have insulation. */
	std::optional<double>	GetInsulationThickness () const;

	/** @return Returns the angle of the Transition in degrees.*/
	double					GetAngle () const;

	/** @return Returns the length of the Transition.*/
	double					GetLength () const;

	/** @return Returns the offset of the Transition in the Y direction.*/
	double					GetOffsetY () const;

	/** @return Returns the offset of the Transition in the Z direction.*/
	double					GetOffsetZ () const;

	/** @return Returns the ID of the narrower port.*/
	UniqueID				GetNarrowerPortID () const;

	/** @return Returns the ID of the wider port.*/
	UniqueID				GetWiderPortID () const;

	/** @return Returns the UniqueID of the RoutingNode that it belongs to. */
	UniqueID				GetRoutingNodeId () const;

	/** @return Returns the domain of the element. */
	Domain					GetDomain () const;

	/**
	 * @brief Picks up and returns the Default of the Transition.
	 * @return Returns a TransitionDefault with the parameters of the object it was called for.
	 */
	TransitionDefault			PickUpDefault () const;
};


} // v1

using v1::Transition;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_TRANSITION_HPP