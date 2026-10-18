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
	inline Pattern (const unsigned char newPattern[8]);

	inline bool IsEmpty () const;
	inline bool IsFull () const;
	inline bool operator== (const Pattern& other) const;
};


// --- Pattern class definition ------------------------------------------------

inline Pattern::Pattern ()
{
	for (UIndex i = 0; i < 8; ++i)
		pat[i] = 0;
}


inline Pattern::Pattern (const unsigned char newPattern[8])
{
	memcpy (pat, newPattern, 8 * sizeof (unsigned char));
}


inline bool Pattern::IsEmpty () const
{
	static unsigned char emptyPattern[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	static_assert (sizeof (emptyPattern) == sizeof (pat));

	return (memcmp (&pat, &emptyPattern, sizeof (pat)) == 0);
}


inline bool Pattern::IsFull () const
{
	static unsigned char fullPattern[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	static_assert (sizeof (fullPattern) == sizeof (pat));

	return (memcmp (&pat, &fullPattern, sizeof (pat)) == 0);
}


inline bool Pattern::operator== (const Pattern& other) const
{
	return (memcmp (&pat, &other.pat, sizeof (pat)) == 0);
}


}	// namespace Gfx

#endif
