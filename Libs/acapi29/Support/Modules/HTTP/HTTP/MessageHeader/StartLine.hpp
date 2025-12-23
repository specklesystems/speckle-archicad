
// *****************************************************************************
//
// Declaration of StartLine class
//
// Module:			HTTP
// Namespace:		HTTP::MessageHeader
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef HTTP_MESSAGEHEADER_STARTLINE_HPP
#define HTTP_MESSAGEHEADER_STARTLINE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "HTTP/HTTPExport.hpp"

#include "UniString.hpp"


namespace GS {
	class OBinaryChannel;
}

namespace HTTP {
namespace MessageHeader {

struct HTTP_API HTTPVersion {

	HTTPVersion (UInt16	major, UInt16 minor):
		majorVersion (major),
		minorVersion (minor)
	{
	}

	inline bool	operator == (const HTTPVersion& rhs) const;
	inline bool	operator != (const HTTPVersion& rhs) const;

	UInt16		majorVersion;
	UInt16		minorVersion;

	GS::UniString ToString () const;

	static const HTTPVersion Version11;
	static const HTTPVersion Version10;
};


class HTTP_API StartLine {

private:
	HTTPVersion		m_httpVersion;

public:
	StartLine ();
	StartLine (const HTTPVersion& httpVersion);
	virtual ~StartLine ();

	inline const HTTPVersion&	GetHTTPVersion () const;
	inline void					SetHTTPVersion (const HTTPVersion& httpVersion);
	inline void					SetHTTPVersion (UInt16 majorVersion, UInt16 minorVersion);

};


// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

inline bool	HTTPVersion::operator == (const HTTPVersion& rhs) const
{
	return ((rhs.minorVersion == this->minorVersion) && (rhs.majorVersion == this->majorVersion));
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

inline bool	HTTPVersion::operator != (const HTTPVersion& rhs) const
{
	return !(*this == rhs);
}

// -----------------------------------------------------------------------------
// ToString
// -----------------------------------------------------------------------------

inline GS::UniString HTTPVersion::ToString () const
{
	return GS::UniString::Printf ("%d.%d", majorVersion, minorVersion);
}

// -----------------------------------------------------------------------------
// GetHTTPVersion
// -----------------------------------------------------------------------------

inline const HTTPVersion& StartLine::GetHTTPVersion () const
{
	return m_httpVersion;
}


// -----------------------------------------------------------------------------
// SetHTTPVersion
// -----------------------------------------------------------------------------

inline void StartLine::SetHTTPVersion (const HTTPVersion& httpVersion)
{
	m_httpVersion = httpVersion;
}


// -----------------------------------------------------------------------------
// SetHTTPVersion
// -----------------------------------------------------------------------------

inline void StartLine::SetHTTPVersion (UInt16 majorVersion, UInt16 minorVersion)
{
	m_httpVersion.majorVersion = majorVersion;
	m_httpVersion.minorVersion = minorVersion;
}


}
}

#endif
