
// *****************************************************************************
//
// Declaration of InflaterMessageContentIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_CHANNELS_INFLATERMESSAGECONTENTIBINARYCHANNEL_HPP
#define COMMUNICATION_CHANNELS_INFLATERMESSAGECONTENTIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentIBinaryChannel.hpp"



// --- InflaterMessageContentIBinaryChannel class ------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API InflaterMessageContentIBinaryChannel : public MessageContentIBinaryChannel {

// Data members:
private:
	MessageContentIBinaryChannelRef			m_inputChannelRef;
	MessageContentIBinaryChannel*			m_inputChannel;

	void*									m_inflater;

	GS::USize								m_inputBufferSize;
	char*									m_inputBuffer;

	GS::USize								m_outputBufferSize;
	GS::USize								m_outputAvailable;
	GS::USize								m_outputPosition;
	char*									m_outputBuffer;

	bool									m_eosReached;

	bool									m_closed;

// Construction / destruction:
public:
	explicit InflaterMessageContentIBinaryChannel (const MessageContentIBinaryChannelRef& ic, GS::USize bufferSize = 1024);
	explicit InflaterMessageContentIBinaryChannel (MessageContentIBinaryChannel& ic, GS::USize bufferSize = 1024);
			 InflaterMessageContentIBinaryChannel (const InflaterMessageContentIBinaryChannel&) = delete;
	virtual ~InflaterMessageContentIBinaryChannel ();

// Operator overloading:
public:
	InflaterMessageContentIBinaryChannel&	operator = (const InflaterMessageContentIBinaryChannel&) = delete;

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

	MessageContentIBinaryChannel&			GetInputChannel () const;
	MessageContentIBinaryChannel&			GetInputChannel ();

	bool									IsClosed () const;

	void									Initialize (GS::USize bufferSize);
	void									FillBuffer ();
	void									Destroy ();

};

}
}

#endif // COMMUNICATION_CHANNELS_INFLATERMESSAGECONTENTIBINARYCHANNEL_HPP