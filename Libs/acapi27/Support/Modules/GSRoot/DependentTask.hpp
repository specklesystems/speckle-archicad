
// *****************************************************************************
//
// Declaration of DependentTask abstract class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_DEPENDENTTASK_HPP
#define GS_DEPENDENTTASK_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Runnable.hpp"
#include "SpinLock.hpp"



// --- Forward declarations ----------------------------------------------------

namespace GS {

class DependentResource;

}



// --- DependentTask class -----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT DependentTask : public Runnable {

// Friend classes:
friend class DependentResource;

// Data members:
private:
	DependentResource*		m_resource;
	volatile bool			m_deleting;
	volatile bool			m_started;
	volatile bool			m_ended;
	mutable SpinLock		m_lock;

// Construction / destruction:
protected:
	explicit DependentTask (DependentResource* resource);
private:
			 DependentTask (const DependentTask&); // Disabled
public:
	virtual ~DependentTask ();

// Operator overloading:
private:
	const DependentTask&	operator = (const DependentTask&); // Disabled

// Operations:
public:
	bool					IsCanceled () const;
	bool					IsStarted () const;
	bool					IsEnded () const;

// Runnable interface implementation:
public:
	virtual void			Run () override;

// Implementation:
protected:
	virtual void			Execute (DependentResource* resource) = 0;
private:
	bool					ResourceDeleting ();

};

}

#endif // GS_DEPENDENTTASK_HPP