
// *****************************************************************************
//
// Declaration of RewritableOBinaryChannel interface 
//
// Module:			HTTP
// Namespace:		HTTP::Encoding
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_ENCODING_REWRITABLEOBINARYCHANNEL_HPP
#define HTTP_ENCODING_REWRITABLEOBINARYCHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/Encoding/BodySubOBinaryChannel.hpp"

#include "MemoryOBinaryChannel.hpp"


namespace HTTP {
namespace Encoding {

class HTTP_API RewritableOBinaryChannel : public BodySubOBinaryChannel {

private:
	GS::MemoryOBinaryChannel	m_moc;
	GS::USize					m_maxBufferSize;
	bool						m_bufferValid;

public:
	RewritableOBinaryChannel (GS::USize initialBufferCapacity = 8192, GS::USize maxBufferSize = 32768);
	virtual ~RewritableOBinaryChannel ();

private:
	RewritableOBinaryChannel (const RewritableOBinaryChannel& source);				// disabled
	RewritableOBinaryChannel&	operator= (const RewritableOBinaryChannel& source);	// disabled

public:
	virtual void	Write (const char* source, USize nOfCharToWrite) override;
	virtual void	Flush () override;
	virtual void	Close () override;
	virtual void	Open (GS::OBinaryChannel* oc) override;
	virtual void	Abort () override;

	bool			Rewrite (GS::OBinaryChannel* outputChannel = nullptr);
	void			ResetBuffer ();
	void			SetMaxBufferSize (GS::USize maxBufferSize);
	GS::USize 		GetMaxBufferSize () const;
	bool			IsBufferValid () const;

};

// -----------------------------------------------------------------------------
// IsBufferValid
// -----------------------------------------------------------------------------

inline bool RewritableOBinaryChannel::IsBufferValid () const
{
	return m_bufferValid;
}

}
}

#endif
