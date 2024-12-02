
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
			 MessageContentIBinaryChannel ();
			 MessageContentIBinaryChannel (const MessageContentIBinaryChannel& rhs);
public:
	virtual ~MessageContentIBinaryChannel ();

// Operator overloading:
protected:
	const MessageContentIBinaryChannel&		operator = (const MessageContentIBinaryChannel& rhs);

// Operations:
public:
	virtual bool							HasMoreContent () const = 0;
	virtual bool							IsAbortable () const = 0;
	virtual bool							IsAborted () const = 0;

};

typedef GS::Ref<MessageContentIBinaryChannel, GS::AtomicCounter> MessageContentIBinaryChannelRef;

////////////////////////////////////////////////////////////////////////////////
// MessageContentIBinaryChannel inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline MessageContentIBinaryChannel::MessageContentIBinaryChannel () :
	GS::IBinaryChannel ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline MessageContentIBinaryChannel::MessageContentIBinaryChannel (const MessageContentIBinaryChannel& rhs) :
	GS::IBinaryChannel (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const MessageContentIBinaryChannel&	MessageContentIBinaryChannel::operator = (const MessageContentIBinaryChannel& rhs)
{
	GS::IBinaryChannel::operator = (rhs);
	
	return *this;
}

}

#endif // COMMUNICATION_MESSAGECONTENTIBINARYCHANNEL_HPP