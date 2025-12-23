
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
#include "ClassCastException.hpp"
#include "Counter.hpp"
#include "GSException.hpp"

// from Standard Library
#include <cstddef>
#include <utility>


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
			throw NullPointerException ("Null pointer.", fileName, lineNumber);
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



// --- ControlBlock ------------------------------------------------------------

namespace GS::Impl {


template<typename CounterT>
struct GS_EXPORT_TYPEINFO ControlBlock {
	CounterT counter {};

	ControlBlock ()
	{
		++counter;
	}

	virtual ~ControlBlock ();

	ControlBlock (const ControlBlock&) = delete;
	ControlBlock& operator= (const ControlBlock&) = delete;
};

template<typename CounterT>
ControlBlock<CounterT>::~ControlBlock () = default;


template<typename CounterT, typename T>
struct GS_EXPORT_TYPEINFO InternalControlBlock : public ControlBlock<CounterT> {
	T object;

	template<typename... Args>
	InternalControlBlock (std::in_place_t, Args&&... args)
		: object (std::forward<Args> (args)...)
	{}

	~InternalControlBlock () override;

	InternalControlBlock (const InternalControlBlock&) = delete;
	InternalControlBlock& operator= (const InternalControlBlock&) = delete;
};

template<typename CounterT, typename T>
InternalControlBlock<CounterT, T>::~InternalControlBlock () = default;


template<typename CounterT, typename T>
struct GS_EXPORT_TYPEINFO ExternalControlBlock : public ControlBlock<CounterT> {
	T* object;

	ExternalControlBlock (T* object)
		: object { object }
	{}

	~ExternalControlBlock () override;

	ExternalControlBlock (const ExternalControlBlock&) = delete;
	ExternalControlBlock& operator= (const ExternalControlBlock&) = delete;
};

template<typename CounterT, typename T>
ExternalControlBlock<CounterT, T>::~ExternalControlBlock ()
{
	delete object;
}


} // namespace GS::Impl



// --- CountedPtrImpl class ----------------------------------------------------

