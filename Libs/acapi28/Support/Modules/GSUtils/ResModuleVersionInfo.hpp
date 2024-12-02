// *********************************************************************************************************************
//
// File:			ResModuleVersionInfo.hpp
//
// Description:		Functions to get BuildNum and other version information.
//
// Project:			GSUtils
//
// Namespace:		ResModuleVersionInfo
//
// Contact person:	FM
//
// SG compatible
// *********************************************************************************************************************

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"

// from GSUtils
#include "GSUtilsExport.h"

// --- Predefinitions --------------------------------------------------------------------------------------------------

typedef	GS::IntPtr GSResModule;
namespace GS { class UniString; }

// --- ResModuleVersionInfo	--------------------------------------------------------------------------------------------

namespace ResModuleVersionInfo {

// the functions bellow works only for modules that contains the VersionInfo.rc2[.r] resources

GSUTILS_DLL_EXPORT
USize		GetBuildNum (GSResModule resModule);

	// Returns 3 char language code (INT, GER, ...) false for non localized modules
GSUTILS_DLL_EXPORT
bool		GetGSLanguageCode (GSResModule resModule, GS::UniString& languageCode);

	// Returns the unique if of the 3 char language code, 0 for non localized modules
GSUTILS_DLL_EXPORT
UIndex      GetCountryCodeNumber (GSResModule resModule);

	// Returns 4 char product type (STUD, UNIV, FULL, ....)
GSUTILS_DLL_EXPORT
bool		GetGSProductType (GSResModule resModule, GS::UniString& productType);

	// Returns version string (or codename in development stage)
GSUTILS_DLL_EXPORT
USize		GetGSProductVersionNumber (GSResModule resModule);

	// Returns the main version number
GSUTILS_DLL_EXPORT
bool		 GetGSProductVersionString (GSResModule resModule, GS::UniString& productVersion);

	// Returns the short release string R1, Beta1, etc.
GSUTILS_DLL_EXPORT
bool		GetShortGSReleaseString (GSResModule resModule, GS::UniString& releaseString);

	// Returns the mainversion.updateversion.hotfixversion formated version
GSUTILS_DLL_EXPORT
bool		GetGSProductCombinedVersionString (GSResModule resModule, GS::UniString& productVersion);

	// Returns the platform (MAC64, ...)
GSUTILS_DLL_EXPORT
bool		GetGSPlatformString (GSResModule resModule, GS::UniString& platformString);

	// Returns the build is private
GSUTILS_DLL_EXPORT
bool		GetGSPrivateBuild (GSResModule resModule, bool& privateBuild);

}
