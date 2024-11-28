
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
			 MessageContentOBinaryChannel ();
			 MessageContentOBinaryChannel (const MessageContentOBinaryChannel& rhs);
public:
	virtual ~MessageContentOBinaryChannel ();

// Operator overloading:
protected:
	const MessageContentOBinaryChannel&		operator = (const MessageContentOBinaryChannel& rhs);

// Operations:
public:
	virtual bool							IsAbortable () const = 0;
	virtual bool							IsAborted () const = 0;

	virtual void							Abort (const GS::UniString& message) = 0;
	virtual void							Abort () = 0;

};

typedef GS::Ref<MessageContentOBinaryChannel, GS::AtomicCounter> MessageContentOBinaryChannelRef;

////////////////////////////////////////////////////////////////////////////////
// MessageContentOBinaryChannel inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline MessageContentOBinaryChannel::MessageContentOBinaryChannel () :
	GS::OBinaryChannel ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline MessageContentOBinaryChannel::MessageContentOBinaryChannel (const MessageContentOBinaryChannel& rhs) :
	GS::OBinaryChannel (rhs)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const MessageContentOBinaryChannel&	MessageContentOBinaryChannel::operator = (const MessageContentOBinaryChannel& rhs)
{
	GS::OBinaryChannel::operator = (rhs);
	
	return *this;
}

}

#endif // COMMUNICATION_MESSAGECONTENTOBINARYCHANNEL_HPP