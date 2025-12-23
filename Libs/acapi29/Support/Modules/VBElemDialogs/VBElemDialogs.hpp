// *********************************************************************************************************************
// VBElemDialogs Module - Virtual Building Element Dialogs
//
// Module:			VBElemDialogs
// Namespace:		TBUI
// Contact person:	PT
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (VBELEMDIALOGS_H)
#define VBELEMDIALOGS_H

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------

// own
#include "VBElemDialogsExport.hpp"


namespace TBUI {

// --- Predeclarations	------------------------------------------------------------------------------------------------

struct CallBackTbl;


// --- Function declarations -------------------------------------------------------------------------------------------

VBELEMDIALOGS_DLL_EXPORT GSErrCode		InitializeModule (const TBUI::CallBackTbl* callbacks);
VBELEMDIALOGS_DLL_EXPORT GSErrCode		TerminateModule (void);


} 	// namespace TBUI

#endif
