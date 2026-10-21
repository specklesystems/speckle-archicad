
// *****************************************************************************
//
// Declaration of ChunkedMessageContentIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_CHUNKEDMESSAGECONTENTIBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_CHUNKEDMESSAGECONTENTIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentIBinaryChannel.hpp"

	// from GSRoot
#include "IOBinProtocolXs.hpp"
#include "UniString.hpp"



// --- ChunkedMessageContentIBinaryChannel class -------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API ChunkedMessageContentIBinaryChannel : public MessageContentIBinaryChannel {

// Data members:
private:
	GS::IBinaryChannelRef					m_inputChannelRef;
	GS::IBinaryChannel*						m_inputChannel;

	const GS::IProtocolX&					m_inputProtocol;

	GS::UniString							m_abortMessage;
	GS::USize								m_remaining;

	bool									m_aborted;
	bool									m_closed;

// Construction / destruction:
public:
	explicit ChunkedMessageContentIBinaryChannel (const GS::IBinaryChannelRef& inputChannel, const GS::IProtocolX& inputProtocol = GS::GetNetworkByteOrderIProtocolX ());
	explicit ChunkedMessageContentIBinaryChannel (GS::IBinaryChannel& inputChannel, const GS::IProtocolX& inputProtocol = GS::GetNetworkByteOrderIProtocolX ());
			 ChunkedMessageContentIBinaryChannel (const ChunkedMessageContentIBinaryChannel&) = delete;
	virtual ~ChunkedMessageContentIBinaryChannel ();

// Operator overloading:
public:
	ChunkedMessageContentIBinaryChannel&	operator = (const ChunkedMessageContentIBinaryChannel&) = delete;

// MessageContentIBinaryChannel interface implementation:
public:
	virtual bool							HasMoreContent () const override;
	virtual bool							IsAbortable () const override;
	virtual bool							IsAborted () const override;

// IBinaryChannel interface implementation:
public:
	virtual GS::UInt64						GetAvailable () const override;

	virtual GS::USize						Read (char* destination, GS::USize nOfCharToRead, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	
	virtual void							Close () override;

// Implementation:
private:
	void									CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;
	void									CheckValid (const char* sourceFile, GS::UInt32 sourceLine) const;

	GS::IBinaryChannel&						GetInputChannel () const;
	GS::IBinaryChannel&						GetInputChannel ();

	bool									IsClosed () const;

	void									ReadChunkHeader ();

	bool									IsEOS () const;

};

}
}

#endif // COMMUNICATION_CHANNELS_CHUNKEDMESSAGECONTENTIBINARYCHANNEL_HPP