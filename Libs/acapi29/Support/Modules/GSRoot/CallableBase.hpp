
// *****************************************************************************
//
// Declaration and implementation of CallableBase class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_CALLABLEBASE_HPP
#define GS_CALLABLEBASE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "AsyncResultPtr.hpp"
#include "Callable.hpp"



// --- CallableBase class ------------------------------------------------------

namespace GS {

template<typename T>
class CallableBase : public Callable {

// Type definition:
public:
	class Result : public Object {

	// Data members:
	private:
		T						m_result;

	// Construction
	public:
		explicit Result (const T& result);

	// Operations:
	public:
		const T&				Get () const;
		T&						Get ();

	// Object overrides:
	public:
		virtual Object*			Clone () const override;

	};

	class AsyncResult {

	// Data members:
	private:
		mutable GS::AsyncResultPtr	m_ptr;

	// Construction / destruction:
	public:
		AsyncResult (const GS::AsyncResultPtr& ptr);

	// Operations:
	public:
		const T&				Get (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr) const;
		T&						Get (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
		const T&				Get (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr) const;
		T&						Get (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
		const T&				Get (bool interruptible = true) const;
		T&						Get (bool interruptible = true);

		bool					IsCanceled () const;
		void					Cancel ();

		bool					Wait (const Timeout& timeout, bool interruptible = true, UInt32* remaining = nullptr);
		bool					Wait (UInt32 timeout, bool interruptible = true, UInt32* remaining = nullptr);
		void					Wait (bool interruptible = true);

	};

	class AsyncResultPtr : public CountedPtr<AsyncResult, AtomicCounter> {

	// Construction / destruction:
	public:
		AsyncResultPtr (const GS::AsyncResultPtr& ptr);

	};

// Construction / destruction:
protected:
			 CallableBase ();
			 CallableBase (const CallableBase<T>&);
public:
	virtual ~CallableBase ();

// Operator overloading:
protected:
	const CallableBase<T>&		operator = (const CallableBase<T>&);

// Callable interface implementation:
public:
	virtual Object*				Call () override;

// Implementation:
protected:
	virtual T					Invoke () = 0;

};

////////////////////////////////////////////////////////////////////////////////
// CallableBase implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<typename T>
inline CallableBase<T>::CallableBase ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<typename T>
inline CallableBase<T>::CallableBase (const CallableBase<T>&)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<typename T>
CallableBase<T>::~CallableBase ()
{
	// Empty destructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T>
inline const CallableBase<T>&	CallableBase<T>::operator = (const CallableBase<T>&)
{
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Callable interface implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Call
// -----------------------------------------------------------------------------

template<typename T>
Object*		CallableBase<T>::Call ()
{
	return new Result (Invoke ());
}



////////////////////////////////////////////////////////////////////////////////
// CallableBase::Result implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T>
inline CallableBase<T>::Result::Result (const T& result) :
	m_result (result)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline const T&		CallableBase<T>::Result::Get () const
{
	return m_result;
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline T&	CallableBase<T>::Result::Get ()
{
	return m_result;
}

////////////////////////////////////////////////////////////////////////////////
// Object overrides
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Clone
// -----------------------------------------------------------------------------

template<typename T>
Object*		CallableBase<T>::Result::Clone () const
{
	return new Result (*this);
}



////////////////////////////////////////////////////////////////////////////////
// CallableBase::AsyncResult implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T>
inline CallableBase<T>::AsyncResult::AsyncResult (const GS::AsyncResultPtr& ptr) :
	m_ptr (ptr)
{
	DBASSERT (ptr != nullptr);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline const T&		CallableBase<T>::AsyncResult::Get (const Timeout& timeout, bool interruptible, UInt32* remaining) const
{
	Result*	result = dynamic_cast<Result*> (m_ptr->Get (timeout (), interruptible, remaining));
	DBASSERT (result != nullptr);
	return result->Get ();
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline T&	CallableBase<T>::AsyncResult::Get (const Timeout& timeout, bool interruptible, UInt32* remaining)
{
	Result*	result = dynamic_cast<Result*> (m_ptr->Get (timeout (), interruptible, remaining));
	DBASSERT (result != nullptr);
	return result->Get ();
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline const T&		CallableBase<T>::AsyncResult::Get (UInt32 timeout, bool interruptible, UInt32* remaining) const
{
	Result*	result = dynamic_cast<Result*> (m_ptr->Get (timeout, interruptible, remaining));
	DBASSERT (result != nullptr);
	return result->Get ();
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline T&	CallableBase<T>::AsyncResult::Get (UInt32 timeout, bool interruptible, UInt32* remaining)
{
	Result*	result = dynamic_cast<Result*> (m_ptr->Get (timeout, interruptible, remaining));
	DBASSERT (result != nullptr);
	return result->Get ();
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline const T&		CallableBase<T>::AsyncResult::Get (bool interruptible) const
{
	Result*	result = dynamic_cast<Result*> (m_ptr->Get (interruptible));
	DBASSERT (result != nullptr);
	return result->Get ();
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<typename T>
inline T&	CallableBase<T>::AsyncResult::Get (bool interruptible)
{
	Result*	result = dynamic_cast<Result*> (m_ptr->Get (interruptible));
	DBASSERT (result != nullptr);
	return result->Get ();
}

// -----------------------------------------------------------------------------
// IsCanceled
// -----------------------------------------------------------------------------

template<typename T>
inline bool		CallableBase<T>::AsyncResult::IsCanceled () const
{
	return m_ptr->IsCanceled ();
}

// -----------------------------------------------------------------------------
// Cancel
// -----------------------------------------------------------------------------

template<typename T>
inline void		CallableBase<T>::AsyncResult::Cancel ()
{
	m_ptr->Cancel ();
}

// -----------------------------------------------------------------------------
// Wait
// -----------------------------------------------------------------------------

template<typename T>
inline bool		CallableBase<T>::AsyncResult::Wait (const Timeout& timeout, bool interruptible, UInt32* remaining)
{
	return m_ptr->Wait (timeout, interruptible, remaining);
}

// -----------------------------------------------------------------------------
// Wait
// -----------------------------------------------------------------------------

template<typename T>
inline bool		CallableBase<T>::AsyncResult::Wait (UInt32 timeout, bool interruptible, UInt32* remaining)
{
	return m_ptr->Wait (timeout, interruptible, remaining);
}

// -----------------------------------------------------------------------------
// Wait
// -----------------------------------------------------------------------------

template<typename T>
inline void		CallableBase<T>::AsyncResult::Wait (bool interruptible)
{
	m_ptr->Wait (interruptible);
}



////////////////////////////////////////////////////////////////////////////////
// CallableBase::AsyncResultPtr implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T>
inline CallableBase<T>::AsyncResultPtr::AsyncResultPtr (const GS::AsyncResultPtr& ptr) :
	CountedPtr<AsyncResult, AtomicCounter> (new AsyncResult (ptr))
{
	// Empty constructor body
}

}

#endif // GS_CALLABLEBASE_HPP
