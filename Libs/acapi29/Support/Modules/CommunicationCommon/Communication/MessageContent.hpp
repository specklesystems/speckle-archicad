
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
			 MessageContent () = default;
			 MessageContent (const MessageContent&) = default;
public:
	virtual ~MessageContent ();

// Operator overloading:
protected:
	MessageContent&					operator = (const MessageContent&) = default;

// Operations:
public:
	virtual GS::UInt64				GetContentLength () const = 0;
	virtual GS::IBinaryChannelRef	GetContent () const = 0;
	
	virtual void					WriteTo (GS::OBinaryChannel& oc) const;

};

typedef GS::Ref<MessageContent, GS::Counter> MessageContentRef;

}

#endif // COMMUNICATION_MESSAGECONTENT_HPP