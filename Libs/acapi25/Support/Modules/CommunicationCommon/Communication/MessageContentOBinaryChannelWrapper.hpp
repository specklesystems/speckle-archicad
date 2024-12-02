
// *****************************************************************************
//
// Declaration of MessageContentOBinaryChannelWrapper class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENTOBINARYCHANNELWRAPPER_HPP
#define COMMUNICATION_MESSAGECONTENTOBINARYCHANNELWRAPPER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentOBinaryChannel.hpp"



// --- MessageContentOBinaryChannelWrapper class -------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API MessageContentOBinaryChannelWrapper : public MessageContentOBinaryChannel {

// Data members:
private:
	MessageContentOBinaryChannelRef				m_outputChannel;

// Construction / destruction:
public:
	explicit MessageContentOBinaryChannelWrapper (const MessageContentOBinaryChannelRef& outputChannel);
private:
			 MessageContentOBinaryChannelWrapper (const MessageContentOBinaryChannelWrapper&); // Disabled

// Operator overloading:
private:
	const MessageContentOBinaryChannelWrapper&	operator = (const MessageContentOBinaryChannelWrapper&); // Disabled

// MessageContentOBinaryChannel interface implementation:
public:
	virtual bool								IsAbortable () const override;
	virtual bool								IsAborted () const override;

	virtual void								Abort (const GS::UniString& message) override;
	virtual void								Abort () override;

// OBinaryChannel interface implementation:
public:
	virtual void								Write (const char* source, USize nOfCharToWrite) override;
	virtual void								Flush () override;
	virtual void								Close () override;

// Operations:
public:
	void										SetChannel (const MessageContentOBinaryChannelRef& outputChannel);
	const MessageContentOBinaryChannelRef&		GetChannel () const;

};

typedef GS::Ref<MessageContentOBinaryChannelWrapper, GS::AtomicCounter> MessageContentOBinaryChannelWrapperRef;

}

#endif // COMMUNICATION_MESSAGECONTENTOBINARYCHANNELWRAPPER_HPP