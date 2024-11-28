// *********************************************************************************************************************
// File:			Graphix.hpp
//
// Description:		Main include of the GRAPHISOFT Graphix Module
//
// Project:			GRAPHISOFT Graphix Module (Graphix)
//
// Namespace:
//
// Contact person:	NZ, DG
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GRAPHIX_HPP
#define	GRAPHIX_HPP

#include	"GraphixDefinitions.hpp"
#include	"FileTypeManager.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

bool		GRAPHIX_DLL_EXPORT CCALL		GraphixInit (bool disableHwAcceleration = false, bool openGLEnabled = true, Int32* flags = nullptr);
void		GRAPHIX_DLL_EXPORT CCALL		GraphixExit ();

void		GRAPHIX_DLL_EXPORT CCALL		GraphixFillWithSupportedFileTypes (FTM::FileTypeManager& fileTypeManager);
GSErrCode	GRAPHIX_DLL_EXPORT CCALL		GetGraphixModuleOwnLocation (IO::Location& ownFileLoc);

bool		GRAPHIX_DLL_EXPORT CCALL		IsHardwareAccelerationAvailable ();
bool										IsHardwareAccelerationDisabled ();	// when force disabled; for internal use

#endif
