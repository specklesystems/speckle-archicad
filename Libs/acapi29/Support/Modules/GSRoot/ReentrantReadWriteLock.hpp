
// *****************************************************************************
//
// Declaration of ReentrantReadWriteLock class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_REENTRANTREADWRITELOCK_HPP
#define GS_REENTRANTREADWRITELOCK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Condition.hpp"
#include "ReentrantLock.hpp"



// --- ReentrantReadWriteLock class --------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ReentrantReadWriteLock {

// Type definitions:
private:
	class GSROOT_DLL_EXPORT ReadLock : public Lockable {

	// Data members:
	private:
		ReentrantReadWriteLock&		m_rwLock;

	// Construction / destruction:
	public:
		explicit ReadLock (ReentrantReadWriteLock& rwLock);
				 ReadLock (const ReadLock&) = delete;
		virtual ~ReadLock ();

	// Operator overloading:
	public:
		ReadLock&					operator = (const ReadLock&) = delete;

	// Lockable interface implementation:
	public:
		virtual void				Acquire (bool interruptible = true) override;
		virtual bool				TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
		virtual void				Release () override;

	};

private:
	class GSROOT_DLL_EXPORT WriteLock : public Lockable {

	// Data members:
	private:
		ReentrantReadWriteLock&		m_rwLock;

	// Construction / destruction:
	public:
		explicit WriteLock (ReentrantReadWriteLock& rwLock);
				 WriteLock (const WriteLock&) = delete;
		virtual ~WriteLock ();

	// Operator overloading:
	public:
		WriteLock&					operator = (const WriteLock&) = delete;

	// Lockable interface implementation:
	public:
		virtual void				Acquire (bool interruptible = true) override;
		virtual bool				TryAcquire (UInt32 timeout = 0, bool interruptible = true, UInt32* remaining = nullptr) override;
		virtual void				Release () override;

	};

// Friend classes:
friend class ReadLock;
friend class WriteLock;

// Data members:
private:
	ReentrantLock					m_lock;				// Lock for serializing access to the internal state, and lock for implementing critical section for writers
	Condition						m_condition;		// Condition for blocking writers

	volatile int					m_readers;			// The number of readers acquired the lock successfully
	volatile int					m_writersWaiting;	// The number of writers waiting for readers
	volatile int					m_writers;			// The number of writers acquired the lock successfully

	ReadLock						m_rLock;			// The read lock
	WriteLock						m_wLock;			// The write lock

// Construction / destruction:
public:
	 ReentrantReadWriteLock ();
	 ReentrantReadWriteLock (const ReentrantReadWriteLock&) = delete;
	~ReentrantReadWriteLock ();

// Operator overloading:
public:
	ReentrantReadWriteLock&			operator = (const ReentrantReadWriteLock&) = delete;

// Operations:
public:
	Lockable&						GetReadLock ();
	Lockable&						GetWriteLock ();

// Implementation:
private:
	ReentrantReadWriteLock&			GetSelf ();

};

////////////////////////////////////////////////////////////////////////////////
// ReentrantReadWriteLock inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ReentrantReadWriteLock::ReentrantReadWriteLock () :
	m_lock (),
	m_condition (m_lock),
	m_readers (0),
	m_writersWaiting (0),
	m_writers (0),
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

inline Lockable&	ReentrantReadWriteLock::GetReadLock ()
{
	return m_rLock;
}

// -----------------------------------------------------------------------------
// GetWriteLock
// -----------------------------------------------------------------------------

inline Lockable&	ReentrantReadWriteLock::GetWriteLock ()
{
	return m_wLock;
}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetSelf
// -----------------------------------------------------------------------------

inline ReentrantReadWriteLock&	ReentrantReadWriteLock::GetSelf ()
{
	return *this;
}



////////////////////////////////////////////////////////////////////////////////
// ReentrantReadWriteLock::ReadLock inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ReentrantReadWriteLock::ReadLock::ReadLock (ReentrantReadWriteLock& rwLock) :
	m_rwLock (rwLock)
{
	// Empty constructor body
}



////////////////////////////////////////////////////////////////////////////////
// ReentrantReadWriteLock::WriteLock inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

inline ReentrantReadWriteLock::WriteLock::WriteLock (ReentrantReadWriteLock& rwLock) :
	m_rwLock (rwLock)
{
	// Empty constructor body
}

}

#endif // GS_REENTRANTREADWRITELOCK_HPP
