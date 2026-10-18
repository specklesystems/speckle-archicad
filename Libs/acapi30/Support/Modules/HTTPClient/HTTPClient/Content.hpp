// *****************************************************************************
//
// HTTPClient Content implementations
//
// Contact person: KI
//
// *****************************************************************************

#ifndef GS_HTTPCLIENT_CONTENT_HPP
#define GS_HTTPCLIENT_CONTENT_HPP

// from GSRoot
#include "IBinaryChannel.hpp"
#include "Owner.hpp"
#include "RawData.hpp"
#include "UniString.hpp"

// from module
#include "Export.hpp"


namespace HTTPClient {

namespace StandardContentTypes {

	extern const HTTPCLIENT_EXPORTED GS::UniString TextXML;
	extern const HTTPCLIENT_EXPORTED GS::UniString TextPlain;
	extern const HTTPCLIENT_EXPORTED GS::UniString ApplicationXML;
	extern const HTTPCLIENT_EXPORTED GS::UniString ApplicationJSON;
	extern const HTTPCLIENT_EXPORTED GS::UniString ApplicationOctetStream;
	extern const HTTPCLIENT_EXPORTED GS::UniString ApplicationFormUrlEncoded;
	extern const HTTPCLIENT_EXPORTED GS::UniString ApplicationYAML;

} // namespace StandardContentTypes


class HTTPCLIENT_EXPORTED Content {
public:
	Content (const GS::RawData& data, const GS::UniString& contentType = StandardContentTypes::ApplicationOctetStream);
	Content (const GS::UniString& string, const GS::UniString& contentType = StandardContentTypes::TextPlain);
	Content (GS::Owner<GS::IBinaryChannel> dataChannel, const GS::UniString& contentType = StandardContentTypes::ApplicationOctetStream);

	const GS::UniString& GetContentType	() const gs_lifebound;

	GS::IBinaryChannel& ReadAsChannel () gs_lifebound;
	GS::UniString ReadAsUniString ();
	GS::RawData ReadAsRawData ();

private:
	GS::Owner<GS::IBinaryChannel> m_dataChannel;
	GS::UniString m_contentType;
};

} // namespace HTTPClient

#endif // GS_HTTPCLIENT_CONTENT_HPP