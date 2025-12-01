
// *****************************************************************************
//
// Declaration of ProcessInfoFetchOptionsBuilder class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_PROCESSINFOFETCHOPTIONSBUILDER_HPP
#define GS_PROCESSINFOFETCHOPTIONSBUILDER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ProcInfoFetchOptions.hpp"



// --- ProcessInfoFetchOptionsBuilder class ------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ProcessInfoFetchOptionsBuilder {

// Data members:
private:
	ProcessInfoFetchOptions				m_fetchOptions;
	
// Operations:
public:
	ProcessInfoFetchOptionsBuilder&		FetchCommandLineArgs ();

	ProcessInfoFetchOptionsBuilder&		FetchAll ();

	ProcessInfoFetchOptions				Build ();

};

////////////////////////////////////////////////////////////////////////////////
// ProcessInfoFetchOptionsBuilder inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// FetchCommandLineArgs
// -----------------------------------------------------------------------------

inline ProcessInfoFetchOptionsBuilder&	ProcessInfoFetchOptionsBuilder::FetchCommandLineArgs ()
{
	m_fetchOptions.SetFetchCommandLineArgs (true);

	return *this;
}
// -----------------------------------------------------------------------------
// FetchAll
// -----------------------------------------------------------------------------

inline ProcessInfoFetchOptionsBuilder&	ProcessInfoFetchOptionsBuilder::FetchAll ()
{
	m_fetchOptions.SetFetchCommandLineArgs (true);

	return *this;
}

}

#endif // GS_PROCESSINFOFETCHOPTIONSBUILDER_HPP