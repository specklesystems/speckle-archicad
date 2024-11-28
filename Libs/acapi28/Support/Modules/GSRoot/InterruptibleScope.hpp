
// *****************************************************************************
//
// Declaration of InterruptibleScope class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_INTERRUPTIBLESCOPE_HPP
#define GS_INTERRUPTIBLESCOPE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Interruptible.hpp"
#include "Thread.hpp"



// --- InterruptibleScope class ------------------------------------------------

namespace GS {

class [[nodiscard]] InterruptibleScope {

// Data members:
private:
	Interruptible*				m_interruptible;

// Construction / destruction:
public:
	explicit InterruptibleScope (Interruptible& interruptible);
private:
			 InterruptibleScope (const InterruptibleScope&); // Disabled
public:
			~InterruptibleScope ();

// Operator overloading:
private:
	const InterruptibleScope&	operator = (const InterruptibleScope&); // Disabled

};

////////////////////////////////////////////////////////////////////////////////
// InterruptibleScope inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline InterruptibleScope::InterruptibleScope (Interruptible& interruptible) :
	m_interruptible (&interruptible)
{
	Thread::GetCurrent ().BlockOn (m_interruptible);
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

inline InterruptibleScope::~InterruptibleScope ()
{
	Thread::GetCurrent ().BlockOn (nullptr);
}

}

#endif // GS_INTERRUPTIBLESCOPE_HPP
