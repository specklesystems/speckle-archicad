
// *****************************************************************************
//
// Declaration of HeaderFieldCollection class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_HEADERFIELDCOLLECTION_HPP
#define HTTP_MESSAGEHEADER_HEADERFIELDCOLLECTION_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/MessageHeader/HeaderField.hpp"
#include "HTTP/MessageHeader/HeaderFieldName.hpp"
#include "HTTP/MessageHeader/HeaderFieldValue.hpp"
#include "HTTP/MessageHeader/RangeField/ContentRange.hpp"
#include "HTTP/MessageHeader/RangeField/Ranges.hpp"

#include "Array.hpp"


namespace HTTP {
namespace MessageHeader {

class HTTP_API HeaderFieldCollection {

public:
	typedef GS::Array <HeaderField>			HeaderFieldStorage;
	typedef GS::Array <HeaderFieldValue>	HeaderValueStorage;

	static const char EntityValueSeparator	= ',';

protected:
	HeaderFieldStorage	m_headerFields;

public:
	HeaderFieldCollection ();
	virtual ~HeaderFieldCollection ();

	void				Add (const HeaderField& headerField);
	void				Add (const GS::UniString& headerFieldName, const GS::UniString& value);
	void				Add (const GS::UniString& headerFieldName, const HeaderFieldValue& value);
	void				Add (const GS::UniString& headerFieldName, const HeaderValueStorage& values, char valueSeparator = EntityValueSeparator);

	void				Insert (UIndex index, const HeaderField& headerField);
	void				Insert (UIndex index, const GS::UniString& headerFieldName, const GS::UniString& value);
	void				Insert (UIndex index, const GS::UniString& headerFieldName, const HeaderValueStorage& values, char valueSeparator = EntityValueSeparator);
	
	bool				Remove (const HeaderField& headerField);
	USize				Remove (const GS::UniString& headerFieldName);
	void				Clear ();

	bool				GetHeaderField (UIndex index, HeaderField& messageHeader) const;
	const HeaderField*	GetHeaderField (UIndex index) const;
	GS::UniString		GetHeaderValue (const GS::UniString& headerFieldName, char valueSeparator = EntityValueSeparator) const;
	GS::UniString		GetHeaderValue (const GS::UniString& headerFieldName, USize& numberOfValue, char valueSeparator = EntityValueSeparator) const;
	void				GetHeaderValue (const GS::UniString& headerFieldName, HeaderValueStorage& values, char valueSeparator = EntityValueSeparator) const;
	bool				GetSingleHeaderValue (const GS::UniString& headerFieldName, HeaderFieldValue& singleValue) const;
	void				GetHeaderFields (HeaderFieldStorage& headerFieldName) const;

	bool				ContainsHeader (const GS::UniString& headerFieldName) const;
	Int32				GetHeaderIndex (const GS::UniString& headerFieldName, USize startIndex = 0) const;

	USize				GetSize () const;

	static void			BuildValue (const HeaderValueStorage& values, GS::UniString& value, char valueSeparator = EntityValueSeparator);
	static void			ParseValue (const GS::UniString& value, HeaderValueStorage& values, char valueSeparator = EntityValueSeparator);

	void				AddContentLength (UInt64 contentLength);
	bool				GetContentLength (UInt64& contentLength) const;
	void				AddContentType (GS::UniString contentType);
	bool				GetContentType (GS::UniString& contentType) const;
	void				AddChunkedTransferEncoding ();
	bool				IsChunkedTransferEncoding () const;
	void				SetConnectionKeepAlive ();
	bool				IsConnectionKeepAlive () const;
	void				SetConnectionClose ();
	bool				IsConnectionClose () const;
	void				AddRange (const RangeField::Ranges& ranges);
	bool				GetRange (RangeField::Ranges& ranges) const;
	void				AddContentRange (const RangeField::ContentRange& contentRanges);
	bool				GetContentRange (RangeField::ContentRange& contentRanges) const;
};

}
}

#endif
