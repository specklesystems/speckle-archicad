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

inline namespace v1 {


class TransitionDefault;


/** @brief The Transition is an element that connects two different Routing Segments.
	@details Routing Segments can differ from each other in size or shape.
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test/New MEP
		Getters @snippet QueryElementsAndDefaults.cpp Transition-Getters-Example
*/
class MEPAPI_EXPORT Transition final : public ElementBase {
private:
	Transition (const UniqueID&);

public:
	class Modifier;
	~Transition ();

	/** @brief Returns a Transition.
		@param uniqueId The UniqueID of the requested Transition.
		@return If the uniqueId belongs to a Transition, returns the object associated to it, otherwise Error.
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

	/** @brief Picks up and returns the Default of the Transition.
		@return Returns a TransitionDefault with the parameters of the object it was called for.
	*/ 
	TransitionDefault			PickUpDefault () const;

	/** @brief Executed the passed modifier scope in an Undoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@param undoString The text which appear in the undo queue of Archicad after executing the command.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
	*/
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT Transition::Modifier {
	Transition& parent;

	Modifier (Transition&);
public:
	friend Transition;

	~Modifier ();

	/** @brief Sets the angle of the Transition.
		@param angle The value to be set. Needs to be between [1, 89] degrees.
		@return Returns an error if the parameter is not in range, otherwise nothing.
	*/
	Result<void> SetAngle (double angle);
};


template <typename ModifierFunc>
Result<void> Transition::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_TRANSITION_HPP