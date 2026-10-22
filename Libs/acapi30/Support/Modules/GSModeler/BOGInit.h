#if !defined (_BOG_HPP_)
#define _BOG_HPP_

#include	"GSModelerExport.h"
#include	"GSModelerVers.h"

namespace IO {
	class Location;
}

GSMODELER_DLL_EXPORT
GSErr		BOGInit (const IO::Location& tempFolder, Int32 *libID);

GSMODELER_DLL_EXPORT
void		BOGExit (void);

#endif
