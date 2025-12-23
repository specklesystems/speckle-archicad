
// *****************************************************************************
//
// Declaration of CountingMessageContentIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_COUNTINGMESSAGECONTENTIBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_COUNTINGMESSAGECONTENTIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentIBinaryChannel.hpp"



// --- CountingMessageContentIBinaryChannel class ------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API CountingMessageContentIBinaryChannel : public MessageContentIBinaryChannel {

// Data members:
private:
	MessageContentIBinaryChannelRef			m_inputChannelRef;
	MessageContentIBinaryChannel*			m_inputChannel;

	GS::UInt64								m_count;

// Construction / destruction:
public:
	explicit CountingMessageContentIBinaryChannel (const MessageContentIBinaryChannelRef& inputChannel);
	explicit CountingMessageContentIBinaryChannel (MessageContentIBinaryChannel& inputChannel);
			 CountingMessageContentIBinaryChannel (const CountingMessageContentIBinaryChannel&) = delete;
	virtual ~CountingMessageContentIBinaryChannel ();

// Operator overloading:
public:
	CountingMessageContentIBinaryChannel&	operator = (const CountingMessageContentIBinaryChannel&) = delete;

// Operations:
public:
	GS::UInt64								GetCount () const;

	void									ResetCount ();

// MessageContentIBinaryChannel interface implementation:
public:
	virtual bool							HasMoreContent () const override;
	
	virtual bool							IsAbortable () const override;
	virtual bool							IsAborted () const override;

	virtual GS::UInt64						GetAvailable () const override;

	virtual GS::USize						Read (char* destination, GS::USize nOfCharToRead, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	
	virtual void							Close () override;

// Implementation:
private:
	MessageContentIBinaryChannel&			GetInputChannel () const;
	MessageContentIBinaryChannel&			GetInputChannel ();

};

////////////////////////////////////////////////////////////////////////////////
// CountingMessageContentIBinaryChannel inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////
	
// -----------------------------------------------------------------------------
// GetCount
// -----------------------------------------------------------------------------

inline GS::UInt64	CountingMessageContentIBinaryChannel::GetCount () const
{
	return m_count;
}

// -----------------------------------------------------------------------------
// ResetCount
// -----------------------------------------------------------------------------

inline void		CountingMessageContentIBinaryChannel::ResetCount ()
{
	m_count = 0;
}

}
}

#endif // COMMUNICATION_CHANNELS_COUNTINGMESSAGECONTENTIBINARYCHANNEL_HPP