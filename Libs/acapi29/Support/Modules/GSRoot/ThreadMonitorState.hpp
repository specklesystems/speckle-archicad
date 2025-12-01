
// *****************************************************************************
//
// Declaration and implementation of ThreadMonitorState class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADMONITORSTATE_HPP
#define GS_THREADMONITORSTATE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSDebug.hpp"



// --- ThreadMonitorState class ------------------------------------------------

namespace GS {

class ThreadMonitorState {

// Type definitions:
public:
	typedef enum {

		Signaled = 1,		// The thread monitor is signaled
		Interrupted,		// The thread monitor is interrupted
		Timedout			// The thread monitor is timed out

	} State;

// Data members:
private:
	State						m_state;

// Construction / destruction:
public:
	ThreadMonitorState ();
	ThreadMonitorState (State state);

// Operator overloading:
public:
	const ThreadMonitorState&	operator =  (State state);

	bool						operator == (const ThreadMonitorState& state) const;
	bool						operator == (State state) const;

	bool						operator != (const ThreadMonitorState& state) const;
	bool						operator != (State state) const;

								operator State () const;

};

////////////////////////////////////////////////////////////////////////////////
// ThreadMonitorState implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ThreadMonitorState::ThreadMonitorState () :
	m_state (Signaled)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ThreadMonitorState::ThreadMonitorState (State state) :
	m_state (state)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ThreadMonitorState&	ThreadMonitorState::operator = (State state)
{
	m_state = state;
	return *this;
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ThreadMonitorState::operator == (const ThreadMonitorState& state) const
{
	return (m_state == state.m_state);
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		ThreadMonitorState::operator == (State state) const
{
	return (m_state == state);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ThreadMonitorState::operator != (const ThreadMonitorState& state) const
{
	return (m_state != state.m_state);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		ThreadMonitorState::operator != (State state) const
{
	return (m_state != state);
}

// -----------------------------------------------------------------------------
// operator State
// -----------------------------------------------------------------------------

inline ThreadMonitorState::operator ThreadMonitorState::State () const
{
	return m_state;
}

}

#endif // GS_THREADMONITORSTATE_HPP
