/*==========================================================================**
**									enProc.h								**
**																			**
**					PROCEDURE TYPES FOR INPUT/OUTPUT ROUTINES				**
**==========================================================================*/

#ifndef		_enProc_H_
#define		_enProc_H_

#pragma once

#ifndef	GSUTILSEXPORT_H
	#include	"GSUtilsExport.h"
#endif

#include	"GSRoot.hpp"

typedef	bool	GSU_CALL		UserBreakProc (bool forward);

typedef	GSErr	GSU_CALL		WriteAuxProc (void* userDataPtr, Int32 len, const void* ptr);

typedef	GSPtr	GSU_CALL		GetAuxPtrProc (void* userDataPtr, Int32 offset);

#endif
