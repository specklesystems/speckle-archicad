
// *****************************************************************************
//
//	                              Class URIFormat
//
// Module: IO
// Namespace: IO::URI
// Contact person: KOVA
//
// SG compatible
//
// *****************************************************************************

#if !defined URIFORMAT_HPP
#define URIFORMAT_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"
#include "UniCHar.hpp"
#include "UniString.hpp"
#include "Array.hpp"


// =========================== Class URIFormat =================================

namespace IO {
namespace URI {

class IO_DLL_EXPORT Range {
public:
	Range ();
	Range (Int32 begin, Int32 length);

	Int32 End (void) const;

	bool IsValid (void) const;
	bool IsEmpty (void) const;

	void SetRange (Int32 rangeBegin, Int32 rangeEnd);
	void Clear (void);

	bool operator== (const Range& other) const;

	Int32 begin;
	Int32 length;
};

class IO_DLL_EXPORT QueryParameterRange
{
public:
	void Reset (void);

	Range keyRange;
	Range valueRange;
};

typedef GS::Array<QueryParameterRange>	QueryParametersRanges;

namespace URIFormat {

	enum ErrorCode { Ok, Error, DecodeError, EncodeError };

	ErrorCode IO_DLL_EXPORT DecodeQuery (const GS::UniChar::Layout* source, UInt32 begin, UInt32 length, GS::UniString& decodedStr);
	ErrorCode IO_DLL_EXPORT DecodeQuery (const char* source, UInt32 begin, UInt32 length, GS::UniString& decodedStr);
	ErrorCode IO_DLL_EXPORT DecodeQuery (const GS::UniString& source, GS::UniString& decodedStr);

	ErrorCode IO_DLL_EXPORT Decode (const char* source, UInt32 begin, UInt32 length, GS::UniString& decodedStr);
	ErrorCode IO_DLL_EXPORT Decode (const GS::UniChar::Layout* source, UInt32 begin, UInt32 length, GS::UniString& decodedStr);
	ErrorCode IO_DLL_EXPORT Decode (const GS::UniString& source, GS::UniString& decodedStr);

	ErrorCode IO_DLL_EXPORT Encode (const char* source, UInt32 begin, UInt32 length, bool (*isReserved)(char), GS::UniString& encodedStr, const GS::UniChar::Layout* reservedEscapeChar = nullptr);
	ErrorCode IO_DLL_EXPORT Encode (const GS::UniChar::Layout* source, UInt32 begin, UInt32 length, bool (*isReserved)(GS::UniChar::Layout), GS::UniString& encodedStr, const GS::UniChar::Layout* reservedEscapeChar = nullptr);
	ErrorCode IO_DLL_EXPORT Encode (const GS::UniString& source, bool (*isReserved)(GS::UniChar::Layout), GS::UniString& encodedStr, const GS::UniChar::Layout* reservedEscapeChar = nullptr);
	ErrorCode IO_DLL_EXPORT Encode (const char* source, UInt32 begin, UInt32 length, bool (*isReserved)(char), GS::UniString& encodedStr, bool encodeURIReservedCharacters, const GS::UniChar::Layout* reservedEscapeChar = nullptr);
	ErrorCode IO_DLL_EXPORT Encode (const GS::UniChar::Layout* source, UInt32 begin, UInt32 length, bool (*isReserved)(GS::UniChar::Layout), GS::UniString& encodedStr, bool encodeURIReservedCharacters, const GS::UniChar::Layout* reservedEscapeChar = nullptr);
	ErrorCode IO_DLL_EXPORT Encode (const GS::UniString& source, bool (*isReserved)(GS::UniChar::Layout), GS::UniString& encodedStr, bool encodeURIReservedCharacters, const GS::UniChar::Layout* reservedEscapeChar = nullptr);

	ErrorCode IO_DLL_EXPORT Parse (const char* spec,
								   const Range& uri,
								   Range& scheme,
								   Range& userInfoRange,
								   Range& serverInfoRange,
								   Range& userName,
								   Range& password,
								   Range& hostName,
								   Range& portNumber,
								   Range& path,
								   Range& query,
								   Range& fragment);

	ErrorCode IO_DLL_EXPORT Parse (const GS::UniChar::Layout* spec,
								   const Range& uri,
								   Range& scheme,
								   Range& userInfoRange,
								   Range& serverInfoRange,
								   Range& userName,
								   Range& password,
								   Range& hostName,
								   Range& portNumber,
								   Range& path,
								   Range& query,
								   Range& fragment);

	ErrorCode IO_DLL_EXPORT ParsePathEtc (const char* spec,
										  Range& pathEtc,
										  Range& path,
										  Range& query,
										  Range& fragment);

	ErrorCode IO_DLL_EXPORT ParsePathEtc (const GS::UniChar::Layout* spec,
										  Range& pathEtc,
										  Range& path,
										  Range& query,
										  Range& fragment);

	ErrorCode IO_DLL_EXPORT ParseUserInfo (const char* spec,
										   Range& userInfo,
										   Range& userName,
										   Range& password);

	ErrorCode IO_DLL_EXPORT ParseUserInfo (const GS::UniChar::Layout* spec,
										   Range& userInfo,
										   Range& userName,
										   Range& password);

	ErrorCode IO_DLL_EXPORT ParseQuery (const char* spec,
										const Range& query,
										QueryParametersRanges& queryParameters);

	ErrorCode IO_DLL_EXPORT ParseQuery (const GS::UniChar::Layout* spec,
										const Range& query,
										QueryParametersRanges& queryParameters);

	ErrorCode IO_DLL_EXPORT ParseAuthority (const char* spec,
											Range& authority,
											Range& userInfoRange,
											Range& serverInfoRange,
											Range& userName,
											Range& password,
											Range& hostName,
											Range& portNumber);

	ErrorCode IO_DLL_EXPORT ParseAuthority (const GS::UniChar::Layout* spec,
											Range& authority,
											Range& userInfoRange,
											Range& serverInfoRange,
											Range& userName,
											Range& password,
											Range& hostName,
											Range& portNumber);


};

}
}


#endif
