#ifndef GS_ACAPI_LICENSE_INFO_PRODUCT_VERSION_INFO_IMPL_BASE_HPP
#define GS_ACAPI_LICENSE_INFO_PRODUCT_VERSION_INFO_IMPL_BASE_HPP

#include "ACAPI/ObjectImpl.hpp"
#include "UniString.hpp"


namespace ACAPI::LicenseInfo::Impl {
/**
 * @brief Constructs an object of the ObjectImpl class.
 * @ingroup APIInfrastructure
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT ProductVersionInfoImplBase : public ACAPI::Impl::ObjectImpl
{
public:
	/**
	 * @brief Constructs an object of the ProductVersionInfoImplBase class with the given token.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @param token The token used by the implementation.
	 */
	ProductVersionInfoImplBase (const API_Token& token);
	virtual ~ProductVersionInfoImplBase ();

	/**
	 * @brief Default implementation of the GetProductFamilyId.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns an empty unistring.
	 */
	virtual GS::UniString	GetProductFamilyId () const;

	/**
	 * @brief Default implementation of the GetProductName.
	 * @ingroup APIInfrastructure
	 * @since Archicad 29
	 * @return Returns an empty unistring.
	 */
	virtual GS::UniString	GetProductName () const;

	/**
	 * @brief Default implementation of the GetGSLanguageCode.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns an empty unistring.
	 */
	virtual GS::UniString	GetGSLanguageCode () const;

	/**
	 * @brief Default implementation of the GetGSProductType.
	 * @ingroup APIInfrastructure
	 * @since Archicad 29
	 * @return Returns an empty unistring.
	 */
	virtual GS::UniString	GetGSProductType () const;
	
	/**
	 * @brief Default implementation of the GetAppVersionString.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns an empty unistring.
	 */
	virtual GS::UniString	GetAppVersionString () const;

	/**
	 * @brief Default implementation of the GetMainVersionString.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns zero.
	 */
	virtual GS::UniString	GetMainVersionString () const;
	
	/**
	 * @brief Default implementation of the GetUpdateVersionString.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns zero.
	 */
	virtual GS::UniString	GetUpdateVersionString () const;
	
	/**
	 * @brief Default implementation of the GetVersioNum3.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns zero.
	 */
	virtual GS::UniString	GetHotfixVersionString () const;
	
	/**
	 * @brief Default implementation of the GetBuildNum.
	 * @ingroup APIInfrastructure
	 * @since Archicad 28
	 * @return Returns zero.
	 */
	virtual Int32			GetBuildNum () const;
};


} // namespace ACAPI::LicenseInfo::Impl

#endif // GS_ACAPI_LICENSE_INFO_PRODUCT_VERSION_INFO_IMPL_BASE_HPP