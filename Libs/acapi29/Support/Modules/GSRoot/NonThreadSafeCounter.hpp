
// *****************************************************************************
//
// Declaration and implementation of NonThreadSafeCounter class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ, SN
//
// *****************************************************************************

#ifndef GS_NONTHREADSAFECOUNTER_HPP
#define GS_NONTHREADSAFECOUNTER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSDebug.hpp"
#include "ThreadingDebug.hpp"



// --- Counter class -----------------------------------------------------------

namespace GS {

class NonThreadSafeCounter: public NonThreadSafeClass {

// Data members:
private:
	UInt32				m_value;

// Construction / destruction:
public:
	explicit NonThreadSafeCounter (UInt32 initialValue = 0L);
private:
			 NonThreadSafeCounter (const NonThreadSafeCounter&); // Disabled

// Operator overloading:
private:
	const NonThreadSafeCounter&		operator = (const NonThreadSafeCounter&); // Disabled
public:
	UInt32				operator ++ (int);	// Postfix increment
	UInt32				operator ++ ();		// Prefix increment
	UInt32				operator -- (int);	// Postfix decrement
	UInt32				operator -- ();		// Prefix decrement

						operator UInt32 () const;

};

////////////////////////////////////////////////////////////////////////////////
// NonThreadSafeCounter implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline NonThreadSafeCounter::NonThreadSafeCounter (UInt32 initialValue) :
	m_value (initialValue)
{
	FUNCTIONCALLEDCHECKTHREAD ();
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ++ (postfix increment)
// -----------------------------------------------------------------------------

inline UInt32	NonThreadSafeCounter::operator ++ (int)
{
	FUNCTIONCALLEDCHECKTHREAD ();

	return m_value ++;
}

// -----------------------------------------------------------------------------
// operator ++ (prefix increment)
// -----------------------------------------------------------------------------

inline UInt32	NonThreadSafeCounter::operator ++ ()
{
	FUNCTIONCALLEDCHECKTHREAD ();

	return ++ m_value;
}

// -----------------------------------------------------------------------------
// operator -- (postfix decrement)
// -----------------------------------------------------------------------------

inline UInt32	NonThreadSafeCounter::operator -- (int)
{
	FUNCTIONCALLEDCHECKTHREAD ();

	DBASSERT (m_value > 0L);
	return m_value --;
}

// -----------------------------------------------------------------------------
// operator -- (prefix decrement)
// -----------------------------------------------------------------------------

inline UInt32	NonThreadSafeCounter::operator -- ()
{
	FUNCTIONCALLEDCHECKTHREAD ();

	DBASSERT (m_value > 0L);
	return -- m_value;
}

// -----------------------------------------------------------------------------
// operator UInt32
// -----------------------------------------------------------------------------

inline NonThreadSafeCounter::operator UInt32 () const
{
	return m_value;
}

}

#endif // GS_NONTHREADSAFECOUNTER_HPP
