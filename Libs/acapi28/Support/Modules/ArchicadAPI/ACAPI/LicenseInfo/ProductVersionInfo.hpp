#ifndef GS_ACAPI_LICENSE_INFO_PRODUCT_VERSION_INFO_HPP
#define GS_ACAPI_LICENSE_INFO_PRODUCT_VERSION_INFO_HPP

#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"

#include "APIdefs_ErrorCodes.h"

namespace ACAPI::LicenseInfo {

namespace Impl { class ProductVersionInfoImplBase; }
namespace Impl { class LicenseInfoManagerImpl; }

namespace v1 {

/**
 * @brief ProductVersionInfo is the central point of the product-related informations.
 * @ingroup LicenseInfo
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT ProductVersionInfo : public Object
{
	friend class Impl::LicenseInfoManagerImpl;

	explicit ProductVersionInfo (std::shared_ptr<Impl::ProductVersionInfoImplBase> productVersionInfoImplBase);

public:
	/**
	 * @ingroup LicenseInfo
	 * @return Returns the family of the product.
	 */
	GS::UniString GetProductFamilyId () const;

	/**
	 * @ingroup LicenseInfo
	 * @return Returns the language of the application in a Graphisoft-specific format.@n
	 * 		   |Graphisoft-specific format|Language|
	 * 		   |---|---|
	 * 		   |ARA|Arabic|
	 * 		   |AUS|Australian English|
	 * 		   |AUT|Austrian|
	 * 		   |BUL|Bulgarian|
	 * 		   |CHE|Swiss German|
	 * 		   |CHI|Simplified Chinese|
	 * 		   |CRO|Croatian|
	 * 		   |CZE|Czech|
	 * 		   |DEN|Danish|
	 * 		   |EST|Estonian|
	 * 		   |FIN|Finnish|
	 * 		   |FRA|French|
	 * 		   |GER|German|
	 * 		   |GRE|Greek|
	 * 		   |HUN|Hungarian|
	 * 		   |ICE|Icelandian|
	 * 		   |ITA|Italian|
	 * 		   |INT|International English|
	 * 		   |ISR|Israeli|
	 * 		   |JPN|Japanese|
	 * 		   |KOR|Korean|
	 * 		   |NED|Dutch|
	 * 		   |NZE|New Zealand English|
	 * 		   |NOR|Norwegian|
	 * 		   |POL|Polish|
	 * 		   |POR|Portuguese|
	 * 		   |ENG|British English|
	 * 		   |ROM|Romanian|
	 * 		   |RUS|Russian|
	 * 		   |SLO|Slovak|
	 * 		   |SPA|Spanish|
	 * 		   |SWE|Swedish|
	 * 		   |TAI|Traditional Chinese|
	 * 		   |TUR|Turkish|
	 * 		   |USA|USA English|
	 * 		   |IND|Indic|
	 * 		   |BRA|Brasil|
	 * 		   |UKI|United Kingdom & Ireland|
	 * 		   |IRN|Iran|
	 * 		   |UKR|Ukraine|
	 */
	GS::UniString GetGSLanguageCode () const;

	/**
	 * @ingroup LicenseInfo
	 * @return Returns the version of the product as a string.
	 */
	GS::UniString GetVersionString () const;

	/**
	 * @ingroup LicenseInfo
	 * @return Returns the first number of the version (main version).
	 */
	Int32 GetVersionNum1 () const;

	/**
	 * @ingroup LicenseInfo
	 * @return Returns the second number of the version (update version).
	 */
	Int32 GetVersionNum2 () const;

	/**
	 * @ingroup LicenseInfo
	 * @return Returns the third number of the version (hotfix version).
	 */
	Int32 GetVersionNum3 () const;

	/**
	 * @ingroup LicenseInfo
	 * @return Returns the build number of the product.
	 */
	Int32 GetBuildNum () const;
};

} // namespace v1

using v1::ProductVersionInfo;

} // namespace ACAPI::LicenseInfo

#endif // GS_ACAPI_LICENSE_INFO_PRODUCT_VERSION_INFO_HPP