
// *****************************************************************************
//
// Declaration of GS::UniString compatible string literal macros
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_UNISTRINGLITERALS_HPP
#define COMMUNICATION_UNISTRINGLITERALS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

	// from GSRoot
#include "UniString.hpp"



// --- Macro definitions -------------------------------------------------------

#if defined (WINDOWS)
#define US(string)	reinterpret_cast<const GS::UniChar::Layout*> (L##string)
#else
#define US(string)	reinterpret_cast<const GS::UniChar::Layout*> (u##string)

static_assert (sizeof (char16_t) == sizeof (GS::UniChar::Layout),
    "GS::UniChar::Layout and char16_t size mismatch.");
#endif


#endif // COMMUNICATION_UNISTRINGLITERALS_HPP
