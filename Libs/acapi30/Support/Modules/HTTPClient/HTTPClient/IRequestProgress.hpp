// *****************************************************************************
//
// HTTPClient IRequestProgress interface
//
// Contact person: EP
//
// *****************************************************************************
#ifndef GS_HTTPCLIENT_IREQUEST_PROGRESS_HPP
#define GS_HTTPCLIENT_IREQUEST_PROGRESS_HPP

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "Export.hpp"

namespace HTTPClient {

enum class RequestStatus {
	NotStarted,
	InProgress,
	Completed,
	Failed,
	Cancelled
};


class HTTPCLIENT_EXPORTED IRequestProgress {
public:
	virtual ~IRequestProgress ();
	
	// Warning: This callback is invoked on an internal worker thread.
	// Do not perform time-consuming or blocking operations in this method.
	// Blocking operations may cause deadlocks or significantly degrade performance.
	virtual void ProgressChanged (const UInt64 totalDownloadSize, const UInt64 downloadedSize, 
								  const UInt64 totalUploadSize,	  const UInt64 uploadedSize) = 0;
	
	// Warning: This callback is invoked on an internal worker thread.
	// Do not perform time-consuming or blocking operations in this method.
	// Blocking operations may cause deadlocks or significantly degrade performance.
	virtual void StatusChanged (const RequestStatus status) = 0;
};

}	// namespace HTTPClient

#endif    // GS_HTTPCLIENT_IREQUEST_PROGRESS_HPP