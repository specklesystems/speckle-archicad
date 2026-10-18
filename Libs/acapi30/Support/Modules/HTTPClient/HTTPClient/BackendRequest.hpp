// *****************************************************************************
//
// BackendRequest class header
//
// Contact person: EP
//
// *****************************************************************************

#ifndef HTTPCLIENT_BACKEND_REQUEST_HPP
#define HTTPCLIENT_BACKEND_REQUEST_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

// from std
#include <memory>

// from GSRoot
#include "Owner.hpp"
#include "UniString.hpp"

// from HTTPClient
#include "Export.hpp"
#include "Request.hpp"
#include "RequestID.hpp"
#include "Options.hpp"
#include "IExchangeLogger.hpp"
#include "IRequestProgress.hpp"


namespace HTTPClient {

class HTTPCLIENT_EXPORTED BackendRequest {
public:
	BackendRequest (RequestID requestID, GS::Owner<Request> request, const Options& options, std::weak_ptr<IRequestProgress> requestProgressMonitor);

	const RequestID&				GetID () const;
	const Options&					GetOptions () const;
	Request&						GetRequest ();
	const Request&					GetRequest () const;
	IExchangeLogger&				GetLogger ();
	std::weak_ptr<IRequestProgress>	GetRequestProgress () const;

	GS::UniString ToString () const;

private:
	RequestID							m_requestID;
	GS::Owner<Request>					m_request;
	Options								m_options;
	GS::Owner<IExchangeLogger>			m_logger;
	std::weak_ptr<IRequestProgress>		m_requestProgress;
};

}	// namespace HTTPClient

#endif	// HTTPCLIENT_BACKEND_REQUEST_HPP