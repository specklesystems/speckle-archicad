// *****************************************************************************
//
// Declaration of HostPatternList class
//
// Module:			HTTP
// Namespace:		HTTP::Common
// Contact person:	NB
//
// *****************************************************************************

#ifndef HTTP_COMMON_HOSTPATTERNLIST_HPP
#define HTTP_COMMON_HOSTPATTERNLIST_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

//from GSRoot
#include "Array.hpp"
#include "Ref.hpp"

// from InputOutput
#include "URI.hpp"

// from HTTP
#include "HTTP/HTTPExport.hpp"

// --- HostPatternList class --------------------------------------------------

namespace HTTP {
namespace Common {

class HTTP_API HostPatternList
{

public:
	class PatternProtocol {
	public:
		enum Protocol {
			Any,
			Http,
			Https
		};

		static bool Match (Protocol serverProtocol, Protocol patternProtocol) {
			if (patternProtocol == PatternProtocol::Any) {
				return true;
			}

			return serverProtocol == patternProtocol;
		}
	};

	struct Pattern {
	private:
		GS::UniString				m_pattern;
		PatternProtocol::Protocol	m_patternProtocol;

	public:
		Pattern (const GS::UniString& pattern, PatternProtocol::Protocol patternProtocol) :
			m_pattern (pattern),
			m_patternProtocol (patternProtocol) {
		}

		const GS::UniString& GetPattern () const {
			return m_pattern;
		}

		const PatternProtocol::Protocol& GetPatternProtocol () const {
			return m_patternProtocol;
		}
	};

	// Data members
private:
	GS::Array<Pattern>		m_hostPatternList;

	// Constructors / Destructor
public:
	HostPatternList (const GS::UniString& hostPatternList);
	HostPatternList (const HostPatternList& rhs);
	~HostPatternList ();

	// Operations
public:
	bool							Match (const GS::UniString& host, PatternProtocol::Protocol protocol) const;
	bool							Match (const IO::URI::URI& url) const;
	const GS::Array<Pattern>&		GetPatterns () const;
private:
	GS::UniString					StandardiseHostPatternList (const GS::UniString& hostPatternList) const;
	void							HandleLocalHost ();
	void							HandleLocalHost (PatternProtocol::Protocol protocol);
};
typedef GS::Ref<HostPatternList, GS::AtomicCounter>	HostPatternListRef;

////////////////////////////////////////////////////////////////////////////////
// HostPatternList inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline HostPatternList::HostPatternList (const HostPatternList& rhs) :
	m_hostPatternList (rhs.m_hostPatternList)
{
}

}
}
#endif
