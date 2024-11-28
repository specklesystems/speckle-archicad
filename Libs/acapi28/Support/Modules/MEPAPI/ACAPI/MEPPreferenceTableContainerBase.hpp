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

namespace v1 {

/**
 * @brief The PreferenceTableContainerBase contains PreferenceTables, and you can Add/Get/Delete them.
 * @ingroup MEP
 * @since Archicad 27
 * @details The containers for the three MEP domains are already initialized and you can get them from DuctPreferenceTableContainer,
 * 			PipePreferenceTableContainer and CableCarrierPreferenceContainer
 * @par Example code snippet from Test / New MEP
 * 		Getters @snippet Preferences.cpp PreferenceTableContainer-Getters-Example
 * 		Modification @snippet Preferences.cpp PreferenceTableContainer-Modification-Example
 */
class MEPAPI_EXPORT PreferenceTableContainerBase : public Object {
protected:
	/**
	 * @brief Constructs a PreferenceTableContainerBase with the given base implementation.
	 * @param impl The given base implementation.
	 */
	PreferenceTableContainerBase (std::shared_ptr<Impl::IPreferenceTableContainerBaseImpl> impl);
	~PreferenceTableContainerBase ();

public:
	class Modifier;

	/** @return Checks if the object still exists. */
	bool Exists () const;

	/** @return Returns the UniqueIDs of the PreferenceTables associated with the caller object's domain. */
	std::vector<UniqueID> GetPreferenceTables () const;

	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function or function pointer) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 */
	template <typename ModifierFunc>
	Result<void> Modify (const ModifierFunc& modifierFunc, const GS::UniString& undoString);
};


class MEPAPI_EXPORT PreferenceTableContainerBase::Modifier : public ACAPI::ModifierBase {
	PreferenceTableContainerBase& parent;
protected:
	/**
	 * @brief Constructs a Modifier with the given PreferenceTableContainerBase.
	 * @param parent The given PreferenceTableContainerBase.
	 */
	Modifier (PreferenceTableContainerBase& parent);

public:
	~Modifier ();

	friend PreferenceTableContainerBase;

	/**
	 * @brief Inserts a new PreferenceTable into the container.
	 * @param tableName The name of the table. It will be trimmed of leading and trailing whitespaces. This must be a non-empty and currently non-existent name in the container.
	 * @param requiredId The guid to be set for the PreferenceTable - optional parameter
	 * @return In case of successful insertion, returns the UniqueID of the newly inserted table.
	 */
	Result<UniqueID> AddNewTable (GS::UniString tableName, const std::optional<API_Guid>& requiredId = std::nullopt);

	/**
	 * @brief Deletes a PreferenceTable from the container.
	 * @param uniqueId The UniqueID of the table.
	 * @return Returns an error if the parameter does not identify a PreferenceTable, otherwise nothing.
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

using v1::PreferenceTableContainerBase;

} // ACAPI::MEP

#endif // GS_ACAPI_MEP_PREFERENCE_TABLE_CONTAINER_BASE_HPP