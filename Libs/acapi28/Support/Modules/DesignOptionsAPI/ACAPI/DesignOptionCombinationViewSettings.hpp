#ifndef ACAPI_DESIGNOPTIONCOMBINATIONVIEWSETTINGS_HPP
#define ACAPI_DESIGNOPTIONCOMBINATIONVIEWSETTINGS_HPP

#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "DesignOptionAPIExport.hpp"
#include "DesignOptionCombination.hpp"
#include <variant>

namespace ACAPI {

namespace Impl {
class DesignOptionCombinationViewSettingsImpl;
class DesignOptionManagerImpl;
} // namespace Impl

namespace DesignOptions {

namespace v1 {

/**
 * @brief A class that represents the design option combination settings of a view.
 * @since Archicad 27
 * @ingroup DesignOptions
 */
class DESIGNOPTIONAPI_EXPORT DesignOptionCombinationViewSettings : public Object {
	friend class Impl::DesignOptionManagerImpl;
	friend class DesignOptionManager;

public:
	class Modifier;

	/**
	 * @brief A type of combination that has no design option connected to it, and only shows the main model.
	 * @ingroup DesignOptions
	 */
	struct MainModelOnly {};

	/**
	 * @brief A type of combination for which the user has selected a specific set of design options.
	 * @ingroup DesignOptions
	 */
	struct Standard {
		/**
		 * @brief The standard combination.
		 * @var combination
		 */
		DesignOptionCombination combination;
	};

	/**
	 * @brief A type of combination that the user has modified, but did not give an explicit name.
	 * @ingroup DesignOptions
	 */
	struct Custom {
		/**
		 * @brief The custom combination.
		 * @var combination
		 */
		DesignOptionCombination combination;
	};

	/**
	 * @brief A type of combination that does not exist, and was previously deleted.
	 * @ingroup DesignOptions
	 */
	struct Missing {};

	/**
	 * @brief Status of the view settings.
	 * @ingroup DesignOptions
	 */
	using Status = std::variant<MainModelOnly, Standard, Custom, Missing>;


	/** @returns The name of a design option combination view setting. */
	GS::UniString GetName () const;

	/**
	 * @returns The combination of the view setting.
	 * @par Example code snippets from Test / Design Options
	 * 		Get @snippet DesignOptions_Test.cpp Get-View-Design-Option-Combination-Example
	 */
	Result<Status> GetStatus () const;

	/**
	 * @brief Modifies the view settings.
	 * @param modifierFunc The function that make the modifications.
	 * @return Result of the modification.
	 */
	template<class ModifierFunc>
	Result<void> Modify (ModifierFunc&& modifierFunc);

private:
	explicit DesignOptionCombinationViewSettings (std::shared_ptr<Impl::DesignOptionCombinationViewSettingsImpl> impl);
};

/** @ingroup DesignOptions */
class DESIGNOPTIONAPI_EXPORT DesignOptionCombinationViewSettings::Modifier : public ACAPI::ModifierBase {
	DesignOptionCombinationViewSettings& parent;
	explicit Modifier (DesignOptionCombinationViewSettings& parent);

	virtual ~Modifier ();

public:
	friend DesignOptionCombinationViewSettings;

	/**
	 * @brief Make the connected view to show only the main model.
	 * @par Example code snippets from Test / Design Options
	 * 		@snippet DesignOptions_Test.cpp Set-View-Design-Option-Combination-Example
	 */
	void SetMainModelOnly ();

	/**
	 * @brief Make the connected view to show a selected design option combination.
	 * @details The list of available combinations can be retrieved via DesignOptionManager::GetAvailableDesignOptionCombinations.
	 * @param combination The combination to be set.
	 */
	void SetStandardCombination (const DesignOptionCombination& combination);
};

template<class ModifierFunc>
Result<void> DesignOptionCombinationViewSettings::Modify (ModifierFunc&& modifierFunc)
{
	Modifier modifier (*this);
	return CallDefaultModifier (modifierFunc, modifier);
}


} // namespace v1

using namespace v1;

} // namespace DesignOptions

} // namespace ACAPI


#endif /* ACAPI_DESIGNOPTIONCOMBINATIONSETTINGS_HPP */
