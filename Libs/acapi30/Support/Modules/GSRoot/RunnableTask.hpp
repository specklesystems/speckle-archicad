
// *****************************************************************************
//
// Declaration and implementation of RunnableTask class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_RUNNABLETASK_HPP
#define GS_RUNNABLETASK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "CountedPtr.hpp"
#include "Runnable.hpp"




// --- RunnableTask class ------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT RunnableTask : public CountedPtr<Runnable, AtomicCounter> {

// Construction / destruction:
public:
	RunnableTask ();
	RunnableTask (Runnable* runnable);
	template<typename T, typename BehaviourT>
	RunnableTask (const CountedPtrImpl<T, AtomicCounter, BehaviourT>& rhs);

// Operator overloading:
public:
	const RunnableTask&		operator = (Runnable* runnable);
	template<typename T, typename BehaviourT>
	const RunnableTask&		operator = (const CountedPtrImpl<T, AtomicCounter, BehaviourT>& rhs);

};

////////////////////////////////////////////////////////////////////////////////
// RunnableTask inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline RunnableTask::RunnableTask () :
	CountedPtr<Runnable, AtomicCounter> ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline RunnableTask::RunnableTask (Runnable* runnable) :
	CountedPtr<Runnable, AtomicCounter> (runnable)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename BehaviourT>
inline RunnableTask::RunnableTask (const CountedPtrImpl<T, AtomicCounter, BehaviourT>& rhs) :
	CountedPtr<Runnable, AtomicCounter> (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const RunnableTask&	RunnableTask::operator = (Runnable* runnable)
{
	CountedPtr<Runnable, AtomicCounter>::operator = (runnable);

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename BehaviourT>
inline const RunnableTask&	RunnableTask::operator = (const CountedPtrImpl<T, AtomicCounter, BehaviourT>& rhs)
{
	CountedPtr<Runnable, AtomicCounter>::operator = (rhs);

	return *this;
}

}

#endif // GS_RUNNABLETASK_HPP
