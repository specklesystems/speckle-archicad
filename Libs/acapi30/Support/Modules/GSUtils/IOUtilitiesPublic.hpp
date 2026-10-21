// *********************************************************************************************************************
// Description:		Utilities based on the InputOutput module
//
// Module:			ARCHICAD / PlotMaker
// Namespace:		IOUtil
// Contact person:	MM
//
// SG compatible
// *********************************************************************************************************************

#ifndef	IOUTILITIESPUBLIC_HPP
#define	IOUTILITIESPUBLIC_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include <stdio.h>

#include "GSUtilsExport.h"

// from InputOutput
#include	"Location.hpp"

namespace IOUtil {

GSUTILS_DLL_EXPORT
bool			CanCreateOrWriteFile (const IO::Location& location);

GSUTILS_DLL_EXPORT
bool			FileExists			 (const IO::Location& location);

}	// namespace

#endif
