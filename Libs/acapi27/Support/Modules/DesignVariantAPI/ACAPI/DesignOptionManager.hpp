#ifndef GS_ACAPI_DESIGNOPTIONMANAGER_HPP
#define GS_ACAPI_DESIGNOPTIONMANAGER_HPP

#include "DesignOptionAPIExport.hpp"
#include "DesignOptionCombinationViewSettings.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/Object.hpp"
#include <vector>


/** @brief Returns the token associated with the AddOn.
	@ingroup AddOnIdentification
	@return The token associated with the add-on.
	@remarks It is not guaranteed that this function will always return the same value. Always obtain your
   token by calling this function on demand.
*/
API_Token ACAPI_GetToken ();

namespace ACAPI {
inline namespace v1 {
	class View;
}


//! @cond Doxygen_Suppress
inline namespace v1 {
	class DesignOptionManager;
	inline DesignOptionManager CreateDesignOptionManager ();
}


namespace v2 {
	inline Result<DesignOptionManager> CreateDesignOptionManager ();
}
//! @endcond
}


namespace ACAPI {

inline namespace v1 {

/** @brief A class that contains design option related functions.
*	@since Archicad 27
*	@ingroup DesignOptions
*/
class DESIGNOPTIONAPI_EXPORT DesignOptionManager : public Object {
	friend DesignOptionManager v1::CreateDesignOptionManager ();
	friend Result<DesignOptionManager> ACAPI::v2::CreateDesignOptionManager ();
public:

	/** @returns The design option combination of a view.
	*   @param view The view of which the design option combniation is requested.
	*	@par Example code snippets from Test / Design Options
	*		Get @snippet DesignOptions_Test.cpp Get-View-Design-Option-Combination-Example
	*		Set @snippet DesignOptions_Test.cpp Set-View-Design-Option-Combination-Example
	*/
	Result<DesignOptionCombinationViewSettings> GetDesignOptionCombinationSettingsOf (const View& view) const;

	/** @returns A list of the available design option combinations in the project.
	*	@par Example code snippets from Test / Design Options
	*		@snippet DesignOptions_Test.cpp Get-Design-Option-Combinations-Example
	*/
	Result<std::vector<DesignOptionCombination>> GetAvailableDesignOptionCombinations () const;

private:
	explicit DesignOptionManager (const API_Token& token);
	static Result<DesignOptionManager> Create (const API_Token& token);
};


/** @brief A function to create design option manager instance, that lets you query and manipulate design option related data.
	@ingroup DesignOptions
	@return The design option manager instance.
	@warning Kept for compatibility reasons. Do not use!
*/
inline DesignOptionManager CreateDesignOptionManager ()
{
	return DesignOptionManager::Create (ACAPI_GetToken ()).Unwrap ();
}

} // namespace v1


namespace v2 {

/** @brief A function to create design option manager instance, that lets you query and manipulate design option related data.
	@ingroup DesignOptions
	@return The design option manager instance.
*/
inline Result<DesignOptionManager> CreateDesignOptionManager ()
{
	return DesignOptionManager::Create (ACAPI_GetToken ());
}

} // namespace v2

} // namespace ACAPI


#endif
