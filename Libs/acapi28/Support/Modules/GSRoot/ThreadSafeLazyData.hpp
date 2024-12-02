// *****************************************************************************
//
// ThreadSafeLazyData class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	BeA
//
// *****************************************************************************

#ifndef GS_THREAD_SAFE_LAZY_DATA_HPP
#define GS_THREAD_SAFE_LAZY_DATA_HPP

#pragma once


// --- Includes ----------------------------------------------------------------
#include <functional>

#include "Definitions.hpp"
#include "Atomic.hpp"
#include "MemoryBarrier.hpp"
#include "GSException.hpp"
#include "TypeTraits.hpp"
#include "Thread.hpp"
#include "SpinLockBase.hpp"


namespace GS {

// Wrapper class for thread-safe handling of lazy data.

template<typename Type>
class ThreadSafeLazyData {
private:
	alignas (Type) mutable char buffer[sizeof (Type)];
	mutable volatile Int32 calculatedState;

	static const Int32 NotCalculated = 0;
	static const Int32 Calculated = 1;
	static const Int32 CalculationInProgress = 2;
	static constexpr Int32 SpinCount = 32;

private:

	void			DestroyValue () const;
	void			CreateValue (const Type& value) const;
	void			CreateValue (Type&& value) const;

	Type&			GetBufferTyped () const;

	template<typename Calculator>
	const Type&		GetCalculatedInternal (const Calculator& calculate) const;

public:

	// Initialize with not calculated state
	ThreadSafeLazyData ();

	// Initialize with calculated state
	ThreadSafeLazyData (const Type& initialValue);
	ThreadSafeLazyData (Type&& initialValue);

	~ThreadSafeLazyData ();

	// Copy value from source if already calculated
	// Can be called concurrently with const operations of source
	ThreadSafeLazyData (const ThreadSafeLazyData& source);
	ThreadSafeLazyData& operator= (const ThreadSafeLazyData& source);

	ThreadSafeLazyData (ThreadSafeLazyData&& source);
	ThreadSafeLazyData& operator= (ThreadSafeLazyData&& source);

	// Call calculate on stored value if it's not yet calculated
	// Blocks (busy wait) if calculation is already in progress on another thread
	// Can be called concurrently with other const operations
	template<typename Calculator>
	const Type& GetCalculatedOrDefaultOnFailure (const Calculator& calculate) const noexcept;

	template<typename Calculator>
	const Type& GetCalculated (const Calculator& calculate) const noexcept;

	// Can be called concurrently with other const operations
	const Type* GetIfCalculated () const;
	bool GetIfCalculated (Type& storedValue) const;

