// *****************************************************************************
//
// HTTPClient module main header
//
// Contact person: EP
//
// *****************************************************************************

#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

// from GSRoot
#include "Owner.hpp"

// from IO
#include "URI.hpp"

// from HTTPClient
#include "Export.hpp"
#include "PendingResult.hpp"
#include "OptionalArguments.hpp"


namespace HTTPClient {

class IBackend;

// Required to be called only if the default-provided backend is not sufficient (e.g. testing)
HTTPCLIENT_EXPORTED void Init (GS::Owner<IBackend> pBackend = nullptr);
// Not necessary to be called manually, unless you would like to call Init again (e.g. testing)
HTTPCLIENT_EXPORTED void Free ();

// Request functions
HTTPCLIENT_EXPORTED PendingResult Get (const IO::URI::URI&		   uri,
									   OptionalArguments<Options, Headers, std::weak_ptr<IRequestProgress>> args = {});

HTTPCLIENT_EXPORTED PendingResult Head (const IO::URI::URI&			uri,
										OptionalArguments<Options, Headers, std::weak_ptr<IRequestProgress>> args = {});

HTTPCLIENT_EXPORTED PendingResult Post (const IO::URI::URI&								uri,
										OptionalArguments<Options, Headers, GS::Owner<Content>, std::weak_ptr<IRequestProgress>> args = {});

HTTPCLIENT_EXPORTED PendingResult Put (const IO::URI::URI&							   uri,
									   OptionalArguments<Options, Headers, GS::Owner<Content>, std::weak_ptr<IRequestProgress>> args = {});

HTTPCLIENT_EXPORTED PendingResult Delete (const IO::URI::URI&		  uri,
										  OptionalArguments<Options, Headers, std::weak_ptr<IRequestProgress>> args = {});

HTTPCLIENT_EXPORTED PendingResult Patch (const IO::URI::URI&							 uri,
										 OptionalArguments<Options, Headers, GS::Owner<Content>, std::weak_ptr<IRequestProgress>> args = {});

template<typename ... Args>
PendingResult Get (const IO::URI::URI& uri, Args&& ... args)
{
	return Get (uri, { std::forward<Args> (args)... });
}


template<typename ... Args>
PendingResult Head (const IO::URI::URI& uri, Args&& ... args)
{
	return Head (uri, {std::forward<Args> (args)...});
}


template<typename ... Args>
PendingResult Post (const IO::URI::URI& uri, Args&& ... args)
{
	return Post (uri, {std::forward<Args> (args)...});
}


template<typename ... Args>
PendingResult Put (const IO::URI::URI& uri, Args&& ... args)
{
	return Put (uri, {std::forward<Args> (args)...});
}


template<typename ... Args>
PendingResult Delete (const IO::URI::URI& uri, Args&& ... args) 
{
	return Delete (uri, {std::forward<Args> (args)...});
}

template<typename ... Args>
PendingResult Patch (const IO::URI::URI& uri, Args&& ... args)
{
	return Patch (uri, {std::forward<Args> (args)...});
}

}	// namespace HTTPClient

#endif // HTTPCLIENT_HPP