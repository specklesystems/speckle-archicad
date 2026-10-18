// *********************************************************************************************************************
// Description:		GRAPHISOFT Resource Manager
//
// Namespaces:		-
// Contact persons:	MM
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (RSTYPES_HPP)
#define	RSTYPES_HPP

#pragma once

// =====================================================================================================================
// Common constants and type definitions
// =====================================================================================================================

#include "Definitions.hpp"

typedef	GS::IntPtr		GSResModule;	// macen nem pointert, hanem 32biten 2db 16bites, 64biten 2 db 32bites int-et tarolunk benne.
typedef UInt32			GSResType;
typedef Int32			GSResID;

typedef bool	(CCALL *EnumResTypesCallback) (GSResType resType, GSResModule resModule, void* userData);
typedef bool	(CCALL *EnumResIDsCallback) (GSResID resID, GSResType resType, GSResModule resModule, void* userData);

enum RSFlags {
	RSF_MissingResourceAlert	= 0x00000001,
	RSF_DontLoadImages			= 0x00000002
};

enum ResStringType {
	RST_Localised	= 0,
	RST_Fixed		= 1
};


const GSResModule	InvalidResModule	= -1;
const GSResModule	AppResModule		= -3;
const GSResModule	SysResModule		= -4;


#if defined (macintosh)
typedef const struct __CFString * CFStringRef;
typedef const struct __CFURL * CFURLRef;
#endif


#endif
