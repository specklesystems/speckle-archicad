#ifndef GS_ACAPI_DESIGNOPTIONMANAGER_HPP
#define GS_ACAPI_DESIGNOPTIONMANAGER_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "DesignOptionAPIExport.hpp"
#include "DesignOptionCombinationViewSettings.hpp"
#include "DesignOptionSet.hpp"
#include "DesignOption.hpp"
#include "HotlinkDesignOptionTable.hpp"
#include "ElemDesignOptionStatus.hpp"
#include <vector>

namespace ACAPI::ModelViews {
class View;
}

//! @cond Doxygen_Suppress
namespace ACAPI::DesignOptions {
class DesignOptionManager;
inline Result<DesignOptionManager> CreateDesignOptionManager ();

} // namespace ACAPI::DesignOptions
//! @endcond

namespace ACAPI {

namespace DesignOptions {

/**
 * @brief A class that contains design option related functions.
 * @since Archicad 27
 * @ingroup DesignOptions
 */
class DESIGNOPTIONAPI_EXPORT DesignOptionManager : public Object {
	friend Result<DesignOptionManager> CreateDesignOptionManager ();

public:

	/**
	* @returns The design option combination of a view.
	* @param view The view of which the design option combination is requested.
	* @par Example code snippets from Test / Design Options
	*		Get @snippet DesignOptions_Test.cpp Get-View-Design-Option-Combination-Example
	*		Set @snippet DesignOptions_Test.cpp Set-View-Design-Option-Combination-Example
	*/
	Result<DesignOptionCombinationViewSettings> GetDesignOptionCombinationSettingsOf (const ACAPI::ModelViews::View& view) const;

	/**
	* @returns A list of the design option combinations in the project
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Get-Design-Option-Combinations-Example
	*/
	Result<std::vector<DesignOptionCombination>> GetDesignOptionCombinations () const;

	/**
	* @returns A list of the design option sets in the project.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Get-Design-Option-Sets-Example
	*/
	Result<std::vector<DesignOptionSet>> GetDesignOptionSets () const;

	/**
	* @returns A list of the design options in the given set, or an error if the set is invalid.
	* @param set The set whose design options are requested.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Get-Design-Options-Of-Set-Example
	*/
	Result<std::vector<DesignOption>> GetDesignOptionsOfSet (const DesignOptionSet& set) const;

	/**
	* @returns A list of the active design options in the given combination, or an error if the combination is invalid.
	* @param combination The combination whose design options are requested.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Get-Active-Design-Options-Of-Combination-Example
	*/
	Result<std::vector<DesignOption>> GetActiveDesignOptionsOfCombination (const DesignOptionCombination& combination) const;

	/**
	 * @returns A list of the design options in the project.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Get-All-Design-Options-Example
	 */
	Result<std::vector<DesignOption>> GetAllDesignOptions () const;

	/**
	* @returns A list of elements linked to a design option.
	* @param option The option whose linked elements are requested.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Get-Elements-Of-Design-Option-Example
	*/
	Result<std::vector<API_Guid>> GetElementsOfDesignOption (const DesignOption& option) const;


	/**
	* @returns A table of the available design options and combinations in the hotlink node.
	* @param hotlinkNode The hotlink node whose design option table is requested.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Get-Hotlink-Design-Option-Table
	*/
	Result<HotlinkDesignOptionTable> GetHotlinkDesignOptionTable (const API_HotlinkNode& hotlinkNode) const;

	/**
	* @returns A table of the available and active design options and combinations in the hotlink instance.
	* @param hotlink The hotlink instance whose design option table is requested.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Get-Hotlink-Instance-Design-Option-Table
	*/
	Result<HotlinkDesignOptionTable> GetHotlinkInstanceDesignOptionTable (const API_HotlinkType& hotlink) const;

	/**
	* @brief Set Design Option data of the given hotlink instance. 
	* @returns An error if the process of modification fails for some reason, otherwise nothing.
	* @param hotlink The hotlink whose design option table is set.
	* @param designOptionTable A table that contains the new data
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Set-Hotlink-Design-Option-Table
	*/
	Result<void> SetHotlinkDesignOptionTable (API_HotlinkType& hotlink, const HotlinkDesignOptionTable& designOptionTable) const;

