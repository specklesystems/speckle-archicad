
// *****************************************************************************
//
//							Page Heap query functions
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	EP
//
// *****************************************************************************

#ifdef WINDOWS
#ifndef GS_PAGEHEAPWIN_HPP
#define GS_PAGEHEAPWIN_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"


namespace GS {
namespace PageHeap {

extern bool isInitialized;
extern bool isEnabled;

void Initialize (void);


inline bool IsEnabled (void)
{
	if (!isInitialized)
		Initialize ();

	return isEnabled;
}

}	// namespace PageHeap
}	// namespace GS

#endif // GS_PAGEHEAPWIN_HPP
#endif // WINDOWS