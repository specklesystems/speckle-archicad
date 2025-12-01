
// *****************************************************************************
//
// Declaration of DeflaterMessageContentOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Channels
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNCATION_CHANNELS_DEFLATERMESSAGECONTENTOBINARYCHANNEL_HPP
#define COMMUNCATION_CHANNELS_DEFLATERMESSAGECONTENTOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/MessageContentOBinaryChannel.hpp"



// --- DeflaterMessageContentOBinaryChannel class ------------------------------

namespace Communication {
namespace Channels {

class COMMUNICATIONCOMMON_API DeflaterMessageContentOBinaryChannel : public MessageContentOBinaryChannel {

// Type definitions:
public:
	enum CompressionLevel {
		DefaultCompression	= -1,
		BestCompression = 9,
		BestSpeed = 1,
		NoCompression = 0

	};

// Data members:
private:
	MessageContentOBinaryChannelRef				m_outputChannelRef;
	MessageContentOBinaryChannel*				m_outputChannel;

	void*										m_deflater;

	GS::USize									m_inputBufferSize;
	GS::UIndex									m_inputPosition;
	char*										m_inputBuffer;

	GS::USize									m_outputBufferSize;
	char*										m_outputBuffer;

	bool										m_closed;

// Construction / destruction:
public:
	explicit DeflaterMessageContentOBinaryChannel (const MessageContentOBinaryChannelRef& outputChannel, GS::Int32 compressionLevel = DefaultCompression, GS::USize bufferSize = 1024);
	explicit DeflaterMessageContentOBinaryChannel (MessageContentOBinaryChannel& outputChannel, GS::Int32 compressionLevel = DefaultCompression, GS::USize bufferSize = 1024);
			 DeflaterMessageContentOBinaryChannel (const DeflaterMessageContentOBinaryChannel&) = delete;
	virtual ~DeflaterMessageContentOBinaryChannel ();

// Operator overloading:
public:
	DeflaterMessageContentOBinaryChannel&		operator = (const DeflaterMessageContentOBinaryChannel&) = delete;

// MessageContentOBinaryChannel interface implementation:
public:
	virtual bool								IsAbortable () const override;
	virtual bool								IsAborted () const override;

	virtual void								Abort (const GS::UniString& message) override;
	virtual void								Abort () override;

// OBinaryChannel interface implementation:
public:
	virtual void								Write (const char* source, USize sourceSize) override;
	
	virtual void								Flush () override;
	virtual void								Close () override; 

// Implementation:
private:
	void										CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

	MessageContentOBinaryChannel&				GetOutputChannel () const;
	MessageContentOBinaryChannel&				GetOutputChannel ();

	bool										IsClosed () const;

	void										Initialize (GS::Int32 compressionLevel, GS::USize bufferSize);
	void										FlushBuffer (int flushType); 
	void										Destroy ();

};

}
}

#endif // COMMUNCATION_CHANNELS_DEFLATERMESSAGECONTENTOBINARYCHANNEL_HPP