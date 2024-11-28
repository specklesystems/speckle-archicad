#ifndef GS_ACAPI_LICENSE_INFO_LICENSE_INFO_MANAGER_HPP
#define GS_ACAPI_LICENSE_INFO_LICENSE_INFO_MANAGER_HPP

#include "ACAPI/ArchicadAPIExport.hpp"

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/LicenseInfo/ProductVersionInfo.hpp"

#include "APIdefs_ErrorCodes.h"

//! @cond Doxygen_Suppress
API_Token ACAPI_GetToken ();
//! @endcond

namespace ACAPI::LicenseInfo {

namespace v1 {

/**
 * @brief LicenseInfoManager is the entry point of the license or product-related informations.
 * @ingroup LicenseInfo
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT LicenseInfoManager : public Object
{
	friend Result<LicenseInfoManager> GetLicenseInfoManager ();
	explicit LicenseInfoManager (const API_Token&);

public:
	/**
	 * @brief Returns an instance of ProductVersionInfo.
	 * @ingroup LicenseInfo
	 * @return Returns the product version info or error.
	 */
	ProductVersionInfo GetProductVersionInfo () const;
};


/**
 * @brief Creates a @ref LicenseInfoManager instance.
 * @ingroup LicenseInfo
 * @return The new LicenseInfoManager instance.
 * @remarks This is the entry point of the license information on the API.
 */
inline Result<LicenseInfoManager> GetLicenseInfoManager ()
{
	LicenseInfoManager manager (ACAPI_GetToken ());
	return Ok (manager);
}

} // namespace v1

using v1::LicenseInfoManager;
using v1::GetLicenseInfoManager;

} // namespace ACAPI::LicenseInfo

#endif // GS_ACAPI_LICENSE_INFO_LICENSE_INFO_MANAGER_HPP