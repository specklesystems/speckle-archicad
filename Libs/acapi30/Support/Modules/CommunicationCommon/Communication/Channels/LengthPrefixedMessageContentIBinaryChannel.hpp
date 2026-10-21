
// *****************************************************************************
//
// Declaration of LengthPrefixedMessageContentIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_LENGTHPREFIXEDMESSAGECONTENTIBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_LENGTHPREFIXEDMESSAGECONTENTIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentIBinaryChannel.hpp"

	// from GSRoot
#include "IOBinProtocolXs.hpp"



// --- LengthPrefixedMessageContentIBinaryChannel class ------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API LengthPrefixedMessageContentIBinaryChannel : public MessageContentIBinaryChannel {

// Data members:
private:
	GS::IBinaryChannelRef							m_inputChannelRef;
	GS::IBinaryChannel*								m_inputChannel;

	const GS::IProtocolX&							m_inputProtocol;

	GS::UInt64										m_length;
	GS::UInt64										m_read;

	bool											m_closed;

// Construction / destruction:
public:
	explicit LengthPrefixedMessageContentIBinaryChannel (const GS::IBinaryChannelRef& inputChannel, const GS::IProtocolX& inputProtocol = GS::GetNetworkByteOrderIProtocolX ());
	explicit LengthPrefixedMessageContentIBinaryChannel (GS::IBinaryChannel& inputChannel, const GS::IProtocolX& inputProtocol = GS::GetNetworkByteOrderIProtocolX ());
			 LengthPrefixedMessageContentIBinaryChannel (const LengthPrefixedMessageContentIBinaryChannel&) = delete;
	virtual ~LengthPrefixedMessageContentIBinaryChannel ();

// Operator overloading:
public:
	LengthPrefixedMessageContentIBinaryChannel&		operator = (const LengthPrefixedMessageContentIBinaryChannel&) = delete;

// MessageContentIBinaryChannel interface implementation:
public:
	virtual bool									HasMoreContent () const override;
	virtual bool									IsAbortable () const override;
	virtual bool									IsAborted () const override;

// IBinaryChannel interface implementation:
public:
	virtual GS::UInt64								GetAvailable () const override;

	virtual GS::USize								Read (char* target, GS::USize targetSize, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;

	virtual void									Close () override;

// Implementation:
private:
	void											CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

	GS::IBinaryChannel&								GetInputChannel () const;
	GS::IBinaryChannel&								GetInputChannel ();

	bool											IsClosed () const;

	void											ReadLength ();

	bool											IsEOS () const;

};

}
}

#endif // COMMUNICATION_CHANNELS_LENGTHPREFIXEDMESSAGECONTENTIBINARYCHANNEL_HPP