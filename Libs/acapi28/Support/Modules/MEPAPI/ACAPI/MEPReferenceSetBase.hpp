#ifndef GS_ACAPI_MEP_REFERENCE_SET_HPP
#define GS_ACAPI_MEP_REFERENCE_SET_HPP


#include "MEPAPIExport.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {

namespace Impl { class IReferenceSetBaseImpl; }

namespace v1 {


/**
 * @brief The ReferenceSetBase represents a named table, and it contains referenceIds which are used as keys in the PreferenceTables. By default, Archicad will provide you the DN referenceSet,
 * 		  but you can choose your own by renaming it and populate it with your desired values.
 * @since Archicad 28
 * @ingroup MEP
 * @details The entries of the set have to be unique and are always in ascending order. Entries that are defined in PreferenceTables cannot be deleted.
 * @par Example code snippet from Test / New MEP
 * 		Getters @snippet Preferences.cpp ReferenceSet-Getters-Example
 * 		Modification @snippet Preferences.cpp ReferenceSet-Modification-Example
 */
class MEPAPI_EXPORT ReferenceSetBase : public Object {
	protected:
	/**
	 * @brief Constructs a ReferenceSetBase with the given base implementation.
	 * @param impl The given base implementation.
	 */
	ReferenceSetBase (std::shared_ptr<Impl::IReferenceSetBaseImpl> impl);
	~ReferenceSetBase ();

public:
	class Modifier;

	/** @return Checks if the object still exists. */
	bool Exists () const;

	/** @return Checks if the object currently is editable. */
	Result<void> IsEditable () const;

	/** @return Returns the name of the referenceSet. */
	GS::UniString GetName () const;

	/** @return Returns the size of the referenceSet. */
	uint32_t GetSize () const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns the referenceId of the row identified by index.
	 */
	Result<uint32_t> GetReferenceId (uint32_t index) const;

	/**
	 * @brief Checks whether an entry from the referenceSet is defined. A referenceId is defined if at least one preferenceTable has values associated to it.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns whether the row identified by index is defined.
	 */
	Result<bool> IsReferenceIdDefined (uint32_t index) const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT ReferenceSetBase::Modifier : public ACAPI::ModifierBase {
	ReferenceSetBase& parent;
protected:
	/**
	 * @brief Constructs a Modifier with the given referenceSetBase.
	 * @param parent The given parent ReferenceSetBase.
	 */
	Modifier (ReferenceSetBase& parent);

public:
	~Modifier ();

	friend ReferenceSetBase;

	/**
	 * @brief Sets the name of the referenceSet.
	 * @param referenceSetName The name to be set.
	 */
	void SetName (const GS::UniString& referenceSetName);

	/**
	 * @brief Adds a new referenceId into the referenceSet. If the id is a duplicate, it will not be inserted twice.
	 * @param id The id to be added.
	 * @return Returns error if the referenceId is a duplicate, otherwise returns the index of the referenceId in the referenceSet.
	 */
	Result<uint32_t> Add (uint32_t id);

	/**
	 * @brief Deletes an entry from the referenceSet. Only undefined referenceIds can be deleted. A referenceId is defined if at least one preferenceTable has
	 * 		  values associated to it.
	 * @param id The id to be deleted.
	 * @return Returns error if the id cannot be deleted due to reasons mentioned above, otherwise nothing.
	 */
	Result<void> Delete (uint32_t id);
};


template <typename ModifierFunc>
Result<void> ReferenceSetBase::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Result<void> editableResult = IsEditable ();
	if (editableResult.IsErr ())
		return editableResult;

	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::ReferenceSetBase;

} // ACAPI::MEP


#endif // GS_ACAPI_MEP_REFERENCE_SET_HPP