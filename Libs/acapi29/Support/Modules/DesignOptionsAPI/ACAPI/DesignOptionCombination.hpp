#ifndef GS_ACAPI_DESIGNOPTIONCOMBINATION_HPP
#define GS_ACAPI_DESIGNOPTIONCOMBINATION_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "DesignOptionAPIExport.hpp"
#include "DesignOptionsManipulationRightsChecker.hpp"


namespace ACAPI {

namespace Impl {
class DesignOptionCombinationImpl;
class DesignOptionCombinationViewSettingsImpl;
class DesignOptionManagerImpl;
} // namespace Impl

namespace DesignOptions {

/**
 * @brief A class that represents the design option combination of the view settings.
 * @since Archicad 27
 * @ingroup DesignOptions
 */
class DESIGNOPTIONAPI_EXPORT DesignOptionCombination : public Object {
	friend class Impl::DesignOptionCombinationViewSettingsImpl;
	friend class DesignOptionManager;

public:

	/**
	 * @brief Checks whether the Design Option Combination is editable
	 * @returns Ok if editable. Otherwise Error, with the reason why the combination is not editable.
	 */
	Result<void> IsEditable () const;

	/** @returns The name of the combination. */
	GS::UniString GetName () const;

	/** @returns The guid of the combination. */
	GS::Guid GetGuid () const;

	/**
	 * @brief Sets the name of the Design Option Combination.
	 * @returns Result of the modification.
	 * @param newName The new name to be set.
	 * @pre This function needs to be called from command scope
	 * @par Example code snippets from Test / Design Options
	 *		@snippet DesignOptions_Test.cpp Modify-Design-Options-Combinations-Name-Example
	 */
	Result<void> SetName (const GS::UniString& newName);

private:
	explicit DesignOptionCombination (std::shared_ptr<Impl::DesignOptionCombinationImpl> impl);
};

} // namespace DesignOptions

} // namespace ACAPI


#endif /* ACAPI_DESIGNOPTIONCOMBINATION_HPP */
