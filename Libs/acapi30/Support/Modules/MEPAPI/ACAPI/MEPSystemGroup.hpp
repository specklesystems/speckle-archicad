#ifndef GS_ACAPI_MEP_SYSTEMGROUP_HPP
#define GS_ACAPI_MEP_SYSTEMGROUP_HPP

#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"

// STL
#include <memory>
#include <concepts>

namespace ACAPI::Impl {
	class ObjectCreator;
}

namespace ACAPI::MEP {

namespace Impl {
	class ISystemGroupImpl;
}

/**
 * @brief A SystemGroup represents a collection of @ref PhysicalSystem "PhysicalSystems".
 * @details	The SystemGroup has its own name and can be used by a user in the system browser to categorize sets of @ref PhysicalSystem "PhysicalSystems".
 *			The @ref PhysicalSystem "PhysicalSystems" contained in the SystemGroup does not need to share a common connection (e.g. domain).
 * @see PhysicalSystem
 * @since Archicad 29
 * @ingroup MEP
 */
class MEPAPI_EXPORT SystemGroup final : public Object {
private:
	friend class ACAPI::Impl::ObjectCreator;
	friend Result<std::vector<UniqueID>> GetSystemGroupIDs ();
	friend Result<SystemGroup> CreateSystemGroup (const GS::UniString& name, const GS::UniString& undoString);

	SystemGroup (std::shared_ptr<Impl::ISystemGroupImpl> impl);
	static Result<std::vector<UniqueID>> GetSystemGroupIDs (const API_Token& APIToken);
	static Result<SystemGroup> CreateSystemGroup (const GS::UniString& name, const API_Token& APIToken, const GS::UniString& undoString);

	const Impl::ISystemGroupImpl& GetImpl () const;
	Impl::ISystemGroupImpl& GetImpl ();

public:
	~SystemGroup ();

	class Modifier;

	/**
	 * @brief Returns the SystemGroup.
	 * @param uniqueId The unique identifier of the SystemGroup object
	 * @return If the uniqueId refers to a SystemGroup, returns the associated object, otherwise an error.
	 *		   @snippet LabelingSystems.cpp SystemGroup-Get-Example
	 */
	static Result<SystemGroup> Get (const UniqueID& uniqueId);

	/**
	* @brief Checks whether the SystemGroup is editable.
	* @return Returns nothing if the SystemGroup is editable, otherwise the error containing information about the reason.
	*/
	Result<void> IsEditable () const;

	/**
	 * @brief Gets the name of the SystemGroup
	 * @return The name of the SystemGroup
	 *		   @snippet LabelingSystems.cpp SystemGroup-GetName-Example
	 */
	GS::UniString GetName () const;

	/**
	 * @brief Gets the IDs of the @ref PhysicalSystem "PhysicalSystems" currently contained in the SystemGroup
	 * @return The IDs of the @ref PhysicalSystem "PhysicalSystems" currently contained in the SystemGroup
	 *		   @snippet LabelingSystems.cpp SystemGroup-GetSystemIDs-Example
	 */
	std::vector<UniqueID> GetSystemIDs () const;


	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function, function pointer or similar) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 *		   @snippet GenerateLargeSystems.cpp SystemGroup-Modify-Example
	 */
	template <std::invocable<SystemGroup::Modifier&> ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc, const GS::UniString& undoString);
};


/**
 * @brief Modifier object for SystemGroup
 * @since Archicad 29
 * @ingroup MEP
 */
class MEPAPI_EXPORT SystemGroup::Modifier : public ACAPI::ModifierBase {
private:
	friend class SystemGroup;

	SystemGroup& mParent;
	Modifier (SystemGroup& parent);

public:
	virtual ~Modifier ();

	/**
	 * @brief Sets the name of the SystemGroup
	 * @param name The new name of the SystemGroup
	 * @return Nothing if setting the name was successful, otherwise an error
	 */
	Result<void> SetName (const GS::UniString& name);

	/**
	 * @brief Creates and adds a new PhysicalSystem to the SystemGroup
	 * @param name The name of the new PhysicalSystem.
	 * @return The ID of the newly created PhysicalSystem if successful, otherwise an error
	 *		   @snippet GenerateLargeSystems.cpp SystemGroup-Modifier-Add-Example
	 */
	Result<UniqueID> Add (const GS::UniString& name);
	/**
	 * @brief Removes an existing PhysicalSystem from the SystemGroup
	 * @param system The ID of the PhysicalSystem to remove
	 * @return Nothing if the PhysicalSystem was removed successfully, otherwise an error
	 */
	Result<void> Remove (const UniqueID& system);
};


/**
 * @brief Fetches the IDs of the current @ref SystemGroup "SystemGroups".
 * @ingroup MEP
 * @return A list of the IDs of the current @ref SystemGroup "SystemGroups".
 *		   @snippet LabelingSystems.cpp GetSystemGroupIDs-Example
 */
inline Result<std::vector<UniqueID>> GetSystemGroupIDs ()
{
	return SystemGroup::GetSystemGroupIDs (ACAPI_GetToken ());
}


/**
 * @brief Creates a new SystemGroup.
 * @param name The name of the new SystemGroup.
 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
 * @ingroup MEP
 * @return A new SystemGroup if successful, otherwise an error.
 *		   @snippet GenerateLargeSystems.cpp CreateSystemGroup-Example
 */
inline Result<SystemGroup> CreateSystemGroup (const GS::UniString& name, const GS::UniString& undoString = "Create system group")
{
	return SystemGroup::CreateSystemGroup (name, ACAPI_GetToken (), undoString);
}


template <std::invocable<SystemGroup::Modifier&> ModifierFunc>
Result<void> SystemGroup::Modify (ModifierFunc&& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier { *this };
	return ExecuteUndoableScope (std::forward<ModifierFunc> (modifierFunc), modifier, *this, undoString);
}

} // namespace ACAPI::MEP

#endif // GS_ACAPI_MEP_SYSTEMGROUP_HPP
