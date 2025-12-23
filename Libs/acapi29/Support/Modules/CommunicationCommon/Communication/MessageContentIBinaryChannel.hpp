
// *****************************************************************************
//
// Declaration of MessageContentIBinaryChannel interface
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENTIBINARYCHANNEL_HPP
#define COMMUNICATION_MESSAGECONTENTIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentChannelAbortedException.hpp"
#include "Communication/MessageContentChannelClosedException.hpp"

	// from GSRoot
#include "IBinaryChannel.hpp"



// --- MessageContentIBinaryChannel class --------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API MessageContentIBinaryChannel : public GS::IBinaryChannel {

// Construction / destruction:
protected:
			 MessageContentIBinaryChannel () = default;
			 MessageContentIBinaryChannel (const MessageContentIBinaryChannel&) = default;
public:
	virtual ~MessageContentIBinaryChannel ();

// Operator overloading:
protected:
	MessageContentIBinaryChannel&	operator = (const MessageContentIBinaryChannel&) = default;

// Operations:
public:
	virtual bool					HasMoreContent () const = 0;
	virtual bool					IsAbortable () const = 0;
	virtual bool					IsAborted () const = 0;

};

typedef GS::Ref<MessageContentIBinaryChannel, GS::AtomicCounter> MessageContentIBinaryChannelRef;

}

#endif // COMMUNICATION_MESSAGECONTENTIBINARYCHANNEL_HPP