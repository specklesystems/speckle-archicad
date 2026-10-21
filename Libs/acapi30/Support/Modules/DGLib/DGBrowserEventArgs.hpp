// *********************************************************************************************************************
// File:			DGBrowserEventArgs.hpp
//
// Description:		Browser Control Classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	VM
// *********************************************************************************************************************

#ifndef DGBROWSEREVENTARGS_HPP
#define DGBROWSEREVENTARGS_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

#include "DG.h"
#include "DGDefs.h"
#include "DGEventArgs.hpp"
#include "DGUtility.hpp"

// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

class BrowserBase;

// --- BrowserURLChangeArg ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserURLChangeArg: public EventArg
{
public:
	GS::UniString newURL;

	BrowserURLChangeArg (const GS::UniString& _newURL): newURL (_newURL) { }

	virtual ~BrowserURLChangeArg ();
};


// --- BrowserNewTabArg ------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserNewTabArg: public EventArg
{
public:
	GS::UniString url;
	bool userGesture;

	BrowserNewTabArg (const GS::UniString& _url, bool _userGesture): url (_url), userGesture (_userGesture) { }

	virtual ~BrowserNewTabArg ();
};


// --- BrowserPageSourceArg --------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserPageSourceArg: public EventArg
{
public:
	GS::UniString pageSource;
	GS::UniString url;

	BrowserPageSourceArg (const GS::UniString& _pageSource, const GS::UniString& _url): pageSource (_pageSource), url (_url) { }

	virtual ~BrowserPageSourceArg ();
};


// --- BrowserLoadingStateChangeArg ------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserLoadingStateChangeArg: public EventArg
{
public:
	bool	isLoading;
	bool	canGoBack;
	bool	canGoForward;

	BrowserLoadingStateChangeArg (bool _isLoading, bool _canGoBack, bool _canGoForward):
		isLoading (_isLoading),
		canGoBack (_canGoBack),
		canGoForward (_canGoForward)
	{
	};

	virtual ~BrowserLoadingStateChangeArg ();
};


