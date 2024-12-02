// *********************************************************************************************************************
// Description:		Available application information, launch, service
//
// Module:			InputOutput
// Namespace:		IO::IPC
// Contact person:	MIJ
//
// SG compatible
// *********************************************************************************************************************

#if !defined IO_IPC_APPLICATIONLAUNCHER_HPP
#define IO_IPC_APPLICATIONLAUNCHER_HPP

#pragma once

#include "IOBase.hpp"
#include "Location.hpp"

namespace IO {
namespace Process {


class IO_DLL_EXPORT ApplicationLauncher {
public:
	enum LaunchMode {
		LaunchDefault,
		LaunchAndActivate,
		LaunchInBackground,
		LaunchDefaultNoNewInstanceOnOSX
	};
	enum LaunchOption {
		DefaultCurrentWorkDirectory,
		OwnCurrentWorkDirectory,
		EnableSubAppLaunch
	};

public:

	static ApplicationLauncher& Instance ();

	GSErrCode Launch (const IO::Location& location, const GS::Array<GS::UniString>& argv = GS::Array<GS::UniString> (), LaunchMode launchMode = LaunchDefault, LaunchOption launchOption = DefaultCurrentWorkDirectory);

private:
	 ApplicationLauncher ();
	~ApplicationLauncher () {}

};

} // Process
} // IO

#endif
