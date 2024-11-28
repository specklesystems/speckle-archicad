#if !defined (_BOG_HPP_)
#define _BOG_HPP_

#include	"GSModelerExport.h"
#include	"GSModelerVers.h"
#include	"RSTypes.hpp" // GSResModule

namespace IO {
	class Location;
}

extern GSResModule gModelerLocStringModule;
extern GSResModule gModelerFixStringModule;

GSMODELER_DLL_EXPORT
GSErr		BOGInit (const IO::Location& tempFolder, GSResModule locStringModule, GSResModule fixStringModule, Int32 *libID);

GSMODELER_DLL_EXPORT
void		BOGExit (void);

#endif
