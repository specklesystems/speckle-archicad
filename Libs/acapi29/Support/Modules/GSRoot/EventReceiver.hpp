
// *****************************************************************************
//
//                              Class EventReceiver
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined EVENTRECEIVER_HPP
#define EVENTRECEIVER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"

#include "Array.hpp"

namespace GS { class EventSenderBase; }
namespace GS { template <class... Args> class EventSenderBaseImp; }

// ============================ Class EventReceiver ============================

namespace GS {

class GSROOT_DLL_EXPORT EventReceiver {
private:
	GS::Array<EventSenderBase*> eventSenders;	// senders of the receiver

	template <class... Args>
	friend class EventSenderBaseImp;			// to allow access to eventSenders

public:
	inline EventReceiver () = default;
	inline EventReceiver (const EventReceiver&) = default;
	inline EventReceiver& operator = (const EventReceiver&) = default;
   ~EventReceiver ();
};

}	// namespace GS

#endif
