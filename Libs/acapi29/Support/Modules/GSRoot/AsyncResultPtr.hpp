
// *****************************************************************************
//
// Declaration of AsyncResultPtr class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_ASYNCRESULTPTR_HPP
#define GS_ASYNCRESULTPTR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "AsyncResult.hpp"
#include "CountedPtr.hpp"



// --- AsycnResultPtr class ----------------------------------------------------

namespace GS {

class AsyncResultPtr : public CountedPtr<AsyncResult, AtomicCounter> {

// Construction / destruction:
public:
	AsyncResultPtr ();
	AsyncResultPtr (AsyncResult* result);
	template<typename T, typename CounterT>
	AsyncResultPtr (const CountedPtr<T, CounterT>& ptr);

// Operator overloading:
public:
	const AsyncResultPtr&	operator = (AsyncResult* result);
	template<typename T, typename CounterT>
	const AsyncResultPtr&	operator = (const CountedPtr<T, CounterT>& ptr) ;

};

////////////////////////////////////////////////////////////////////////////////
// AsyncResultPtr implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline AsyncResultPtr::AsyncResultPtr () :
	CountedPtr<AsyncResult, AtomicCounter> ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline AsyncResultPtr::AsyncResultPtr (AsyncResult* result) :
	CountedPtr<AsyncResult, AtomicCounter> (result)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline AsyncResultPtr::AsyncResultPtr (const CountedPtr<T, CounterT>& ptr) :
	CountedPtr<AsyncResult, AtomicCounter> (ptr)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const AsyncResultPtr&	AsyncResultPtr::operator = (AsyncResult* result)
{
	CountedPtr<AsyncResult, AtomicCounter>::operator = (result);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline const AsyncResultPtr&	AsyncResultPtr::operator = (const CountedPtr<T, CounterT>& ptr)
{
	CountedPtr<AsyncResult, AtomicCounter>::operator = (ptr);

	return *this;
}

}

#endif // GS_ASYNCRESULTPTR_HPP
