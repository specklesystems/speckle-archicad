// *****************************************************************************
// File:			Color.hpp
//
// Description:		Color class
//
// Project:			GSRoot
//
// Namespace:		Gfx
//
// Contact person:	NZ
//
// SG compatible
// *****************************************************************************

#ifndef PATTERN_HPP
#define PATTERN_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"

namespace Gfx {

// --- Pattern class declaration -----------------------------------------------

class Pattern
{
public:
	unsigned char pat[8];

public:
	inline Pattern ();
	inline Pattern (const unsigned char pat[8]);

	inline bool IsEmpty () const;
	inline bool IsFull () const;
};


// --- Pattern class definition ------------------------------------------------

inline Pattern::Pattern ()
{
#ifdef GS_64BIT
	*((UInt64*) &pat[0]) = 0;
#else
	*((UInt32*) &pat[0]) = 0;
	*((UInt32*) &pat[4]) = 0;
#endif
}

inline Pattern::Pattern (const unsigned char pat[8])
{
	memcpy (this->pat, pat, 8 * sizeof (unsigned char));
}

inline bool Pattern::IsEmpty () const
{
#ifdef GS_64BIT
	return (*((UInt64*) &pat[0]) == 0x0);
#else
	return (*((UInt32*) &pat[0]) == 0x0) && (*((UInt32*) &pat[4]) == 0x0);
#endif
}

inline bool Pattern::IsFull () const
{
#ifdef GS_64BIT
	return (*((UInt64*) &pat[0]) == 0xFFFFFFFFFFFFFFFF);
#else
	return (*((UInt32*) &pat[0]) == 0xFFFFFFFF) && (*((UInt32*) &pat[4]) == 0xFFFFFFFF);
#endif
}

}	// namespace Gfx

#endif
