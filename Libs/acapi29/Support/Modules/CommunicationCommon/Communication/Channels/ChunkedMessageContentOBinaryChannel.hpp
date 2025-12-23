
// *****************************************************************************
//
// Declaration of ChunkedMessageContentOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_CHUNKEDMESSAGECONTENTOBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_CHUNKEDMESSAGECONTENTOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentOBinaryChannel.hpp"

	// from GSRoot
#include "IOBinProtocolXs.hpp"



// --- ChunkedMessageContentOBinaryChannel class -------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API ChunkedMessageContentOBinaryChannel : public MessageContentOBinaryChannel {

// Data members:
private:
	GS::OBinaryChannelRef					m_outputChannelRef;
	GS::OBinaryChannel*						m_outputChannel;

	const GS::OProtocolX&					m_outputProtocol;

	GS::USize								m_bufferCapacity;
	GS::USize								m_bufferSize;
	char*									m_buffer;

	bool									m_aborted;
	bool									m_closed;

// Construction / destruction:
public:
	explicit ChunkedMessageContentOBinaryChannel (const GS::OBinaryChannelRef& outputChannel, const GS::OProtocolX& outputProtocol = GS::GetNetworkByteOrderOProtocolX (), GS::USize chunkSize = 16384U);
	explicit ChunkedMessageContentOBinaryChannel (GS::OBinaryChannel& outputChannel, const GS::OProtocolX& outputProtocol = GS::GetNetworkByteOrderOProtocolX (), GS::USize chunkSize = 16384U);
			 ChunkedMessageContentOBinaryChannel (const ChunkedMessageContentOBinaryChannel&) = delete;
	virtual ~ChunkedMessageContentOBinaryChannel ();

// Operator overloading:
public:
	ChunkedMessageContentOBinaryChannel&	operator = (const ChunkedMessageContentOBinaryChannel&) = delete;

// MessageContentOBinaryChannel interface implementation:
public:
	virtual bool							IsAbortable () const override;
	virtual bool							IsAborted () const override;

	virtual void							Abort (const GS::UniString& message) override;
	virtual void							Abort () override;

// OBinaryChannel interface implementation:
public:
	virtual void							Write (const char* source, USize sourceSize) override;

	virtual void							Flush () override;
	virtual void							Close () override; 

// Implementation:
private:
	void									CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;
	void									CheckValid (const char* sourceFile, GS::UInt32 sourceLine) const;

	GS::OBinaryChannel&						GetOutputChannel () const;
	GS::OBinaryChannel&						GetOutputChannel (); 

	bool									IsClosed () const;

	void									WriteMessage (const GS::UniString& message);

	void									WriteChunkIfNotEmpty (bool aborted = false, bool flush = true);
	void									WriteChunkIfFull ();

	void									WriteChunk (bool aborted = false, bool flush = true);

};

}
}

#endif // COMMUNICATION_CHANNELS_CHUNKEDMESSAGECONTENTOBINARYCHANNEL_HPP