
// *****************************************************************************
//
//                           Class StateEventSource
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, AZS
//
// SG compatible
//
// *****************************************************************************


#if !defined STATEEVENTSOURCE_HPP
#define STATEEVENTSOURCE_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "EventSource.hpp"


// ------------------------------ Predeclarations ------------------------------

namespace GS { class StateObserver; }



// ========================== Class StateEventSource ===========================

namespace GS {

class GSROOT_DLL_EXPORT StateEventSource: public EventSource {
private:
	USize	scopeNestingDepth;	// counts depth of the scope nesting

protected:
	StateEventSource ();
	StateEventSource (const StateEventSource& source);
   ~StateEventSource ();
	StateEventSource&	operator= (const StateEventSource& source);

	void	SendChange (void);
	void	SendChange (GS::IntPtr hint);

	void	OpenScope  (void);
	void	CloseScope (void);

public:
	void	Attach (StateObserver& observer);
	void	Detach (StateObserver& observer);
};

}	// namespace GS

// __________________________ Class StateEventSource ___________________________


#endif
