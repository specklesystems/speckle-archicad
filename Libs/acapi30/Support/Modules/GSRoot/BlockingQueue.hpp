
// *****************************************************************************
//
// Declaration and implementation of BlockingQueue class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_BLOCKINGQUEUE_HPP
#define GS_BLOCKINGQUEUE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Condition.hpp"
#include "Guard.hpp"
#include "InterruptedException.hpp"
#include "Queue.hpp"
#include "Array.hpp"
#include "ReentrantLock.hpp"



// --- BlockingQueue class -----------------------------------------------------

namespace GS {

template<typename T>
class BlockingQueue {

// Static constants:
private:
	static const USize		unbound		= 0xFFFFFFFF;

// Data members:
private:
	mutable ReentrantLock	m_lock;			// Lock for serializing access to internal state
	Condition				m_notEmpty;		// Condition for blocking pops
	Condition				m_notFull;		// Condition for blocking puts
	Queue<T>				m_queue;		// Storage for the items of the blocking queue
	USize					m_capacity;		// The capacity of the bound blocking queue, or unbound if none

// Construction / destruction:
public:
			 BlockingQueue ();
	explicit BlockingQueue (USize capacity);
private:
			 BlockingQueue (const BlockingQueue&); // Disabled

// Operator overloading:
private:
	const BlockingQueue&	operator = (const BlockingQueue&); // Disabled

// Operations:
public:
	bool					IsEmpty () const;
	USize					GetSize () const;

	bool					Contains (const T& item) const;

	T						Peek () const;
	bool					Peek (T* item) const;

	T						Pop ();
	void					PopAll (Array<T>& items);
	T						Pop (UInt32 timeout);
	T						Pop (const Timeout& timeout);

	void					Pop (T* item);
	bool					Pop (T* item, UInt32 timeout);
	bool					Pop (T* item, const Timeout& timeout);

	void					Push (const T& item);
	void					Push (T&& item);
	bool					Push (const T& item, UInt32 timeout);
	bool					Push (T&& item, UInt32 timeout);
	bool					Push (const T& item, const Timeout& timeout);
	bool					Push (T&& item, const Timeout& timeout);

