
// *****************************************************************************
//
//                             Class EventObserver
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, AZS
//
// SG compatible
//
// *****************************************************************************


#if !defined EVENTOBSERVER_HPP
#define EVENTOBSERVER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"

#include "Array.hpp"

// ------------------------------ Predeclarations ------------------------------

namespace GS { class EventSource; }



// ============================ Class EventObserver ============================

namespace GS {

class GSROOT_DLL_EXPORT EventObserver {
private:
	GS::Array<EventSource*> eventSources;
protected:
	friend class EventSource;	// to allow access to event-dispatching methods

	EventObserver ();
	EventObserver (const EventObserver&);
	virtual ~EventObserver ();
	EventObserver& operator = (const EventObserver&);

	virtual void	SourceDestroyed (EventSource* source);
};

}	// namespace GS

// ____________________________ Class EventObserver ____________________________


#endif
