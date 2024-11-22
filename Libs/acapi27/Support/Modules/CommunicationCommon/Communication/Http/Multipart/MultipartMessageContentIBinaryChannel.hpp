
// *****************************************************************************
//
// Declaration of MultipartMessageContentIBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http::Multipart
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_MULTIPART_MULTIPARTMESSAGECONTENTIBINARYCHANNEL_HPP
#define COMMUNICATION_HTTP_MULTIPART_MULTIPARTMESSAGECONTENTIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/Multipart/Part.hpp"
#include "Communication/MessageContentIBinaryChannel.hpp"



// --- MultipartMessageContentIBinaryChannel class -----------------------------

namespace Communication {
namespace Http {
namespace Multipart {

class COMMUNICATIONCOMMON_API MultipartMessageContentIBinaryChannel : public MessageContentIBinaryChannel {

// Data members:
private:
	MessageContentIBinaryChannelRef			m_inputChannelRef;
	MessageContentIBinaryChannel*			m_inputChannel;

	GS::UniString							m_boundary;

	GS::UniString							m_partStartDelimiter;

	GS::USize								m_partEndDelimiterLength;
	char*									m_partEndDelimiter;

	GS::UniString							m_closeDelimiter;

	bool									m_preambleRead;
	bool									m_partRead;
	bool									m_endRead;

	PartRef									m_part;

	GS::USize								m_pushbackBufferCapacity;
	GS::USize								m_pushbackBufferPosition;
	GS::USize								m_pushbackBufferSize;
	char*									m_pushbackBuffer;

	GS::USize								m_lineBufferCapacity;
	GS::USize								m_lineBufferSize;
	char*									m_lineBuffer;

	bool									m_closed;

// Construction / destruction:
public:
			 MultipartMessageContentIBinaryChannel (const MessageContentIBinaryChannelRef& inputChannel, const GS::UniString& boundary);
			 MultipartMessageContentIBinaryChannel (MessageContentIBinaryChannel& inputChannel, const GS::UniString& boundary);
			 MultipartMessageContentIBinaryChannel (const MultipartMessageContentIBinaryChannel&) = delete;
	virtual ~MultipartMessageContentIBinaryChannel ();

// Operator overloading:
public:
	MultipartMessageContentIBinaryChannel&	operator = (const MultipartMessageContentIBinaryChannel&) = delete;

// Operations:
public:
	PartRef									GetCurrentPart () const;
	bool									HasCurrentPart () const;

	PartRef									GetNextPart ();
	void									ClosePart ();

// MessageContentIBinaryChannel interface implementation:
public:
	virtual bool							HasMoreContent () const override;
	
	virtual bool							IsAbortable () const override;
	virtual bool							IsAborted () const override;

// IBinaryChannel interface implementation:
public:
	virtual GS::UInt64						GetAvailable () const override;

	virtual GS::USize						Read (char* target, GS::USize targetSize, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	
	virtual void							Close () override;

// Implementation:
private:
	void									CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

	const MessageContentIBinaryChannel&		GetInputChannel () const;
	MessageContentIBinaryChannel&			GetInputChannel ();

	void									Init ();


	void									ReadPreamble ();
	void									ReadEpilogue ();

	bool									ReadPartContent (char* target, GS::USize targetSize, GS::USize& read);
	bool									ReadPartStart (Headers& headers);
	void									ReadHeaders (Headers& headers);
	void									ReadPartEnd ();


	bool									IsPartStart (const GS::UniString& line) const;
	bool									IsEnd (const GS::UniString& line) const;


	void									EnsurePushbackBufferCapacity (GS::UInt32 minimumCapacity);
	void									EnsureLineBufferCapacity (GS::UInt32 minimumCapacity);

	void									PushbackLine (const GS::UniString& line);

	void									Pushback (const char* source, GS::USize sourceSize);
	void									Pushback (const GS::UniString& str);
	void									Pushback (const char* str);


	GS::USize								ReadImpl (char* target, GS::USize targetSize);


	void									AppendToLineBuffer (char* source, GS::USize sourceSize);
	void									ResetLineBuffer ();

	bool									ReadLine (GS::UniString& line);

// Static implementation:
private:
	static bool								ParseHeader (const GS::UniString& headerLine, Header& header);
	static Header							ParseHeader (const GS::UniString& headerLine);

};

}
}
}

#endif // COMMUNICATION_HTTP_MULTIPART_MULTIPARTMESSAGECONTENTIBINARYCHANNEL_HPP