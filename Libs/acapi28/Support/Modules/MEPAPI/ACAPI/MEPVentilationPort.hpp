#ifndef GS_ACAPI_MEP_VENTILATION_PORT_HPP
#define GS_ACAPI_MEP_VENTILATION_PORT_HPP

#include "MEPAPIExport.hpp"
#include "MEPPortBase.hpp"

#include "ACAPI/Result.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The VentilationPort represents a connection point of a duct.
 * @ingroup MEP
 * @since Archicad 27
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PortBase "PortBase"
 */
class MEPAPI_EXPORT VentilationPort final : public PortBase {
	VentilationPort (const UniqueID&);

public:
	~VentilationPort ();

	class Modifier;

	/**
	 * @brief Returns a VentilationPort.
	 * @param uniqueId The UniqueID of the requested VentilationPort.
	 * @return If the uniqueId belongs to a VentilationPort, returns the object associated to it, otherwise Error.
	 */
	static Result<VentilationPort> Get (const UniqueID& uniqueId);

	/** @return Returns the wall thickness of the VentilationPort. */
	double GetWallThickness () const;

	/** @return Returns the flow direction of the VentilationPort. */
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


class MEPAPI_EXPORT VentilationPort::Modifier final : public PortBase::Modifier {
	VentilationPort& parent;

	Modifier (VentilationPort&);
public:
	~Modifier ();

	friend VentilationPort;

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
Result<void> VentilationPort::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::VentilationPort;

} // ACAPI::MEP


#endif /*GS_ACAPI_MEP_VENTILATION_PORT_HPP*/