#ifndef GS_ACAPI_MEP_TAKE_OFF_HPP
#define GS_ACAPI_MEP_TAKE_OFF_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPTakeOffDefault.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The Take-off is a simple element with two ports on a single axis.
 * @since Archicad 28
 * @ingroup MEP
 */
class MEPAPI_EXPORT TakeOff final : public ModifiableElementBase {
	TakeOff (const UniqueID&);

public:
	class Modifier;
	~TakeOff ();

	/**
	 * @brief Returns a Take-off.
	 * @param uniqueId The UniqueID of the requested Take-off.
	 * @return If the uniqueId belongs to a Take-off, returns the object associated to it, otherwise Error.
	 */
	static Result<TakeOff> Get (const UniqueID& uniqueId);

	/**
	 * @brief Picks up the Default from the Take-off.
	 * @return Returns a TakeOffDefault with the parameters of the object it was called for.
	 */
	TakeOffDefault PickUpDefault () const;

	/**
	 * @brief Returns the domain of the Take-off.
	 * @return The returned domain can currently only be ventilation.
	 */
	Domain GetDomain () const;

	/**
	 * @brief Returns the length of the Take-off.
	 * @return The length of the Take-off
	 */
	double GetLength () const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT TakeOff::Modifier : public ModifiableElementBase::Modifier {
	TakeOff& parent;

	Modifier (TakeOff&);
	virtual ~Modifier ();

public:
	friend TakeOff;

	/**
	 * @brief Sets the length of the Take-off
	 * @param length The new length of the Take-off in meters
	 */
	void SetLength (double length);

	/**
	 * @brief Injects the Default settings into the Take-off.
	 * @param TakeOffDefault The Default what will be injected. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const TakeOffDefault& TakeOffDefault);
};


template <typename ModifierFunc>
Result<void> TakeOff::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::TakeOff;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_TAKE_OFF_HPP */