// *****************************************************************************
//
// Declaration of Configuration class
//
// Module:			HTTP
// Namespace:		HTTP::Common:.Configuration
// Contact person:	NB
//
// *****************************************************************************

#ifndef HTTP_COMMON_CONFIGURATION_CONFIGURATION_HPP
#define HTTP_COMMON_CONFIGURATION_CONFIGURATION_HPP

#pragma once

// --- Includes ----------------------------------------------------------------

//from GSRoot
#include "Array.hpp"
#include "HashTable.hpp"
#include "Singleton.hpp"
#include "Ref.hpp"
#include "ReentrantLock.hpp"
#include "UniString.hpp"

// from HTTP
#include "HTTP/HTTPExport.hpp"


// --- Configuration class -----------------------------------------------------

namespace HTTP {
namespace Common {
namespace Configuration {

class HTTP_API Configuration
{
friend class GS::LazyInstantiationPolicy;

	// Typedefs
private:
	class ProxySettings {
	private:
		GS::Array<GS::UniString>	m_proxies;
		GS::UniString				m_bypass;
	public:
		ProxySettings (GS::Array<GS::UniString>& proxies, const GS::UniString& bypass);
		ProxySettings (const ProxySettings& rhs);
		const GS::Array<GS::UniString>&		GetProxies () const;
		const GS::UniString&				GetByPass () const;
	};
	typedef GS::Ref<ProxySettings, GS::AtomicCounter>		ProxySettingsRef;

	// Data members
private:
	mutable GS::ReentrantLock								m_reentrantLock;
	GS::HashTable<GS::UniString, ProxySettingsRef>			m_ProxySettings;

	// Constructors / Destructor
private:
	Configuration ();
public:
	~Configuration ();

	// Operations
public:
	GS::UniString	GetProxyUrl (const GS::UniString& url);
	void			Clear ();

	// Static Operations:
public:
	static Configuration&	GetInstance ();
};

////////////////////////////////////////////////////////////////////////////////
// ProxySettings inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Configuration::ProxySettings::ProxySettings (GS::Array<GS::UniString>& proxies,
													const GS::UniString& bypass) :
	m_proxies (proxies),
	m_bypass (bypass)
{
}

// -----------------------------------------------------------------------------
// Copy constructor
// -----------------------------------------------------------------------------

inline Configuration::ProxySettings::ProxySettings (const ProxySettings& rhs) :
	m_proxies (rhs.m_proxies),
	m_bypass (rhs.m_bypass)
{
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// GetProxies
// -----------------------------------------------------------------------------

inline const GS::Array<GS::UniString>&	Configuration::ProxySettings::GetProxies () const
{
	return m_proxies;
}

// -----------------------------------------------------------------------------
// GetByPass
// -----------------------------------------------------------------------------

inline const GS::UniString&	Configuration::ProxySettings::GetByPass () const
{
	return m_bypass;
}


////////////////////////////////////////////////////////////////////////////////
// Configuration inlines

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

inline Configuration::Configuration () :
	m_reentrantLock (),
	m_ProxySettings ()
{
}

}
}
}
#endif
