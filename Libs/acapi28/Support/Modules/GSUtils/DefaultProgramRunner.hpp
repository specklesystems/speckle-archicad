#ifndef	DEFAULTPROGRAMRUNNER_HPP
#define	DEFAULTPROGRAMRUNNER_HPP

#include "GSUtilsExport.h"

namespace GS { class UniString ; }

namespace OSUtils {
	GSUTILS_DLL_EXPORT_CPP bool GSU_CALL OpenWithDefaultProgram (const GS::UniString& path);
	GSUTILS_DLL_EXPORT_CPP bool GSU_CALL OpenWithDefaultBrowser (const GS::UniString& url);
}	// namespace OSUtils

#endif