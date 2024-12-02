/*==========================================================================**
**									GSUtils.h								**
**																			**
**					CONSTANTS, TYPES AND PROTOTYPES FOR GSUtils				**
**==========================================================================*/

/*
	Copyright (c) 1995-2024 by Graphisoft SUA_ChgCopyrightYear_PrevToNextYear_DONOTDELETETHISCOMMENT
	All rights reserved.
	Any part of the GDL import library kit (including this file) may be used
	for any purpose only under a separate written permission.

	GRAPHISOFT SE
	H-1031 Budapest, Zahony u. 7.
	Phone: 36.1/437-3000
	E-mail: archicadapi@graphisoft.com
*/

#ifndef	GSSYSTEM_H
#define	GSSYSTEM_H

#pragma once

#if !defined (COMPROC_H)
#include	"comProc.h"
#endif

#ifndef	GSUTILSEXPORT_H
	#include	"GSUtilsExport.h"
#endif

/*---------------------------------------------------------------------------*/

GSUTILS_DLL_EXPORT
void GSU_CALL GSSysBeep ();
GSUTILS_DLL_EXPORT
void GSU_CALL GSRegisterSound (const GS::UniString& appName, const GS::UniString& soundPath, const GS::UniString& soundName, const GS::UniString& description, bool overWritesoundName);
GSUTILS_DLL_EXPORT
void GSU_CALL GSUnRegisterSound (const GS::UniString& appName, const GS::UniString& soundPath, const GS::UniString& soundName);
GSUTILS_DLL_EXPORT
void GSU_CALL GSPlaySound (const GS::UniString&	soundName);

#endif //GSSYSTEM_H
