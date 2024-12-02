// *********************************************************************************************************************
// File:			TrackerDefinitions.hpp
//
// Description:		Common constants of the GRAPHISOFT Tracker Module
//
// Project:			GRAPHISOFT Tracker Module (TrackerLib)
//
// Namespace:		Tracking
//
// Contact person:	BM, DG, NZ
//
// SG compatible
// *********************************************************************************************************************

#ifndef	TRACKERDEFINITIONS_HPP
#define	TRACKERDEFINITIONS_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "PlatformDLLExport.hpp"


// --- Module export defines -------------------------------------------------------------------------------------------

#if defined (TRACKER_DLL_COMPILE)
	#define TRACKER_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
	#define TRACKER_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

namespace Tracking {

const short				IconLeftGap		= 3;

}

#endif