	void					Clear ();

};

////////////////////////////////////////////////////////////////////////////////
// BlockingQueue implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T>
inline BlockingQueue<T>::BlockingQueue () :
	m_lock (),
	m_notEmpty (m_lock),
	m_notFull (m_lock),
	m_queue (),
	m_capacity (unbound)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T>
inline BlockingQueue<T>::BlockingQueue (USize capacity) :
	m_lock (),
	m_notEmpty (m_lock),
	m_notFull (m_lock),
	m_queue (),
	m_capacity (capacity)
{
	DBASSERT (capacity > 0);
	DBASSERT (capacity != unbound);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// IsEmpty
// -----------------------------------------------------------------------------

template<typename T>
inline bool		BlockingQueue<T>::IsEmpty () const
{
	synchronized (m_lock) { // Serialize access to the internal state...
		return m_queue.IsEmpty ();
	}
}

// -----------------------------------------------------------------------------
// GetSize
// -----------------------------------------------------------------------------

template<typename T>
USize	BlockingQueue<T>::GetSize () const
{
	synchronized (m_lock) { // Serialize access to the internal state...
		return m_queue.GetSize ();
	}
}

// -----------------------------------------------------------------------------
// Contains
// -----------------------------------------------------------------------------

template<typename T>
bool	BlockingQueue<T>::Contains (const T& item) const
{
	synchronized (m_lock) { // Serialize access to the internal state...
		return m_queue.Contains (item);
	}
}

// -----------------------------------------------------------------------------
// Peek
// -----------------------------------------------------------------------------

template<typename T>
inline T	BlockingQueue<T>::Peek () const
{
	synchronized (m_lock) { // Serialize access to the internal state...
		return m_queue.Peek ();
	}
}

// -----------------------------------------------------------------------------
// Peek
// -----------------------------------------------------------------------------

template<typename T>
inline bool		BlockingQueue<T>::Peek (T* item) const
{
	synchronized (m_lock) { // Serialize access to the internal state...
		return m_queue.Peek (item);
	}
}

// -----------------------------------------------------------------------------
// Pop
// -----------------------------------------------------------------------------

template<typename T>
T	BlockingQueue<T>::Pop ()
{
	synchronized (m_lock) { // Serialize access to the internal state...
		while (m_queue.GetSize () == 0) {
			m_notEmpty.Wait ();
		}

		T item = m_queue.Pop ();

		m_notFull.Notify ();

		return item;
	}
}

// -----------------------------------------------------------------------------
// PopAll
// -----------------------------------------------------------------------------

template<typename T>
void	BlockingQueue<T>::PopAll (Array<T>& items)
{
	synchronized (m_lock) {
		while (m_queue.GetSize () == 0) {
			m_notEmpty.Wait ();
		}

		items.SetCapacity (m_queue.GetSize ());

		for (auto item : m_queue) {
			items.Push (item);
		}

		m_queue.Clear ();
		m_notFull.Notify ();
	}
}

// -----------------------------------------------------------------------------
// Pop
// -----------------------------------------------------------------------------

template<typename T>
T	BlockingQueue<T>::Pop (UInt32 timeout)
{
	synchronized (m_lock) { // Serialize access to the internal state...
		while (m_queue.GetSize () == 0) {
			if (m_notEmpty.Wait (timeout) == false) {
				throw TimeoutException ("Timeout expired.", __FILE__, __LINE__);
			}
		}

		T item = m_queue.Pop ();

		m_notFull.Notify ();

		return item;
	}
}

// -----------------------------------------------------------------------------
// Pop
// -----------------------------------------------------------------------------

template<typename T>
T	BlockingQueue<T>::Pop (const Timeout& timeout)
{
	return Pop (timeout ());
}

// -----------------------------------------------------------------------------
// Pop
// -----------------------------------------------------------------------------

template<typename T>
void	BlockingQueue<T>::Pop (T* item)
{
	NULL_PTR_CHECK (item);

	synchronized (m_lock) { // Serialize access to the internal state...
		while (m_queue.GetSize () == 0) {
			m_notEmpty.Wait ();
		}

		m_queue.Pop (item);
		m_notFull.Notify ();
	}
}

// -----------------------------------------------------------------------------
// Pop
// -----------------------------------------------------------------------------

template<typename T>
bool	BlockingQueue<T>::Pop (T* item, UInt32 timeout)
{
	NULL_PTR_CHECK (item);

	try {
		synchronized (m_lock) { // Serialize access to the internal state...
			while (m_queue.GetSize () == 0) {
				if (m_notEmpty.Wait (timeout) == false) {
					return false;
				}
			}

			m_queue.Pop (item);
			m_notFull.Notify ();

			return true;
		}
	}
	catch (InterruptedException&) {
		return false;
	}
}

// -----------------------------------------------------------------------------
// Pop
// -----------------------------------------------------------------------------

template<typename T>
inline bool		BlockingQueue<T>::Pop (T* item, const Timeout& timeout)
{
	return Pop (item, timeout ());
}

// -----------------------------------------------------------------------------
// Push
// -----------------------------------------------------------------------------

template<typename T>
void	BlockingQueue<T>::Push (const T& item)
{
	synchronized (m_lock) { // Serialize access to the internal state...
		if (m_capacity != unbound) { // The queue is bound....
			while (m_queue.GetSize () == m_capacity) {
				m_notFull.Wait ();
			}
		}

		m_queue.Push (item);
		m_notEmpty.Notify ();
	}
}

// -----------------------------------------------------------------------------
// Push
// -----------------------------------------------------------------------------

template<typename T>
void	BlockingQueue<T>::Push (T&& item)
{
	synchronized (m_lock) { // Serialize access to the internal state...
		if (m_capacity != unbound) { // The queue is bound....
			while (m_queue.GetSize () == m_capacity) {
				m_notFull.Wait ();
			}
		}

		m_queue.Push (std::move (item));
		m_notEmpty.Notify ();
	}
}

// -----------------------------------------------------------------------------
// Push
// -----------------------------------------------------------------------------

template<typename T>
bool	BlockingQueue<T>::Push (const T& item, UInt32 timeout)
{
	try {
		synchronized (m_lock) { // Serialize access to the internal state...
			if (m_capacity != unbound) { // The queue is bound....
				while (m_queue.GetSize () == m_capacity) {
					if (m_notFull.Wait (timeout) == false) {
						return false;
					}
				}
			}

			m_queue.Push (item);
			m_notEmpty.Notify ();
		}
	}
	catch (InterruptedException&) {
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------
// Push
// -----------------------------------------------------------------------------

template<typename T>
bool	BlockingQueue<T>::Push (T&& item, UInt32 timeout)
{
	try {
		synchronized (m_lock) { // Serialize access to the internal state...
			if (m_capacity != unbound) { // The queue is bound....
				while (m_queue.GetSize () == m_capacity) {
					if (m_notFull.Wait (timeout) == false) {
						return false;
					}
				}
			}

			m_queue.Push (std::move (item));
			m_notEmpty.Notify ();
		}
	}
	catch (InterruptedException&) {
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------
// Push
// -----------------------------------------------------------------------------

template<typename T>
inline bool		BlockingQueue<T>::Push (const T& item, const Timeout& timeout)
{
	return Push (item, timeout ());
}

// -----------------------------------------------------------------------------
// Push
// -----------------------------------------------------------------------------

template<typename T>
inline bool		BlockingQueue<T>::Push (T&& item, const Timeout& timeout)
{
	return Push (std::move (item), timeout ());
}

// -----------------------------------------------------------------------------
// Clear
// -----------------------------------------------------------------------------

template<typename T>
void	BlockingQueue<T>::Clear ()
{
	synchronized (m_lock) { // Serialize access to the internal state...
		// Clear the underlying storage and notify the threads are blocked on one
		// of the push operations.

		try {
			m_queue.Clear ();
		}
		catch (Exception&) { // Handle exception to avoid lost wake ups...
			// Empty handler
		}

		m_notFull.NotifyAll ();
	}
}

}

#endif // GS_BLOCKINGQUEUE_HPP
