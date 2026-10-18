
// *****************************************************************************
//
//                             Class StateObserver
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, AZS
//
// SG compatible
//
// *****************************************************************************


#if !defined STATEOBSERVER_HPP
#define STATEOBSERVER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "EventObserver.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace GS { class StateEventSource; }



// ============================ Class StateObserver ============================

namespace GS {

class GSROOT_DLL_EXPORT StateObserver: public EventObserver {
protected:
	friend class StateEventSource;	// to allow access to Event methods

   ~StateObserver ();

	virtual void	StateChanged (StateEventSource* source);
	virtual void	StateChanged (StateEventSource* source, GS::IntPtr hint);
};

}	// namespace GS

// ____________________________ Class StateObserver ____________________________


#endif
