// *********************************************************************************************************************
// Description:		GRAPHISOFT Debug Manager
//
// Module:			GSRoot
// Namespace:		-
// Contact person:	MB
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GSLOGUTILITIES_HPP
#define	GSLOGUTILITIES_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"FastLogger.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------


// --- Debug functions -------------------------------------------------------------------------------------------------

GSROOT_DLL_EXPORT void		DBAppendCallStack (class GS::FastLogger::LogComposer* logComposer);

#endif
