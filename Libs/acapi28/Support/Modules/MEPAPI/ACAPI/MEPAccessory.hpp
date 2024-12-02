#ifndef GS_ACAPI_MEP_ACCESSORY_HPP
#define GS_ACAPI_MEP_ACCESSORY_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPAccessoryDefault.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The Accessory is a complex element with two ports on a single axis.
 * @since Archicad 27
 * @ingroup MEP
 */
class MEPAPI_EXPORT Accessory final : public ModifiableElementBase {
	Accessory (const UniqueID&);

public:
	class Modifier;
	~Accessory ();

	/**
	 * @brief Returns an Accessory.
	 * @param uniqueId The UniqueID of the requested Accessory.
	 * @return If the uniqueId belongs to an Accessory, returns the object associated to it, otherwise Error.
	 */
	static Result<Accessory> Get (const UniqueID& uniqueId);

	/**
	 * @brief Picks up the Default from the Accessory.
	 * @return Returns an AccessoryDefault with the parameters of the object it was called for.
	 */
	AccessoryDefault PickUpDefault () const;

	/**
	 * @brief Returns the domain of the Accessory.
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


class MEPAPI_EXPORT Accessory::Modifier : public ModifiableElementBase::Modifier {
	Accessory& parent;

	Modifier (Accessory&);
	virtual ~Modifier ();

public:
	friend Accessory;

	/**
	 * @brief Injects the Default settings into the Accessory.
	 * @param accessoryDefault The Default what will be injected. One should pay attention to the parameter, it has to belong to the same domain than the object it is called for.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const AccessoryDefault& accessoryDefault);
};


template <typename ModifierFunc>
Result<void> Accessory::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::Accessory;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_ACCESSORY_HPP */