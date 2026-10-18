#ifndef GS_ACAPI_MEP_ANGLE_SET_HPP
#define GS_ACAPI_MEP_ANGLE_SET_HPP


#include "MEPAPIExport.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {

namespace Impl { class IAngleSetBaseImpl; }


/**
 * @brief The AngleSetBase represents a named table, and it contains angles which are used as keys in the PreferenceTables. By default, Archicad will provide you the Angle angleSet,
 * 		  but you can choose your own by renaming it and populate it with your desired values.
 * @since Archicad 29
 * @ingroup MEP
 * @details The entries of the set have to be unique and are always in ascending order. Entries that are defined in PreferenceTables cannot be deleted.
 * @par Example code snippet from Test / New MEP
 * 		Getters @snippet Preferences.cpp AngleSet-Getters-Example
 * 		Modification @snippet Preferences.cpp AngleSet-Modification-Example
 */
class MEPAPI_EXPORT AngleSetBase : public Object {
	protected:
	/**
	 * @brief Constructs a AngleSetBase with the given base implementation.
	 * @param impl The given base implementation.
	 */
	AngleSetBase (std::shared_ptr<Impl::IAngleSetBaseImpl> impl);
	~AngleSetBase ();

public:
	class Modifier;

	/** @return Checks if the object still exists. */
	bool Exists () const;

	/**
	 * @brief Checks whether the table is editable.
	 * @return Returns nothing if the table is editable, otherwise the error code and error message containing information about the reason.
	 */
	Result<void> IsEditable () const;

	/** @return Returns the name of the angleSet. */
	GS::UniString GetName () const;

	/** @return Returns the size of the angleSet. */
	uint32_t GetSize () const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns the angle of the row identified by index.
	 */
	Result<double> GetAngle (uint32_t index) const;

	/**
	 * @brief Checks whether an entry from the angleSet is defined. A angle is defined if at least one preferenceTable has values associated to it.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns whether the row identified by index is defined.
	 */
	Result<bool> IsAngleDefined (uint32_t index) const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


/**
 * @brief Modifier of the AngleSetBase.
 * @ingroup MEP
 */
class MEPAPI_EXPORT AngleSetBase::Modifier : public ACAPI::ModifierBase {
	AngleSetBase& parent;

	friend AngleSetBase;
protected:
	/**
	 * @brief Constructs a Modifier with the given angleSetBase.
	 * @param parent The given parent AngleSetBase.
	 */
	Modifier (AngleSetBase& parent);

public:
	~Modifier ();

	/**
	 * @brief Sets the name of the angleSet.
	 * @param angleSetName The name to be set.
	 */
	void SetName (const GS::UniString& angleSetName);

	/**
	 * @brief Adds a new angle into the angleSet. If the id is a duplicate, it will not be inserted twice.
	 * @param angle The angle to be added.
	 * @return Returns error if the angle is a duplicate, otherwise returns the index of the angle in the angleSet.
	 */
	Result<uint32_t> Add (double angle);

	/**
	 * @brief Deletes an entry from the angleSet. Only undefined angles can be deleted. A angle is defined if at least one preferenceTable has
	 * 		  values associated to it.
	 * @param angle The angle to be deleted.
	 * @return Returns error if the id cannot be deleted due to reasons mentioned above, otherwise nothing.
	 */
	Result<void> Delete (double angle);
};


template <typename ModifierFunc>
Result<void> AngleSetBase::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Result<void> editableResult = IsEditable ();
	if (editableResult.IsErr ())
		return editableResult;

	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // ACAPI::MEP


#endif // GS_ACAPI_MEP_ANGLE_SET_HPP