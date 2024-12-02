
// *****************************************************************************
//
// Declaration of MultipartMessageContentOBinaryChannel class
//
// Module:			CommunicationCommon
// Namespace:		Communication::Http::Multipart
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HTTP_MULTIPART_MULTIPARTMESSAGECONTENTOBINARYCHANNEL_HPP
#define COMMUNICATION_HTTP_MULTIPART_MULTIPARTMESSAGECONTENTOBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/Http/Multipart/Part.hpp"
#include "Communication/MessageContentOBinaryChannel.hpp"



// --- MultipartMessageContentOBinaryChannel class -----------------------------

namespace Communication {
namespace Http {
namespace Multipart {

class COMMUNICATIONCOMMON_API MultipartMessageContentOBinaryChannel : public MessageContentOBinaryChannel {

// Data members:
private:
	MessageContentOBinaryChannelRef			m_outputChannelRef;
	MessageContentOBinaryChannel*			m_outputChannel;

	GS::UniString							m_boundary;

	PartRef									m_part;

	bool									m_closed;

// Construction / destruction:
public:
			 MultipartMessageContentOBinaryChannel (const MessageContentOBinaryChannelRef& outputChannel, const GS::UniString& boundary);
			 MultipartMessageContentOBinaryChannel (MessageContentOBinaryChannel& outputChannel, const GS::UniString& boundary);
	explicit MultipartMessageContentOBinaryChannel (const MessageContentOBinaryChannelRef& outputChannel);
	explicit MultipartMessageContentOBinaryChannel (MessageContentOBinaryChannel& outputChannel);
			 MultipartMessageContentOBinaryChannel (const MultipartMessageContentOBinaryChannel&) = delete;
	virtual ~MultipartMessageContentOBinaryChannel ();

// Operator overloading:
public:
	MultipartMessageContentOBinaryChannel&	operator = (const MultipartMessageContentOBinaryChannel&) = delete;

// Operations:
public:
	const GS::UniString&					GetBoundary () const;

	PartRef									GetCurrentPart () const;
	bool									HasCurrentPart () const;

	PartRef									PutNextPart (const Headers& headers);
	void									ClosePart ();

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

	const MessageContentOBinaryChannel&		GetOutputChannel () const;
	MessageContentOBinaryChannel&			GetOutputChannel ();


	void									WriteHeaderSeparator ();
	
	void									WriteHeaders (const Headers& headers);
	void									WriteHeader (const Header& header);

	void									WriteBoundary ();

	void									WritePartStart ();
	void									WritePartEnd ();

	void									WriteEnd ();

	void									WriteDashes ();
	void									WriteCRLF ();


	void									WriteRawData (const char* data, GS::USize dataSize);

	void									WriteString (const GS::UniString& str);
	void									WriteString (const char* str);

// Static operations:
public:
	static GS::UniString					GenerateBoundary ();

};

////////////////////////////////////////////////////////////////////////////////
// MultipartMessageContentOBinaryChannel inlines

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetBoundary
// -----------------------------------------------------------------------------

inline const GS::UniString&		MultipartMessageContentOBinaryChannel::GetBoundary () const
{
	return m_boundary;
}

}
}
}

#endif // COMMUNICATION_HTTP_MULTIPART_MULTIPARTMESSAGECONTENTOBINARYCHANNEL_HPP