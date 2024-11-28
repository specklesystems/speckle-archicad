#ifndef GS_ACAPI_MEP_PIPE_ELBOW_PREFERENCE_TABLE_HPP
#define GS_ACAPI_MEP_PIPE_ELBOW_PREFERENCE_TABLE_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {


namespace v1 {

/**
 * @brief The PipeElbowPreferenceTable contains cross section related information for Pipe elbows.
 * @ingroup MEP
 * @since Archicad 28
 * @details The table uses the keys defined by the @ref PipeReferenceSet.
 * 			To consider a table row usable and valid, it should have all its fields filled, beside its description, which is optional.
 * @par Example code snippet from Test / New MEP
 * 		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
 */
class MEPAPI_EXPORT PipeElbowPreferenceTable final : public Object {
	PipeElbowPreferenceTable (const UniqueID&);

public:
	class Modifier;
	~PipeElbowPreferenceTable ();

	/**
	 * @brief Returns a PipeElbowPreferenceTable.
	 * @param uniqueId The UniqueID of the requested PipeElbowPreferenceTable.
	 * @return If the uniqueId belongs to a PipeElbowPreferenceTable, returns the object associated to it, otherwise Error.
	 */
	static Result<PipeElbowPreferenceTable> Get (const UniqueID& uniqueId);

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
	 * @return Returns error if the index is out of range, otherwise returns the referenceId of the table's row.
	 */
	Result<uint32_t> GetReferenceId (uint32_t index) const;

	/**
	 * @brief A row is considered valid if its diameter and radius contains non-zero values, description is optional.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValid (uint32_t index) const;

	/**
	 * @brief A row is considered valid if its diameter and radius contains non-zero values, description is optional.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the referenceId is not in the PipeReferenceSet, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValidByReferenceId (uint32_t referenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the diameter value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetDiameter (uint32_t index) const;

	/**
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the referenceId is not in the table, otherwise returns the diameter value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetDiameterByReferenceId (uint32_t referenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the radius value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetRadius (uint32_t index) const;

	/**
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the referenceId is not in the table, otherwise returns the radius value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetRadiusByReferenceId (uint32_t referenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescription (uint32_t index) const;

	/**
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the referenceId is not in the table, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescriptionByReferenceId (uint32_t referenceId) const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT PipeElbowPreferenceTable::Modifier : public ACAPI::ModifierBase {
	PipeElbowPreferenceTable& parent;

protected:
	/**
	 * @brief Constructs a Modifier with the given PipeElbowPreferenceTable.
	 * @param parent The given PipeElbowPreferenceTable.
	 */
	Modifier (PipeElbowPreferenceTable& parent);

public:
	~Modifier ();

	friend PipeElbowPreferenceTable;

	/**
	 * @brief Sets the name of the table.
	 * @param tableName The name to be set.
	 */
	void SetName (const GS::UniString& tableName);

	/**
	 * @brief Empties a row from the table.
	 * @param index The index of the row. Index starts from 0.
	 * @details The row itself will not be deleted, only becomes invalid.
	 * @return Returns error if the index is out of range or this is the last valid row of the table, otherwise nothing.
	 */
	Result<void> EmptyRow (uint32_t index);

	/**
	 * @brief Empties a row from the table.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @details The row itself will not be deleted, only becomes invalid.
	 * @return Returns error if the referenceId is not in the table or this is the last valid row of the table, otherwise nothing.
	 */
	Result<void> EmptyRowByReferenceId (uint32_t referenceId);

	/**
	 * @brief Sets the diameter value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDiameter (uint32_t index, double diameter);

	/**
	 * @brief Sets the diameter value of a table's row.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @details If there isn't any row with the given referenceId, but the referenceId is defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns error if the referenceId is not in the PipeReferenceSet, otherwise nothing.
	 */
	Result<void> SetDiameterByReferenceId (uint32_t referenceId, double diameter);

	/**
	 * @brief Sets the radius value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param radius The value to be set. Must be a non-zero positive number. Radius must be greater or equal than 0.6 * diameter.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetRadius (uint32_t index, double radius);

	/**
	 * @brief Sets the radius value of a table's row.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param radius The value to be set. Must be a non-zero positive number. Radius must be greater or equal than 0.6 * diameter.
	 * @details If there isn't any row with the given referenceId, but the referenceId is defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns error if the referenceId is not in the PipeReferenceSet, otherwise nothing.
	 */
	Result<void> SetRadiusByReferenceId (uint32_t referenceId, double radius);

	/**
	 * @brief Sets the description of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param description The description to be set.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDescription (uint32_t index, const GS::UniString& description);

	/**
	 * @brief Sets the description of a table's row.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param description The description to be set.
	 * @details If there isn't any row with the given referenceId, but the referenceId is defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns error if the referenceId is not in the PipeReferenceSet, otherwise nothing.
	 */
	Result<void> SetDescriptionByReferenceId (uint32_t referenceId, const GS::UniString& description);
};


template <typename ModifierFunc>
Result<void> PipeElbowPreferenceTable::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Result<void> editableResult = IsEditable ();
	if (editableResult.IsErr ())
		return editableResult;

	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1


using v1::PipeElbowPreferenceTable;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_PIPE_ELBOW_PREFERENCE_TABLE_HPP