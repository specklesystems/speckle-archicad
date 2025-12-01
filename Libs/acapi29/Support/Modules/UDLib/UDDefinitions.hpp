// *********************************************************************************************************************
// File:			UDDefinitions.hpp
//
// Description:		Common constants of the GRAPHISOFT User Dialog Module
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	BM
//
// SG compatible
// *********************************************************************************************************************

#ifndef	UDDEFINITIONS_HPP
#define	UDDEFINITIONS_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"


// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (UD_DLL_COMPILE)
	#define UD_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define UD_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif

#endif
