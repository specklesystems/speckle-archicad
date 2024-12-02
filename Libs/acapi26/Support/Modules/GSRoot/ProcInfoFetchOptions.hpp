
// *****************************************************************************
//
// Declaration of ProcessInfoFetchOptions class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSINFOFETCHOPTIONS_HPP
#define GS_PROCESSINFOFETCHOPTIONS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "UniString.hpp"



// --- ProcessInfoFetchOptions class -------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ProcessInfoFetchOptions {

// Data members:
private:
	bool							m_fetchCommandLineArgs;

// Construction / destruction:
public:
	ProcessInfoFetchOptions ();

// Operator overloading:
public:
	bool							operator == (const ProcessInfoFetchOptions& rhs) const;
	bool							operator != (const ProcessInfoFetchOptions& rhs) const;

// Operations:
public:
	void							SetFetchCommandLineArgs (bool fetchCommandLineArgs);
	bool							GetFetchCommandLineArgs () const;

	GS::UniString					ToString () const;

	void							Swap (ProcessInfoFetchOptions& rhs);

// Static operations:
public:
	static ProcessInfoFetchOptions	GetDefault ();

};

////////////////////////////////////////////////////////////////////////////////
// ProcessInfoFetchOptions inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ProcessInfoFetchOptions::ProcessInfoFetchOptions () :
	m_fetchCommandLineArgs (false)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ProcessInfoFetchOptions::operator == (const ProcessInfoFetchOptions& rhs) const
{
	if (this != &rhs) {
		return (m_fetchCommandLineArgs == rhs.m_fetchCommandLineArgs);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ProcessInfoFetchOptions::operator != (const ProcessInfoFetchOptions& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetFetchCommandLineArgs
// -----------------------------------------------------------------------------

inline void		ProcessInfoFetchOptions::SetFetchCommandLineArgs (bool fetchCommandLineArgs)
{
	m_fetchCommandLineArgs = fetchCommandLineArgs;
}

// -----------------------------------------------------------------------------
// GetFetchCommandLineArgs
// -----------------------------------------------------------------------------

inline bool		ProcessInfoFetchOptions::GetFetchCommandLineArgs () const
{
	return m_fetchCommandLineArgs;
}

}

#endif // GS_PROCESSINFOFETCHOPTIONS_HPP