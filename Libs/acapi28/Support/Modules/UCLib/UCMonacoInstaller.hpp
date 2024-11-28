#ifndef UCMONACOINSTALLER_HPP
#define UCMONACOINSTALLER_HPP
#include "Result.hpp"
#include "Location.hpp"
#include "RSTypes.hpp"
#include "UC.h"

namespace UC {

class UC_DLL_EXPORT MonacoInstaller {
	GSResModule module;

	GSErrCode WriteZipFileFromResource (GSHandle resHandle, const IO::Location& zipFileLoc) const;
	GS::Result<IO::Location, GSErrCode> GetZipFileLoc () const;

public:
	MonacoInstaller ();
	GS::Result<IO::Location, GSErrCode> GetExtractLocation () const;
	GSErrCode ExtractMonaco () const;

};

}

#endif // UCMONACOINSTALLER_HPP
