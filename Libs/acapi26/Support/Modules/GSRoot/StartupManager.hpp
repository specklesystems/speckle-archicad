
// *****************************************************************************
//
// Declaration of StartupManager class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_STARTUPMANAGER_HPP
#define GS_STARTUPMANAGER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "PagedArray.hpp"
#include "Singleton.hpp"
#include "StartupListener.hpp"



// --- StartupManager class ----------------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT StartupManager {

// Friend classes:
friend class StaticInstantiationHelper<StartupManager>;

// Construction / destruction:
private:
	StartupManager ();
	StartupManager (const StartupManager&); // Disabled

// Operator overloading:
private:
	const StartupManager&	operator = (const StartupManager&); // Disabled

// Operations:
public:
	USize					GetAttachedStartupListeners (PagedArray<StartupListener*>& startupListeners) const;
	bool					IsStartupListenerAttached (StartupListener* startupListener) const;
	
	void					AttachStartupListener (StartupListener* startupListener);
	bool					DetachStartupListener (StartupListener* startupListener);
	
	void					DetachStartupListeners ();

// Static operations:
public:
	static StartupManager&	GetInstance ();

};

}

#endif // GS_STARTUPMANAGER_HPP