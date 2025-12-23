
// *****************************************************************************
//
// Declaration of ThreadLocalKey class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADLOCALKEY_HPP
#define GS_THREADLOCALKEY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "HashCommon.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class ThreadLocalImpl;

}



// --- ThreadLocalKey class ----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadLocalKey {

// Data members:
private:
	ThreadLocalImpl*		m_threadLocal;
	UInt32					m_sequence;

// Construction / destruction:
public:
	explicit ThreadLocalKey (ThreadLocalImpl* threadLocal = nullptr, UInt32 sequence = 0);

// Operator overloading:
public:
	bool					operator == (const ThreadLocalKey& rhs) const;
	bool					operator != (const ThreadLocalKey& rhs) const;

// Operations:
public:
	ULong					GenerateHashValue () const;


// Static implementation:
public:
	static ThreadLocalKey	Create (ThreadLocalImpl* threadLocal);

};

////////////////////////////////////////////////////////////////////////////////
// ThreadLocalKey inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ThreadLocalKey::ThreadLocalKey (ThreadLocalImpl* threadLocal, UInt32 sequence) :
	m_threadLocal (threadLocal),
	m_sequence (sequence)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ThreadLocalKey::operator == (const ThreadLocalKey& rhs) const
{
	return (m_threadLocal == rhs.m_threadLocal &&
			m_sequence == rhs.m_sequence);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ThreadLocalKey::operator != (const ThreadLocalKey& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GenerateHashValue
// -----------------------------------------------------------------------------

inline ULong	ThreadLocalKey::GenerateHashValue () const
{
	ULong hashValue = 17;

	hashValue = hashValue * 37 + GS::CalculateHashValue (m_threadLocal);
	hashValue = hashValue * 37 + GS::CalculateHashValue (m_sequence);

	return hashValue;
}

}


#endif // GS_THREADLOCALKEY_HPP
