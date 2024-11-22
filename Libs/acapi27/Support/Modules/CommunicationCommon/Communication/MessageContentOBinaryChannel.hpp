
// *****************************************************************************
//
// Declaration of MessageContentOBinaryChannel interface
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENTOBINARYCHANNEL_HPP
#define COMMUNICATION_MESSAGECONTENTOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentChannelAbortedException.hpp"
#include "Communication/MessageContentChannelClosedException.hpp"

	// from GSRoot
#include "OBinaryChannel.hpp"
#include "UniString.hpp"



// --- MessageContentOBinaryChannel class --------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API MessageContentOBinaryChannel : public GS::OBinaryChannel {

// Construction / destruction:
protected:
			 MessageContentOBinaryChannel () = default;
			 MessageContentOBinaryChannel (const MessageContentOBinaryChannel&) = default;
public:
	virtual ~MessageContentOBinaryChannel ();

// Operator overloading:
protected:
	MessageContentOBinaryChannel&	operator = (const MessageContentOBinaryChannel&) = default;

// Operations:
public:
	virtual bool					IsAbortable () const = 0;
	virtual bool					IsAborted () const = 0;

	virtual void					Abort (const GS::UniString& message) = 0;
	virtual void					Abort () = 0;

};

typedef GS::Ref<MessageContentOBinaryChannel, GS::AtomicCounter> MessageContentOBinaryChannelRef;

}

#endif // COMMUNICATION_MESSAGECONTENTOBINARYCHANNEL_HPP