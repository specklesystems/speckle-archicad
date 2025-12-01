#ifndef GS_ACAPI_MEP_DUCT_CIRCULAR_SEGMENT_PREFERENCE_TABLE_HPP
#define GS_ACAPI_MEP_DUCT_CIRCULAR_SEGMENT_PREFERENCE_TABLE_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"


namespace ACAPI::MEP {


/**
 * @brief The DuctCircularSegmentPreferenceTable contains cross section related information for Circular Duct routing segments.
 * @ingroup MEP
 * @since Archicad 28
 * @details The table uses the keys defined by the @ref DuctReferenceSet.
 * 			To consider a table row usable and valid, it should have all its fields filled, beside its description, which is optional.
 * @par Example code snippet from Test / New MEP
 *   	Getters @snippet Preferences.cpp DuctSegmentPreferenceTable-Getters-Example
 *   	Modification @snippet Preferences.cpp DuctSegmentPreferenceTable-Modification-Example
 */
class MEPAPI_EXPORT DuctCircularSegmentPreferenceTable final : public Object {
	DuctCircularSegmentPreferenceTable (const UniqueID&);
public:
	class Modifier;
	~DuctCircularSegmentPreferenceTable ();

	/**
	 * @brief Returns a DuctCircularSegmentPreferenceTable.
	 * @param uniqueId The UniqueID of the requested DuctCircularSegmentPreferenceTable.
	 * @return If the uniqueId belongs to a DuctSegmentPreferenceTable, returns the object associated to it, otherwise Error.
	 */
	static Result<DuctCircularSegmentPreferenceTable> Get (const UniqueID& uniqueId);

	/** @return Checks if the object still exists. */
	bool Exists () const;

	/**
	 * @brief Checks whether the table is editable.
	 * @return Returns nothing if the table is editable, otherwise the error code and error message containing information about the reason.
	 */
	Result<void> IsEditable () const;

	/** @return Returns the name of the table. */
	GS::UniString GetName () const;

	/** @return Returns the size of the table. */
	uint32_t GetSize () const;

