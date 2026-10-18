#ifndef GS_HTTPCLIENT_HEADER_HPP
#define GS_HTTPCLIENT_HEADER_HPP

// from standard lib
#include <map>

// from GSRoot
#include "String.hpp"
#include "UniString.hpp"
#include "StringComparison.hpp"

#include "Export.hpp"

namespace HTTPClient {

using Header  = std::pair     <GS::UniString, GS::UniString>;
using Headers = std::multimap <GS::UniString, GS::UniString, GS::Deprecated::CaseInsensitiveComparator>;

namespace StandardHeaderFields {

	extern const HTTPCLIENT_EXPORTED GS::UniString AcceptLanguage;
	extern const HTTPCLIENT_EXPORTED GS::UniString ContentType;
	extern const HTTPCLIENT_EXPORTED GS::UniString Authorization;
	extern const HTTPCLIENT_EXPORTED GS::UniString AcceptEncoding;
	extern const HTTPCLIENT_EXPORTED GS::UniString Host;
	extern const HTTPCLIENT_EXPORTED GS::UniString IfNoneMatch;
	extern const HTTPCLIENT_EXPORTED GS::UniString IfMatch;
	extern const HTTPCLIENT_EXPORTED GS::UniString IfModifiedSince;
	extern const HTTPCLIENT_EXPORTED GS::UniString ContentLength;
	extern const HTTPCLIENT_EXPORTED GS::UniString ContentEncoding;
	extern const HTTPCLIENT_EXPORTED GS::UniString CacheControl;

} // namespace StandardHeaderFields
} // namespace HTTPClient

#endif // GS_HTTPCLIENT_HEADER_HPP