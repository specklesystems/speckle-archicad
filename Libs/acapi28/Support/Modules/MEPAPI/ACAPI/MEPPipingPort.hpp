#ifndef GS_ACAPI_MEP_PIPING_PORT_HPP
#define GS_ACAPI_MEP_PIPING_PORT_HPP

#include "MEPAPIExport.hpp"
#include "MEPPortBase.hpp"

#include "ACAPI/Result.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The PipingPort represents a connection point of a pipe segment.
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PortBase "PortBase"
 */
class MEPAPI_EXPORT PipingPort final : public PortBase {
	PipingPort (const UniqueID&);

public:
	~PipingPort ();

	class Modifier;

	/**
	 * @brief Returns a PipingPort.
	 * @param uniqueId The UniqueID of the requested PipingPort.
	 * @return If the uniqueId belongs to a PipingPort, returns the object associated to it, otherwise Error.
	 */
	static Result<PipingPort> Get (const UniqueID& uniqueId);

	/** @return Returns the outer diameter of the PipingPort. */
	double			GetOuterDiameter () const;

	/** @return Returns the wall thickness of the PipingPort. */
	double			GetWallThickness () const;

	/** @return Returns the flow direction of the PipingPort. */
	FlowDirection	GetFlowDirection () const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT PipingPort::Modifier final : public PortBase::Modifier {
	PipingPort& parent;

	Modifier (PipingPort&);
public:
	~Modifier ();

	friend PipingPort;

	/**
	 * @brief Sets the outer diameter of the port.
	 * @param diameter The value to be set.
	 * @return Returns an error if you are trying to modify a Port of a Branch, otherwise nothing.
	 */
	Result<void> SetOuterDiameter (double diameter);

	/**
	 * @brief Sets the thickness of the port's wall.
	 * @param thickness The value to be set.
	 */
	void SetWallThickness (double thickness);

	/**
	 * @brief Sets the flow direction of the port.
	 * @param flowDirection The value to be set.
	 */
	void SetFlowDirection (FlowDirection flowDirection);
};


template <typename ModifierFunc>
Result<void> PipingPort::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::PipingPort;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_PIPING_PORT_HPP*/