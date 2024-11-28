
// *****************************************************************************
//
// Declaration of Executor interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_EXECUTOR_HPP
#define GS_EXECUTOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "AsyncResultPtr.hpp"
#include "CallableTask.hpp"
#include "Cancelable.hpp"
#include "RunnableTask.hpp"
#include "Waitable.hpp"



// --- Executor interface ------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT Executor : public Cancelable, public Waitable {

// Construction / destruction:
protected:
			 Executor ();
			 Executor (const Executor&);
public:
	virtual ~Executor ();

// Operator overloading:
protected:
	const Executor&				operator = (const Executor&);

// Interface methods:
public:
	virtual void				Execute (const RunnableTask& runnable) = 0;
	virtual AsyncResultPtr		Execute (const CallableTask& callable);

};

////////////////////////////////////////////////////////////////////////////////
// Executor inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Executor::Executor ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline Executor::Executor (const Executor&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const Executor&	Executor::operator = (const Executor&)
{
	return *this;
}

}

#endif // GS_EXECUTOR_HPP
