
// *****************************************************************************
//
// Declaration and implementation of AtomicCounter class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_ATOMICCOUNTER_HPP
#define GS_ATOMICCOUNTER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Atomic.hpp"
#include "GSDebug.hpp"



// --- AtomicCounter class -----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT AtomicCounter {

// Data members:
private:
	UInt32 volatile			m_value;

// Construction / destruction:
public:
	explicit AtomicCounter (UInt32 initialValue = 0L);
private:
			 AtomicCounter (const AtomicCounter&); // Disabled

// Operator overloading:
private:
	const AtomicCounter&	operator = (const AtomicCounter&); // Disabled
public:
	UInt32					operator ++ (int);	// Postfix increment
	UInt32					operator ++ ();		// Prefix increment
	UInt32					operator -- (int);	// Postfix decrement
	UInt32					operator -- ();		// Prefix decrement

							operator UInt32 () const;

// Operations:
public:
	void					Set (UInt32 value);

	void					Swap (AtomicCounter& rhs);

};

////////////////////////////////////////////////////////////////////////////////
// AtomicCounter implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline AtomicCounter::AtomicCounter (UInt32 initialValue) :
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

inline UInt32	AtomicCounter::operator ++ (int)
{
	return static_cast<UInt32> (AtomicIncrement (reinterpret_cast<Int32 volatile*> (&m_value)) - 1);
}

// -----------------------------------------------------------------------------
// operator ++ (prefix increment)
// -----------------------------------------------------------------------------

inline UInt32	AtomicCounter::operator ++ ()
{
	return static_cast<UInt32> (AtomicIncrement (reinterpret_cast<Int32 volatile*> (&m_value)));
}

// -----------------------------------------------------------------------------
// operator -- (postfix decrement)
// -----------------------------------------------------------------------------

inline UInt32	AtomicCounter::operator -- (int)
{
	DBASSERT (m_value > 0L);

	return static_cast<UInt32> (AtomicDecrement (reinterpret_cast<Int32 volatile*> (&m_value)) + 1);
}

// -----------------------------------------------------------------------------
// operator -- (prefix decrement)
// -----------------------------------------------------------------------------

inline UInt32	AtomicCounter::operator -- ()
{
	DBASSERT (m_value > 0L);

	return static_cast<UInt32> (AtomicDecrement (reinterpret_cast<Int32 volatile*> (&m_value)));
}

// -----------------------------------------------------------------------------
// operator UInt32
// -----------------------------------------------------------------------------

inline AtomicCounter::operator UInt32 () const
{
	return m_value;
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Set
// -----------------------------------------------------------------------------

inline void		AtomicCounter::Set (UInt32 value)
{
	m_value = value;
}

// -----------------------------------------------------------------------------
// Swap
// -----------------------------------------------------------------------------

inline void		AtomicCounter::Swap (AtomicCounter& rhs)
{
	GS::UInt32 temp; temp = m_value; m_value = rhs.m_value; rhs.m_value = temp;
}

}

#endif // GS_ATOMICCOUNTER_HPP
