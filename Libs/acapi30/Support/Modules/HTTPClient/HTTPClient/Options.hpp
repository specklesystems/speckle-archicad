// *****************************************************************************
//
// Options class
//
// Contact person: KI
//
// *****************************************************************************

#ifndef GS_HTTPCLIENT_OPTIONS_HPP
#define GS_HTTPCLIENT_OPTIONS_HPP

#include <functional>

// form GSRoot
#include "Definitions.hpp"
#include "Optional.hpp"
#include "URI.hpp"

// from HTTPClient
#include "OutputFile.hpp"
#include "Export.hpp"


namespace HTTPClient {

class HTTPCLIENT_EXPORTED Options {
public:
	using BytesPerSecond = UInt64;

	Options ();

	bool     GetFollowRedirects () const;
	Options& SetFollowRedirects (bool follow);

	bool	 GetResumeDownload () const;
	Options& SetResumeDownload (bool isEnabled);

	UInt32   GetTimeoutMilliSeconds () const;
	Options& SetTimeoutMilliSeconds (UInt32 timeoutMilliSeconds);

	UInt32   GetConnectionTimeoutMilliSeconds () const;
	Options& SetConnectionTimeoutMilliSeconds (UInt32 connectionTimeoutMilliSeconds);

	BytesPerSecond GetMaxReceiveSpeedLimit () const;
	Options& SetMaxReceiveSpeedLimit (BytesPerSecond maxSpeedLimit);

	const OutputFile& GetOutputFile () const;
	Options& SetOutputFile (const OutputFile& outputFile);

	bool     GetFireAndForget () const;
	Options& SetFireAndForget (bool fireAndForget);

private:
	bool m_shouldFollowRedirects;
	bool m_resumeDownload;
	UInt32 m_timeoutMilliSeconds;
	UInt32 m_connectionTimeoutMilliSeconds;
	BytesPerSecond m_maxReceiveSpeedLimit;
	OutputFile m_outputFile;
	bool m_fireAndForget;
};

}	// namespace HTTPClient

#endif // GS_HTTPCLIENT_OPTIONS_HPP