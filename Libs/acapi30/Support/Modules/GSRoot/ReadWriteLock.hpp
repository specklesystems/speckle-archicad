
// *****************************************************************************
//
// Declaration of ReadWriteLock class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_READWRITELOCK_HPP
#define GS_READWRITELOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Condition.hpp"
#include "Lock.hpp"



// --- ReadWriteLock class -----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ReadWriteLock {

// Type definitions:
private:
	class GSROOT_DLL_EXPORT ReadLock : public Lockable {

	// Data members:
	private:
		ReadWriteLock&		m_rwLock;

	// Construction / destruction:
	public:
		explicit ReadLock (ReadWriteLock& rwLock);
				 ReadLock (const ReadLock&) = delete;
		virtual ~ReadLock ();

	// Operator overloading:
	public:
		ReadLock&			operator = (const ReadLock&) = delete;

	// Lockable interface implementation:
	public:
		virtual void		Acquire (bool interruptible = true) override;
		virtual bool		TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
		virtual void		Release () override;

	};

private:
	class GSROOT_DLL_EXPORT WriteLock : public Lockable {

	// Data members:
	private:
		ReadWriteLock&		m_rwLock;

	// Construction / destruction:
	public:
		explicit WriteLock (ReadWriteLock& rwLock);
				 WriteLock (const WriteLock&) = delete;
		virtual ~WriteLock ();

	// Operator overloading:
	public:
		WriteLock&			operator = (const WriteLock&) = delete;

	// Lockable interface implementation:
	public:
		virtual void		Acquire (bool interruptible = true) override;
		virtual bool		TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
		virtual void		Release () override;

	};

// Friend classes:
friend class ReadLock;
friend class WriteLock;

// Data members:
private:
	Lock					m_lock;				// Lock for serializing access to the internal state, and lock for implementing critical section for writers
	
	Condition				m_condition;		// Condition for blocking writers

	volatile int			m_writersWaiting;	// The number of writers waiting for readers
	volatile int			m_readers;			// The number of readers acquired the lock successfully

	ReadLock				m_rLock;			// The read lock
	WriteLock				m_wLock;			// The write lock

// Construction / destruction:
public:
	 ReadWriteLock ();
	 ReadWriteLock (const ReadWriteLock&) = delete;
	~ReadWriteLock ();

// Operator overloading:
public:
	ReadWriteLock&			operator = (const ReadWriteLock&) = delete;

// Operations:
public:
	Lockable&				GetReadLock ();
	Lockable&				GetWriteLock ();

// Implementation:
private:
	ReadWriteLock&			GetSelf ();

};

////////////////////////////////////////////////////////////////////////////////
// ReadWriteLock inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ReadWriteLock::ReadWriteLock () :
	m_lock (),
	m_condition (m_lock),
	m_writersWaiting (0),
	m_readers (0),
	m_rLock (GetSelf ()),
	m_wLock (GetSelf ())
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetReadLock
// -----------------------------------------------------------------------------

inline Lockable&	ReadWriteLock::GetReadLock ()
{
	return m_rLock;
}

// -----------------------------------------------------------------------------
// GetWriteLock
// -----------------------------------------------------------------------------

inline Lockable&	ReadWriteLock::GetWriteLock ()
{
	return m_wLock;
}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetSelf
// -----------------------------------------------------------------------------

inline ReadWriteLock&	ReadWriteLock::GetSelf ()
{
	return *this;
}



////////////////////////////////////////////////////////////////////////////////
// ReadWriteLock::ReadLock inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ReadWriteLock::ReadLock::ReadLock (ReadWriteLock& rwLock) :
	m_rwLock (rwLock)
{
	// Empty constructor body
}



////////////////////////////////////////////////////////////////////////////////
// ReadWriteLock::WriteLock inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ReadWriteLock::WriteLock::WriteLock (ReadWriteLock& rwLock) :
	m_rwLock (rwLock)
{
	// Empty constructor body
}

}

#endif // GS_READWRITELOCK_HPP
