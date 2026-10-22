
// *****************************************************************************
//
// Declaration of Headers class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_HEADERS_HPP
#define COMMUNICATION_HEADERS_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/HeaderIterator.hpp"

	// from GSRoot
#include "HashTable.hpp"



// --- Headers class -----------------------------------------------------------

namespace Communication {

class COMMUNICATIONCOMMON_API Headers {

// Type definitions:
private:
	typedef GS::HashTable<GS::UniString, GS::PagedArray<Header>> HeaderMap;

// Data members:
private:
	HeaderMap				m_headers;

// Operator overloading:
public:
	bool					operator == (const Headers& rhs) const;
	bool					operator != (const Headers& rhs) const;

// Operations:
public:
	GS::USize				GetSize () const;

	bool					GetFirstHeader (const GS::UniString& headerName, Header& header) const;
	bool					GetLastHeader (const GS::UniString& headerName, Header& header) const;

	ConstHeaderIterator		GetHeaders (const GS::UniString& headerName) const;
	ConstHeaderIterator		GetHeaders () const;

	bool					RemoveHeaders (const GS::UniString& headerName);
	bool					RemoveHeader (const Header& header);

	void					AddHeader (const GS::UniString& headerName, const GS::UniString& headerValue);
	void					AddHeader (const Header& header);

	void					SetHeader (const GS::UniString& headerName, const GS::UniString& headerValue);
	void					SetHeader (const Header& header);

	void					Clear ();

// Implementation:
private:
	GS::UniString			NormalizeHeaderName (const GS::UniString& headerName) const;

};

}

#endif // COMMUNICATION_HEADERS_HPP