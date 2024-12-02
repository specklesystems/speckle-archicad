
// *****************************************************************************
//
// Declaration of MessageContentIBinaryChannelWrapper class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_MESSAGECONTENTIBINARYCHANNELWRAPPER_HPP
#define COMMUNICATION_MESSAGECONTENTIBINARYCHANNELWRAPPER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentIBinaryChannel.hpp"



// --- MessageContentIBinaryChannelWrapper class -------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API MessageContentIBinaryChannelWrapper : public MessageContentIBinaryChannel {

// Data members:
private:
	MessageContentIBinaryChannelRef			m_inputChannel;

// Construction / destruction:
public:
	explicit MessageContentIBinaryChannelWrapper (const MessageContentIBinaryChannelRef& inputChannel);
			 MessageContentIBinaryChannelWrapper (const MessageContentIBinaryChannelWrapper&) = delete;

// Operator overloading:
public:
	MessageContentIBinaryChannelWrapper&	operator = (const MessageContentIBinaryChannelWrapper&) = delete;

// MessageContentIBinaryChannel interface implementation:
public:
	virtual bool							HasMoreContent () const override;
	virtual bool							IsAbortable () const override;
	virtual bool							IsAborted () const override;

// IBinaryChannel interface implementation:
public:
	virtual GS::USize						Read (char* destination, GS::USize nOfCharToRead, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	virtual GS::UInt64						GetAvailable () const override;
	virtual void							Close () override;

// Operations:
public:
	void									SetChannel (const MessageContentIBinaryChannelRef& inputChannel);
	const MessageContentIBinaryChannelRef&	GetChannel () const;

};

typedef GS::Ref<MessageContentIBinaryChannelWrapper, GS::AtomicCounter> MessageContentIBinaryChannelWrapperRef;

}

#endif // COMMUNICATION_MESSAGECONTENTIBINARYCHANNELWRAPPER_HPP