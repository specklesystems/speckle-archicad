
// *****************************************************************************
//
// Declaration and implementation of CallableTask class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CALLABLETASK_HPP
#define GS_CALLABLETASK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Callable.hpp"
#include "CountedPtr.hpp"




// --- CallableTask class ------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT CallableTask : public CountedPtr<Callable, AtomicCounter> {

// Construction / destruction:
public:
	CallableTask ();
	CallableTask (Callable* callable);
	template<typename T, typename CounterT>
	CallableTask (const CountedPtr<T, CounterT>& ptr);

// Operator overloading:
public:
	const CallableTask&		operator = (Callable* callable);
	template<typename T, typename CounterT>
	const CallableTask&		operator = (const CountedPtr<T, CounterT>& ptr);

};

////////////////////////////////////////////////////////////////////////////////
// CallableTask implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline CallableTask::CallableTask () :
	CountedPtr<Callable, AtomicCounter> ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline CallableTask::CallableTask (Callable* callable) :
	CountedPtr<Callable, AtomicCounter> (callable)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline CallableTask::CallableTask (const CountedPtr<T, CounterT>& ptr) :
	CountedPtr<Callable, AtomicCounter> (ptr)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const CallableTask&	CallableTask::operator = (Callable* callable)
{
	CountedPtr<Callable, AtomicCounter>::operator = (callable);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT>
inline const CallableTask&	CallableTask::operator = (const CountedPtr<T, CounterT>& ptr)
{
	CountedPtr<Callable, AtomicCounter>::operator = (ptr);

	return *this;
}

}

#endif // GS_CALLABLETASK_HPP
