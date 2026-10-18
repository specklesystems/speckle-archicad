// *********************************************************************************************************************
// Description:		GXMedia Module Interface
//
// Module:
// Namespace:
// Contact person:
//
// *********************************************************************************************************************

#ifndef GXMEDIA_HPP
#define GXMEDIA_HPP

// --- Includes ----------------------------------------------------------------

#include	"GXMediaExport.hpp"
#include	"FileTypeManager.hpp"

// --- Main functions ----------------------------------------------------------

bool	GXMEDIA_DLL_EXPORT CCALL		GXMediaInit ();
void	GXMEDIA_DLL_EXPORT CCALL		GXMediaExit ();

void	GXMEDIA_DLL_EXPORT CCALL		GXMediaAddMovieFileTypeGroup (FTM::FileTypeManager& fileTypeManager, FTM::GroupID parentGroup);

#endif
