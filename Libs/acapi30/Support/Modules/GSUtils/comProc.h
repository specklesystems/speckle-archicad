/*==========================================================================**
**									comProc.h								**
**																			**
**							COMMON FUNCTION PROTOTYPES						**
**==========================================================================*/

#ifndef	COMPROC_H
#define COMPROC_H

#pragma once

#if !defined (GSROOT_HPP)
#include	"GSRoot.hpp"
#endif

#ifndef	GSUTILSEXPORT_H
	#include	"GSUtilsExport.h"
#endif

#include "GSTime.hpp"
#include "GSGuid.hpp"

typedef GS::IntPtr GSResModule;

/****************************************************************************/
/****************************************************************************/
/*																			*/
/*							RESOURCE AND ERROR FUNCTIONS					*/
/*																			*/
/****************************************************************************/
/****************************************************************************/


/****************************************************************************/
/*																			*/
/*								GetFixStrProc								*/
/*																			*/
/****************************************************************************/
/*
Called to get GDL keywords and fixed (language independent) error messages
from resources.
----------------------------------------------------------------------------*/


typedef	bool	GSU_CALL	GetFixStrProc (char *str, short resID, short index, GSResModule module);
typedef	bool	GSU_CALL	GetFixStrProc_UStr (GS::UniString& str, short resID, short index, GSResModule module);


/*----------------------------------------------------------------------------
*/


/****************************************************************************/
/*																			*/
/*								GetLocStrProc								*/
/*																			*/
/****************************************************************************/
/*
Called to get GDL language dependent error messages from resources.
----------------------------------------------------------------------------*/


typedef	bool	GSU_CALL	GetLocStrProc (char *str, short resID, short index, GSResModule module);
typedef	bool	GSU_CALL	GetLocStrProc_UStr (GS::UniString& str, short resID, short index, GSResModule module);


/*----------------------------------------------------------------------------
*/


/****************************************************************************/
/*																			*/
/*									MessageProc								*/
/*																			*/
/****************************************************************************/
/*
Called always when a message string should be sent to the output (dialog box,
report, debug)
----------------------------------------------------------------------------*/


typedef	GSErr	GSU_CALL	MessageProc (const char *str, const GS::Guid* guid);
typedef	GSErr	GSU_CALL	MessageProc_UStr (const GS::UniString& str, const GS::Guid* guid);


/*----------------------------------------------------------------------------
*/


//typedef	void	GSU_CALL	DialogMessageProc (const char *str);
//typedef	void	GSU_CALL	ReportMessageProc (const char *str);


/****************************************************************************/
/*																			*/
/*								ErrorStringProc								*/
/*																			*/
/****************************************************************************/
/*
Called when the engine want send the string of an error.
----------------------------------------------------------------------------*/


typedef	bool	GSU_CALL	ErrorStringProc (GSErrCode errnum, char *errstr);
typedef	bool	GSU_CALL	ErrorStringProc_UStr (GSErrCode errnum, GS::UniString& errstr);


/*----------------------------------------------------------------------------
*/


/****************************************************************************/
/*																			*/
/*								GetDateStrProc								*/
/*																			*/
/****************************************************************************/
/*
Called when the engine want write the string of the current date based on the
actual system settings
----------------------------------------------------------------------------*/


typedef	void	GSU_CALL	GetDateStrProc (GSTime actime, char *str);
typedef	void	GSU_CALL	GetDateStrProc_UStr (GSTime actime, GS::UniString& str);


/*----------------------------------------------------------------------------
*/


/****************************************************************************/
/*																			*/
/*								BeepProc									*/
/*																			*/
/****************************************************************************/
/*
Send a beep message.
----------------------------------------------------------------------------*/


typedef	void	GSU_CALL	BeepProc (short sind);


/*----------------------------------------------------------------------------
*/


/****************************************************************************/
/*																			*/
/*								GetTickProc									*/
/*																			*/
/****************************************************************************/
/*
Get the current number of ticks since the system last started up.
----------------------------------------------------------------------------*/


typedef	GSTicks	GSU_CALL	GetTickProc (void);


/*----------------------------------------------------------------------------
*/


/****************************************************************************/
/*																			*/
/*								GetTimeProc									*/
/*																			*/
/****************************************************************************/
/*
Called when the engine wants to know the current time based on the GSTime from
GSRoot
----------------------------------------------------------------------------*/


typedef	GSTime	GSU_CALL	GetTimeProc (void);


/*----------------------------------------------------------------------------
*/


/****************************************************************************/
/*																			*/
/*								GetTimeStrProc								*/
/*																			*/
/****************************************************************************/
/*
Called when the engine want write the string of the current time based on the
actual system settings
----------------------------------------------------------------------------*/


typedef	GS::UniString	GSU_CALL	GetTimeStrProc (void);


/*----------------------------------------------------------------------------
*/


#endif
