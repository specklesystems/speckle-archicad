// **************************************************************************************
// Description:		Operation System related informations
//
// Namespaces:		OS
// Contact persons:	MM
//
// [SG compatible]
// **************************************************************************************

#ifndef OSINFO_HPP
#define OSINFO_HPP

#pragma once

#define OS_VERS_NUM_SIZE			128
#define OS_VERS_STR_SIZE			128
#define OS_VERS_BUGREP_STR_SIZE		256


// --- Includes	-------------------------------------------------------------------------

//from GSRoot
#include "GSRootExport.hpp"
#include "Definitions.hpp"


// --- OSInfo namespace	-----------------------------------------------------------------

namespace OS {


// --- Predeclarations	-----------------------------------------------------------------

class OSVersionInfoImpl;


// --- OSVersionInfo class --------------------------------------------------------------

class GSROOT_DLL_EXPORT OSVersionInfo {
private:
	OSVersionInfoImpl* impl;

public:
	 OSVersionInfo ();
	~OSVersionInfo ();

	bool		Is64BitOS () const;
	bool		IsWinOS () const;
	bool		IsMacOS () const;
	bool		IsLinux () const;

	GSErrCode	GetVersionNumbers (Int32& majorVersion, Int32& minorVersion, Int32& bugFixVersion, bool& hasBugFixVersion) const;
	GSErrCode	GetVersionNumber (char* result, UInt32 size) const;
	GSErrCode	GetVersionString (char* result, UInt32 size) const;
	GSErrCode	GetBugRepString (char* result, UInt32 size) const;
};


	// Check if OS version is at least the given one
	//	uses decimal numbers!

GSROOT_DLL_EXPORT	bool	IsAtLeastVersion (Int32 majorVersion, Int32 minorVersion, Int32 patchVersion = 0);


} // namespace OS

#endif