// --- BrowserLoadErrorArg ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserLoadErrorArg: public EventArg
{
public:
	enum class LoadErrorCode {
		Failed = -2,
		Aborted = -3,
		InvalidArgument = -4,
		InvalidHandle = -5,
		FileNotFound = -6,
		TimedOut = -7,
		FileTooBig = -8,
		Unexpected = -9,
		AccessDenied = -10,
		NotImplemented = -11,
		ConnectionClosed = -100,
		ConnectionReset = -101,
		ConnectionRefused = -102,
		ConnectionAborted = -103,
		ConnectionFailed = -104,
		NameNotResolved = -105,
		InternetDisconnected = -106,
		SslProtocolError = -107,
		AddressInvalid = -108,
		AddressUnreachable = -109,
		SslClientAuthCertNeeded = -110,
		TunnelConnectionFailed = -111,
		NoSslVersionsEnabled = -112,
		SslVersionOrCipherMismatch = -113,
		SslRenegotiationRequested = -114,
		CertCommonNameInvalid = -200,
		CertDateInvalid = -201,
		CertAuthorityInvalid = -202,
		CertContainsErrors = -203,
		CertNoRevocationMechanism = -204,
		CertUnableToCheckRevocation = -205,
		CertRevoked = -206,
		CertInvalid = -207,
		CertEnd = -208,
		InvalidUrl = -300,
		DisallowedUrlScheme = -301,
		UnknownUrlScheme = -302,
		TooManyRedirects = -310,
		UnsafeRedirect = -311,
		UnsafePort = -312,
		InvalidResponse = -320,
		InvalidChunkedEncoding = -321,
		MethodNotSupported = -322,
		UnexpectedProxyAuth = -323,
		EmptyResponse = -324,
		ResponseHeadersTooBig = -325,
		CacheMiss = -400,
		InsecureResponse = -501,
	};

	LoadErrorCode	errorCode;
	GS::UniString	url;

	BrowserLoadErrorArg (LoadErrorCode _errorCode, const GS::UniString& _url):
		errorCode (_errorCode),
		url (_url)
	{
	};

	virtual ~BrowserLoadErrorArg ();

	static GS::UniString LoadErrorCodeToString (LoadErrorCode code)
	{
		switch (code) {
			case LoadErrorCode::Failed: return "Failed";
			case LoadErrorCode::Aborted: return "Aborted";
			case LoadErrorCode::InvalidArgument: return "Invalid Argument";
			case LoadErrorCode::InvalidHandle: return "Invalid Handle";
			case LoadErrorCode::FileNotFound: return "File Not Found";
			case LoadErrorCode::TimedOut: return "Timed Out";
			case LoadErrorCode::FileTooBig: return "File Too Big";
			case LoadErrorCode::Unexpected: return "Unexpected";
			case LoadErrorCode::AccessDenied: return "Access Denied";
			case LoadErrorCode::NotImplemented: return "Not Implemented";
			case LoadErrorCode::ConnectionClosed: return "Connection Closed";
			case LoadErrorCode::ConnectionReset: return "Connection Reset";
			case LoadErrorCode::ConnectionRefused: return "Connection Refused";
			case LoadErrorCode::ConnectionAborted: return "Connection Aborted";
			case LoadErrorCode::ConnectionFailed: return "Connection Failed";
			case LoadErrorCode::NameNotResolved: return "Name Not Resolved";
			case LoadErrorCode::InternetDisconnected: return "Internet Disconnected";
			case LoadErrorCode::SslProtocolError: return "SSL Protocol Error";
			case LoadErrorCode::AddressInvalid: return "Address Invalid";
			case LoadErrorCode::AddressUnreachable: return "Address Unreachable";
			case LoadErrorCode::SslClientAuthCertNeeded: return "SSL Client Auth Cert Needed";
			case LoadErrorCode::TunnelConnectionFailed: return "Tunnel Connection Failed";
			case LoadErrorCode::NoSslVersionsEnabled: return "No SSL Versions Enabled";
			case LoadErrorCode::SslVersionOrCipherMismatch: return "SSL Version or Cipher Mismatch";
			case LoadErrorCode::SslRenegotiationRequested: return "SSL Renegotiation Requested";
			case LoadErrorCode::CertCommonNameInvalid: return "Certificate Common Name Invalid";
			case LoadErrorCode::CertDateInvalid: return "Certificate Date Invalid";
			case LoadErrorCode::CertAuthorityInvalid: return "Certificate Authority Invalid";
			case LoadErrorCode::CertContainsErrors: return "Certificate Contains Errors";
			case LoadErrorCode::CertNoRevocationMechanism: return "Certificate No Revocation Mechanism";
			case LoadErrorCode::CertUnableToCheckRevocation: return "Certificate Unable to Check Revocation";
			case LoadErrorCode::CertRevoked: return "Certificate Revoked";
			case LoadErrorCode::CertInvalid: return "Certificate Invalid";
			case LoadErrorCode::CertEnd: return "Certificate End";
			case LoadErrorCode::InvalidUrl: return "Invalid URL";
			case LoadErrorCode::DisallowedUrlScheme: return "Disallowed URL Scheme";
			case LoadErrorCode::UnknownUrlScheme: return "Unknown URL Scheme";
			case LoadErrorCode::TooManyRedirects: return "Too Many Redirects";
			case LoadErrorCode::UnsafeRedirect: return "Unsafe Redirect";
			case LoadErrorCode::UnsafePort: return "Unsafe Port";
			case LoadErrorCode::InvalidResponse: return "Invalid Response";
			case LoadErrorCode::InvalidChunkedEncoding: return "Invalid Chunked Encoding";
			case LoadErrorCode::MethodNotSupported: return "Method Not Supported";
			case LoadErrorCode::UnexpectedProxyAuth: return "Unexpected Proxy Authentication";
			case LoadErrorCode::EmptyResponse: return "Empty Response";
			case LoadErrorCode::ResponseHeadersTooBig: return "Response Headers Too Big";
			case LoadErrorCode::CacheMiss: return "Cache Miss";
			case LoadErrorCode::InsecureResponse: return "Insecure Response";
			default: return GS::UniString::Printf ("Unknown Error Code: (%d)", static_cast<Int32>(code));;
		}
	}
};


// --- BrowserBeforeDownloadArg ----------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserBeforeDownloadArg: public EventArg
{
public:
	Int32			id;
	GS::UniString	url;
	GS::UniString	suggestedName;
	GS::UniString	mimeType;
	bool			showDefDlg;

public:
	BrowserBeforeDownloadArg () :
		id (0),
		url (),
		suggestedName (),
		mimeType (),
		showDefDlg (true)
	{
	};

	BrowserBeforeDownloadArg (int _id, GS::UniString _url, GS::UniString _suggestedName, GS::UniString _mimeType, bool _showDefDlg) :
		id (_id),
		url (_url),
		suggestedName (_suggestedName),
		mimeType (_mimeType),
		showDefDlg (_showDefDlg)
	{
	};

	virtual ~BrowserBeforeDownloadArg ();
};


// --- BrowserDragEnterArg ---------------------------------------------------------------------------------------------

enum class DG_DLL_EXPORT CefDragOperations
{
	None,
	Copy,
	Link,
	Generic,
	Private,
	Move,
	Delete,
	Every
 };

CefDragOperations OperationsMaskToEnum (int operationsMask);

class DG_DLL_EXPORT BrowserDragEnterArg: public EventArg
{
public:
	CefDragOperations operations;
	GS::UniString dragOutFile;
	GS::Array<GS::UniString> dragInFiles;
	GS::UniString urlOfDraggedLink;
	GS::UniString fragmentHtml;
	GS::UniString fragmentText;

public:
	BrowserDragEnterArg ()
	{
	};

	BrowserDragEnterArg (CefDragOperations operations, GS::UniString dragOutFile, GS::Array<GS::UniString> dragInFiles, GS::UniString urlOfDraggedLink, GS::UniString fragmentHtml, GS::UniString fragmentText) :
		operations (operations),
		dragOutFile (dragOutFile),
		dragInFiles (dragInFiles),
		urlOfDraggedLink (urlOfDraggedLink),
		fragmentHtml (fragmentHtml),
		fragmentText (fragmentText)
	{
	};

