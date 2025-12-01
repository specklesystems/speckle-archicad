#if !defined ADDONREDIRECTQUERY_HPP
#define	ADDONREDIRECTQUERY_HPP

#include "GSUtilsExport.h"

namespace GS { class UniString ; }


namespace GSUtils {
	GSUTILS_DLL_EXPORT_CPP GS::UniString GSU_CALL ConstructRedirectAddOnUpdateVersionQueryUrl (const GS::UniString& lang, const GS::UniString& version, const GS::UniString& build, const GS::UniString& typeStr);
}

#endif	// ADDONREDIRECTQUERY_HPP