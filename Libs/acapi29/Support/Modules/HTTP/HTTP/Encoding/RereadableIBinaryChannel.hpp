
// *****************************************************************************
//
// Declaration of RereadableIBinaryChannel interface 
//
// Module:			HTTP
// Namespace:		HTTP::Encoding
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_ENCODING_REREADABLEIBINARYCHANNEL_HPP
#define HTTP_ENCODING_REREADABLEIBINARYCHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/Encoding/BodySubIBinaryChannel.hpp"


namespace HTTP {
namespace Encoding {

class HTTP_API RereadableIBinaryChannel : public BodySubIBinaryChannel {

private:
	USize			m_bufferCapacity;
	USize			m_bufferSize;
	USize			m_bufferStart;
	char*			m_buffer;

public:
	RereadableIBinaryChannel (GS::USize bufferCapacity = 1024);
	virtual ~RereadableIBinaryChannel ();

private:
	RereadableIBinaryChannel (const RereadableIBinaryChannel& source);				// disabled
	RereadableIBinaryChannel&	operator= (const RereadableIBinaryChannel& source);	// disabled

public:
	virtual USize	Read (char* destination, USize nOfCharToRead, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	virtual UInt64	GetAvailable () const override;
	virtual void	Open (GS::IBinaryChannel* ic) override;
	virtual void	Abort () override;
	virtual void	Close () override;

	void			RestoreRereadableData (const char* source, USize length);

	GS::USize		GetRereadableCount () const;

};

}
}

#endif
