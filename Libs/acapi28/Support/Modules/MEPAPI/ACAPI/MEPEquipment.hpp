#ifndef GS_ACAPI_MEP_EQUIPMENT_HPP
#define GS_ACAPI_MEP_EQUIPMENT_HPP

#include "MEPAPIExport.hpp"

#include "MEPModifiableElementBase.hpp"
#include "MEPEquipmentDefault.hpp"


namespace ACAPI::MEP {

namespace v1 {


/**
 * @brief The Equipment is a complex element with more than two ports.
 * @since Archicad 27
 * @ingroup MEP
 */
class MEPAPI_EXPORT Equipment final : public ModifiableElementBase {
	Equipment (const UniqueID&);

public:
	class Modifier;
	~Equipment ();

	/**
	 * @brief Returns an Equipment.
	 * @param uniqueId The UniqueID of the requested Equipment.
	 * @return If the uniqueId belongs to an Equipment, returns the object associated to it, otherwise Error.
	 */
	static Result<Equipment> Get (const UniqueID& uniqueId);

	/**
	 * @brief Picks up the Default from the Equipment.
	 * @return Returns an EquipmentDefault with the parameters of the object it was called for.
	 */
	EquipmentDefault PickUpDefault () const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT Equipment::Modifier : public ModifiableElementBase::Modifier {
	Equipment& parent;

	Modifier (Equipment&);
	virtual ~Modifier ();

public:
	friend Equipment;

	/**
	 * @brief Injects the Default settings into the Equipment.
	 * @param equipmentDefault The Default what will be injected.
	 * @return Returns an error if the injection fails for some reason, otherwise nothing.
	 */
	Result<void> Inject (const EquipmentDefault& equipmentDefault);
};


template <typename ModifierFunc>
Result<void> Equipment::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::Equipment;

} // ACAPI::MEP


#endif /* GS_ACAPI_MEP_EQUIPMENT_HPP */