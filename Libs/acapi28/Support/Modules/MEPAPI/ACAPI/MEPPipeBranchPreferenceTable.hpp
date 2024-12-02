#ifndef GS_ACAPI_MEP_PIPE_BRANCH_PREFERENCE_TABLE_HPP
#define GS_ACAPI_MEP_PIPE_BRANCH_PREFERENCE_TABLE_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {


namespace v1 {

/**
* @brief The PipeBranchPreferenceTable contains cross section and geometry related information for Pipe branches.
* @ingroup MEP
* @since Archicad 28
* @details The table uses the keys defined by the @ref PipeReferenceSet.
*		To consider a table row usable and valid, it should have all its fields filled, beside its description, which is optional.
* @par Example code snippet from Test / New MEP
*      Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT PipeBranchPreferenceTable final : public Object {
	PipeBranchPreferenceTable (const UniqueID&);

public:
	class Modifier;
	~PipeBranchPreferenceTable ();

	/**
	 * @brief Returns a PipeBranchPreferenceTable.
	 * @param uniqueId The UniqueID of the requested PipeBranchPreferenceTable.
	 * @return If the uniqueId belongs to a PipeBranchPreferenceTable, returns the object associated to it, otherwise Error.
	 */
	static Result<PipeBranchPreferenceTable> Get (const UniqueID& uniqueId);

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
	* @return Returns error if the index is out of range, otherwise returns the main axis referenceId of the table's row.
	*/
	Result<uint32_t> GetMainAxisReferenceId (uint32_t index) const;

	/**
	* @param index The index of the row. Index starts from 0.
	* @return Returns error if the index is out of range, otherwise returns the branch axis referenceId of the table's row.
	*/
	Result<uint32_t> GetBranchAxisReferenceId (uint32_t index) const;

	/**
	 * @brief A row is considered valid if both diameters, the length, the branchOffset and the connectionLength contains non-zero values, description is optional.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValid (uint32_t index) const;

	/**
	 * @brief A row is considered valid if both diameters, the length, the branchOffset and the connectionLength contains non-zero values, description is optional.
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValidByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the main axis diameter value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetMainAxisDiameter (uint32_t index) const;

	/**
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the main axis diameter value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetMainAxisDiameterByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the branch axis diameter value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetBranchAxisDiameter (uint32_t index) const;

	/**
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the branch axis diameter value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetBranchAxisDiameterByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the length value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetLength (uint32_t index) const;

	/**
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the length value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetLengthByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the branch offset value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetBranchOffset (uint32_t index) const;

	/**
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the branch offset value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetBranchOffsetByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the connection length value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetConnectionLength (uint32_t index) const;

	/**
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the connection length value of the table's row.
	 * If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetConnectionLengthByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescription (uint32_t index) const;

	/**
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescriptionByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId) const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT PipeBranchPreferenceTable::Modifier : public ACAPI::ModifierBase {
	PipeBranchPreferenceTable& parent;

protected:
	/**
	 * @brief Constructs a Modifier with the given PipeBranchPreferenceTable.
	 * @param parent The given PipeBranchPreferenceTable.
	 */
	Modifier (PipeBranchPreferenceTable& parent);

public:
	~Modifier ();

	friend PipeBranchPreferenceTable;

	/**
	* @brief Sets the name of the table.
	* @param tableName The name to be set.
	*/
	void SetName (const GS::UniString& tableName);

	/**
	 * @brief Inserts a new row into the table.
	 * @param mainAxisReferenceId The main axis referenceId of the new row. It must be a referenceId that is defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the new row. It must be a referenceId that is defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds is already present in the table or if the branch axis referenceId is larger than the main axis referenceId, otherwise the index of the new row.
	 */
	Result<uint32_t> AddNewRow (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId);

