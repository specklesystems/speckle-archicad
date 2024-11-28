
// *****************************************************************************
//
// Declaration of Timeout class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_TIMEOUT_HPP
#define GS_TIMEOUT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"



// --- Timeout class -----------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Timeout {

// Constants:
public:
	static const UInt32		Infinite	= UInt32 (-1);

// Data members:
private:
	UInt32		m_milliseconds;

// Construction / destruction:
public:
	Timeout (UInt32 hours, UInt32 minutes, UInt32 seconds, UInt32 milliseconds = 0);

// Operations overloading:
public:
	UInt32		operator ()() const;

};

////////////////////////////////////////////////////////////////////////////////
// Timeout inlines

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ()()
// -----------------------------------------------------------------------------

inline UInt32	Timeout::operator ()() const
{
	return m_milliseconds;
}

}

#endif // GS_TIMEOUT_HPP
