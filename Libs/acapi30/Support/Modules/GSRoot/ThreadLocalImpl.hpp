
// *****************************************************************************
//
// Declaration of ThreadLocalImpl abstract class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADLOCALIMPL_HPP
#define GS_THREADLOCALIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "ThreadLocalKey.hpp"
#include "ThreadLocalValue.hpp"



// --- ThreadLocalImpl class ---------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadLocalImpl {

// Data members:
protected:
	ThreadLocalKey				m_key;

// Construction / destruction:
protected:
			 ThreadLocalImpl ();
			 ThreadLocalImpl (const ThreadLocalImpl& rhs);
public:
	virtual ~ThreadLocalImpl ();

// Operator overloading:
protected:
	const ThreadLocalImpl&		operator = (const ThreadLocalImpl& rhs);

// Operations:
public:
	ThreadLocalValueBase&		GetValue (ThreadLocalValueBase* (*pfnCeateValue) ()) const;
	void						Clear ();

// Nested classes:
public:
	template<class T>
	class DefaultInitializator {

	// Operator overloading:
	public:
		void		operator () (T&) { }

	};

	template<class T>
	class NullInitializator {

	// Operator overloading:
	public:
		void		operator () (T& v) { v = 0; }

	};

};

////////////////////////////////////////////////////////////////////////////////
// ThreadLocalImpl inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ThreadLocalImpl::ThreadLocalImpl (const ThreadLocalImpl& rhs) :
	m_key (rhs.m_key)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ThreadLocalImpl&	ThreadLocalImpl::operator = (const ThreadLocalImpl& rhs)
{
	if (this != &rhs) {
		m_key = rhs.m_key;
	}

	return *this;
}

}

#endif // GS_THREADLOCALIMPL_HPP
