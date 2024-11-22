#ifndef GS_ACAPI_MEP_PREFERENCE_TABLE_BASE_HPP
#define GS_ACAPI_MEP_PREFERENCE_TABLE_BASE_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {


inline namespace v1 {

/** @brief The PreferenceTableBase represents a named entity, that contains inner tables associated with cross section shapes and these table contains rows that
	consists of a size and a description. The rows have to be unique by value and are always in ascending order.
	@ingroup MEP
	@since Archicad 27
	@ingroup MEP
	@details For every domain the shapes are as follows:
		Duct - Rectangular and Circular
		Pipe - Circular
		CableCarrier - Rectangular
	This means, that by adding/getting a PreferenceTable, it will already contain one or two inner shape-tables, depending on the domain. These could be empty, but
	you cannot add new shapes to a PreferenceTableBase, nor delete them.
	@par Example code snippet from Test / New MEP
		Take a look at @ref PreferenceTableContainerBase "PreferenceTableContainerBase"
*/
class MEPAPI_EXPORT PreferenceTableBase final : public Object {
	PreferenceTableBase (const UniqueID&);
public:
	class Modifier;
	~PreferenceTableBase ();

	/** @brief Returns a PreferenceTableBase.
		@param uniqueId The UniqueID of the requested PreferenceTableBase.
		@return If the uniqueId belongs to a PreferenceTable, returns the object associated to it, otherwise Error.
	*/
	static Result<PreferenceTableBase> Get (const UniqueID& uniqueId);

	/** @return Checks if the object still exists. */
	bool Exists () const;

	/** @return Returns the name of the table. */
	GS::UniString GetName () const;

	/** @param shape The shape of the table.
		@return Returns error if the shape is not defined for the PreferenceTable, otherwise returns the size of the inner shape-table.
	*/
	Result<uint32_t> GetSize (PreferenceTableShape shape) const;

	/** @param shape The shape of the preference table.
		@param index The index of the row. Index starts from 0.
		@return Returns error if the shape is not defined for the PreferenceTable, otherwise returns the value of a table's row of the inner shape-table.
	*/
	Result<double> GetValue (PreferenceTableShape shape, uint32_t index) const;

	/** @param shape The shape of the preference table.
		@param index The index of the row. Index starts from 0.
		@return Returns error if the shape is not defined for the PreferenceTable, otherwise returns the description of a table's row of the inner shape-table.
	*/
	Result<GS::UniString> GetDescription (PreferenceTableShape shape, uint32_t index) const;

	/** @brief Executes the passed modifier scope in an Undoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@param undoString The text which appears in the undo queue of Archicad after executing the command.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
	*/
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT PreferenceTableBase::Modifier : public ACAPI::ModifierBase {
	PreferenceTableBase& parent;

protected:
	Modifier (PreferenceTableBase&);

	void FinalizeModification () override;

public:
	~Modifier ();

	friend PreferenceTableBase;

	/** @brief Sets the name of the table.
		@param tableName The name to be set.
	*/
	void SetName (const GS::UniString& tableName);

	/** @brief Inserts a new empty line in the table.
		@param shape The shape of the table to insert into.
		@return Returns error if the shape is not defined for the PreferenceTable, otherwise returns the index of the newly inserted row. Do not forget to set a value to it afterwards,
		otherwise it will be automatically deleted at the end of the Modify scope.
	*/
	Result<uint32_t> AddNewPreference (PreferenceTableShape shape);

	/** @brief Deletes a row from the table.
		@param shape The shape of the table to delete from.
		@param index The index of the row. Index starts from 0.
		@return Returns error if the shape is not defined for the PreferenceTable or the index is out of range, otherwise nothing.
	*/
	Result<void> Delete (PreferenceTableShape shape, uint32_t index);

	/** @brief Sets the value of a table's row.
		@param shape The shape of the preference table.
		@param index The index of the row. Index starts from 0.
		@param value The value to be set. Must be a non-zero positive number.
		@return Returns error if the shape is not defined for the PreferenceTable, the index is out of range or if the new value would be a duplicate, otherwise returns the new index of the modified row.
	*/
	Result<uint32_t> SetValue (PreferenceTableShape shape, uint32_t index, double value);

	/** @brief Sets the description of a table's row.
		@param shape The shape of the preference table.
		@param index The index of the row. Index starts from 0.
		@param description The description to be set.
		@return Returns error if the shape is not defined for the PreferenceTable or the index is out of range, otherwise nothing.
	*/
	Result<void> SetDescription (PreferenceTableShape shape, uint32_t index, const GS::UniString& description);
};


template <typename ModifierFunc>
Result<void> PreferenceTableBase::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_PREFERENCE_TABLE_BASE_HPP