
// *****************************************************************************
//
// Declaration of TaskGroupWaiterQueue class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_TASKGROUPWAITERQUEUE_HPP
#define GS_TASKGROUPWAITERQUEUE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "FastLock.hpp"
#include "HashTable.hpp"
#include "StableArray.hpp"
#include "ThreadImpl.hpp"



// --- TaskGroupWaiterQueue class ----------------------------------------------

namespace GS {

class TaskGroupWaiterQueue {

// Type definitions:
private:
	typedef PagedArray<ThreadImpl*>	ThreadList;

	class TaskGroup {

	// Data members:
	private:
		UInt32						m_id;			// The identifier of the task group
		USize						m_tasks;		// The the number of active tasks in the task group
		ThreadList					m_waiters;		// The list of threads waiting for the tasks of the task group

	// Construction / destruction:
	public:
				 TaskGroup ();
		explicit TaskGroup (UInt32 id);

	// Operator overloading:
	public:
		bool						operator == (const TaskGroup& rhs) const;
		bool						operator != (const TaskGroup& rhs) const;

	// Operations:
	public:
		UInt32						GetId () const;

		USize						GetTaskCount () const;

		USize						IncrementTaskCount ();
		USize						DecrementTaskCount ();

		USize						GetWaiterCount () const;
		bool						HasWaiter () const;

		ThreadList::ConstIterator	EnumerateWaiters () const;
		ThreadList::Iterator		EnumerateWaiters ();

		void						AddWaiter (ThreadImpl* thread);
		void						RemoveWaiter (ThreadImpl* thread);

	};

	typedef StableArray<TaskGroup> TaskGroupList;
	typedef HashTable<Runnable*, UInt32> TaskGroupMap;

// Data members:
private:
	mutable FastLock				m_lock;			// Lock for serializing access to the internal state
	mutable TaskGroupList			m_groups;		// The list of active task groups
	TaskGroupMap					m_tasks;		// The map which maps tasks to task groups
	UInt32							m_id;			// The identifier of the next group created

// Construction / destruction:
public:
	 TaskGroupWaiterQueue ();
private:
	 TaskGroupWaiterQueue (const TaskGroupWaiterQueue&); // Disabled
public:
	~TaskGroupWaiterQueue ();

// Operator overloading:
private:
	const TaskGroupWaiterQueue&	operator = (const TaskGroupWaiterQueue&); // Disabled

// Operations:
public:
	USize							GetSize () const;
	bool							IsEmpty () const;

	bool							Contains (Runnable* task) const;
	void							Add (Runnable* task);
	void							Remove (Runnable* task);

	bool							Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
	void							Wait (bool interruptible = true);

// Implementation:
private:
	USize							GetTaskCount () const;
	void							WakeUp (TaskGroup& group);

};

////////////////////////////////////////////////////////////////////////////////
// TaskGroupWaiterQueue inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// IsEmpty
// -----------------------------------------------------------------------------

inline bool		TaskGroupWaiterQueue::IsEmpty () const
{
	return (GetSize () == 0);
}

// -----------------------------------------------------------------------------
// Wait
// -----------------------------------------------------------------------------

inline void		TaskGroupWaiterQueue::Wait (bool interruptible)
{
	Wait (Timeout::Infinite, interruptible, nullptr);
}



////////////////////////////////////////////////////////////////////////////////
// TaskGroupWaiterQueue::TaskGroup inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline TaskGroupWaiterQueue::TaskGroup::TaskGroup () :
	m_id (0),
	m_tasks (0),
	m_waiters ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline TaskGroupWaiterQueue::TaskGroup::TaskGroup (UInt32 id) :
	m_id (id),
	m_tasks (0),
	m_waiters ()
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool		TaskGroupWaiterQueue::TaskGroup::operator == (const TaskGroup& rhs) const
{
	return (m_id == rhs.m_id);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool		TaskGroupWaiterQueue::TaskGroup::operator != (const TaskGroup& rhs) const
{
	return (m_id != rhs.m_id);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetId
// -----------------------------------------------------------------------------

inline UInt32	TaskGroupWaiterQueue::TaskGroup::GetId () const
{
	return m_id;
}

// -----------------------------------------------------------------------------
// GetTaskCount
// -----------------------------------------------------------------------------

inline USize	TaskGroupWaiterQueue::TaskGroup::GetTaskCount () const
{
	return m_tasks;
}

// -----------------------------------------------------------------------------
// IncrementTaskCount
// -----------------------------------------------------------------------------

inline USize	TaskGroupWaiterQueue::TaskGroup::IncrementTaskCount ()
{
	return ++ m_tasks;
}

// -----------------------------------------------------------------------------
// DecrementTaskCount
// -----------------------------------------------------------------------------

inline USize	TaskGroupWaiterQueue::TaskGroup::DecrementTaskCount ()
{
	return -- m_tasks;
}

// -----------------------------------------------------------------------------
// GetWaiterCount
// -----------------------------------------------------------------------------

inline USize	TaskGroupWaiterQueue::TaskGroup::GetWaiterCount () const
{
	return m_waiters.GetSize ();
}

// -----------------------------------------------------------------------------
// HasWaiter
// -----------------------------------------------------------------------------

inline bool		TaskGroupWaiterQueue::TaskGroup::HasWaiter () const
{
	return (m_waiters.GetSize () > 0);
}

// -----------------------------------------------------------------------------
// EnumerateWaiters
// -----------------------------------------------------------------------------

inline TaskGroupWaiterQueue::ThreadList::ConstIterator	TaskGroupWaiterQueue::TaskGroup::EnumerateWaiters () const
{
	return m_waiters.Enumerate ();
}

// -----------------------------------------------------------------------------
// EnumerateWaiters
// -----------------------------------------------------------------------------

inline TaskGroupWaiterQueue::ThreadList::Iterator	TaskGroupWaiterQueue::TaskGroup::EnumerateWaiters ()
{
	return m_waiters.Enumerate ();
}

}

#endif // GS_TASKGROUPWAITERQUEUE_HPP
