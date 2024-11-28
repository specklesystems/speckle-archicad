
// *****************************************************************************
//
// Declaration of BodyOBinaryChannel interface
//
// Module:			HTTP
// Namespace:		HTTP::Encoding
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_ENCODING_BODYOBINARYCHANNEL_HPP
#define HTTP_ENCODING_BODYOBINARYCHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/HTTPException.hpp"
#include "HTTP/MessageHeader/HeaderFieldCollection.hpp"

#include "OBinaryChannel.hpp"
#include "Array.hpp"


namespace HTTP {
namespace Encoding {
	class BodySubOBinaryChannel;
}
}

namespace HTTP {
namespace Encoding {

class HTTP_API BodyOBinaryChannel : public GS::OBinaryChannel {

private:
	mutable GS::Array <BodySubOBinaryChannel*>	m_subChannels;
	BodySubOBinaryChannel*						m_firstSubChannel;
	BodySubOBinaryChannel*						m_lastSubChannel;
	BodySubOBinaryChannel*						m_outputWriterChannel;
	bool										m_aborted;
	bool										m_bodyBufferingAllowed;

public:
	BodyOBinaryChannel ();
	virtual ~BodyOBinaryChannel ();

private:
	BodyOBinaryChannel (const BodyOBinaryChannel&);				// Disabled
	BodyOBinaryChannel& operator = (const BodyOBinaryChannel&);	// Disabled

public:
	virtual void Write (const char* source, USize nOfCharToWrite) override;
	virtual void Flush () override;
	virtual void Close () override;
	void		 Finish ();
	void		 Abort ();
	void		 Reset ();

	void		 BuildSubChannels (GS::OBinaryChannel* outputChannel, HTTP::MessageHeader::HeaderFieldCollection& headers);
	void		 BuildEmptyBody (GS::OBinaryChannel* outputChannel);
	void		 ReplaceOutputChannel (GS::OBinaryChannel* outputChannel);

	bool		 CanResendBody () const;
	void		 ResendBody (GS::OBinaryChannel* outputChannel);
	void		 ResetBodyBuffer ();
	void		 SetBodyBufferingAllowed (bool bodyBufferingAllowed);
	bool		 GetBodyBufferingAllowed () const;
	void		 SetBodyBufferSize (GS::USize maxBodyBufferSize);
	GS::USize 	 GetBodyBufferSize () const;

};

}
}

#endif
