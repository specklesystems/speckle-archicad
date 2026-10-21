// *********************************************************************************************************************
// File:			DGGraphix.hpp
//
// Description:		Main include of the GRAPHISOFT DG Graphix Module
//
// Project:			GRAPHISOFT DG Graphix Module (DGGraphix)
//
// Namespace:
//
// Contact person:	NZ, DG
//
// SG compatible
// *********************************************************************************************************************

#ifndef	DGGRAPHIX_HPP
#define	DGGRAPHIX_HPP

#include	"DGGraphixDefinitions.hpp"
#include	"FileTypeManager.hpp"

// --- Module export defines -------------------------------------------------------------------------------------------

bool	DGGRAPHIX_DLL_EXPORT CCALL		DGGraphixInit (bool disableHwAcceleration = false);
void	DGGRAPHIX_DLL_EXPORT CCALL		DGGraphixExit ();


#endif
