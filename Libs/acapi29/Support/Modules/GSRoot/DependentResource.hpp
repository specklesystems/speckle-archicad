
// *****************************************************************************
//
// Declaration of DependentResource class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_DEPENDENTRESOURCE_HPP
#define GS_DEPENDENTRESOURCE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Condition.hpp"
#include "DependentTask.hpp"
#include "HashSet.hpp"
#include "Lock.hpp"



// --- DependentResource class -------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT DependentResource {

// Friend classes:
friend class DependentTask;

// Type definitions:
protected:
	typedef HashSet<DependentTask*> DependentTasks; 

// Data members:
protected:
	DependentTasks				m_tasks;
	Condition					m_taskEnded;
	mutable Lock				m_lock;

// Construction / destruction:
protected:
			 DependentResource ();
private:
			 DependentResource (const DependentResource&); // Disabled
public:
	virtual ~DependentResource ();

// Operator overloading:
private:
	const DependentResource&	operator = (const DependentResource&); // Disabled

// Implementation:
protected:
	void						Destroy ();
private:
	void						TaskCreated (DependentTask* task);
	void						TaskDeleted (DependentTask* task);
	void						TaskStarted (DependentTask* task);
	void						TaskEnded (DependentTask* task);

};

}

#endif // GS_DEPENDENTRESOURCE_HPP