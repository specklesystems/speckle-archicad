
// *****************************************************************************
//
// Declaration of ThreadLocalValue<T> class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADLOCALVALUE_HPP
#define GS_THREADLOCALVALUE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"



// --- ThreadLocalValueBase class ----------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadLocalValueBase {

// Construction / destruction:
protected:
			 ThreadLocalValueBase ();
private:
			 ThreadLocalValueBase (const ThreadLocalValueBase&); // Disabled
public:
	virtual ~ThreadLocalValueBase ();

// Operator overloading:
private:
	const ThreadLocalValueBase&		operator = (const ThreadLocalValueBase&); // Disabled

};

////////////////////////////////////////////////////////////////////////////////
// ThreadLocalValueBase inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ThreadLocalValueBase::ThreadLocalValueBase ()
{
	// Empty constructor body
}

}



// --- ThreadLocalValue<T> class -----------------------------------------------

namespace GS {

template<class T>
class ThreadLocalValue : public ThreadLocalValueBase {

// Data members:
private:
	T			m_value;

// Construction / destruction:
public:
			 ThreadLocalValue ();
	explicit ThreadLocalValue (const T& value);

// Operations:
public:
	const T&	Get () const;
	T&			Get ();
	void		Set (const T& value);

};

////////////////////////////////////////////////////////////////////////////////
// ThreadLocalValue implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<class T>
inline ThreadLocalValue<T>::ThreadLocalValue () :
	m_value ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class T>
inline ThreadLocalValue<T>::ThreadLocalValue (const T& value) :
	m_value (value)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<class T>
inline const T&		ThreadLocalValue<T>::Get () const
{
	return m_value;
}

// -----------------------------------------------------------------------------
// Get
// -----------------------------------------------------------------------------

template<class T>
inline T&	ThreadLocalValue<T>::Get ()
{
	return m_value;
}

// -----------------------------------------------------------------------------
// Set
// -----------------------------------------------------------------------------

template<class T>
inline void		ThreadLocalValue<T>::Set (const T& value)
{
	m_value = value;
}

}

#endif // GS_THREADLOCALVALUE_HPP
