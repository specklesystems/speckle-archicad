
// *****************************************************************************
//
//	                              Class URI
//
// Module: IO
// Namespace: IO::URI
// Contact person: KOVA
//
// SG compatible
//
// *****************************************************************************


#if !defined URI_HPP
#define URI_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "UniString.hpp"
#include "Channel.hpp"
#include "HashTable.hpp"
#include "URIFormat.hpp"

// from GSRoot
#include "Ref.hpp"


#if defined SetPort
#undef SetPort
#endif

// =========================== Class URI ======================================

namespace IO {
namespace URI {

typedef GS::Array <GS::UniString> ParameterValues;
typedef GS::HashTable <GS::UniString, ParameterValues> QueryParameters;


class IO_DLL_EXPORT URI {

private:

	enum UserInfoValidity {
		UserNameValid = 0x01,
		PasswordValid = 0x02,
		UserInfoValid = 0x04,
		AllUserInfoValid = UserNameValid | PasswordValid | UserInfoValid
	};

	enum QueryValidity {
		RawQueryValid = 0x01,
		QueryMapValid = 0x02,
		AllQueryValid = RawQueryValid | QueryMapValid
	};

	enum FragmentValidity {
		FragmentValid = 0x01,
		RawFragmentValid = 0x02,
		AllFragmentValid = FragmentValid | RawFragmentValid
	};

	

	GS::UniString	rawHost;

	GS::UniString	rawPath;

	GS::UniString	scheme;

	mutable GS::UniString	username;
	mutable GS::UniString	password;
	mutable GS::UniString	userInfo;
	mutable unsigned short	userInfoValidity;

	GS::UShort		port;

	mutable GS::UniString	rawQuery;
	mutable QueryParameters queryMap;
	mutable unsigned short  queryValidity;

	mutable GS::UniString	fragment;
	mutable GS::UniString	rawFragment;
	mutable unsigned short  fragmentValidity;

	void		UpdateUserName () const;
	void		UpdatePassword () const;
	void		UpdateUserInfo () const;

	void		UpdateRawQuery () const;
	void		UpdateQueryMap () const;

	void		UpdateFragment () const;
	void		UpdateRawFragment () const;

	bool		IsIPV6Address (const GS::UniString& host) const;

public:

	enum Encoding {
		NoEncoding,
		URIEncoding
	};

	// Construction

	URI	();
	explicit URI	(const GS::UniString& uriString);
	URI	(const GS::UniString& scheme, const GS::UniString& authority);
	URI (const GS::UniString& scheme, const GS::UniString& authority, const GS::UniString& pathEtc);
	URI (const GS::UniString& scheme, const GS::UniString& authority, const GS::UniString& rawpath, const GS::UniString& rawQuery);
	URI (const GS::UniString& scheme, const GS::UniString& authority, const GS::UniString& rawpath, const GS::UniString& rawQuery, const GS::UniString& rawFragment);
	explicit URI (const char* uri);
	URI (const char* uri, Int32 uriLength);

	// String conversion

	GS::UniString	ToString	(Encoding encoding = URIEncoding) const;

	// Parsing

	IO::URI::URIFormat::ErrorCode	Parse	(const GS::UniString& uriString);

	// Scheme name operations

	GS::UniString	GetScheme	(void) const;
	void			SetScheme	(const GS::UniString& newScheme);

	// User name operations

	GS::UniString	GetUserName	(void) const;
	void			SetUserName	(const GS::UniString& newUserName);

	// Password operations

	GS::UniString	GetPassword	(void) const;
	void			SetPassword	(const GS::UniString& newPassword);

	// UserInfo operations

	GS::UniString	GetUserInfo	(void) const;
	void			SetUserInfo	(const GS::UniString& newUserInfo);

	// Port operations

	unsigned short	GetPort		(void) const;
	void			SetPort		(unsigned short newPort);

	// Host operations

	GS::UniString	GetRawHost		(void) const;
	GS::UniString	GetHost			(void) const;
	void			SetRawHost		(const GS::UniString& newRawHost);
	void			SetHost			(const GS::UniString& newHost);
	void			AppendToHost	(const GS::UniString& hostPart);
	void			AppendToRawHost	(const GS::UniString& rawHostPart);
	void			GetHostParts	(GS::Array<GS::UniString>& hostParts) const;

	// Authority operations

	GS::UniString	GetAuthority	(void) const;
	void			SetAuthority	(const GS::UniString& newAuthority);

	// Path operations

	GS::UniString	GetRawPath		(void) const;
	GS::UniString	GetPath			(void) const;
	void			SetRawPath		(const GS::UniString& newRawPath);
	void			SetPath			(const GS::UniString& newPath);
	void			AppendToPath	(const GS::UniString& path);
	void			AppendPartToPath(const GS::UniString& pathPart);
	void			AppendToRawPath	(const GS::UniString& rawPart);
	void			GetPathParts	(GS::Array<GS::UniString>& pathPart) const;

	void			SetPathEtc		(const GS::UniString& newPathEtc);
	GS::UniString	GetPathEtc		(void) const;
	GS::UniString	GetPathAndQuery (void) const;

	// Query operations

	GS::UniString	GetRawQuery (void) const;
	void			GetQueryParameters		(QueryParameters& queryParameters) const;
	bool			GetQueryParameterValues (const GS::UniString& key, ParameterValues& parameterValues) const;
	bool			GetQueryFirstParameterValue (const GS::UniString& key, GS::UniString& parameterValue) const;

	void			SetRawQuery (const GS::UniString& newRawQuery);
	void			SetQueryParameters		(const QueryParameters& newQueryParameters);
	void			SetQueryParameterValues (const GS::UniString& key, const ParameterValues& parameterValues);
	void			SetQueryFirstParameterValue (const GS::UniString& key, const GS::UniString& parameterValue);

	void			AddQueryParameterValue	(const GS::UniString& key, const GS::UniString& parameterValue);
	void			AddQueryParameter	    (const GS::UniString& key);

	void			RemoveQueryParameters	(const GS::UniString& key);

	void			ClearQuery	(void);

	// Fragment identifier operations

	GS::UniString	GetFragment		(void) const;
	GS::UniString	GetRawFragment	(void) const;
	void			SetFragment		(const GS::UniString& newFragment);
	void			SetRawFragment	(const GS::UniString& newRawFragment);

	void			ClearFragment	();

	bool			IsRelative	(void) const;

	void			Clear (void);

};

typedef GS::Ref<URI, GS::AtomicCounter> URIRef;

} // namespace IO
} // namespace URI

inline GS::UniString	IO::URI::URI::GetRawHost (void) const
{
	return rawHost;
}

inline GS::UniString	IO::URI::URI::GetRawPath () const
{
	return rawPath;
}


inline void		IO::URI::URI::SetRawPath (const GS::UniString& newPath)
{
	rawPath = newPath;
}


inline GS::UniString	IO::URI::URI::GetScheme (void) const
{
	return scheme;
}


inline void		IO::URI::URI::SetScheme (const GS::UniString& newScheme)
{
	scheme = newScheme;
}

inline void		IO::URI::URI::SetPort (unsigned short newPort)
{
	port = newPort;
}


inline unsigned short	IO::URI::URI::GetPort () const
{
	return port;
}


#endif
