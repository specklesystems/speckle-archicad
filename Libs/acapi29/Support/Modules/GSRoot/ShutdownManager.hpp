
// *****************************************************************************
//
// Declaration of ShutdownManager class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_SHUTDOWNMANAGER_HPP
#define GS_SHUTDOWNMANAGER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "PagedArray.hpp"
#include "RunnableTask.hpp"
#include "ShutdownListener.hpp"
#include "Singleton.hpp"



// --- ShutdownManager class ---------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT ShutdownManager {

// Friend classes:
friend class StaticInstantiationHelper<ShutdownManager>;

// Construction / destruction:
private:
	 ShutdownManager ();
	 ShutdownManager (const ShutdownManager&); // Disabled

// Operator overloading:
private:
	const ShutdownManager&		operator = (const ShutdownManager&); // Disabled

// Operations:
public:
	USize						GetAttachedShutdownListeners (PagedArray<ShutdownListener*>& shutdownListeners) const;
	bool						IsShutdownListenerAttached (ShutdownListener* shutdownListener) const;

	void						AttachShutdownListener (ShutdownListener* shutdownListener);
	bool						DetachShutdownListener (ShutdownListener* shutdownListener);

	void						DetachShutdownListeners ();

	USize						GetRegisteredShutdownTasks (PagedArray<RunnableTask>& shutdownTasks) const;
	bool						IsShutdownTaskRegistered (const RunnableTask& shutdownTask) const;

	void						RegisterShutdownTask (const RunnableTask& shutdownTask);
	bool						RevokeShutdownTask (const RunnableTask& shutdownTask);
	void						ClearShutdownTasks ();

// Static operations:
public:
	static ShutdownManager&		GetInstance ();

};

}

#endif // GS_SHUTDOWNMANAGER_HPP
