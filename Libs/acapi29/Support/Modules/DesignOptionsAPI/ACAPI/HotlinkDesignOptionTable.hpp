#ifndef GS_ACAPI_HOTLINKDESIGNOPTIONTABLE_HPP
#define GS_ACAPI_HOTLINKDESIGNOPTIONTABLE_HPP

#include "DesignOptionAPIExport.hpp"
#include "UniString.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/Object.hpp"

#include <vector>
#include <optional>
#include <memory>

namespace ACAPI {

namespace Impl {
class HotlinkDesignOptionTableImpl;
class DesignOptionManagerImpl;
} // namespace Impl

namespace DesignOptions {

/**
 * @brief A class that represents the design option structure of a hotlink or node.
 * @since Archicad 29
 * @ingroup DesignOptions
 */
class DESIGNOPTIONAPI_EXPORT HotlinkDesignOptionTable : public Object {
	friend class DesignOptionManager;
	friend class Impl::DesignOptionManagerImpl;

public:
	/**
	 * @brief The mode how the hotlink instance's elements are filtered by Design Options. Only the filtered elements are visible.
	 * @enum FilterMode
	 * @ingroup DesignOptions
	 */
	enum class FilterMode {
		MainModelOnly		= 0,
		FilterByOptions		= 1,
		FilterByCombination = 2,
	};

	/** @returns The guid of the hotlink node which belongs to this design option table. */
	const GS::Guid GetNodeGuid () const;

	/** @returns The names of the design option combinations from a hotlink. */
	std::vector<GS::UniString> GetCombinationsNames () const;

	/** @returns The names of the design option sets from a hotlink. */
	std::vector<GS::UniString> GetSetsNames () const;

	/** 
	 * @returns The list of names of the design options in a given set from hotlink. 
	 * @param setName The name of the set whose options are requested.
	 */
	std::vector<GS::UniString> GetOptionsNamesOfSet (const GS::UniString& setName) const;

	/** @returns The name of the active combination. */
	std::optional<GS::UniString> GetActiveCombination () const;

	/** 
	 * @returns The name of the active option in set. 
	 * @param setName The name of the set whose active option will be returned.
	 */
	std::optional<GS::UniString> GetActiveOptionInSet (const GS::UniString& setName) const;

	/**
	 * @returns The Design Option filtering mode.
	 */
	FilterMode GetFilterMode () const;

	/** 
	 * @brief Activates the given combination.
	 * @returns An error if the given combination is missing, otherwise nothing.
	 * @param combinationName Name of the combination that will be activated.
	 */
	ACAPI::Result<void> ActivateCombination (const GS::UniString& combinationName);

	/** 
	 * @brief Activates an option in a set and deactivates the previous active option. 
	 * @returns An error if the given set or option is missing, otherwise nothing.
	 * @param setName The name of the set in which the option will be activated.
	 * @param optionName The name of the option that will be activated.
	 */
	ACAPI::Result<void> ActivateOptionInSet (const GS::UniString& setName, const GS::UniString& optionName);

	/** 
	 * @brief Deactivates the active option if it existed.
	 * @returns An error if the given set is missing, otherwise nothing.
	 * @param setName The name of the set in which the option will be deactivated.
	 */
	ACAPI::Result<void> DeactivateOptionsInSet (const GS::UniString& setName);

	/**
	 * @brief Deactivates the active combination if it existed.
	 */
	void DeactivateCombination ();

	/**
	 * @brief Sets the Design Option filtering mode of the Hotlink.
	 * @param filterMode The new filter mode to be set.
	 */
	void SetFilterMode (FilterMode filterMode);

private:
	explicit HotlinkDesignOptionTable (std::shared_ptr<Impl::HotlinkDesignOptionTableImpl> impl);
};

} // namespace DesignOptions

} // namespace ACAPI


#endif   /* GS_ACAPI_HOTLINKDESIGNOPTIONTABLE_HPP */