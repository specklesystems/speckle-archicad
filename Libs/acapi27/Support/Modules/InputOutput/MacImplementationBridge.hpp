

#ifndef MACIMPLEMENTATIONBRIDGE_HPP
#define MACIMPLEMENTATIONBRIDGE_HPP

#if defined (macintosh)

#include "Location.hpp"

namespace IO {
	class IO_DLL_EXPORT MacImplementationBridge {
	protected:
		static MacImplementationBridge* Get ();
		MacImplementationBridge ();

		virtual GSErrCode	LocationToCFURL_Local (const IO::Location& target, CFURLRef* result) = 0;
		virtual GSErrCode	LocationToUTF8POSIXPath_Local (const IO::Location& target, Path* result) = 0;

		virtual GSErrCode FillLocation_Local (IO::Location& target, const char* targetPath) = 0;
		virtual GSErrCode FillLocation_Local (IO::Location& target, const CFURLRef& targetRef) = 0;

	public:
		virtual ~MacImplementationBridge ();

		static GSErrCode	LocationToCFURL (const IO::Location& target, CFURLRef* result);
		static GSErrCode	LocationToUTF8POSIXPath (const IO::Location& target, Path* result);

		static IO::Location CreateLocation (const CFURLRef& targetRef);
		static IO::Location CreateLocationFromPosixPath (const char* path);
	};
}

#endif // macintosh

#endif // MACIMPLEMENTATIONBRIDGE_HPP