	/**
	 * @brief A row is considered valid if its diameter and wallThickness contain non-zero values, description is optional.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValid (uint32_t index) const;

	/**
	 * @brief A row is considered valid if its diameter and wallThickness contain non-zero values, description is optional.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet.
	 * @return Returns error if the referenceId is not in the DuctReferenceSet, otherwise returns the validity state of the row.
	 */
	Result<bool> IsRowValidByKey (uint32_t referenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the referenceId of the table's row.
	 */
	Result<uint32_t> GetReferenceId (uint32_t index) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the diameter value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetDiameter (uint32_t index) const;

	/**
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet.
	 * @return Returns error if the referenceId is not in the table, otherwise returns the diameter value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetDiameterByKey (uint32_t referenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the wall thickness value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetWallThickness (uint32_t index) const;

	/**
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet.
	 * @return Returns error if the referenceId is not in the table, otherwise returns the wall thickness value of the table's row.
	 * 		   If the returned value is 0.0, the row is not valid yet.
	 */
	Result<double> GetWallThicknessByKey (uint32_t referenceId) const;

	/**
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescription (uint32_t index) const;

	/**
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet.
	 * @return Returns error if the referenceId is not in the table, otherwise returns the description of the table's row.
	 */
	Result<GS::UniString> GetDescriptionByKey (uint32_t referenceId) const;

	/**
	 * @brief Returns whether the rigid segment segmentation is turned on.
	 * If this is false, there will be only one rigid segment for each routing segment, and the minimum and maximum segmentation lengths are ignored when generating routings.
	 * @return Returns true if the rigid segment segmentation is turned on, and false if it's turned off.
	 */
	bool GetUseIndividualSegmentLengths () const;

	/**
	 * @return Returns the minimum segmentation length of the rigid segment.
	 * If the segmentation is turned off, the value is ignored when generating routings,
	 * and the rigid segment will be the same length as the routing segment.
	 */
	double GetMinimumSegmentationLength () const;

	/**
	 * @return Returns the maximum segmentation length of the rigid segment.
	 * If the segmentation is turned off, the value is ignored when generating routings, 
	 * and the rigid segment will be the same length as the routing segment.
	 */
	double GetMaximumSegmentationLength () const;

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
 * @brief Modifier of the DuctCircularSegmentPreferenceTable.
 * @ingroup MEP
 */
class MEPAPI_EXPORT DuctCircularSegmentPreferenceTable::Modifier : public ACAPI::ModifierBase {
	DuctCircularSegmentPreferenceTable& parent;

	friend DuctCircularSegmentPreferenceTable;
protected:
	/**
	 * @brief Constructs a Modifier with the given DuctCircularSegmentPreferenceTable.
	 * @param parent The given DuctCircularSegmentPreferenceTable.
	 */
	Modifier (DuctCircularSegmentPreferenceTable& parent);

public:
	~Modifier ();

	/**
	 * @brief Sets the name of the table.
	 * @param tableName The name to be set.
	 */
	void SetName (const GS::UniString& tableName);

	/**
	 * @brief Empties a row from the table.
	 * @param index The index of the row. Index starts from 0.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> EmptyRow (uint32_t index);

	/**
	 * @brief Empties a row from the table.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet.
	 * @return Returns error if the referenceId is not in the table, otherwise nothing.
	 */
	Result<void> EmptyRowByKey (uint32_t referenceId);

	/**
	 * @brief Sets the diameter value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param value The value to be set. Must be a non-zero positive number.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDiameter (uint32_t index, double value);

	/**
	 * @brief Sets the diameter value of a table's row. 
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet.
	 * @param value The value to be set. Must be a non-zero positive number.
	 * @details If there isn't any row with the given referenceId, but the referenceId is defined in the DuctReferenceSet, it will insert the row. 
	 * @return Returns error if the referenceId is not in the DuctReferenceSet, otherwise nothing.
	 */
	Result<void> SetDiameterByKey (uint32_t referenceId, double value);

	/**
	 * @brief Sets the wall thickness value of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param value The value to be set. Must be a non-zero positive number.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetWallThickness (uint32_t index, double value);

	/**
	 * @brief Sets the wall thickness value of a table's row.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet.
	 * @param value The value to be set. Must be a non-zero positive number.
	 * @details If there isn't any row with the given referenceId, but the referenceId is defined in the DuctReferenceSet, it will insert the row.
	 * @return Returns error if the referenceId is not in the DuctReferenceSet, otherwise nothing.
	 */
	Result<void> SetWallThicknessByKey (uint32_t referenceId, double value);

	/**
	 * @brief Sets the description of a table's row.
	 * @param index The index of the row. Index starts from 0.
	 * @param description The description to be set.
	 * @return Returns error if the index is out of range, otherwise nothing.
	 */
	Result<void> SetDescription (uint32_t index, const GS::UniString& description);

	/**
	 * @brief Sets the description of a table's row.
	 * @param referenceId The referenceId of the row. The table only contains the referenceIds that are defined in the DuctReferenceSet.
	 * @param description The description to be set.
	 * @details If there isn't any row with the given referenceId, but the referenceId is defined in the DuctReferenceSet, it will insert the row.
	 * @return Returns error if the referenceId is not in the DuctReferenceSet, otherwise nothing.
	 */
	Result<void> SetDescriptionByKey (uint32_t referenceId, const GS::UniString& description);

	/**
	 * @brief Sets the use of individual segment lengths. If this is false, there will be only one rigid segment for each routing segment, 
	 * and the minimum and maximum segmentation lengths are ignored when generating routings.
	 * @param value The value to be set.
	 */
	void SetUseIndividualSegmentLengths (bool value);

	/**
	 * @brief Sets the segmentation lengths of the rigid segment. If the segmentation is turned off, 
	 * the value is ignored when generating routings, and the rigid segment will be the same length as the routing segment.
	 * @param minimum The minimum segmentation length of the rigid segment.
	 * @param maximum The maximum segmentation length of the rigid segment.
	 * @return Returns error if any of the parameters are negative, or if the condition minimum * 2 <= maximum is false, otherwise nothing.
	 */
	Result<void> SetSegmentationLengths (double minimum, double maximum);
};


template <typename ModifierFunc>
Result<void> DuctCircularSegmentPreferenceTable::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Result<void> editableResult = IsEditable ();
	if (editableResult.IsErr ())
		return editableResult;

	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_DUCT_CIRCULAR_SEGMENT_PREFERENCE_TABLE_HPP