// *****************************************************************************
// Initialize the LibPartFile module
//
// Namespace:		-
// Contact person:	MM
//
// [SG compatible]
// *****************************************************************************

#ifndef	INITLIBPARTFILE_HPP
#define	INITLIBPARTFILE_HPP

#pragma once


#include "GSRoot.hpp"
#include "GSMSectionsExport.h"


typedef struct {
} GSMSectionsCallBacks;


GSMSECTIONS_DLL_EXPORT void InitLibPartFile (const GSMSectionsCallBacks& callbacks, GS::UniString comdDefaultSet);

#endif
