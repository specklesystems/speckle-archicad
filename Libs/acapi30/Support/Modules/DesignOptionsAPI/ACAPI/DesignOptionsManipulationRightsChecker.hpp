#ifndef GS_ACAPI_DESIGNOPTIONSMANIPULATIONRIGHTCHECKER_HPP
#define GS_ACAPI_DESIGNOPTIONSMANIPULATIONRIGHTCHECKER_HPP

#include "ACAPI/Result.hpp"
#include "DesignOptionAPIExport.hpp"

#include <optional>


namespace ACAPI {
	
namespace DesignOptions {

/**
 * @brief A class to check manipulation rights for Design Options.
 * @since Archicad 29
 * @ingroup DesignOptions
 */
class DESIGNOPTIONAPI_EXPORT DesignOptionsManipulationRightsChecker {

public:
/**
* @returns An error if there is no opened project, or if the given window type is not Design Options compatible
* @since Archicad 29
* @ingroup DesignOptions
*/
static std::optional<Error> CheckProjectExistanceAndWindowType ();


/**
* @returns An error if design option/design option set/design option combination creation is not allowed
* @since Archicad 29
* @ingroup DesignOptions
*/
static std::optional<Error> CheckCreationRights ();


/**
* @returns An error if design option/design option set/design option combination modification/deletion is not allowed.
* @param designOptionsTypeGuid The guid of the  design option/design option set/design option combination to check
* @since Archicad 29
* @ingroup DesignOptions
*/
static std::optional<Error> CheckModificationAndDeletionRights (const GS::Guid& designOptionsTypeGuid);

};

} // namespace DesignOptions

} // namespace ACAPI

#endif  // GS_ACAPI_DESIGNOPTIONSMANIPULATIONRIGHTCHECKER_HPP
