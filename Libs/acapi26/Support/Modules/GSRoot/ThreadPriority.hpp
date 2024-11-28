
// *****************************************************************************
//
// Declaration and implementation of ThreadPriority class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	PP, SN
//
// *****************************************************************************

#ifndef GS_THREADPRIORITY_HPP
#define GS_THREADPRIORITY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"



// --- ThreadPriority class ----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadPriority {

// Type definitions
public:
	enum {
		Min				= 1,
		BelowNormal		= 3,
		Normal			= 5,
		AboveNormal		= 7,
		Max				= 10
	};

// Data members:
private:
	Int32	m_priority;

// Construction / destruction:
public:
	ThreadPriority (Int32 priority = Normal);

// Operator overloading:
public:
	bool		operator == (Int32 priority) const;
	bool		operator != (Int32 priority) const;
				
				operator Int32 () const;

};

////////////////////////////////////////////////////////////////////////////////
// ThreadPriority implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ThreadPriority::ThreadPriority (Int32 priority /*= Normal*/)
{
	if (priority < Min || priority > Max)
		throw IllegalArgumentException ("Invalid priority value.", __FILE__, __LINE__);
	
	m_priority = priority;
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ThreadPriority::operator == (Int32 priority) const
{
	return (m_priority == priority);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ThreadPriority::operator != (Int32 priority) const
{
	return (m_priority != priority);
}

// -----------------------------------------------------------------------------
// operator Int32
// -----------------------------------------------------------------------------

inline ThreadPriority::operator Int32 () const
{
	return m_priority;
}

}

#endif // GS_THREADPRIORITY_HPP