	/**
	 * @brief Deletes a row from the table.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> DeleteRow (uint32_t index);

	/**
	 * @brief Deletes a row from the table.
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @return Returns error if the pair of referenceIds does not occur in the table, otherwise nothing.
	 */
	Result<void> DeleteRowByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId);

	/**
	 * @brief Sets the main axis diameter value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @return Returns error if the index is out of range or if the value is smaller than the branch axis diameter, otherwise nothing.
	 */
	Result<void> SetMainAxisDiameter (uint32_t index, double diameter);

	/**
	 * @brief Sets the main axis diameter value of a table's row.
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @details If there isn't any row with the given pair of referenceIds, but both the referenceIds are defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns error if at least one referenceId is not in the PipeReferenceSet, or if the value is smaller than the branch axis diameter, otherwise nothing.
	 */
	Result<void> SetMainAxisDiameterByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId, double diameter);

	/**
	 * @brief Sets the branch axis diameter value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if the index is out of range;
	 *			- if the value is larger than the already defined main axis diameter;
	 *			- if the value is larger or equal than the already defined length;
	 *			- if branch offset is already defined and the value is larger than 2 * branchOffset;
	 *			- if branch offset and length are already defined and the value is larger than 2 * (length - branchOffset).
	 */
	Result<void> SetBranchAxisDiameter (uint32_t index, double diameter);

	/**
	 * @brief Sets the branch axis diameter value of a table's row.
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @details If there isn't any row with the given pair of referenceIds, but both the referenceIds are defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if at least one referenceId is not in the PipeReferenceSet;
	 *			- if the value is larger than the already defined main axis diameter;
	 *			- if the value is larger or equal than the already defined length;
	 *			- if branch offset is already defined and the value is larger than 2 * branchOffset;
	 *			- if branch offset and length are already defined and the value is larger than 2 * (length - branchOffset).
	 */
	Result<void> SetBranchAxisDiameterByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId, double diameter);

	/**
	 * @brief Sets the length value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param length The value to be set. Must be a non-zero positive number.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if the index is out of range;
	 *			- if the value is smaller than the branch axis diameter;
	 *			- if the value is smaller than (branchOffset + branchAxisDiameter / 2).
	 */
	Result<void> SetLength (uint32_t index, double length);

	/**
	 * @brief Sets the diameter value of a table's row.
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param length The value to be set. Must be a non-zero positive number.
	 * @details If there isn't any row with the given pair of referenceIds, but both the referenceIds are defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if at least one referenceId is not in the PipeReferenceSet;
	 *			- if the value is smaller than the branch axis diameter;
	 *			- if the value is smaller than (branchOffset + branchAxisDiameter / 2).
	 */
	Result<void> SetLengthByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId, double length);

	/**
	 * @brief Sets the branch offset value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param branchOffset The value to be set. Must be a non-zero positive number.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if the index is out of range;
	 *			- if the value is smaller than (branchAxisDiameter / 2);
	 *			- if length and branch axis diameter are already defined and the value is larger than the (length - branchAxisDiameter / 2).
	 */
	Result<void> SetBranchOffset (uint32_t index, double branchOffset);

	/**
	 * @brief Sets the branch offset value of a table's row.
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchOffset The value to be set. Must be a non-zero positive number.
	 * @details If there isn't any row with the given pair of referenceIds, but both the referenceIds are defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns nothing if the operation was successful, or returns error:
	 *			- if at least one referenceId is not in the PipeReferenceSet;
	 *			- if the value is smaller than (branchAxisDiameter / 2);
	 *			- if length and branch axis diameter are already defined and the value is larger than the (length - branchAxisDiameter / 2).
	 */
	Result<void> SetBranchOffsetByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId, double branchOffset);

	/**
	 * @brief Sets the connection length value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param connectionLength The value to be set. Must be a non-zero positive number.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetConnectionLength (uint32_t index, double connectionLength);

	/**
	 * @brief Sets the connection length value of a table's row.
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param connectionLength The value to be set. Must be a non-zero positive number.
	 * @details If there isn't any row with the given pair of referenceIds, but both the referenceIds are defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns error if at least one referenceId is not in the PipeReferenceSet, otherwise nothing.
	 */
	Result<void> SetConnectionLengthByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId, double connectionLength);

	/**
	 * @brief Sets the description of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param description The description to be set.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDescription (uint32_t index, const GS::UniString& description);

	/**
	 * @brief Sets the description of a table's row.
	 * @param mainAxisReferenceId The main axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param branchAxisReferenceId The branch axis referenceId of the row. The table only contains the referenceIds that are defined in the PipeReferenceSet.
	 * @param description The description to be set.
	 * @details If there isn't any row with the given pair of referenceIds, but both the referenceIds are defined in the PipeReferenceSet, it will insert the row.
	 * @return Returns error if at least one referenceId is not in the PipeReferenceSet, otherwise nothing.
	 */
	Result<void> SetDescriptionByReferenceIds (uint32_t mainAxisReferenceId, uint32_t branchAxisReferenceId, const GS::UniString& description);
};


template <typename ModifierFunc>
Result<void> PipeBranchPreferenceTable::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Result<void> editableResult = IsEditable ();
	if (editableResult.IsErr ())
		return editableResult;

	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

using v1::PipeBranchPreferenceTable;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_PIPE_BRANCH_PREFERENCE_TABLE_HPP