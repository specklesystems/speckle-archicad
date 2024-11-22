#ifndef ACAPI_VIEW_HPP
#define ACAPI_VIEW_HPP

#include "ArchicadAPIExport.hpp"
#include "Object.hpp"
#include "Result.hpp"

/** @brief Returns the token associated with the AddOn.
	@ingroup AddOnIdentification
	@return The token associated with the add-on.
	@remarks It is not guaranteed that this function will always return the same value. Always obtain your
   token by calling this function on demand.
*/
API_Token ACAPI_GetToken ();

namespace ACAPI {

inline namespace v1 {

/// @brief A class that represents an Archicad navigator view.
/// @ingroup View
class ARCHICADAPI_EXPORT View : public Object {
	friend Result<View> FindViewByGuid (const API_Guid& guid);
public:
	/// @brief Retrieves the guid of the view.
	const API_Guid& GetGuid () const;

private:
	explicit View (const API_Guid& guid, const API_Token& token);
};

/// @brief Constuct a view object referring to an existing Archicad view by guid.
/// @ingroup View
/// @details It is compatible with the guid member of the API_NavigatorItem struct.
/// @param guid The guid of the view.
inline Result<View> FindViewByGuid (const API_Guid& guid)
{
	return Ok (View (guid, ACAPI_GetToken ()));
}

} // namespace v1

} // namespace ACAPI


#endif /* ACAPI_VIEW_HPP */
