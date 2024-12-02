
// *****************************************************************************
//
// Declaration and implementation of ThreadState class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADSTATE_HPP
#define GS_THREADSTATE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSDebug.hpp"
#include "GSRootExport.hpp"



// --- ThreadState class -------------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadState {

// Type definitions:
public:
	typedef enum {

		Initialized = 0,		// The thread has been initialized, but has not yet started
		Running,				// The thread is executing its task
		Finished,				// The thread has finished executing and has exited
		Wrapper					// The thread is a wrapper around a native thread

	} State;

// Data members:
private:
	State		m_state;

// Construction / destruction:
public:
	ThreadState ();
	ThreadState (State state);

// Operator overloading:
public:
	bool		operator == (const ThreadState& state) const;
	bool		operator == (State state) const;

	bool		operator != (const ThreadState& state) const;
	bool		operator != (State state) const;

				operator State () const;

// Operations:
public:
	bool		IsInitialized () const;
	bool		IsRunning () const;
	bool		IsFinished () const;
	bool		IsWrapper () const;

	bool		SetInitialized ();
	bool		SetRunning ();
	bool		SetFinished ();
	bool		SetWrapper ();

};

////////////////////////////////////////////////////////////////////////////////
// ThreadState implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ThreadState::ThreadState () :
	m_state (Initialized)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ThreadState::ThreadState (State state) :
	m_state (state)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ThreadState::operator == (const ThreadState& state) const
{
	return (m_state == state.m_state);
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ThreadState::operator == (State state) const
{
	return (m_state == state);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ThreadState::operator != (const ThreadState& state) const
{
	return (m_state != state.m_state);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ThreadState::operator != (State state) const
{
	return (m_state != state);
}

// -----------------------------------------------------------------------------
// operator State
// -----------------------------------------------------------------------------

inline ThreadState::operator ThreadState::State () const
{
	return m_state;
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// IsInitialized
// -----------------------------------------------------------------------------

inline bool		ThreadState::IsInitialized () const
{
	return (m_state == Initialized);
}

// -----------------------------------------------------------------------------
// IsRunning
// -----------------------------------------------------------------------------

inline bool		ThreadState::IsRunning () const
{
	return (m_state == Running);
}

// -----------------------------------------------------------------------------
// IsFinished
// -----------------------------------------------------------------------------

inline bool		ThreadState::IsFinished () const
{
	return (m_state == Finished);
}

// -----------------------------------------------------------------------------
// IsWrapper
// -----------------------------------------------------------------------------

inline bool		ThreadState::IsWrapper () const
{
	return (m_state == Wrapper);
}

// -----------------------------------------------------------------------------
// SetInitialized
// -----------------------------------------------------------------------------

inline bool		ThreadState::SetInitialized ()
{
	if (DBERROR (m_state != Running)) {
		return false;
	}

	m_state = Initialized;

	return true;
}

// -----------------------------------------------------------------------------
// SetRunning
// -----------------------------------------------------------------------------

inline bool		ThreadState::SetRunning ()
{
	if (DBERROR (m_state != Initialized)) {
		return false;
	}

	m_state = Running;

	return true;
}

// -----------------------------------------------------------------------------
// SetFinished
// -----------------------------------------------------------------------------

inline bool		ThreadState::SetFinished ()
{
	m_state = Finished;

	return true;
}

// -----------------------------------------------------------------------------
// SetWrapper
// -----------------------------------------------------------------------------

inline bool		ThreadState::SetWrapper ()
{
	if (DBERROR (m_state != Initialized)) {
		return false;
	}

	m_state = Wrapper;

	return true;
}

}

#endif // GS_THREADSTATE_HPP
