#ifndef GS_ACAPI_MEP_TERMINAL_HPP
#define GS_ACAPI_MEP_TERMINAL_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPTerminalDefault.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The Terminal is a complex element with a single port.
 * @since Archicad 27
 * @ingroup MEP
 */
class MEPAPI_EXPORT Terminal final : public ModifiableElementBase {
	Terminal (const UniqueID&);

public:
	class Modifier;
	~Terminal ();

	/**
	 * @brief Returns a Terminal.
	 * @param uniqueId The UniqueID of the requested Terminal.
	 * @return If the uniqueId belongs to a Terminal, returns the object associated to it, otherwise Error.
	 */
	static Result<Terminal> Get (const UniqueID& uniqueId);

	/**
	 * @brief Picks up the Default from the Terminal.
	 * @return Returns a TerminalDefault with the parameters of the object it was called for.
	 */
	TerminalDefault PickUpDefault () const;

	/**
	 * @brief Returns the domain of the Terminal.
	 * @return The returned domain can be ventilation or piping.
	 */
	Domain GetDomain () const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT Terminal::Modifier : public ModifiableElementBase::Modifier {
	Terminal& parent;

	Modifier (Terminal&);
	virtual ~Modifier ();

public:
	friend Terminal;

	/**
	 * @brief Injects the Default settings into the Terminal.
	 * @param terminalDefault The Default what will be injected. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const TerminalDefault& terminalDefault);
};


template <typename ModifierFunc>
Result<void> Terminal::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::Terminal;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_TERMINAL_HPP */