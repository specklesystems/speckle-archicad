
// *****************************************************************************
//
// Declaration of BodySubIBinaryChannel interface
//
// Module:			HTTP
// Namespace:		HTTP::Encoding
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_ENCODING_BODYSUBIBINARYCHANNEL_HPP
#define HTTP_ENCODING_BODYSUBIBINARYCHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/HTTPException.hpp"

#include "IBinaryChannel.hpp"


namespace HTTP {
namespace Encoding {

class HTTP_API BodySubIBinaryChannel : public GS::IBinaryChannel {

protected:
	GS::IBinaryChannel*	m_ic;
	bool				m_closed;

public:
	BodySubIBinaryChannel ();
	virtual ~BodySubIBinaryChannel ();

private:
	BodySubIBinaryChannel (const BodySubIBinaryChannel& source);				// disabled
	BodySubIBinaryChannel&	operator= (const BodySubIBinaryChannel& source);	// disabled

public:
	virtual void	Open (GS::IBinaryChannel* ic) = 0;
	virtual void	Abort () = 0;

protected:
	void			OpenChannel (GS::IBinaryChannel* ic);
	void			AbortChannel ();
	void			CloseChannel ();
	void			CheckUsability (const char* sourceFile, GS::UInt32 sourceLine) const;

};

class HTTP_API BodyLengthManagerIBinaryChannel : public BodySubIBinaryChannel {

public:
	BodyLengthManagerIBinaryChannel ();
	virtual ~BodyLengthManagerIBinaryChannel ();

public:
	virtual bool	HasMoreContent () const = 0;
};

}
}

#endif
