
// *****************************************************************************
//
// Declaration of MessageContent interface
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENT_HPP
#define COMMUNICATION_MESSAGECONTENT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/CommunicationCommonExport.hpp"

	// from GSRoot
#include "IBinaryChannel.hpp"
#include "OBinaryChannel.hpp"



// --- MessageContent class ----------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API MessageContent {

// Construction / destruction:
protected:
			 MessageContent ();
			 MessageContent (const MessageContent&);
public:
	virtual ~MessageContent ();

// Operator overloading:
protected:
	const MessageContent&			operator = (const MessageContent&);

// Operations:
public:
	virtual GS::UInt64				GetContentLength () const = 0;
	virtual GS::IBinaryChannelRef	GetContent () const = 0;
	
	virtual void					WriteTo (GS::OBinaryChannel& oc) const;

};

typedef GS::Ref<MessageContent, GS::Counter> MessageContentRef;

////////////////////////////////////////////////////////////////////////////////
// MessageContent inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline MessageContent::MessageContent ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline MessageContent::MessageContent (const MessageContent&)
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator =
// -----------------------------------------------------------------------------

inline const MessageContent&	MessageContent::operator = (const MessageContent&)
{
	return *this;
}

}

#endif // COMMUNICATION_MESSAGECONTENT_HPP