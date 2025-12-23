#ifndef UCMONACOINSTALLER_HPP
#define UCMONACOINSTALLER_HPP
#include "DeprecatedResult.hpp"
#include "Location.hpp"
#include "RSTypes.hpp"
#include "UC.h"

namespace UC {

class UC_DLL_EXPORT MonacoInstaller {
	GSResModule module;

	GSErrCode WriteZipFileFromResource (GSHandle resHandle, const IO::Location& zipFileLoc) const;
	GS::Deprecated::Result<IO::Location, GSErrCode> GetZipFileLoc () const;

public:
	MonacoInstaller ();
	GS::Deprecated::Result<IO::Location, GSErrCode> GetExtractLocation () const;
	GSErrCode ExtractMonaco () const;

};

}

#endif // UCMONACOINSTALLER_HPP
