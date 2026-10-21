
// *****************************************************************************
//
// Declaration of ThreadListener interface
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_THREADLISTENER_HPP
#define GS_THREADLISTENER_HPP

#pragma once


// --- Forward declarations ----------------------------------------------------

namespace GS {

class ThreadImpl;

}



// --- ThreadListener class ----------------------------------------------------

namespace GS {

class ThreadListener {

// Construction / destruction:
protected:
			 ThreadListener ();
			 ThreadListener (const ThreadListener&);
public:
	virtual ~ThreadListener ();

// Operator overloading:
protected:
	const ThreadListener&	operator = (const ThreadListener&);

// Operations:
public:
	virtual void			ThreadCreated (ThreadImpl* thread) = 0;
	virtual void			ThreadStarted (ThreadImpl* thread) = 0;
	virtual void			ThreadStopped (ThreadImpl* thread) = 0;
	virtual void			ThreadDeleted (ThreadImpl* thread) = 0;

};

////////////////////////////////////////////////////////////////////////////////
// ThreadListener inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline ThreadListener::ThreadListener ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline ThreadListener::ThreadListener (const ThreadListener&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const ThreadListener&	ThreadListener::operator = (const ThreadListener&)
{
	return *this;
}

}

#endif // GS_THREADLISTENER_HPP