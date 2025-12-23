#ifndef GS_ACAPI_DESIGNOPTIONSET_HPP
#define GS_ACAPI_DESIGNOPTIONSET_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "DesignOptionAPIExport.hpp"
#include "DesignOptionsManipulationRightsChecker.hpp"

namespace ACAPI {

namespace Impl {
class DesignOptionSetImpl;
class DesignOptionManagerImpl;
} // namespace Impl

namespace DesignOptions {

/**
 * @brief A class that represents the design option set.
 * @since Archicad 29
 * @ingroup DesignOptions
 */
class DESIGNOPTIONAPI_EXPORT DesignOptionSet : public Object {
    friend class DesignOptionManager;

public:

    /**
    * @brief Checks whether the design option set is editable.
    * @returns Ok if editable or Error otherwise.
    */
    Result<void> IsEditable () const;

    /** @returns The name of the design option set. */
    GS::UniString GetName () const;

    /** @returns The guid of the design option set. */
    GS::Guid GetGuid () const;

    /**
    * @brief Sets the name of the Design Option.
	* @return Result of the modification.
	* @param newName The new name to be set.
	* @pre This function needs to be called from an undo scope.
    */
    Result<void> SetName (const GS::UniString& newName);

private:
    explicit DesignOptionSet (std::shared_ptr<Impl::DesignOptionSetImpl> impl);
};

} // namespace DesignOptions

} // namespace ACAPI


#endif  /* ACAPI_DESIGNOPTIONSET_HPP */