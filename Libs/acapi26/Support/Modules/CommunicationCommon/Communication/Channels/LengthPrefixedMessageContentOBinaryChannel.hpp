
// *****************************************************************************
//
// Declaration of LengthPrefixedMessageContentOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_LENGTHPREFIXEDMESSAGECONTENTOBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_LENGTHPREFIXEDMESSAGECONTENTOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentOBinaryChannel.hpp"

	// from GSRoot
#include "IOBinProtocolXs.hpp"
#include "MemoryOBinaryChannel.hpp"



// --- LengthPrefixedMessageContentOBinaryChannel class ------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API LengthPrefixedMessageContentOBinaryChannel : public MessageContentOBinaryChannel {

// Data members:
private:
	GS::OBinaryChannelRef							m_outputChannelRef;
	GS::OBinaryChannel*								m_outputChannel;

	const GS::OProtocolX&							m_outputProtocol;

	GS::MemoryOBinaryChannel						m_buffer;

	bool											m_closed;

// Construction / destruction:
public:
	explicit LengthPrefixedMessageContentOBinaryChannel (const GS::OBinaryChannelRef& outputChannel, const GS::OProtocolX& outputProtocol = GS::GetNetworkByteOrderOProtocolX ());
	explicit LengthPrefixedMessageContentOBinaryChannel (GS::OBinaryChannel& outputChannel, const GS::OProtocolX& outputProtocol = GS::GetNetworkByteOrderOProtocolX ());
			 LengthPrefixedMessageContentOBinaryChannel (const LengthPrefixedMessageContentOBinaryChannel&) = delete;
	virtual ~LengthPrefixedMessageContentOBinaryChannel ();

// Operator overloading:
public:
	LengthPrefixedMessageContentOBinaryChannel&		operator = (const LengthPrefixedMessageContentOBinaryChannel&) = delete;

// MessageContentOBinaryChannel interface implementation:
public:
	virtual bool									IsAbortable () const override;
	virtual bool									IsAborted () const override;

	virtual void									Abort (const GS::UniString& message) override;
	virtual void									Abort () override;

// OBinaryChannel interface implementation:
public:
	virtual void									Write (const char* source, USize nOfCharToWrite) override;
	virtual void									Flush () override;
	virtual void									Close () override; 

// Implementation:
private:
	void											CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

	GS::OBinaryChannel&								GetOutputChannel () const;
	GS::OBinaryChannel&								GetOutputChannel ();

	bool											IsClosed () const;

};

}
}

#endif // COMMUNICATION_CHANNELS_LENGTHPREFIXEDMESSAGECONTENTOBINARYCHANNEL_HPP