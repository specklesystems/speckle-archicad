/****************************************************************************/
/*																			*/
/*							PROTOTYPES FOR OU... ROUTINES					*/
/*																			*/
/****************************************************************************/

#ifndef _OU_H_
#define _OU_H_

#pragma once

#include	"enProc.h"
#include	"comProc.h"

#include	"UniString.hpp"
#include	"BM.hpp"

#ifndef	GSUTILSEXPORT_H
	#include	"GSUtilsExport.h"
#endif

namespace GS {

	class OProtocol;
	class OChannel;

}
using GS::UInt64;			// temporary

/*================================	CONSTANTS	============================*/

enum { LineLength = 511 };

/*================================	  TYPES     ============================*/

typedef	struct {
	MessageProc_UStr*			warning3D;
	MessageProc_UStr*			error3D;
	MessageProc_UStr*			report3D;
	MessageProc_UStr*			debug3D;
	GetFixStrProc_UStr*			getfixstr;
	GetLocStrProc_UStr*			getlocstr;
	ErrorStringProc_UStr*		errorstr;
	GetDateStrProc_UStr*		getdatestr;
	BeepProc*					beep;
	GetTickProc*				gettick;
	GetTimeProc*				gettime;
	GetTimeStrProc*				gettimestr;
} OU_GLOBALS;

/*================================	PROTOTYPES	============================*/

GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUSetEnv (const OU_GLOBALS* ouCallBacks);

GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUGetEnv (OU_GLOBALS* ouCallBacks);

GSUTILS_DLL_EXPORT
short		GSU_CALL	OUSetReportState (short	reportState);

GSUTILS_DLL_EXPORT		GetLocStrProc		OUGetLocString;
GSUTILS_DLL_EXPORT_CPP	GetLocStrProc_UStr	OUGetLocString;
GSUTILS_DLL_EXPORT		GetFixStrProc		OUGetFixString;
GSUTILS_DLL_EXPORT_CPP	GetFixStrProc_UStr	OUGetFixString;

GSUTILS_DLL_EXPORT		MessageProc			OUWarningStr;
GSUTILS_DLL_EXPORT_CPP	MessageProc_UStr	OUWarningStr;
GSUTILS_DLL_EXPORT		MessageProc			OUErrorStr;
GSUTILS_DLL_EXPORT_CPP	MessageProc_UStr	OUErrorStr;
GSUTILS_DLL_EXPORT		MessageProc			OUReport;
GSUTILS_DLL_EXPORT_CPP	MessageProc_UStr	OUReport;
GSUTILS_DLL_EXPORT		MessageProc			OUDebug;
GSUTILS_DLL_EXPORT_CPP	MessageProc_UStr	OUDebug;

GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUsysError (short code, GSErrCode sysErr, const GS::Guid* guid = nullptr);
GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUcgError (short code, short cgcode);

GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUError (short code, const GS::Guid* guid = nullptr);
GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUWarning (short code, const GS::Guid* guid = nullptr);
GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUcgWarning (short code, short cgcode);
GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUinError (short code, const char *buf);
GSUTILS_DLL_EXPORT
GSErr		GSU_CALL	OUcgErrInd (Int32 errcode);

GSUTILS_DLL_EXPORT		BMAbortProc OUmemError;

GSUTILS_DLL_EXPORT
void		GSU_CALL	OUBeep (short sind);

/* OR.h */

GSUTILS_DLL_EXPORT
GSTicks		GSU_CALL			OUGetTick (void);	/*mm-GSTicks*/
GSUTILS_DLL_EXPORT
GSTime		GSU_CALL			OUGetTime (void);	/*mm-GSTime**/
GSUTILS_DLL_EXPORT_CPP
GS::UniString	GSU_CALL		OUGetTimeStr (void);	/*mm-const*/
GSUTILS_DLL_EXPORT
void		GSU_CALL			OUReportDateStr (GSTime actime, char *str);	/*mm-GSTime*/
GSUTILS_DLL_EXPORT_CPP
void		GSU_CALL			OUReportDateStr (GSTime actime, GS::UniString& str);	/*mm-GSTime*/
GSUTILS_DLL_EXPORT
bool		GSU_CALL			OUSystemErrorString (GSErrCode errnum, char *errstr);
GSUTILS_DLL_EXPORT_CPP
bool		GSU_CALL			OUSystemErrorString (GSErrCode errnum, GS::UniString& errstr);

/****************************************************************************/
/*																			*/
/*								ReportChannel								*/
/*																			*/
/****************************************************************************/

class GSUTILS_DLL_EXPORT_CPP ReportChannel: public GS::OChannel
{
private:
	char	line [LineLength + 1];
	UIndex	j;

public:
	ReportChannel ();

	virtual GSErrCode	WriteBin (const char* source, USize nOfCharToWrite, USize* written = nullptr) override;
	virtual	GSErrCode	DirectOutputAccess (UIndex startPosition, char** output, USize* accessibleDataSize) override;
	virtual GSErrCode   GetOutputPosition (UInt64* pos) const override;

	virtual	void		SetDefaultOutputProtocol (void) override;

	virtual GSErrCode	PushMark	(void) override;
	virtual GSErrCode	PopMark		(void) override;
	virtual USize		GetOffset	(void) const override;
	virtual void		ResetOffset	(void) override;

	virtual GSErrCode	GetOutputStatus	  (void) const override;
	virtual void		ResetOutputStatus (void) override;
};


extern GSResModule gLocStringModule;
extern GSResModule gFixStringModule;

#endif
