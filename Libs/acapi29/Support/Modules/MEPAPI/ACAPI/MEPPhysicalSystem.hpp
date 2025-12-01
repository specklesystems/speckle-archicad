#ifndef GS_ACAPI_MEP_PHYSICALSYSTEM_HPP
#define GS_ACAPI_MEP_PHYSICALSYSTEM_HPP

#include "MEPAPIExport.hpp"
#include "MEPUniqueID.hpp"

// ACAPI
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"

// STL
#include <memory>
#include <optional>
#include <concepts>

namespace ACAPI::Impl {
	class ObjectCreator;
}

namespace ACAPI::MEP {
	class DistributionSystemsGraph;

namespace Impl {
	class IPhysicalSystemImpl;
}

/**
 * @brief A PhysicalSystem represents a physical instance of a system.
 * 
 * @details Where a DistributionSystem represents a logical grouping of connected elements, a PhysicalSystem represents a
 * 			physical one. A PhysicalSystem only specifies certain instance specific attributes about a system like its name,
 * 			"root" / "calculation starting point" and domain, but does not track the elements contained in the system.
 * 
 * 			Given that the PhysicalSystem has an assosiated "root" element, the PhysicalSystem can be represented by a DistributionSystem,
 * 			and the elements currently contained by the PhysicalSystem can be queried for via its DistributionSystem.
 * 
 * 			Contrary to a DistributionSystem, a PhysicalSystem *is* a database object and will be serialized to a pln file.
 * @see SystemGroup
 * @since Archicad 29
 * @ingroup MEP
 */
class MEPAPI_EXPORT PhysicalSystem final : public Object {
private:
	friend class ACAPI::Impl::ObjectCreator;

	PhysicalSystem (std::shared_ptr<Impl::IPhysicalSystemImpl> impl);

	const Impl::IPhysicalSystemImpl& GetImpl () const;
	Impl::IPhysicalSystemImpl& GetImpl ();

public:
	~PhysicalSystem ();

	class Modifier;

	/**
	 * @brief Fetch a PhysicalSystem.
	 * @param uniqueId The unique identifier of the PhysicalSystem object
	 * @return If the uniqueId refers to a PhysicalSystem, returns the associated object, otherwise an error.
	 *		   @snippet LabelingSystems.cpp PhysicalSystem-Get-Example
	 */
	static Result<PhysicalSystem> Get (const UniqueID& uniqueId);
	/**
	 * @brief Creates a new PhysicalSystem.
	 * @param name The name of the new PhysicalSystem.
	 * @param groupId The unique identifier of the owning SystemGroup object.
	 * @remarks Creating a new PhysicalSystem in a teamwork project requires the owning SystemGroup to be reserved for the current user.
	 *			This function is simply an alternative to invoking SystemGroup::Modifier::Add.
	 * @return Returns the newly created PhysicalSystem if successful, otherwise an error.
	 */
	static Result<PhysicalSystem> Create (const GS::UniString& name, const UniqueID& groupId);


	/**
	 * @brief Find PhysicalSystems by a list of unique identifiers of elements in the system.
	 * @param elementIds A list of unique identifiers of an element objects present in PhysicalSystems.
	 * @param distributionGraph The current distributionGraph if available, otherwise nullptr. In which case the function will calculate it. Should be supplied for better overall performance.
	 * @details This function is useful when the user has unique identifiers of elements and wants to find all PhysicalSystems they belong to.
	 *			e.g. if the user has an element selected in the UI and wants to find the PhysicalSystems it belongs to.
	 * @return If the element ids given are present in one or more PhysicalSystems those PhysicalSystem objects will be returned or an empty list will be returned.
	 *			Each elementId will have a corresponding list of PhysicalSystem objects in the returned vector.
	 */
	static Result<std::vector<std::vector<UniqueID>>> FindSystemIdsFromElementIds (const std::vector<UniqueID>& elementIds, const ACAPI::MEP::DistributionSystemsGraph* distributionGraph);


	/**
	* @brief Checks whether the PhysicalSystem is editable.
	* @return Returns nothing if the PhysicalSystem is editable, otherwise the error code and error message containing information about the reason.
	*/
	Result<void> IsEditable () const;


	/**
	 * @brief Get the currently assigned root element ID
	 * @return If the PhysicalSystem has a root element assigned, returns the UniqueID of the root element, otherwise std::nullopt
	 *		   @snippet LabelingSystems.cpp PhysicalSystem-GetRootElementId-Example
	 */
	std::optional<UniqueID> GetRootElementId () const;

	/**
	 * @brief Get the name of the PhysicalSystem
	 * @return The name of the PhysicalSystem
	 *		   @snippet LabelingSystems.cpp PhysicalSystem-GetName-Example
	 */
	GS::UniString GetName () const;

	/**
	 * @brief Get the system category of the PhysicalSystem
	 * @return The attribute index of the system category of the PhysicalSystem
	 */
	API_AttributeIndex GetSystemCategory () const;


	/**
	 * @brief Executes the passed modifier scope in an Undoable command.
	 * @param modifierFunc The modifier scope (lambda, std::function, function pointer or similar) the caller wants to execute.
	 * @param undoString The text which appears in the undo queue of Archicad after executing the command.
	 * @return Returns an error if the process of modification fails for some reason, otherwise nothing.
	 *		   @snippet GenerateLargeSystems.cpp PhysicalSystem-Modify-Example
	 */
	template <std::invocable<PhysicalSystem::Modifier&> ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc, const GS::UniString& undoString);
};


/**
 * @brief Modifier object for PhysicalSystem
 * @since Archicad 29
 * @ingroup MEP
 */
class MEPAPI_EXPORT PhysicalSystem::Modifier : public ACAPI::ModifierBase {
private:
	friend class PhysicalSystem;
	
	PhysicalSystem& mParent;
	Modifier (PhysicalSystem& parent);

public:
	virtual ~Modifier ();

	/**
	 * @brief Set the currently assigned root element ID
	 * @param rootElementId The UniqueID of the element to set as the new root element
	 * @remarks For a route to be a valid root, it requires that either one or both ends
	 *			are not logically connected to another MEP element.
	 * @return Nothing is the root element was set successfully, otherwise an error
	 */
	Result<void> SetRootElement (const UniqueID& rootElementId);

	/**
	 * @brief Set the name of the PhysicalSystem
	 * @param name The new name of the PhysicalSystem
	 * @return Nothing if the name was set successfully, otherwise an error
	 */
	Result<void> SetName (const GS::UniString& name);

	/**
	 * @brief Set the system category of the PhysicalSystem
	 * @param index The attribute index of the system category to set
	 * @return Nothing if the system category was set successfully, otherwise an error
	 */
	Result<void> SetSystemCategory (API_AttributeIndex index);
};


template <std::invocable<PhysicalSystem::Modifier&> ModifierFunc>
Result<void> PhysicalSystem::Modify (ModifierFunc&& modifierFunc, const GS::UniString& undoString)
{
	Modifier modifier { *this };
	return ExecuteUndoableScope (std::forward<ModifierFunc> (modifierFunc), modifier, *this, undoString);
}

} // namespace ACAPI::MEP

#endif // GS_ACAPI_MEP_PHYSICALSYSTEM_HPP
