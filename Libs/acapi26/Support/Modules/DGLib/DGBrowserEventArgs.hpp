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

#include "DGBrowserJSHandler.hpp"

// --- Class declarations ----------------------------------------------------------------------------------------------

namespace DG {

// --- BrowserURLChangeArg ---------------------------------------------------------------------------------------------

class DG_DLL_EXPORT BrowserURLChangeArg: public EventArg
{
public:
	GS::UniString newURL;

	BrowserURLChangeArg (const GS::UniString& _newURL): newURL (_newURL) { }

	virtual ~BrowserURLChangeArg ();
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


// --- BrowserLoadingStateChangeArg --------------------------------------------------------------------------------------------

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


// --- BrowserLoadErrorArg --------------------------------------------------------------------------------------------

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

class DG_DLL_EXPORT BrowserDragEnterArg: public EventArg
{
public:
	GS::UInt32 operationsMask;
	GS::UniString dragOutFile;
	GS::Array<GS::UniString> dragInFiles;
	GS::UniString linkUrl;
	GS::UniString framgMentHtml;
	GS::UniString framgmentText;

public:
	BrowserDragEnterArg ()
	{
	};

	BrowserDragEnterArg (GS::UInt32 _operationsMask, GS::UniString _dragOutFile, GS::Array<GS::UniString> _dragInFiles, GS::UniString _linkUrl, GS::UniString _framgMentHtml, GS::UniString _framgmentText) :
		operationsMask (_operationsMask),
		dragOutFile (_dragOutFile),
		dragInFiles (_dragInFiles),
		linkUrl (_linkUrl),
		framgMentHtml (_framgMentHtml),
		framgmentText (_framgmentText)
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

	BrowserDownloadingArg (int _id, GS::UniString _url, GS::UniString _fullPath, int64_t _currentSpeed, int64_t _totalBytes, int _percentComplete, bool _isInProgress, bool _isComplete, bool _isCanceled) :
		id (_id),
		url (_url),
		fullPath (_fullPath),
		currentSpeed (_currentSpeed),
		totalBytes (_totalBytes),
		percentComplete (_percentComplete),
		isInProgress (_isInProgress),
		isComplete (_isComplete),
		isCanceled (_isCanceled)
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
public:
	enum EventType {
		KeyUp	= 0,
		KeyDown	= 1
	};

private:
	EventType eventType;
	DG::Key::Code code;
	DG::Key::Modifier modifier;

public:
	BrowserKeyboardEventArg (const EventType eventType, const DG::Key::Code code, const DG::Key::Modifier modifier):
		eventType (eventType),
		code (code),
		modifier (modifier)
	{
	};

	virtual ~BrowserKeyboardEventArg ();

	EventType			GetEventType () const	{ return eventType; }
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


// --- BrowserNotifyHandler --------------------------------------------------------------------------------------------

class BrowserNotifyHandler
{
public:
	virtual ~BrowserNotifyHandler ();

	virtual void	URLChanged (const BrowserURLChangeArg& /*eventArg*/) = 0;
	virtual bool	URLWillChange (const BrowserURLChangeArg& /*eventArg*/) = 0;
	virtual void	OnPageSourceVisited (const BrowserPageSourceArg& /*eventArg*/) = 0;
	virtual void	OnLoadingStateChange (const BrowserLoadingStateChangeArg& /*eventArg*/) = 0;
	virtual void	OnLoadError (const BrowserLoadErrorArg& /*eventArg*/) = 0;
	virtual bool	OnDragEnter (const BrowserDragEnterArg& /*eventArg*/) = 0;
	virtual bool	BeforeDownload (const BrowserBeforeDownloadArg&  /*eventArg*/) = 0;
	virtual bool	OnDownloading (const BrowserDownloadingArg&  /*eventArg*/) = 0;
	virtual void	OnFinalFind (const BrowserFinalFindArg& /*eventArg*/) = 0;
	virtual bool	KeyboardEventOccured (const BrowserKeyboardEventArg& /*eventArg*/) = 0;
	virtual void	ContentHeightChanged (const BrowserHeightChangedArg& pixelHeight) = 0;
};

}	// namespace DG

#endif
