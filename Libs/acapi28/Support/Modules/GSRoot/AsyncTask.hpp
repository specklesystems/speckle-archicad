
// *****************************************************************************
//
// Declaration of AsyncTask class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_ASYNCTASK_HPP
#define GS_ASYNCTASK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "AsyncResult.hpp"
#include "CallableTask.hpp"
#include "Condition.hpp"
#include "GSException.hpp"
#include "Lock.hpp"
#include "RunnableTask.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class ThreadImpl;

}




// --- AsyncTask class ---------------------------------------------------------

namespace GS {

class AsyncTask : public AsyncResult, public Runnable {

// Type definitions:
private:
	typedef enum {

		Initial = 0,						// Task is created and ready for run (initial state)
		Running,							// Task is running
		Completted,							// Task is completed, result generated
		Canceled							// Task is canceled

	} State;

// Data members:
private:
	CallableTask			m_task;			// The callable task to be executed by the asynchronous task
	mutable Lock			m_lock;			// Lock for serializing access to the internal state

	Condition				m_done;			// Condition for blocking threads waiting for task completion
	State					m_state;		// The state of the asynchronous task

	ThreadImpl* volatile	m_runner;		// The thread which runs the asynchronous task

	Object*					m_result;		// The result of the callable task
	Exception*				m_exception;	// The exception thrown by the callable task during execution

// Construction / destruction:
public:
	explicit AsyncTask (const CallableTask& callable);
			 AsyncTask (const RunnableTask& runnable, Object* result);
private:
			 AsyncTask (const AsyncTask&); // Disabled
public:
	virtual ~AsyncTask ();

// Operator overloading:
private:
	const AsyncTask&		operator = (const AsyncTask&); // Disabled

// Operations:
public:
	const CallableTask&		GetTask () const;

// AsyncResult interface implementation:
public:
	virtual bool			IsCompleted () const override;

	virtual Object*			Get (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual Object*			Get (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual	Object*			Get (bool interruptible = true) override;

// Cancelable interface implementation:
public:
	virtual bool			IsCanceled () const override;
	virtual void			Cancel () override;

// Runnable interface implementation:
public:
	virtual void			Run () override;

// Waitable interface implementation:
public:
	virtual bool			Wait (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual bool			Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) override;
	virtual void			Wait (bool interruptible = true) override;

// Implementation:
private:
	void					SetResult (Object* result);
	void					SetException (const Exception& exception);

};

////////////////////////////////////////////////////////////////////////////////
// AsyncTask inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetTask
// -----------------------------------------------------------------------------

inline const CallableTask&	AsyncTask::GetTask () const
{
	return m_task;
}

}

#endif // GS_ASYNCTASK_HPP
