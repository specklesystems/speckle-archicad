
// *****************************************************************************
//
// Declaration and implementation of FifoThreadImplList class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADIMPLLIST_HPP
#define GS_THREADIMPLLIST_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "PagedArray.hpp"
#include "ThreadImpl.hpp"



// --- FifoThreadImplList class ------------------------------------------------

namespace GS {

class FifoThreadImplList {

// Type definitions:
public:
	typedef PagedArray<ThreadImpl*>::ConstIterator ConstIterator;
	typedef PagedArray<ThreadImpl*>::Iterator Iterator;

// Data members:
private:
	PagedArray<ThreadImpl*>	m_threads;

// Construction / destruction:
public:
	FifoThreadImplList ();

// Operator overloading:
public:
	const ThreadImpl*		operator [] (UIndex index) const;
	ThreadImpl*				operator [] (UIndex index);

// Operations:
public:
	USize					GetSize () const;

	ConstIterator			Enumerate () const;
	Iterator				Enumerate ();

	void					Add (ThreadImpl* thread);
	void					Remove (ThreadImpl* thread);
	void					Clear ();

};

////////////////////////////////////////////////////////////////////////////////
// FifoThreadImplList implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline FifoThreadImplList::FifoThreadImplList () :
	m_threads ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator []
// -----------------------------------------------------------------------------

inline const ThreadImpl*	FifoThreadImplList::operator [] (UIndex index) const
{
	return m_threads [index];
}

// -----------------------------------------------------------------------------
// operator []
// -----------------------------------------------------------------------------

inline ThreadImpl*	FifoThreadImplList::operator [] (UIndex index)
{
	return m_threads [index];
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetSize
// -----------------------------------------------------------------------------

inline USize	FifoThreadImplList::GetSize () const
{
	return m_threads.GetSize ();
}

// -----------------------------------------------------------------------------
// Enumerate
// -----------------------------------------------------------------------------

inline FifoThreadImplList::ConstIterator	FifoThreadImplList::Enumerate () const
{
	return m_threads.Enumerate ();
}

// -----------------------------------------------------------------------------
// Enumerate
// -----------------------------------------------------------------------------

inline FifoThreadImplList::Iterator		FifoThreadImplList::Enumerate ()
{
	return m_threads.Enumerate ();
}

// -----------------------------------------------------------------------------
// Add
// -----------------------------------------------------------------------------

inline void		FifoThreadImplList::Add (ThreadImpl* thread)
{
	DBASSERT (thread != nullptr);
	m_threads.Push (thread);
}

// -----------------------------------------------------------------------------
// Remove
// -----------------------------------------------------------------------------

inline void		FifoThreadImplList::Remove (ThreadImpl* thread)
{
	DBASSERT (thread != nullptr);
	m_threads.DeleteFirst (thread);
}

// -----------------------------------------------------------------------------
// Clear
// -----------------------------------------------------------------------------

inline void		FifoThreadImplList::Clear ()
{
	m_threads.Clear ();
}

}

#endif // GS_THREADIMPLLIST_HPP
