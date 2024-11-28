
// *****************************************************************************
//
// Declaration and implementation of CountedPtrImpl class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_COUNTEDPTRIMPL_HPP
#define GS_COUNTEDPTRIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "AtomicCounter.hpp"
#include "BaseAlgorithms.hpp"
#include "ClassCastException.hpp"
#include "Counter.hpp"
#include "GSException.hpp"
#include "HashCommon.hpp"



// --- PtrBehaviour class ------------------------------------------------------

namespace GS {

class PtrBehaviour {

// Static operations:
public:
	template<typename T>
	static void			CheckPtr (const T* ptr, const char*, UInt32)
	{
		DBASSERT (ptr != nullptr);
		UNUSED_PARAMETER (ptr);
	}

	template<typename T, typename U>
	static void			CheckBadCast (const T* source, const U* target, const char*, UInt32)
	{
		DBASSERT (source != nullptr && target != nullptr || source == nullptr && target == nullptr);
		UNUSED_PARAMETER (source, target);
	}

};

}



// --- RefBehaviour class ------------------------------------------------------

namespace GS {

class RefBehaviour {

// Static operations:
public:
	template<typename T>
	static void			CheckPtr (const T* ptr, const char* fileName, UInt32 lineNumber)
	{
		if (DBERROR (ptr == nullptr)) {
			throw NullReferenceException ("Null reference.", fileName, lineNumber);
		}
	}

	template<typename T, typename U>
	static void			CheckBadCast (const T* source, const U* target, const char* fileName, UInt32 lineNumber)
	{
		if (DBERROR (source != nullptr && target == nullptr)) { // Cast failed...
			throw ClassCastException ("Bad cast.", fileName, lineNumber);
		}
	}

};

}



// --- Macro definitions -------------------------------------------------------

#ifndef CHECK_PTR
#define CHECK_PTR(ptr) BehaviourT::CheckPtr (ptr, __FILE__, __LINE__)
#endif

#ifndef CHECK_BADCAST
#define CHECK_BADCAST(source, target) BehaviourT::CheckBadCast (source, target, __FILE__, __LINE__)
#endif



// --- Cast selectors ----------------------------------------------------------

namespace GS {

class StaticCastSelector {};
class ConstCastSelector {};
class DynamicCastSelector {};

}



// --- CountedPtrImpl class ----------------------------------------------------

namespace GS {

template<typename T, typename CounterT = Counter, typename BehaviourT = PtrBehaviour>
class CountedPtrImpl {

// Friend classes:
template<typename U, typename CounterU, typename BehaviourU> friend class CountedPtrImpl;

// Data members:
protected:
	T*						m_instance;
	CounterT*				m_counter;

// Construction / destruction:
public:
	 CountedPtrImpl ();
	 CountedPtrImpl (std::nullptr_t);
	 template<typename U>
	 CountedPtrImpl (U* instance);
	 CountedPtrImpl (const CountedPtrImpl& rhs);
	 CountedPtrImpl (CountedPtrImpl&& rhs);
	 template<typename U, typename BehaviourU>
	 CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs);
	 template<typename U, typename BehaviourU>
	 CountedPtrImpl (CountedPtrImpl<U, CounterT, BehaviourU>&& rhs);
	 template<typename U, typename BehaviourU>
	 CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, StaticCastSelector);
	 template<typename U, typename BehaviourU>
	 CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, ConstCastSelector);
	 template<typename U, typename BehaviourU>
	 CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, DynamicCastSelector);
	~CountedPtrImpl ();

// Operator overloading:
public:
	CountedPtrImpl&			operator =  (std::nullptr_t);
	template<typename U>
	CountedPtrImpl&			operator =  (U* instance);
	CountedPtrImpl&			operator =  (const CountedPtrImpl& rhs);
	CountedPtrImpl&			operator =  (CountedPtrImpl&& rhs);
	template<typename U, typename BehaviourU>
	CountedPtrImpl&			operator =  (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs);
	template<typename U, typename BehaviourU>
	CountedPtrImpl&			operator =  (CountedPtrImpl<U, CounterT, BehaviourU>&& rhs);

	bool					operator == (std::nullptr_t) const;
	template<typename U, typename BehaviourU>
	bool					operator == (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) const;

	bool					operator != (std::nullptr_t) const;
	template<typename U, typename BehaviourU>
	bool					operator != (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) const;

							operator T* () const;

	T*						operator -> () const;
	T&						operator *  () const;

// Counter access:
public:
	CounterT&				GetCounter ();

// Implementation
protected:
	template<typename U, typename BehaviourU>
	void					Swap (CountedPtrImpl<U, CounterT, BehaviourU>& rhs);

	void					Release ();

};

////////////////////////////////////////////////////////////////////////////////
// CountedPtrImpl implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl () :
	m_instance (nullptr),
	m_counter (nullptr)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (U* instance) :
	m_instance (instance),
	m_counter (nullptr)
{
	if (instance != nullptr) {
		++ (*(m_counter = new CounterT ()));
	}
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (std::nullptr_t) :
	m_instance (nullptr),
	m_counter (nullptr)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl& rhs) :
	m_instance (rhs.m_instance),
	m_counter (rhs.m_counter)
{
	if (m_counter != nullptr) {
		++ (*m_counter);
	}
}

