// *********************************************************************************************************************
// File:			DGDLLExport.h
//
// Description:		DGDLLExport include file of the GRAPHISOFT Dialog Manager
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	BL
// *********************************************************************************************************************

#ifndef DG_DLL_EXPORT_H
#define DG_DLL_EXPORT_H

#pragma once

#include "PlatformDLLExport.hpp"

#define DGCALLBACK	CCALL

#if defined (DG_DLL_COMPILE)
#define DG_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
#define DG_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif
