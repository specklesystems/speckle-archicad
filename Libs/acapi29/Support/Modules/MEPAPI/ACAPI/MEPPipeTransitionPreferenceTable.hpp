#ifndef GS_ACAPI_MEP_PIPE_TRANSITION_PREFERENCE_TABLE_HPP
#define GS_ACAPI_MEP_PIPE_TRANSITION_PREFERENCE_TABLE_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {


/**
* @brief The PipeTransitionPreferenceTable contains cross section and geometry related information for Pipe transitions.
* @ingroup MEP
* @since Archicad 29
* @details The table uses the keys defined by the @ref PipeReferenceSet.
*		To consider a table row usable and valid, it should have all its fields filled, beside its description, which is optional.
* @par Example code snippet from Test / New MEP
*      Getters @snippet Preferences.cpp PipeTransitionPreferenceTable-Getters-Example
*      Modification: take a look at @ref PipeTransitionPreferenceTable "PipeTransitionPreferenceTable"
*/
class MEPAPI_EXPORT PipeTransitionPreferenceTable final : public Object {
	PipeTransitionPreferenceTable (const UniqueID&);

public:
	class Modifier;

	/**
	 * @brief The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @ingroup MEP
	 * @since Archicad 29
	 */
	struct Key
	{
		/** @brief The begin referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet. */
		uint32_t beginReferenceId;

		/** @brief The end referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet. */
		uint32_t endReferenceId;
	};

	~PipeTransitionPreferenceTable ();

	/**
	 * @brief Returns a PipeTransitionPreferenceTable.
	 * @param uniqueId The UniqueID of the requested PipeTransitionPreferenceTable.
	 * @return If the uniqueId belongs to a PipeTransitionPreferenceTable, returns the object associated to it, otherwise Error.
	 */
	static Result<PipeTransitionPreferenceTable> Get (const UniqueID& uniqueId);

	/** @return Checks if the object still exists. */
	bool Exists () const;

	/**
	 * @brief Checks whether the table is editable.
	 * @return Returns nothing if the table is editable, otherwise the error code and error message containing information about the reason.
	 */
	Result<void> IsEditable () const;

	/** @return Returns the name of the table. */
	GS::UniString GetName () const;

	/** @return Returns the size of table. */
	uint32_t GetSize () const;

	/**
	* @param index The index of the row. Index starts from 0.
	* @return Returns error if the index is out of range, otherwise returns the begin referenceId of the table's row.
	*/
	Result<uint32_t> GetBeginReferenceId (uint32_t index) const;

	/**
	* @param index The index of the row. Index starts from 0.
	* @return Returns error if the index is out of range, otherwise returns the end referenceId of the table's row.
	*/
	Result<uint32_t> GetEndReferenceId (uint32_t index) const;

	/**
	 * @brief A row is considered valid if both diameters and the transition length contains non-zero values, description is optional.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValid (uint32_t index) const;

	/**
	 * @brief A row is considered valid if both diameters and the transition length contains non-zero values, description is optional.
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValidByKey (const Key& key) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the begin diameter value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetBeginDiameter (uint32_t index) const;

	/**
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the begin diameter value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetBeginDiameterByKey (const Key& key) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the end diameter value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetEndDiameter (uint32_t index) const;

	/**
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the end diameter value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetEndDiameterByKey (const Key& key) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the length value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetLength (uint32_t index) const;

	/**
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the length value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetLengthByKey (const Key& key) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescription (uint32_t index) const;

	/**
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescriptionByKey (const Key& key) const;

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
 * @brief Modifier of the PipeTransitionPreferenceTable.
 * @ingroup MEP
 */
class MEPAPI_EXPORT PipeTransitionPreferenceTable::Modifier : public ACAPI::ModifierBase {
	PipeTransitionPreferenceTable& parent;

