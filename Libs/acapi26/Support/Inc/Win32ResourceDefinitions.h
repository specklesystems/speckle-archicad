// *********************************************************************************************************************
// Description:		Includes header files for Win32 resource definitions
//
// Module:			Resource compilations
// Namespace:		-
// Contact person:	MM
//
// SG compatible
// *********************************************************************************************************************

#if !defined (WIN32RESOURCEDEFINITIONS_H)
#define WIN32RESOURCEDEFINITIONS_H

#ifndef	_WIN32_WINNT
#define	_WIN32_WINNT	0x0501		//  _WIN32_WINNT_WINXP
#endif

#ifndef	WINDOWS
#define	WINDOWS
#endif

#ifndef	SDKDDKVER_H_INCLUDED
#define	SDKDDKVER_H_INCLUDED
#include	<sdkddkver.h>
#endif

#ifndef	WINUSER_RH_INCLUDED
#define	WINUSER_RH_INCLUDED
#include	<WinUser.rh>
#endif

#ifndef	WINVER_H_INCLUDED
#define	WINVER_H_INCLUDED
#include	<WinVer.h>
#endif

#ifndef	COMMCTRL_H_INCLUDED
#define	COMMCTRL_H_INCLUDED
#include	<CommCtrl.h>
#endif

#endif
