// *****************************************************************************
//
// IBackend interface header
//
// Contact person: EP
//
// *****************************************************************************

#ifndef HTTPCLIENT_IBACKEND_HPP
#define HTTPCLIENT_IBACKEND_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

// from GSRoot
#include "Owner.hpp"
#include "Expected.hpp"
#include "UniString.hpp"

// from HTTPClient
#include "ErrorCode.hpp"
#include "Export.hpp"
#include "BackendRequest.hpp"
#include "Response.hpp"

namespace HTTPClient {

class HTTPCLIENT_EXPORTED IBackend {
public:
	using Result = GS::Expected<GS::Owner<Response>, ErrorCode>;

	IBackend ();
	virtual ~IBackend ();

	virtual Result Execute (BackendRequest& backendRequest) = 0;

	// Returns a string identifying the backend (and possibly its version)
	virtual GS::UniString GetID () = 0;
};

}	// namespace HTTPClient

#endif	// HTTPCLIENT_IBACKEND_HPP