	/**
	 * @brief This function is used to get the guid of the Design Option object set. This guid can be used for TW reserve/release
	 * @returns The guid of the object set.
	 */
	Result<API_Guid> GetTWID () const;

	/**
	* @returns Whether the provided element can be moved to another design option.
	* @param elemGuid Guid of the element.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Can-Be-Moved-To-Other-Design-Option
	*/
	Result<void> CanBeMovedToOtherDesignOption (const API_Guid& elemGuid) const;


	/**
	* @brief Creates a new design option in the given set.
	* @returns The created item
	* @param designOptionSet The set in which the design option will be created.
	* @param prevDesignOption The name of the design option after which the new design option should be created.
	*		If this is @c std::nullopt, then the new option will be created as the first design option in the set.
	* @param id The id of the new design option.
	* @param name The name of the new design option.
	* @pre This call needs undo scope. The object set should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Create-Design-Option-Example
	*/
	Result<DesignOption> CreateDesignOption (const DesignOptionSet& designOptionSet,
											 const std::optional<DesignOption>& prevDesignOption,
											 const GS::UniString& name,
											 const GS::UniString& id);

	/**
	* @brief Deletes the Design Option
	* @returns Result of the deletion
	* @param designOption The design option to delete.
	* @pre This call needs undo scope. The element should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Delete-Design-Option-Example
	*/
	Result<void> DeleteDesignOption (const DesignOption& designOption);

	/**
	* @brief Moves the design option to an other set. The design option will be the last in this set.
	* @returns Result of the movement
	* @param designOption The design option to move.
	* @param designOptionSet The set into which the design option will be moved.
	* @pre This call needs undo scope. The element should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Move-To-Other-Set-Example
	*/
	Result<void>		MoveDesignOptionToOtherSet (const DesignOption& designOption,
													const DesignOptionSet& designOptionSet);

	/**
	* @brief Moves the design option within the set.
	* @returns Result of the movement
	* @param designOption The design option to move.
	* @param nextDesignOption The option before which the design option will be placed.
	*		If this is std::nullopt, then the design option will be moved to the end.
	* @pre This call needs undo scope. The element should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Move-Within-Set-Example
	*/
	Result<void>		MoveDesignOptionWithinSet (const DesignOption& designOption,
												   const std::optional<DesignOption>& nextDesignOption);

	/**
	* @brief Sets the design option as default
	* @returns Whether the set operation was successful
	* @param designOption The design option to be set to default.
	*		If this is @c std::nullopt, then the main model will be set as default.
	* @pre 	This call needs undo scope. The object set should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Set-Design-Option-As-Default-Example
	*/
	Result<void> SetDesignOptionAsDefault (const std::optional<DesignOption>& designOption);

	/**
	* @brief Relinks the given element represented by elemGuid to the given design option.
	* @returns Whether the relink operation was successful
	* @param elemGuid The guid of the element to be moved to another design option
	* @param designOption The optional design option the element should be moved into.
	*		If it is std::nullopt the element will be moved back to the main model.
	* @pre This call needs undo scope. The element should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Move-Elem-To-Design-Option-Example
	*/
	Result<void>		RelinkElementToDesignOption (const API_Guid& elemGuid,
												     const std::optional<DesignOption>& designOption);
	/**
	* @brief Creates a new design option set.
	* @returns The created item
	* @param prevDesignOptionSet The name of the design option set after which the new design option set should be created.
	*		If this is @c std::nullopt, then the new option set will be created as the first.
	* @param name The name of the new design option set.
	* @pre 	This call needs undo scope. The object set should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Create-Design-Option-Set-Example
	*/
	Result<DesignOptionSet> CreateDesignOptionSet (const std::optional<DesignOptionSet>& prevDesignOptionSet,
												   const GS::UniString& name);
	/**
	* @brief Deletes the Design Option Set
	* @returns Result of the deletion
	* @param designOptionSet The design option set to delete.
	* @pre This call needs undo scope. The element should be modifiable.
	* @par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Delete-Design-Option-Set-Example
	*/
	Result<void> DeleteDesignOptionSet (const DesignOptionSet& designOptionSet);

