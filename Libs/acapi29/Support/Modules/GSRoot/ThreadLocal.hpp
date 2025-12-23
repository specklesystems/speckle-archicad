
// *****************************************************************************
//
// Declaration and implementation of ThreadLocal<T> class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADLOCAL_HPP
#define GS_THREADLOCAL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadLocalImpl.hpp"



// --- ThreadLocal<T> class ----------------------------------------------------

namespace GS {

template<class T, class Initializator = ThreadLocalImpl::DefaultInitializator<T> >
class ThreadLocal : private ThreadLocalImpl {

// Type definitions
public:
	typedef ThreadLocalImpl::DefaultInitializator<T> DefaultInitializator;
	typedef ThreadLocalImpl::NullInitializator<T> NullInitializator;

// Construction / destruction:
public:
			 ThreadLocal ();
			 ThreadLocal (const ThreadLocal& rhs);
	virtual ~ThreadLocal ();

// Operator overloading:
public:
	const ThreadLocal&				operator = (const ThreadLocal& rhs);

// Operations:
public:
	const T&						Get () const;
	T&								Get ();
	void							Set (const T& value);
	void							Clear ();

// Static implementation:
private:
	static ThreadLocalValueBase*	CreateValue ();

};

////////////////////////////////////////////////////////////////////////////////
// ThreadLocal implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline ThreadLocal<T, Initializator>::ThreadLocal () :
	ThreadLocalImpl ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline ThreadLocal<T, Initializator>::ThreadLocal (const ThreadLocal& rhs) :
	ThreadLocalImpl (rhs)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline ThreadLocal<T, Initializator>::~ThreadLocal ()
{
	// Empty destructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline const ThreadLocal<T, Initializator>&		ThreadLocal<T, Initializator>::operator = (const ThreadLocal& rhs)
{
	ThreadLocalImpl::operator = (rhs);

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline const T&		ThreadLocal<T, Initializator>::Get () const
{
	return static_cast<ThreadLocalValue<T>&> (GetValue (CreateValue)).Get ();
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline T&	ThreadLocal<T, Initializator>::Get ()
{
	return static_cast<ThreadLocalValue<T>&> (GetValue (CreateValue)).Get ();
}

// -----------------------------------------------------------------------------
// Set
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline void		ThreadLocal<T, Initializator>::Set (const T& value)
{
	static_cast<ThreadLocalValue<T>&> (GetValue (CreateValue)).Set (value);
}

// -----------------------------------------------------------------------------
// Clear
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline void		ThreadLocal<T, Initializator>::Clear ()
{
	ThreadLocalImpl::Clear ();
}

////////////////////////////////////////////////////////////////////////////////
// Static implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// CreateValue
// -----------------------------------------------------------------------------

template<class T, class Initializator>
inline ThreadLocalValueBase*	ThreadLocal<T, Initializator>::CreateValue ()
{
	ThreadLocalValue<T>* tlv = new ThreadLocalValue<T> ();

	try {
		Initializator () (tlv->Get ());
	}
	catch (...) {
		delete tlv;
		throw;
	}

	return tlv;
}

}

#endif // GS_THREADLOCAL_HPP
