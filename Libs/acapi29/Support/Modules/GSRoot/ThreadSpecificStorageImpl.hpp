
// *****************************************************************************
//
// Declaration of ThreadSpecificStorageImpl abstract class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADSPECIFICSTORAGEIMPL_HPP
#define GS_THREADSPECIFICSTORAGEIMPL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"




// --- ThreadSpecificStorageImpl class -----------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ThreadSpecificStorageImpl {

// Construction / destruction:
protected:
			 ThreadSpecificStorageImpl ();
			 ThreadSpecificStorageImpl (const ThreadSpecificStorageImpl&);
public:
	virtual ~ThreadSpecificStorageImpl ();

// Operator overloading:
protected:
	const ThreadSpecificStorageImpl&	operator = (const ThreadSpecificStorageImpl&);

// Operations:
public:
	virtual IntPtr						Get () const = 0;
	virtual void						Set (IntPtr value) = 0;

	virtual ThreadSpecificStorageImpl*	Clone () const = 0;

// Static operations:
public:
	static ThreadSpecificStorageImpl*	Create ();

};

////////////////////////////////////////////////////////////////////////////////
// ThreadSpecificStorageImpl inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ThreadSpecificStorageImpl::ThreadSpecificStorageImpl ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ThreadSpecificStorageImpl::ThreadSpecificStorageImpl (const ThreadSpecificStorageImpl&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ThreadSpecificStorageImpl&	ThreadSpecificStorageImpl::operator = (const ThreadSpecificStorageImpl&)
{
	return *this;
}

}

#endif // GS_THREADSPECIFICSTORAGEIMPL_HPP