	/**
	 * @brief Moves the Design Option Set.
	 * @returns Result of the movement.
	 * @param designOptionSet The design option set to move.
	 * @param nextOptionSet The option set before which the current option set will be placed. 
	 *		If this is std::nullopt, then the current option set will be moved to the end.
	 * @pre  This call needs undo scope. The object set should be modifiable.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Move-Design-Option-Set-Example
	 */
	Result<void> MoveDesignOptionSet (const DesignOptionSet& designOptionSet,
									  const std::optional <DesignOptionSet>& nextOptionSet);

	/**
	 * @brief Creates a new design option combination.
	 * @returns The created item
	 * @param name The name of the new design option combination.
	 * @pre This call needs undo scope. The combination should be modifiable.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Create-Design-Option-Combination-Example
	 */
	Result<DesignOptionCombination> CreateDesignOptionCombination (const GS::UniString& name);

	/**
	 * @brief Deletes the Design Option Combination
	 * @returns Result of the deletion
	 * @param designOptionCombination The design option combination to delete.
	 * @pre This call needs undo scope. The element should be modifiable.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Delete-Design-Option-Combination-Example
	 */
	Result<void> DeleteDesignOptionCombination (const DesignOptionCombination& designOptionCombination);

	/**
	 * @brief Activates a design option in a design option combination
	 * @returns Result of the activation
	 * @param designOptionCombination The design option combination in which the option will be activated
	 * @param designOption The design option to activate
	 * @pre This call needs undo scope. The elements should be modifiable.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Activate-First-Option-Of-Every-Set-In-Combination-Example
	 */
	Result<void> ActivateDesignOptionInCombination (const DesignOptionCombination& designOptionCombination, const DesignOption& designOption);

	/**
	 * @brief Deactivates a design option in a design option combination
	 * @returns Result of the deactivation
	 * @param designOptionCombination The design option combination in which the option will be deactivated
	 * @param designOption The design option to deactivate
	 * @pre This call needs undo scope. The elements should be modifiable.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Activate-First-Option-Of-Every-Set-In-Combination-Example
	 */
	Result<void> DeactivateDesignOptionInCombination (const DesignOptionCombination& designOptionCombination, const DesignOption& designOption);

	/**
	 * @brief Activates a list design options in a design option combination
	 * @returns Result of the activations
	 * @param designOptionCombination The design option combination in which the options will be activated
	 * @param designOptions The design options to activate
	 * @pre This call needs undo scope. The elements should be modifiable.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Deactivate-Every-Option-In-Combination-Example
	 */
	Result<void> SetActiveOptionsInCombination (const DesignOptionCombination& designOptionCombination, const std::vector<DesignOption>& designOptions);

	/**
	 * @brief Duplicates a design option combination
	 * @returns The new combination created by the duplication
	 * @param sourceCombination The design option combination to duplicate
	 * @pre This call needs undo scope. The elements should be modifiable.
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Duplicate-Design-Option-Combination-Example
	 */
	Result<DesignOptionCombination> DuplicateDesignOptionCombination (const DesignOptionCombination& sourceCombination);

	/**
	 * @returns The design option status of the provided element.
	 * @param elemGuid Guid of the element.	
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Get-Design-Option-Status-Of-Example
	 */
	Result<ElemDesignOptionStatus>	GetDesignOptionStatusOf (const API_Guid& elemGuid) const;

private:
	explicit DesignOptionManager (const API_Token& token);
	static Result<DesignOptionManager> Create (const API_Token& token);
};

/**
 * @brief A function to create design option manager instance, that lets you query and manipulate design option related data.
 * @ingroup DesignOptions
 * @returns The design option manager instance.
 */
inline Result<DesignOptionManager> CreateDesignOptionManager ()
{
	return DesignOptionManager::Create (ACAPI_GetToken ());
}

} // namespace DesignOptions

} // namespace ACAPI


#endif
