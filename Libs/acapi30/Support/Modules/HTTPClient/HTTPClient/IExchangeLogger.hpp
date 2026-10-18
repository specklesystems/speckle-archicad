#ifndef HTTPCLIENT_IEXCHANGE_LOGGER_HPP
#define HTTPCLIENT_IEXCHANGE_LOGGER_HPP

#include "Export.hpp"
#include "Header.hpp"
#include "StatusCode.hpp"


namespace HTTPClient {

class HTTPCLIENT_EXPORTED IExchangeLogger {
public:
	virtual ~IExchangeLogger ();

	virtual	void LogRequestInitializationFailed (const GS::UniString& errorMsg) = 0;
	virtual	void LogRequestStarted () = 0;
	virtual	void LogRequestFinished (StatusCode statusCode, UInt32 durationInMS) = 0;
	virtual	void LogRequestFailed (const GS::UniString& errorMsg, UInt32 durationInMS) = 0;
	virtual	void LogConnectionInfo (const GS::UniString& connectionInfo) = 0;
	virtual	void LogRequestHeader (const Header& header) = 0;
	virtual	void LogRequestData (const char* data, size_t size) = 0;
	virtual	void LogResponseHeader (const Header& header) = 0;
	virtual	void LogResponseData (const char* data, size_t size) = 0;
};

} // namespace HTTPClient

#endif // HTTPCLIENT_IEXCHANGE_LOGGER_HPP