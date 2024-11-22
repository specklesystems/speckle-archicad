#ifndef GS_ACAPI_MEP_BEND_HPP
#define GS_ACAPI_MEP_BEND_HPP

#include "MEPAPIExport.hpp"
#include "MEPElementBase.hpp"

// ACAPI
#include "ACAPI/Result.hpp"

#include <optional>

namespace ACAPI::MEP {

inline namespace v1 {


class BendDefault;


/** @brief The Bend can connect two straight RoutingSegments with the same dimensions but different directions.
	@details This type of element can be placed in RoutingNodes.
	@since Archicad 27
	@ingroup MEP
	@par Example code snippet from Test/New MEP
		Getters @snippet QueryElementsAndDefaults.cpp Bend-Getters-Example
*/
class MEPAPI_EXPORT Bend final : public ElementBase {
	Bend (const UniqueID&);
public:
	class Modifier;
	~Bend ();

	/** @brief Returns a Bend.
		@param uniqueId The UniqueID of the requested Bend.
		@return If the uniqueId belongs to a Bend, returns the object associated to it, otherwise Error.
	*/
	static Result<Bend>		Get (const UniqueID& uniqueId);

	/** @return Returns the insulation thickness if the Bend has insulation, otherwise std::nullopt. Bend of cable carrier domain cannot have insulation. */
	std::optional<double>	GetInsulationThickness () const;

	/** @return Returns the width of the Bend. */
	double					GetWidth () const;

	/** @return Returns the height of the Bend. */
	double					GetHeight () const;

	/** @return Returns the shape of the Bend. */
	ConnectorShape			GetShape () const;

	/** @return Returns the radius of the Bend. */
	double					GetRadius () const;

	/** @brief The radius of the Bend is calculated with the help of this value.
		@return Returns the factor of the Bend.
	*/
	double					GetFactorRadius () const;

	/** @return Returns the UniqueID of the RoutingNode that it belongs to. */
	UniqueID				GetRoutingNodeId () const;

	/** @return Returns the domain of the Bend. */
	Domain					GetDomain () const;

	/** @return Returns a BendDefault with the parameters of the object it was called for. */
	BendDefault				PickUpDefault () const;

	/** @brief Executed the passed modifier scope in an Undoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@param undoString The text which appear in the undo queue of Archicad after executing the command.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
	*/
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT Bend::Modifier {
	Bend& parent;

	Modifier (Bend&);
public:
	friend Bend;

	~Modifier ();

	/** @brief Sets the factor of the radius of the Bend.
		@param factor The value to be set. Needs to be between 0.6 and 3.0.
		@return Returns an error if the parameter is not in range, otherwise nothing.
	*/
	Result<void>	SetFactorRadius (double factor);
};


template <typename ModifierFunc>
Result<void> Bend::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

} // ACAPI::MEP

#endif /*GS_ACAPI_MEP_BEND_HPP*/