
// *****************************************************************************
//
// Declaration and implementation of Counter class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_COUNTER_HPP
#define GS_COUNTER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSDebug.hpp"



// --- Counter class -----------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Counter {

// Data members:
private:
	UInt32				m_value;

// Construction / destruction:
public:
	explicit Counter (UInt32 initialValue = 0L);
private:
			 Counter (const Counter&); // Disabled

// Operator overloading:
private:
	const Counter&		operator = (const Counter&); // Disabled
public:
	UInt32				operator ++ (int);	// Postfix increment
	UInt32				operator ++ ();		// Prefix increment
	UInt32				operator -- (int);	// Postfix decrement
	UInt32				operator -- ();		// Prefix decrement

						operator UInt32 () const;

};

////////////////////////////////////////////////////////////////////////////////
// Counter implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Counter::Counter (UInt32 initialValue) :
	m_value (initialValue)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ++ (postfix increment)
// -----------------------------------------------------------------------------

inline UInt32	Counter::operator ++ (int)
{
	return m_value ++;
}

// -----------------------------------------------------------------------------
// operator ++ (prefix increment)
// -----------------------------------------------------------------------------

inline UInt32	Counter::operator ++ ()
{
	return ++ m_value;
}

// -----------------------------------------------------------------------------
// operator -- (postfix decrement)
// -----------------------------------------------------------------------------

inline UInt32	Counter::operator -- (int)
{
	DBASSERT (m_value > 0L);
	return m_value --;
}

// -----------------------------------------------------------------------------
// operator -- (prefix decrement)
// -----------------------------------------------------------------------------

inline UInt32	Counter::operator -- ()
{
	DBASSERT (m_value > 0L);
	return -- m_value;
}

// -----------------------------------------------------------------------------
// operator UInt32
// -----------------------------------------------------------------------------

inline Counter::operator UInt32 () const
{
	return m_value;
}

}

#endif // GS_COUNTER_HPP
