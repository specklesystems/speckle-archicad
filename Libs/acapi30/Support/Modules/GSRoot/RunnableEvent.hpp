
// *****************************************************************************
//
// Declaration of RunnableEvent class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_RUNNABLEEVENT_HPP
#define GS_RUNNABLEEVENT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Event.hpp"
#include "RunnableTask.hpp"



// --- RunnableEvent class -----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT RunnableEvent : public Event {

// Data members:
private:
	RunnableTask			m_task;

// Construction / destruction:
public:
	explicit RunnableEvent (const RunnableTask& task);

// Operations:
public:
	const RunnableTask&		GetTask () const;
	RunnableTask&			GetTask ();

// Event overrides:
public:
	virtual Event*			Clone () const override;

};

////////////////////////////////////////////////////////////////////////////////
// RunnableEvent inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetTask
// -----------------------------------------------------------------------------

inline const RunnableTask&	RunnableEvent::GetTask () const
{
	return m_task;
}

// -----------------------------------------------------------------------------
// GetTask
// -----------------------------------------------------------------------------

inline RunnableTask&	RunnableEvent::GetTask ()
{
	return m_task;
}

}

#endif // GS_RUNNABLEEVENT_HPP