namespace GS {

template<typename T, typename CounterT = Counter, typename BehaviourT = PtrBehaviour>
class CountedPtrImpl {

// Friend classes:
template<typename U, typename CounterU, typename BehaviourU> friend class CountedPtrImpl;

// Data members:
protected:
	T*								m_instance;
	Impl::ControlBlock<CounterT>*	m_control;

// Construction / destruction:
public:
	 CountedPtrImpl ();
	 CountedPtrImpl (std::nullptr_t);
	 template<typename U>
	 CountedPtrImpl (U* instance);
	 template<typename... Args>
	 CountedPtrImpl (std::in_place_t, Args&&...);
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
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl () :
	m_instance (nullptr),
	m_control (nullptr)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (U* instance) :
	m_instance (instance),
	m_control (nullptr)
{
	if (m_instance != nullptr) {
		m_control = new Impl::ExternalControlBlock<CounterT, T> { m_instance };
	}
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename... Args>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (std::in_place_t, Args&&... args)
{
	auto* const control = new Impl::InternalControlBlock<CounterT, T> { std::in_place, std::forward<Args> (args)... };

	m_instance = &control->object;
	m_control = control;
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (std::nullptr_t) :
	m_instance (nullptr),
	m_control (nullptr)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl& rhs) :
	m_instance (rhs.m_instance),
	m_control (rhs.m_control)
{
	if (m_control != nullptr) {
		++m_control->counter;
	}
}

// -----------------------------------------------------------------------------
// Move constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (CountedPtrImpl&& rhs) :
	m_instance (rhs.m_instance),
	m_control (rhs.m_control)
{
	rhs.m_instance	= nullptr;
	rhs.m_control	= nullptr;
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) :
	m_instance (rhs.m_instance),
	m_control (rhs.m_control)
{
	if (m_control != nullptr) {
		++m_control->counter;
	}
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (CountedPtrImpl<U, CounterT, BehaviourU>&& rhs) :
	m_instance (rhs.m_instance),
	m_control (rhs.m_control)
{
	rhs.m_instance = nullptr;
	rhs.m_control = nullptr;
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, StaticCastSelector) :
	m_instance (static_cast<T*> (rhs.m_instance)),
	m_control (rhs.m_control)
{
	if (m_control != nullptr) {
		++m_control->counter;
	}
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, ConstCastSelector) :
	m_instance (const_cast<T*> (rhs.m_instance)),
	m_control (rhs.m_control)
{
	if (m_control != nullptr) {
		++m_control->counter;
	}
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
CountedPtrImpl<T, CounterT, BehaviourT>::CountedPtrImpl (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs, DynamicCastSelector) :
	m_instance (dynamic_cast<T*> (rhs.m_instance)),
	m_control (rhs.m_control)
{
	if (m_instance != nullptr && m_control != nullptr) {
		++m_control->counter;
	} else {
		m_control = nullptr;
	}

	CHECK_BADCAST (rhs.m_instance, m_instance);
}

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
CountedPtrImpl<T, CounterT, BehaviourT>::~CountedPtrImpl ()
{
	if (m_control != nullptr && --m_control->counter == 0) {
		delete m_control;
	}

	GS_DEBUG_ONLY (m_instance = reinterpret_cast<T*> (BadPointer));
	GS_DEBUG_ONLY (m_control =  reinterpret_cast<Impl::ControlBlock<CounterT>*> (BadPointer));
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (std::nullptr_t)
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
CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (U* instance)
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
CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (const CountedPtrImpl& rhs)
{
	if (m_control != rhs.m_control) {
		typedef CountedPtrImpl<T, CounterT, BehaviourT> ThisT;
		ThisT (rhs).Swap (*this);
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (CountedPtrImpl&& rhs)
{
	if (m_control != rhs.m_control) {
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
CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs)
{
	if (m_control != rhs.m_control) {
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
CountedPtrImpl<T, CounterT, BehaviourT>&	CountedPtrImpl<T, CounterT, BehaviourT>::operator = (CountedPtrImpl<U, CounterT, BehaviourU>&& rhs)
{
	if (m_control != rhs.m_control) {
		typedef CountedPtrImpl<T, CounterT, BehaviourT> ThisT;
		ThisT (std::move (rhs)).Swap (*this);
	}

	return *this;
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
bool	CountedPtrImpl<T, CounterT, BehaviourT>::operator == (std::nullptr_t) const
{
	return (m_control == nullptr);
}

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
bool	CountedPtrImpl<T, CounterT, BehaviourT>::operator == (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) const
{
	return (m_control == rhs.m_control);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
bool	CountedPtrImpl<T, CounterT, BehaviourT>::operator != (std::nullptr_t) const
{
	return (m_control != nullptr);
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
bool	CountedPtrImpl<T, CounterT, BehaviourT>::operator != (const CountedPtrImpl<U, CounterT, BehaviourU>& rhs) const
{
	return (m_control != rhs.m_control);
}

// -----------------------------------------------------------------------------
// operator T*
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
CountedPtrImpl<T, CounterT, BehaviourT>::operator T* () const
{
	return m_instance;
}

// -----------------------------------------------------------------------------
// operator ->
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
T*		CountedPtrImpl<T, CounterT, BehaviourT>::operator -> () const
{
	CHECK_PTR (m_instance);

	return m_instance;
}

// -----------------------------------------------------------------------------
// operator *
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
T&		CountedPtrImpl<T, CounterT, BehaviourT>::operator * () const
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
CounterT&	CountedPtrImpl<T, CounterT, BehaviourT>::GetCounter ()
{
	CHECK_PTR (m_control);

	return m_control->counter;
}


////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Swap
// -----------------------------------------------------------------------------

template<typename T, typename CounterT, typename BehaviourT>
template<typename U, typename BehaviourU>
void	CountedPtrImpl<T, CounterT, BehaviourT>::Swap (CountedPtrImpl<U, CounterT, BehaviourU>& rhs)
{
	std::swap (m_instance, rhs.m_instance);
	std::swap (m_control, rhs.m_control);
}

} // namespace GS

#ifdef CHECK_PTR
#undef CHECK_PTR
#endif

#ifdef CHECK_BADCAST
#undef CHECK_BADCAST
#endif

#endif // GS_COUNTEDPTRIMPL_HPP
