#ifndef GS_ACAPI_MEP_DUCT_ELBOW_PREFERENCE_TABLE_HPP
#define GS_ACAPI_MEP_DUCT_ELBOW_PREFERENCE_TABLE_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {


/**
 * @brief The DuctElbowPreferenceTable contains cross section related information for Duct elbows.
 * @ingroup MEP
 * @since Archicad 28
 * @details The table uses the keys defined by the @ref DuctReferenceSet and @ref DuctAngleSet.
 * 			To consider a table row usable and valid, it should have all its fields filled, beside its description, which is optional.
 * @par Example code snippet from Test / New MEP
 *		Getters @snippet Preferences.cpp DuctElbowPreferenceTable-Getters-Example
 *		Modification: take a look at @ref DuctElbowPreferenceTable "DuctElbowPreferenceTable"
 */
class MEPAPI_EXPORT DuctElbowPreferenceTable final : public Object {
	DuctElbowPreferenceTable (const UniqueID&);

public:
	class Modifier;

	/**
	 * @brief The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @ingroup MEP
	 * @since Archicad 29
	 */
	struct Key
	{
		/** @brief The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet. */
		uint32_t referenceId;

		/** @brief The angle of the row. The table only contains the angles that are defined in the DuctAngleSet. Needs to be between [1, 90] degrees. */
		double angle;
	};

	~DuctElbowPreferenceTable ();

	/**
	 * @brief Returns a DuctElbowPreferenceTable.
	 * @param uniqueId The UniqueID of the requested DuctElbowPreferenceTable.
	 * @return If the uniqueId belongs to a DuctElbowPreferenceTable, returns the object associated to it, otherwise Error.
	 */
	static Result<DuctElbowPreferenceTable> Get (const UniqueID& uniqueId);

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
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the angle of the table's row.
	 */
	Result<double> GetAngle (uint32_t index) const;

	/**
	 * @brief A row is considered valid if its diameter and radius contains non-zero values, description is optional.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValid (uint32_t index) const;

	/**
	 * @brief A row is considered valid if its diameter and radius contains non-zero values, description is optional.
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @return Returns error if the referenceId and angle is not in the DuctReferenceSet and DuctAngleSet, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValidByKey (const Key& key) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the diameter value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetDiameter (uint32_t index) const;

	/**
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @return Returns error if a row for a given key does not occur in the table, otherwise returns the diameter value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetDiameterByKey (const Key& key) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the radius value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetRadius (uint32_t index) const;

	/**
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @return Returns error if a row for a given key does not occur in the table, otherwise returns the radius value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetRadiusByKey (const Key& key) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescription (uint32_t index) const;

	/**
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @return Returns error if a row for a given key does not occur in the table, otherwise returns the description of the table's row.
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
 * @brief Modifier of the DuctElbowPreferenceTable.
 * @ingroup MEP
 */
class MEPAPI_EXPORT DuctElbowPreferenceTable::Modifier : public ACAPI::ModifierBase {
	DuctElbowPreferenceTable& parent;

	friend DuctElbowPreferenceTable;
protected:
	/**
	 * @brief Constructs a Modifier with the given DuctElbowPreferenceTable.
	 * @param parent The given DuctElbowPreferenceTable.
	 */
	Modifier (DuctElbowPreferenceTable& parent);

public:
	~Modifier ();

	/**
	 * @brief Sets the name of the table.
	 * @param tableName The name to be set.
	 */
	void SetName (const GS::UniString& tableName);

	/**
	 * @brief Inserts a new row into the table.
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @return Returns error if the pair of referenceId and angle is already present in the table, otherwise the index of the new row.
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
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @return Returns error if the pair of referenceId  and angle does not occur in the table, otherwise nothing.
	 */
	Result<void> DeleteRowByKey (const Key& key);

	/**
	 * @brief Sets the diameter value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDiameter (uint32_t index, double diameter);

	/**
	 * @brief Sets the diameter value of a table's row.
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @param diameter The value to be set. Must be a non-zero positive number.
	 * @details If no row exists for the given key, but the key contains valid referenceId and angle, it inserts the row.
	 * @return Returns error if the referenceId and angle is not in the DuctReferenceSet and DuctAngleSet, otherwise nothing.
	 */
	Result<void> SetDiameterByKey (const Key& key, double diameter);

	/**
	 * @brief Sets the radius value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param radius The value to be set. Must be a non-zero positive number. Radius must be greater or equal than 0.6 * diameter.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetRadius (uint32_t index, double radius);

	/**
	 * @brief Sets the radius value of a table's row.
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @param radius The value to be set. Must be a non-zero positive number. Radius must be greater or equal than 0.6 * diameter.
	 * @details If no row exists for the given key, but the key contains valid referenceId and angle, it inserts the row.
	 * @return Returns error if the referenceId and angle is not in the DuctReferenceSet and DuctAngleSet, otherwise nothing.
	 */
	Result<void> SetRadiusByKey (const Key& key, double radius);

	/**
	 * @brief Sets the description of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param description The description to be set.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDescription (uint32_t index, const GS::UniString& description);

	/**
	 * @brief Sets the description of a table's row.
	 * @param key The key that uniquely identifies a row in the DuctElbowPreferenceTable.
	 * @param description The description to be set.
	 * @details If no row exists for the given key, but the key contains valid referenceId and angle, it inserts the row.
	 * @return Returns error if the referenceId and angle is not in the DuctReferenceSet and DuctAngleSet, otherwise nothing.
	 */
	Result<void> SetDescriptionByKey (const Key& key, const GS::UniString& description);
};


template <typename ModifierFunc>
Result<void> DuctElbowPreferenceTable::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Result<void> editableResult = IsEditable ();
	if (editableResult.IsErr ())
		return editableResult;

	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_DUCT_ELBOW_PREFERENCE_TABLE_HPP