	// Can NOT be called concurrently with any other operation
	Type* GetModifiableIfCalculated ();
	void Set (const Type& newValue);
	void Set (Type&& newValue);
	void SetNotCalculated ();
};


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData ()
	: calculatedState (NotCalculated)
{
}


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData (const Type& initialValue)
	: calculatedState (Calculated)
{
	CreateValue (initialValue);
}


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData (Type&& initialValue)
	: calculatedState (Calculated)
{
	CreateValue (std::move (initialValue));
}


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData (const ThreadSafeLazyData& source)
	: ThreadSafeLazyData ()
{
	const Type* sourceValue = source.GetIfCalculated ();

	if (sourceValue != nullptr) {
		CreateValue (*sourceValue);
		calculatedState = Calculated;
	}
}


template<typename Type>
ThreadSafeLazyData<Type>::ThreadSafeLazyData (ThreadSafeLazyData&& source)
	: ThreadSafeLazyData ()
{
	if (source.calculatedState == Calculated) {
		CreateValue (std::move (source.GetBufferTyped ()));
		calculatedState = Calculated;
	}
}


template<typename Type>
ThreadSafeLazyData<Type>::~ThreadSafeLazyData ()
{
	if (calculatedState == Calculated)
		DestroyValue ();
}


template<typename Type>
Type& ThreadSafeLazyData<Type>::GetBufferTyped () const
{
	return *reinterpret_cast<Type*> (buffer);
}


template<typename Type>
void ThreadSafeLazyData<Type>::DestroyValue () const
{
	GetBufferTyped ().~Type ();
}


template<typename Type>
void ThreadSafeLazyData<Type>::CreateValue (const Type& value) const
{
	new (buffer) Type { value };
}


template<typename Type>
void ThreadSafeLazyData<Type>::CreateValue (Type&& value) const
{
	new (buffer) Type { std::move (value) };
}


template<typename Type>
template<typename Calculator>
const Type& ThreadSafeLazyData<Type>::GetCalculatedInternal (const Calculator& calculate) const
{
	Int32 spinCount = SpinCount;
	for (;;) {
		const Int32 currentCalculatedState = calculatedState;
		GS::MemoryBarrierForVolatile ();
		if (currentCalculatedState == Calculated) {
			break;
		}
		if (GS::AtomicCompareAndSwap (&calculatedState, CalculationInProgress, NotCalculated)) {
			CreateValue (calculate ());
			GS::MemoryBarrierForVolatile ();
			calculatedState = Calculated;
			break;
		}
		if (--spinCount < 0) {
			GS::Thread::Yield ();
			spinCount = SpinCount;
		} else {
			GS::SpinLockBase::Pause ();
		}
	}
	return GetBufferTyped ();
}


template<typename Type>
ThreadSafeLazyData<Type>& ThreadSafeLazyData<Type>::operator= (const ThreadSafeLazyData& source)
{
	if (&source != this) {
		const Type* sourceValue = source.GetIfCalculated ();
		if (sourceValue != nullptr) {
			Set (*sourceValue);
		} else {
			SetNotCalculated ();
		}
	}
	return *this;
}


template<typename Type>
ThreadSafeLazyData<Type>& ThreadSafeLazyData<Type>::operator= (ThreadSafeLazyData&& source)
{
	if (&source != this) {
		if (source.calculatedState == Calculated) {
			Set (std::move (source.GetBufferTyped ()));
		} else {
			SetNotCalculated ();
		}
	}
	return *this;
}


template<typename Type>
template<typename Calculator>
const Type& ThreadSafeLazyData<Type>::GetCalculatedOrDefaultOnFailure (const Calculator& calculate) const noexcept
{
	static_assert (IsDefaultConstructible<Type>, "Type must be default constructible!");
	static_assert (IsInvocableR<void, Calculator, Type&>, "Calculator must be callable with signature <void (Type&)>!");

	try {
		return GetCalculatedInternal ([&] {
			Type value = {};
			try {
				calculate (value);
			}
			catch (const GS::Exception&) {
				DBBREAK ();
			}
			return value;
		});
	}
	catch (const GS::Exception&) {
		std::terminate ();
	}
}


template<typename Type>
template<typename Calculator>
const Type& ThreadSafeLazyData<Type>::GetCalculated (const Calculator& calculate) const noexcept
{
	static_assert (IsNothrowMoveConstructible<Type>, "Type must be nothrow move constructible!");
	static_assert (IsNothrowInvocableR<Type, Calculator>, "Calculator must be callable with signature <Type (void) noexcept>!");

	// If you tried this with std::function, and failed: std::function doesn't handle noexcept,
	// so wrap it inside a noexcept lambda.

	return GetCalculatedInternal (calculate);
}


template<typename Type>
const Type* ThreadSafeLazyData<Type>::GetIfCalculated () const
{
	const Int32 currentCalculatedState = calculatedState;
	GS::MemoryBarrierForVolatile ();
	if (currentCalculatedState == Calculated) {
		return &GetBufferTyped ();
	} else {
		return nullptr;
	}
}


template<typename Type>
bool ThreadSafeLazyData<Type>::GetIfCalculated (Type& storedValue) const
{
	const Type* valueIfCalculated = GetIfCalculated ();
	if (valueIfCalculated != nullptr) {
		storedValue = *valueIfCalculated;
		return true;
	} else {
		return false;
	}
}


template<typename Type>
Type* ThreadSafeLazyData<Type>::GetModifiableIfCalculated ()
{
	if (calculatedState == Calculated) {
		return &GetBufferTyped ();
	}

	return nullptr;
}


template<typename Type>
void ThreadSafeLazyData<Type>::Set (const Type& newValue)
{
	if (calculatedState == Calculated)
		DestroyValue ();
	CreateValue (newValue);
	calculatedState = Calculated;
}


template<typename Type>
void ThreadSafeLazyData<Type>::Set (Type&& newValue)
{
	if (calculatedState == Calculated)
		DestroyValue ();
	CreateValue (std::move (newValue));
	calculatedState = Calculated;
}


template<typename Type>
void ThreadSafeLazyData<Type>::SetNotCalculated ()
{
	if (calculatedState != NotCalculated) {
		DestroyValue ();
		calculatedState = NotCalculated;
	}
}


}

#endif // GS_THREAD_SAFE_LAZY_DATA_HPP
