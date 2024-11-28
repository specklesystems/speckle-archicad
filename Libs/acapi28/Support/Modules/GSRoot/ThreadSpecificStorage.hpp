
// *****************************************************************************
//
// Declaration and implementation of ThreadSpecificStorage<T> class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADSPECIFICSTORAGE_HPP
#define GS_THREADSPECIFICSTORAGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSDebug.hpp"
#include "ThreadSpecificStorageImpl.hpp"



// --- ThreadSpecificStorage<T> class ------------------------------------------

namespace GS {

template<typename T>
class ThreadSpecificStorage {

#if defined (DEBUVERS)
	static char ST[(sizeof (T) <= sizeof (void*)) ? 1 : -1] GCC_UNUSED;
#endif

// Data members:
private:
	ThreadSpecificStorageImpl*		m_impl;

// Construction / destruction:
public:
			 ThreadSpecificStorage ();
			 ThreadSpecificStorage (const ThreadSpecificStorage<T>& rhs);
	virtual ~ThreadSpecificStorage ();

// Operator overloading:
public:
	const ThreadSpecificStorage<T>&	operator = (const ThreadSpecificStorage<T>& rhs);

// Operations:
public:
	T								Get () const;
	void							Set (T value);

};

////////////////////////////////////////////////////////////////////////////////
// ThreadSpecificStorage implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<typename T>
inline ThreadSpecificStorage<T>::ThreadSpecificStorage () :
	m_impl (ThreadSpecificStorageImpl::Create ())
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<typename T>
inline ThreadSpecificStorage<T>::ThreadSpecificStorage (const ThreadSpecificStorage<T>& rhs) :
	m_impl (rhs.m_impl->Clone ())
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<typename T>
inline ThreadSpecificStorage<T>::~ThreadSpecificStorage ()
{
	delete m_impl;
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T>
inline const ThreadSpecificStorage<T>&	ThreadSpecificStorage<T>::operator = (const ThreadSpecificStorage<T>& rhs)
{
	if (m_impl != rhs.m_impl) {
		if (m_impl != nullptr) {
			delete m_impl;
		}
		m_impl = rhs.m_impl->Clone ();
	}

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline T	ThreadSpecificStorage<T>::Get () const
{
#if defined (_MSC_VER)
#pragma warning(push)
#pragma warning (disable: 4311 4800)
#endif
	return T (m_impl->Get ());
#if defined (_MSC_VER)
#pragma warning(pop)
#endif
}

// -----------------------------------------------------------------------------
// Set
// -----------------------------------------------------------------------------

template<typename T>
inline void		ThreadSpecificStorage<T>::Set (T value)
{
#if defined (_MSC_VER)
#pragma warning(push)
#pragma warning (disable: 4312 4800)
#endif
	m_impl->Set (IntPtr (value));
#if defined (_MSC_VER)
#pragma warning(pop)
#endif
}

}

#endif // GS_THREADSPECIFICSTORAGE_HPP