// -----------------------------------------------------------------------------
// Move constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (CountedPtrImpl&& rhs) :
	m_instance (std::move (rhs.m_instance)),
	m_counter (std::move (rhs.m_counter))
{
	rhs.m_instance	= nullptr;
	rhs.m_counter	= nullptr;
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) :
	m_instance (rhs.m_instance),
	m_counter (rhs.m_counter)
{
	if (m_counter != nullptr) {
		++ (*m_counter);
	}
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (CountedPtrImpl<U, CounterT, BehaviourU>&& rhs) :
	m_instance (std::move (rhs.m_instance)),
	m_counter (std::move (rhs.m_counter))
{
	rhs.m_instance = nullptr;
	rhs.m_counter = nullptr;
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, StaticCastSelector) :
	m_instance (static_cast<T*> (rhs.m_instance)),
	m_counter (rhs.m_counter)
{
	if (m_counter != nullptr) {
		++ (*m_counter);
	}
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, ConstCastSelector) :
	m_instance (const_cast<T*> (rhs.m_instance)),
	m_counter (rhs.m_counter)
{
	if (m_counter != nullptr) {
		++ (*m_counter);
	}
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, DynamicCastSelector) :
	m_instance (dynamic_cast<T*> (rhs.m_instance)),
	m_counter (rhs.m_counter)
{
	if (m_instance != nullptr && m_counter != nullptr) {
		++ (*m_counter);
	} else {
		m_counter = nullptr;
	}

	CHECK_BADCAST (rhs.m_instance, m_instance);
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
CountedPtrImpl<T, CounterT, BehaviourT>::~CountedPtrImpl ()
{
	Release ();

	GS_DEBUG_ONLY (m_instance = reinterpret_cast<T*> (BadPointer));
	GS_DEBUG_ONLY (m_counter =  reinterpret_cast<CounterT*> (BadPointer));
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (std::nullptr_t)
{
	if (m_instance != nullptr) {
		typedef CountedPtrImpl<T, CounterT, BehaviourT> ThisT;
		ThisT ().Swap (*this);
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U>
inline CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (U* instance)
{
	if (m_instance != instance) {
		typedef CountedPtrImpl<T, CounterT, BehaviourT> ThisT;
		ThisT (instance).Swap (*this);
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (const CountedPtrImpl& rhs)
{
	if (m_counter != rhs.m_counter) {
		typedef CountedPtrImpl<T, CounterT, BehaviourT> ThisT;
		ThisT (rhs).Swap (*this);
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (CountedPtrImpl&& rhs)
{
	if (m_counter != rhs.m_counter) {
		typedef CountedPtrImpl<T, CounterT, BehaviourT> ThisT;
		ThisT (std::move (rhs)).Swap (*this);
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs)
{
	if (m_counter != rhs.m_counter) {
		typedef CountedPtrImpl<T, CounterT, BehaviourT> ThisT;
		ThisT (rhs).Swap (*this);
	}

	return *this;
}


// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (CountedPtrImpl<U, CounterT, BehaviourU>&& rhs)
{
	if (m_counter != rhs.m_counter) {
		typedef CountedPtrImpl<T, CounterT, BehaviourT> ThisT;
		ThisT (std::move (rhs)).Swap (*this);
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline bool		CountedPtrImpl<T, CounterT, BehaviourT>::operator == (std::nullptr_t) const
{
	return (m_counter == nullptr);
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline bool		CountedPtrImpl<T, CounterT, BehaviourT>::operator == (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) const
{
	return (m_counter == rhs.m_counter);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline bool		CountedPtrImpl<T, CounterT, BehaviourT>::operator != (std::nullptr_t) const
{
	return (m_counter != nullptr);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline bool		CountedPtrImpl<T, CounterT, BehaviourT>::operator != (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) const
{
	return (m_counter != rhs.m_counter);
}

// -----------------------------------------------------------------------------
// operator T*
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CountedPtrImpl<T, CounterT, BehaviourT>::operator T* () const
{
	return m_instance;
}

// -----------------------------------------------------------------------------
// operator ->
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline T*		CountedPtrImpl<T, CounterT, BehaviourT>::operator -> () const
{
	CHECK_PTR (m_instance);

	return m_instance;
}

// -----------------------------------------------------------------------------
// operator *
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline T&		CountedPtrImpl<T, CounterT, BehaviourT>::operator * () const
{
	CHECK_PTR (m_instance);

	return *m_instance;
}

////////////////////////////////////////////////////////////////////////////////
// Counter access
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetCounter
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline CounterT&		CountedPtrImpl<T, CounterT, BehaviourT>::GetCounter ()
{
	return *m_counter;
}


////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Swap
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
inline void		CountedPtrImpl<T, CounterT, BehaviourT>::Swap (CountedPtrImpl<U, CounterT, BehaviourU>& rhs)
{
	GS::Swap (m_instance, rhs.m_instance);
	GS::Swap (m_counter, rhs.m_counter);
}

// -----------------------------------------------------------------------------
// Release
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
inline void		CountedPtrImpl<T, CounterT, BehaviourT>::Release ()
{
	if (m_counter != nullptr && -- (*m_counter) == 0) {
		if (m_instance != nullptr) {
			try {
				delete m_instance;
			}
			catch (Exception&) {
				DBBREAK ();
			}
			catch (...) {
				DBBREAK ();
			}
		}

		delete m_counter;
	}

	m_instance = nullptr;
	m_counter = nullptr;
}

}

#ifdef CHECK_PTR
#undef CHECK_PTR
#endif

#ifdef CHECK_BADCAST
#undef CHECK_BADCAST
#endif

#endif // GS_COUNTEDPTRIMPL_HPP