	virtual ~BrowserDragEnterArg ();
};

// --- BrowserDownloadingArg -------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserDownloadingArg: public EventArg
{
public:
	int				id;
	GS::UniString	url;
	GS::UniString	fullPath;
	int64_t			currentSpeed;
	int64_t			totalBytes;
	int				percentComplete;
	bool			isInProgress;
	bool			isComplete;
	bool			isCanceled;

public:
	BrowserDownloadingArg () :
		id (0),
		url (),
		fullPath (),
		currentSpeed (0),
		totalBytes (0),
		percentComplete (0),
		isInProgress (false),
		isComplete (false),
		isCanceled (false)
	{
	};

	BrowserDownloadingArg (int id, GS::UniString url, GS::UniString fullPath, int64_t currentSpeed, int64_t totalBytes, int percentComplete, bool isInProgress, bool isComplete, bool isCanceled) :
		id (id),
		url (url),
		fullPath (fullPath),
		currentSpeed (currentSpeed),
		totalBytes (totalBytes),
		percentComplete (percentComplete),
		isInProgress (isInProgress),
		isComplete (isComplete),
		isCanceled (isCanceled)
	{
	};

	virtual ~BrowserDownloadingArg ();
};


// --- BrowserFindArg --------------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserFinalFindArg: public EventArg
{
public:
	int 			count;
	int 			activeMatchOrdinal;

public:
	BrowserFinalFindArg (int inCount, int ordinal) :
		count (inCount),
		activeMatchOrdinal (ordinal)
	{
	};

	virtual ~BrowserFinalFindArg ();
};


// --- BrowserKeyboardEventArg -----------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserKeyboardEventArg: public EventArg
{
	friend class DG::BrowserBase;
public:
	enum EventType {
		KeyUp	= 0,
		KeyDown,
		Char
	};

	enum InputType {
		Unknown = 0,
		Character,
		Control
	};

private:
	EventType eventType;
	InputType inputType;
	DG::Key::Code code;
	DG::Key::Modifier modifier;

public:
	BrowserKeyboardEventArg (const EventType eventType, const DG::Key::Code& code, const DG::Key::Modifier& modifier, const InputType& inputType = Unknown):
		eventType (eventType),
		code (code),
		modifier (modifier),
		inputType (inputType)
	{
	};

	virtual ~BrowserKeyboardEventArg ();

	EventType			GetEventType () const	{ return eventType; }
	InputType			GetInputType () const 	{ return inputType; }
	DG::Key::Code		GetCode () const		{ return code; }
	DG::Key::Modifier	GetModifier () const	{ return modifier; }
};


class DG_DLL_EXPORT BrowserHeightChangedArg: public EventArg
{
private:
	Int32	pixelHeight = 0;

public:
	BrowserHeightChangedArg (Int32 pixelH) : pixelHeight (pixelH) {};

	virtual ~BrowserHeightChangedArg ();
	Int32	GetContentHeight () const { return pixelHeight; }
};

// --- BrowserContextMenuEventArg --------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserContextMenuEventArg: public EventArg
{
private:
	DG::NativePoint position;
public:
	BrowserContextMenuEventArg (const DG::NativePoint& position) : position (position) {}
	virtual ~BrowserContextMenuEventArg ();
	DG::NativePoint GetPosition () const { return position; }
};


// --- BrowserNotifyHandler --------------------------------------------------------------------------------------------

class BrowserNotifyHandler
{
public:
	virtual ~BrowserNotifyHandler ();

	virtual void	URLChanged (const BrowserURLChangeArg& /*eventArg*/) = 0;
	virtual bool	URLWillChange (const BrowserURLChangeArg& /*eventArg*/) = 0;
	virtual void	NewTabRequested (const BrowserNewTabArg& /*eventArg*/) = 0;
	virtual void	OnPageSourceVisited (const BrowserPageSourceArg& /*eventArg*/) = 0;
	virtual void	OnLoadingStateChange (const BrowserLoadingStateChangeArg& /*eventArg*/) = 0;
	virtual void	OnLoadError (const BrowserLoadErrorArg& /*eventArg*/) = 0;
	virtual bool	OnDragEnter (const BrowserDragEnterArg& /*eventArg*/) = 0;
	virtual bool	BeforeDownload (const BrowserBeforeDownloadArg&  /*eventArg*/) = 0;
	virtual bool	OnDownloading (const BrowserDownloadingArg&  /*eventArg*/) = 0;
	virtual void	OnFinalFind (const BrowserFinalFindArg& /*eventArg*/) = 0;
	virtual void	ContentHeightChanged (const BrowserHeightChangedArg& /*pixelHeight*/) = 0;
	virtual bool	OnPreKeyEvent (const BrowserKeyboardEventArg& /*eventArg*/) = 0;
	virtual bool	OnKeyEvent (BrowserKeyboardEventArg& /*eventArg*/) = 0;
};

}	// namespace DG

#endif
