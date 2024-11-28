
// *****************************************************************************
//
// Declaration of BodyIBinaryChannel interface
//
// Module:			HTTP
// Namespace:		HTTP::Encoding
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_ENCODING_BODYIBINARYCHANNEL_HPP
#define HTTP_ENCODING_BODYIBINARYCHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/HTTPException.hpp"
#include "HTTP/MessageHeader/HeaderFieldCollection.hpp"

#include "IBinaryChannel.hpp"
#include "Array.hpp"


namespace HTTP {
namespace Encoding {
	class BodySubIBinaryChannel;
	class BodyLengthManagerIBinaryChannel;
}
}

namespace HTTP {
namespace Encoding {

class HTTP_API BodyIBinaryChannel : public GS::IBinaryChannel {

private:
	GS::Array <BodySubIBinaryChannel*>	m_subChannels;
	BodyLengthManagerIBinaryChannel*	m_firstSubChannel;
	BodySubIBinaryChannel*				m_lastSubChannel;
	bool								m_aborted;

public:
	BodyIBinaryChannel ();
	virtual ~BodyIBinaryChannel ();

private:
	BodyIBinaryChannel (const BodyIBinaryChannel&);				// Disabled
	BodyIBinaryChannel& operator = (const BodyIBinaryChannel&);	// Disabled

public:
	virtual USize	Read (char* destination, USize nOfCharToRead, GS::ReadSomeModeSelector readSomeMode = GS::ReadSomeMode) override;
	virtual UInt64	GetAvailable () const override;
	bool			HasMoreContent () const;
	virtual void	Close () override;
	void			Finish ();
	void			Abort ();
	void			Reset ();

	void			BuildSubChannels (GS::IBinaryChannel* inputChannel, const HTTP::MessageHeader::HeaderFieldCollection& headers, bool allRemainingCanBody, bool contentLengthForBody);
	void			BuildEmptyBody (GS::IBinaryChannel* inputChannel);

};

}
}

#endif
