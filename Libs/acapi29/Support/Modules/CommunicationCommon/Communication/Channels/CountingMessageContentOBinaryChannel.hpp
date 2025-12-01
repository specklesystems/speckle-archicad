
// *****************************************************************************
//
// Declaration of CountingMessageContentOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_COUNTINGMESSAGECONTENTOBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_COUNTINGMESSAGECONTENTOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentOBinaryChannel.hpp"



// --- CountingMessageContentOBinaryChannel class ------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API CountingMessageContentOBinaryChannel : public MessageContentOBinaryChannel {

// Data members:
private:
	MessageContentOBinaryChannelRef			m_outputChannelRef;
	MessageContentOBinaryChannel*			m_outputChannel;

	GS::UInt64								m_count;

// Construction / destruction:
public:
	explicit CountingMessageContentOBinaryChannel (const MessageContentOBinaryChannelRef& outputChannel);
	explicit CountingMessageContentOBinaryChannel (MessageContentOBinaryChannel& outputChannel);
			 CountingMessageContentOBinaryChannel (const CountingMessageContentOBinaryChannel&) = delete;
	virtual ~CountingMessageContentOBinaryChannel ();

// Operator overloading:
public:
	CountingMessageContentOBinaryChannel&	operator = (const CountingMessageContentOBinaryChannel&) = delete;

// Operations:
public:
	GS::UInt64								GetCount () const;

	void									ResetCount ();

// MessageContentOBinaryChannel interface implementation:
public:
	virtual bool							IsAbortable () const override;
	virtual bool							IsAborted () const override;

	virtual void							Abort (const GS::UniString& message) override;
	virtual void							Abort () override;

	virtual void							Write (const char* source, USize nOfCharToWrite) override;
	
	virtual void							Flush () override;
	
	virtual void							Close () override;

// Implementation:
private:
	MessageContentOBinaryChannel&			GetOutputChannel () const;
	MessageContentOBinaryChannel&			GetOutputChannel ();

};

////////////////////////////////////////////////////////////////////////////////
// CountingMessageContentOBinaryChannel inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetCount
// -----------------------------------------------------------------------------

inline GS::UInt64	CountingMessageContentOBinaryChannel::GetCount () const
{
	return m_count;
}

// -----------------------------------------------------------------------------
// ResetCount
// -----------------------------------------------------------------------------

inline void		CountingMessageContentOBinaryChannel::ResetCount ()
{
	m_count = 0;
}

}
}

#endif // COMMUNICATION_CHANNELS_COUNTINGMESSAGECONTENTOBINARYCHANNEL_HPP