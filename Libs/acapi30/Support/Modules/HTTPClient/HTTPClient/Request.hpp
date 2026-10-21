// *****************************************************************************
//
// HTTPClient Request class
//
// Contact person: KI
//
// *****************************************************************************

#ifndef GS_HTTPCLIENT_REQUEST_HPP
#define GS_HTTPCLIENT_REQUEST_HPP

// from GSRoot
#include "Owner.hpp"

// from InputOutput
#include "URI.hpp"

// from module
#include "Content.hpp"
#include "Method.hpp"
#include "Header.hpp"


namespace HTTPClient {

class HTTPCLIENT_EXPORTED Request {
public:
	Request (const IO::URI::URI&, Method, const Headers& = {}, GS::Owner<Content> = nullptr);

	const IO::URI::URI&				GetURI () const gs_lifebound							{ return m_URI; }
	Method							GetMethod () const										{ return m_method; }
	const Headers&					GetHeaders () const gs_lifebound						{ return m_headers; }
	Content*						GetContent () gs_lifebound								{ return m_content.Get (); }
	const Content*					GetContent () const gs_lifebound						{ return m_content.Get (); }

private:
	IO::URI::URI				m_URI;
	Method						m_method;
	Headers						m_headers;
	GS::Owner<Content>			m_content;
};

} // namespace HTTPClient

#endif // GS_HTTPCLIENT_REQUEST_HPP