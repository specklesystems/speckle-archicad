
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


#if !defined TSEVENTOBSERVER_HPP
#define TSEVENTOBSERVER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Array.hpp"
#include "ThreadingDebug.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace GS {
	namespace TS {
		class EventSource;
	}
}


// ============================ Class EventObserver ============================

namespace GS { namespace TS {

class GSROOT_DLL_EXPORT EventObserver : public NonThreadSafeClass {
private:
	typedef ArrayFB<EventSource*, 1>	TEventSourceContainer;
	TEventSourceContainer				eventSources;
	static ULong						maxItem;

protected:
	friend class EventSource;	// to allow access to event-dispatching methods

					EventObserver (void);
					EventObserver (const EventObserver& source);
	EventObserver&	operator= (const EventObserver& source);

	virtual			~EventObserver ();

	virtual void	SourceDestroyed (EventSource* source);
};

}	// namespace TS
}	// namespace GS

// ____________________________ Class EventObserver ____________________________


#endif
