#ifndef ACAPI_GSID_HPP
#define ACAPI_GSID_HPP

#include "ACAPI/Object.hpp"
#include "Result.hpp"
#include <set>


namespace ACAPI {
namespace v1 {

/** @brief Serves as a means to query various unique identifiers of the logged-in user, facilitating stable user identification
*	@class GSID
*	@since Archicad 28
*	@ingroup GSID
*   @remark These identifiers are stable; for the same user and organization, the same result is returned even if queried from different Archicad versions and computers.
*   It is not possible to infer any personal information (such as the organization's or the user's name or e-mail address) through them.
*   They are not tied to license technology, identity, or content; for example, they are queryable even in demo mode, given the user is signed in with a GSID account in Archicad.
*/
class ARCHICADAPI_EXPORT GSID final : public Object 
{
	friend Result<GSID> CreateGSIDObject ();

private:
	explicit GSID (const API_Token& token);

public:
	~GSID ();

	/** @brief Function used to query the organization identifiers belonging to the logged-in user.
	*	@return If successful, returns a Result object containing the user's organization identifiers.
	*	Returns an Error object otherwise.
	*   @par Example code snippet from Test / Protection
	*	@snippet Protection_Test.cpp Check-GSID-Authorization-Example
	*/
	Result<std::set<GS::UniString>>	GetOrganizationIds () const;

	/** @brief Function used to query the GSID User ID of the logged-in user.
	*	@return If successful, returns a Result object containing the user's GSID User ID.
	*	Returns an Error object otherwise.
	* 	@par Example code snippet from Test / Protection
	*	@snippet Protection_Test.cpp Check-GSID-Authorization-Example
	*/
	Result<GS::UniString> GetUserId () const;
};

/** @brief Creates an instance of class GSID.
	@ingroup GSID
	@return Returns a new GSID instance.
*/
inline Result<GSID> CreateGSIDObject ()
{
	return Ok (GSID (ACAPI_GetToken ()));
}

} // namespace v1

using v1::CreateGSIDObject;
using v1::GSID;

} // namespace ACAPI

#endif // ACAPI_GSID_HPP