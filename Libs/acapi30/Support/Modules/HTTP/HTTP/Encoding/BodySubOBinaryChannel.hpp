
// *****************************************************************************
//
// Declaration of BodySubOBinaryChannel interface
//
// Module:			HTTP
// Namespace:		HTTP::Encoding
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_ENCODING_BODYSUBOBINARYCHANNEL_HPP
#define HTTP_ENCODING_BODYSUBOBINARYCHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"
#include "HTTP/HTTPException.hpp"

#include "OBinaryChannel.hpp"


namespace HTTP {
namespace Encoding {

class HTTP_API BodySubOBinaryChannel : public GS::OBinaryChannel {

protected:
	GS::OBinaryChannel* m_oc;
	bool				m_closed;

public:
	BodySubOBinaryChannel ();
	virtual ~BodySubOBinaryChannel ();

private:
	BodySubOBinaryChannel (const BodySubOBinaryChannel& source);				// disabled
	BodySubOBinaryChannel&	operator= (const BodySubOBinaryChannel& source);	// disabled

public:
	virtual void	Open (GS::OBinaryChannel* oc) = 0;
	virtual void	Abort () = 0;
	void			ReplaceOutputChannel (GS::OBinaryChannel* oc);

protected:
	void			OpenChannel (GS::OBinaryChannel* oc);
	void			AbortChannel ();
	void			CloseChannel ();

	void			CheckUsability (const char* sourceFile, GS::UInt32 sourceLine) const;

};


}
}

#endif
