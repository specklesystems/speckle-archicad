#ifndef GS_ACAPI_MEP_CABLECARRIER_SEGMENT_PREFERENCE_TABLE_HPP
#define GS_ACAPI_MEP_CABLECARRIER_SEGMENT_PREFERENCE_TABLE_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {


namespace v1 {

/**
 * @brief The CableCarrierSegmentPreferenceTable represents a named entity, that contains rows that consists of a size and a description.
 * 		  The rows have to be unique by value and are always in ascending order.
 * @ingroup MEP
 * @since Archicad 28
 * @ingroup MEP
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
 */
class MEPAPI_EXPORT CableCarrierSegmentPreferenceTable final : public Object {
	CableCarrierSegmentPreferenceTable (const UniqueID&);
public:
	class Modifier;
	~CableCarrierSegmentPreferenceTable ();

	/**
	 * @brief Returns a CableCarrierSegmentPreferenceTable.
	 * @param uniqueId The UniqueID of the requested CableCarrierSegmentPreferenceTable.
	 * @return If the uniqueId belongs to a CableCarrierSegmentPreferenceTable, returns the object associated to it, otherwise Error.
	 */
	static Result<CableCarrierSegmentPreferenceTable> Get (const UniqueID& uniqueId);

	/** @return Checks if the object still exists. */
	bool Exists () const;

	/**
	 * @brief Checks whether the table is editable.
	 * @return Returns nothing if the table is editable, otherwise the error code and error message containing information about the reason.
	 */
	Result<void> IsEditable () const;

	/** @return Returns the name of the table. */
	GS::UniString GetName () const;

	/**
	 * @return Returns the size of the table.
	 */
	uint32_t GetSize () const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is not defined for the CableCarrierSegmentPreferenceTable, otherwise returns the value of a table's row.
	 */
	Result<double> GetValue (uint32_t index) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is not defined for the CableCarrierSegmentPreferenceTable, otherwise returns the description of a table's row.
	 */
	Result<GS::UniString> GetDescription (uint32_t index) const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT CableCarrierSegmentPreferenceTable::Modifier : public ACAPI::ModifierBase {
	CableCarrierSegmentPreferenceTable& parent;

protected:
	/**
	 * @brief Constructs a Modifier with the CableCarrierSegmentPreferenceTable.
	 * @param parent The given CableCarrierSegmentPreferenceTable.
	 */
	Modifier (CableCarrierSegmentPreferenceTable& parent);

	/**
	 * @brief Finalizes the modifications.
	 */
	void FinalizeModification () override;

public:
	~Modifier ();

	friend CableCarrierSegmentPreferenceTable;

	/**
	 * @brief Sets the name of the table.
	 * @param tableName The name to be set.
	 */
	void SetName (const GS::UniString& tableName);

	/**
	 * @brief Inserts a new empty line in the table.
	 * @return Returns error if there is already an unset row in the CableCarrierSegmentPreferenceTable, otherwise returns the index of the newly inserted row. Do not forget to set a value to it afterwards,
	 * 		   otherwise it will be automatically deleted at the end of the Modify scope.
	 */
	Result<uint32_t> AddNewPreference ();

	/**
	 * @brief Deletes a row from the table.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> Delete (uint32_t index);

	/**
	 * @brief Sets the value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param value The value to be set. Must be a non-zero positive number.
	 * @return Returns error if the index is out of range or if the new value would be a duplicate, otherwise returns the new index of the modified row.
	 */
	Result<uint32_t> SetValue (uint32_t index, double value);

	/**
	 * @brief Sets the description of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param description The description to be set.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDescription (uint32_t index, const GS::UniString& description);
};


template <typename ModifierFunc>
Result<void> CableCarrierSegmentPreferenceTable::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Result<void> editableResult = IsEditable ();
	if (editableResult.IsErr ())
		return editableResult;

	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1


using v1::CableCarrierSegmentPreferenceTable;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_CABLECARRIER_SEGMENT_PREFERENCE_TABLE_HPP