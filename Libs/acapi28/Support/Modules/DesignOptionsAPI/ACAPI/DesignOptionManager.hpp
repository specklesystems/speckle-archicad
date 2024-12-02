#ifndef GS_ACAPI_DESIGNOPTIONMANAGER_HPP
#define GS_ACAPI_DESIGNOPTIONMANAGER_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "DesignOptionAPIExport.hpp"
#include "DesignOptionCombinationViewSettings.hpp"
#include <vector>

namespace ACAPI::ModelViews::v1 {
class View;
}

namespace ACAPI::DesignOptions {

//! @cond Doxygen_Suppress
namespace v1 {
class DesignOptionManager;
inline DesignOptionManager CreateDesignOptionManager ();
} // namespace v1


namespace v2 {
inline Result<v1::DesignOptionManager> CreateDesignOptionManager ();
}
//! @endcond

} // namespace ACAPI


namespace ACAPI {

namespace DesignOptions {

namespace v1 {

/**
 * @brief A class that contains design option related functions.
 * @since Archicad 27
 * @ingroup DesignOptions
 */
class DESIGNOPTIONAPI_EXPORT DesignOptionManager : public Object {
	friend DesignOptionManager		   v1::CreateDesignOptionManager ();
	friend Result<DesignOptionManager> ACAPI::DesignOptions::v2::CreateDesignOptionManager ();

public:
	/**
	 * @returns The design option combination of a view.
	 * @param view The view of which the design option combniation is requested.
	 * @par Example code snippets from Test / Design Options
	 * 		Get @snippet DesignOptions_Test.cpp Get-View-Design-Option-Combination-Example
	 * 		Set @snippet DesignOptions_Test.cpp Set-View-Design-Option-Combination-Example
	 */
	Result<DesignOptionCombinationViewSettings> GetDesignOptionCombinationSettingsOf (const ACAPI::ModelViews::v1::View& view) const;

	/**
	 * @returns A list of the available design option combinations in the project.
	 * @par Example code snippets from Test / Design Options
	 * 		@snippet DesignOptions_Test.cpp Get-Design-Option-Combinations-Example
	 */
	Result<std::vector<DesignOptionCombination>> GetAvailableDesignOptionCombinations () const;

private:
	explicit DesignOptionManager (const API_Token& token);
	static Result<DesignOptionManager> Create (const API_Token& token);
};


/**
 * @brief A function to create design option manager instance, that lets you query and manipulate design option related data.
 * @ingroup DesignOptions
 * @return The design option manager instance.
 * @warning Kept for compatibility reasons. Do not use!
 */
inline DesignOptionManager CreateDesignOptionManager ()
{
	return DesignOptionManager::Create (ACAPI_GetToken ()).Unwrap ();
}

using v1::DesignOptionManager;

} // namespace v1

} // DesignOptions

namespace DesignOptions {

namespace v2 {

/**
 * @brief A function to create design option manager instance, that lets you query and manipulate design option related data.
 * @ingroup DesignOptions
 * @return The design option manager instance.
 */
inline Result<DesignOptionManager> CreateDesignOptionManager ()
{
	return DesignOptionManager::Create (ACAPI_GetToken ());
}


} // namespace v2

using v2::CreateDesignOptionManager;

} // DesignOptions

} // namespace ACAPI


#endif
