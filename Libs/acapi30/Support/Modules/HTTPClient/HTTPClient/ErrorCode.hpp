// *****************************************************************************
//
// HTTPClient ErrorCode type
//
// Contact person: EP
//
// *****************************************************************************

#ifndef GS_HTTPCLIENT_ERROR_CODE_HPP
#define GS_HTTPCLIENT_ERROR_CODE_HPP

namespace HTTPClient {

enum class ErrorCode {
	Success = 0,

	// Async errors
	ExecutionPending,
	ExecutionCancelled,

	// Connection errors
	CouldntConnect,
	InvalidSSLCertificate,
	TransmissionError,
	TooManyRedirects,
	Timeout,

	// Other
	ResumeNotSupported,
	TooManyConcurrentRequests,
	ContentReadError,
	ContentWriteError,
	InternalError
};

} // namespace HTTPClient

#endif // GS_HTTPCLIENT_ERROR_CODE_HPP