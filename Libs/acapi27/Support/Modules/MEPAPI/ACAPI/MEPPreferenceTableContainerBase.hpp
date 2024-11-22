#ifndef GS_ACAPI_MEP_PREFERENCE_TABLE_CONTAINER_BASE_HPP
#define GS_ACAPI_MEP_PREFERENCE_TABLE_CONTAINER_BASE_HPP

#include "MEPAPIExport.hpp"

#include "MEPTypes.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"

#include <vector>


namespace ACAPI::MEP {

namespace Impl { class IPreferenceTableContainerBaseImpl; }

inline namespace v1 {

/** @brief The PreferenceTableContainerBase contains PreferenceTables, and you can Add/Get/Delete them.
	@ingroup MEP
	@since Archicad 27
	@ingroup MEP
	@details The containers for the three MEP domains are already initialized and you can get them from DuctPreferenceTableContainer,
	PipePreferenceTableContainer and CableCarrierPreferenceContainer
	@par Example code snippet from Test / New MEP
		Getters @snippet Preferences.cpp PreferenceTableContainer-Getters-Example
		Modification @snippet Preferences.cpp PreferenceTableContainer-Modification-Example
*/
class MEPAPI_EXPORT PreferenceTableContainerBase : public Object {
protected:
	PreferenceTableContainerBase (std::shared_ptr<Impl::IPreferenceTableContainerBaseImpl>);
	~PreferenceTableContainerBase ();

public:
	class Modifier;

	/** @return Checks if the object still exists. */
	bool Exists () const;

	/** @return Returns the UniqueIDs of the PreferenceTables associated with the caller object's domain. */
	std::vector<UniqueID> GetPreferenceTables () const;

	/** @brief Executes the passed modifier scope in an Undoable command.
		@param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
		@param undoString The text which appears in the undo queue of Archicad after executing the command.
		@return Returns an error if the process of modification fails for some reason, otherwise nothing.
	*/
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT PreferenceTableContainerBase::Modifier : public ACAPI::ModifierBase {
	PreferenceTableContainerBase& parent;
protected:
	Modifier (PreferenceTableContainerBase&);

public:
	~Modifier ();

	friend PreferenceTableContainerBase;

	/** @brief Inserts a new preference table into the container.
		@param tableName The name of the table. It will be trimmed of leading and trailing whitespaces. This must be a non-empty and currently non-existent name in the container.
		@return In case of successful insertion, returns the UniqueID of the newly inserted table.
	*/
	Result<UniqueID> AddNewTable (GS::UniString tableName);

	/** @brief Deletes a preference table from the container.
		@param uniqueId The UniqueID of the table.
		@return Returns an error if the parameter does not identify a PreferenceTable, otherwise nothing.
	*/
	Result<void> Delete (const UniqueID& uniqueId);
};


template <typename ModifierFunc>
Result<void> PreferenceTableContainerBase::Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier (*this);
	return ExecuteUndoableScope (modifierFunc, modifier, *this, undoString);
}


} // v1

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_PREFERENCE_TABLE_CONTAINER_BASE_HPP