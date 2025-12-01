
// *****************************************************************************
//
// Declaration and implementation of Initializer class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADINGINITIALIZER_HPP
#define GS_THREADINGINITIALIZER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Threading.hpp"



// --- Initializer class -------------------------------------------------------

namespace GS {
namespace Threading {

class Initializer {

// Construction / destruction:
public:
	 Initializer ();
private:
	 Initializer (const Initializer&); // Disabled
public:
	~Initializer ();

// Operator overloading:
private:
	const Initializer&	operator = (const Initializer&); // Disabled

};

////////////////////////////////////////////////////////////////////////////////
// Initializer inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Initializer::Initializer ()
{
	Threading::Initialize ();
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

inline Initializer::~Initializer ()
{
	Threading::Terminate ();
}

}
}

#endif // GS_THREADINGINITIALIZER_HPP
