
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

#include "GSAssertCore.hpp"

#ifndef GS_BUILD_MODULE
// from Standard Library
#include <atomic>
#endif


// --- AtomicCounter class -----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT AtomicCounter {

// Data members:
private:
	std::atomic<UInt32>		m_value;

// Construction / destruction:
public:
	explicit AtomicCounter (UInt32 initialValue = 0U);

public:
	UInt32					operator ++ (int);	// Postfix increment
	UInt32					operator ++ ();		// Prefix increment
	UInt32					operator -- (int);	// Postfix decrement
	UInt32					operator -- ();		// Prefix decrement

							operator UInt32 () const;

// Operations:
public:
	void					Set (UInt32 value);

	UInt32					Exchange (UInt32 value);
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
	return m_value.fetch_add (1U, std::memory_order::acq_rel);
}

// -----------------------------------------------------------------------------
// operator ++ (prefix increment)
// -----------------------------------------------------------------------------

inline UInt32	AtomicCounter::operator ++ ()
{
	return m_value.fetch_add (1U, std::memory_order::acq_rel) + 1U;
}

// -----------------------------------------------------------------------------
// operator -- (postfix decrement)
// -----------------------------------------------------------------------------

inline UInt32	AtomicCounter::operator -- (int)
{
	UInt32 prev = m_value.fetch_sub (1U, std::memory_order::acq_rel);

	GSASSERT_DB (prev != 0U);

	return prev;
}

// -----------------------------------------------------------------------------
// operator -- (prefix decrement)
// -----------------------------------------------------------------------------

inline UInt32	AtomicCounter::operator -- ()
{
	UInt32 prev = m_value.fetch_sub (1U, std::memory_order::acq_rel);

	GSASSERT_DB (prev != 0U);

	return prev - 1U;
}

// -----------------------------------------------------------------------------
// operator UInt32
// -----------------------------------------------------------------------------

inline AtomicCounter::operator UInt32 () const
{
	return m_value.load (std::memory_order_relaxed);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Set
// -----------------------------------------------------------------------------

inline void		AtomicCounter::Set (UInt32 value)
{
	m_value.store (value, std::memory_order_relaxed);
}

// -----------------------------------------------------------------------------
// Exchange
// -----------------------------------------------------------------------------

inline UInt32		AtomicCounter::Exchange (UInt32 value)
{
	return m_value.exchange (value, std::memory_order_relaxed);
}

}

#endif // GS_ATOMICCOUNTER_HPP
