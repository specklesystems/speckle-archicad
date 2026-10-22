// *****************************************************************************
//
// HTTPClient Response class
//
// Contact person: KI
//
// *****************************************************************************

#ifndef GS_HTTPCLIENT_RESPONSE_HPP
#define GS_HTTPCLIENT_RESPONSE_HPP

// --------------------------------- Includes ----------------------------------

//from InputOutput
#include "URI.hpp"

// from HTTPClient
#include "Export.hpp"
#include "Content.hpp"
#include "Header.hpp"
#include "StatusCode.hpp"


namespace HTTPClient {

class HTTPCLIENT_EXPORTED Response {
public:
	Response (const IO::URI::URI&, StatusCode, const Headers& = {}, GS::Owner<GS::IBinaryChannel> = nullptr);

	const IO::URI::URI&		GetURI        () const gs_lifebound					{ return m_uri; }
	StatusCode				GetStatusCode () const								{ return m_statusCode; }
	const Headers&			GetHeaders	  () const gs_lifebound					{ return m_headers; }
	Content*				GetContent	  () gs_lifebound						{ return m_content.Get (); }
	const Content*			GetContent	  () const gs_lifebound					{ return m_content.Get (); }

private:
	IO::URI::URI		m_uri;
	StatusCode			m_statusCode;
	Headers				m_headers;
	GS::Owner<Content>  m_content;
};

}	// namespace HTTPClient

#endif	// GS_HTTPCLIENT_RESPONSE_HPP