	friend PipeTransitionPreferenceTable;
protected:
	/**
	 * @brief Constructs a Modifier with the given PipeTransitionPreferenceTable.
	 * @param parent The given PipeTransitionPreferenceTable.
	 */
	Modifier (PipeTransitionPreferenceTable& parent);
public:
	~Modifier ();

	/**
	* @brief Sets the name of the table.
	* @param tableName The name to be set.
	*/
	void SetName (const GS::UniString& tableName);

	/**
	 * @brief Inserts a new row into the table.
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @details If endReferenceId is larger than the beginReferenceId, the two values will be swapped before insertion.
	 * @return Returns error if the pair of referenceIds is already present in the table, otherwise the index of the new row.
	 */
	Result<uint32_t> AddNewRow (const Key& key);

	/**
	 * @brief Deletes a row from the table.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> DeleteRow (uint32_t index);

	/**
	 * @brief Deletes a row from the table.
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise nothing.
	 */
	Result<void> DeleteRowByKey (const Key& key);

	/**
	 * @brief Sets the begin diameter value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if the index is out of range;
	 *			- if the end diameter and length are already defined, and the calculation of the transition angle is not between [1, 89] degrees.
	 */
	Result<void> SetBeginDiameter (uint32_t index, double diameter);

	/**
	 * @brief Sets the begin diameter value of a table's row.
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @details If no row exists for the given key, but the key contains valid referenceIds, it inserts the row.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if at least one referenceId from the key is not in the PipeReferenceSet;
	 *			- if the end diameter and length are already defined, and the calculation of the transition angle is not between [1, 89] degrees.
	 */
	Result<void> SetBeginDiameterByKey (const Key& key, double diameter);

	/**
	 * @brief Sets the end diameter value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if the index is out of range;
	 *			- if the begin diameter and length are already defined, and the calculation of the transition angle is not between [1, 89] degrees.
	 */
	Result<void> SetEndDiameter (uint32_t index, double diameter);

	/**
	 * @brief Sets the end diameter value of a table's row.
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @details If no row exists for the given key, but the key contains valid referenceIds, it inserts the row.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if at least one referenceId from the key is not in the PipeReferenceSet;
	 *			- if the begin diameter and length are already defined, and the calculation of the transition angle is not between [1, 89] degrees.
	 */
	Result<void> SetEndDiameterByKey (const Key& key, double diameter);

	/**
	 * @brief Sets the length value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param length The value to be set. Must be a non-zero positive number.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if the index is out of range;
	 *			- if the begin diameter and end diameter are already defined, and the calculation of the transition angle is not between [1, 89] degrees.
	 */
	Result<void> SetLength (uint32_t index, double length);

	/**
	 * @brief Sets the length value of a table's row.
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @param length The value to be set. Must be a non-zero positive number.
	 * @details If no row exists for the given key, but the key contains valid referenceIds, it inserts the row.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if at least one referenceId from the key is not in the PipeReferenceSet;
	 *			- if the begin diameter and end diameter are already defined, and the calculation of the transition angle is not between [1, 89] degrees.
	 */
	Result<void> SetLengthByKey (const Key& key, double length);

	/**
	 * @brief Sets the description of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param description The description to be set.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDescription (uint32_t index, const GS::UniString& description);

	/**
	 * @brief Sets the description of a table's row.
	 * @param key The key that uniquely identifies a row in the PipeTransitionPreferenceTable.
	 * @param description The description to be set.
	 * @details If no row exists for the given key, but the key contains valid referenceIds, it inserts the row.
	 * @return Returns error if at least one referenceId from the key is not in the PipeReferenceSet, otherwise nothing.
	 */
	Result<void> SetDescriptionByKey (const Key& key, const GS::UniString& description);
};


template <typename ModifierFunc>
Result<void> PipeTransitionPreferenceTable::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Result<void> editableResult = IsEditable ();
	if (editableResult.IsErr ())
		return editableResult;

	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_PIPE_TRANSITION_PREFERENCE_TABLE_HPP