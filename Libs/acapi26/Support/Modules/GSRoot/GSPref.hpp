// *********************************************************************************************************************
// Description:		Preferences Manager
//
// Namespaces:		-
// Contact persons:	FM
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef GSPREF_HPP
#define GSPREF_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"	// GS::ErrCode
#include	"CH.hpp"			// GSCharCode
#include	"uchar_t.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {
	class UniString;
}

// --- GSPref namespace	------------------------------------------------------------------------------------------------

namespace GSPref
{

// --- Type definitions	------------------------------------------------------------------------------------------------

class GSROOT_DLL_EXPORT IRoot {
public:

		// Error codes
	enum {
		KeyNotFound			= GS::GSPrefErrors+1,	// No such key found
		ValueNotFound		= GS::GSPrefErrors+2,	// No such value found
		TypeMismatch		= GS::GSPrefErrors+3,	// The stored key type does not match the requested key path
		AccessDenied		= GS::GSPrefErrors+4	// The application has not enough right to perform the operation

	};

	enum WriteBackMode {
		WriteBack			= 1,			// Write back if the value was not found
		DontWriteBack		= 0				// Don't write back
	};

	// Set/Get Value
	virtual GS::ErrCode	SetLongValue (
							const char*			iKeyPath,
							const char*			iValueName,
							const Int32 		iData
						) = 0;

	virtual GS::ErrCode	GetLongValue (
							const char*			iKeyPath,
							const char*			iValueName,
							Int32*				oValue,
							const Int32			iDefValue,
							WriteBackMode 		iWriteBack
						) = 0;

	virtual GS::ErrCode	SetDoubleValue (
							const char*			iKeyPath,
							const char*			iValueName,
							const double 		iData
						) = 0;

	virtual GS::ErrCode	GetDoubleValue (
							const char*			iKeyPath,
							const char*			iValueName,
							double*				oValue,
							const double		iDefValue,
							WriteBackMode 		iWriteBack
						) = 0;

	virtual GS::ErrCode	SetBoolValue (
							const char*			iKeyPath,
							const char*			iValueName,
							const bool 			iData
						) = 0;

	virtual GS::ErrCode	GetBoolValue (
							const char*			iKeyPath,
							const char*			iValueName,
							bool*				oValue,
							const bool			iDefValue,
							WriteBackMode 		iWriteBack
						) = 0;

	virtual GS::ErrCode	SetStringValue (
							const char*			iKeyPath,
							const char*			iValueName,
							const GS::uchar_t*	iData
						) = 0;

	virtual GS::ErrCode	SetStringValue (
							const char*             iKeyPath,
							const char*             iValueName,
							const GS::UniString&	iData
						) = 0;

	virtual GS::ErrCode	GetStringValue (
							const char*			iKeyPath,
							const char*			iValueName,
							GS::uchar_t*		oValue,
							unsigned int		iBufferByteSize,
							const GS::uchar_t*	iDefValue,
							WriteBackMode		iWriteBack
						) = 0;

	virtual GS::ErrCode	GetStringValue (
							const char*             iKeyPath,
							const char*             iValueName,
							GS::UniString*          oValue,
							const GS::UniString&	iDefValue,
							WriteBackMode           iWriteBack
						) = 0;

	// Delete Key/Value
	virtual GS::ErrCode	DeleteValue (
							const char*			iKeyPath,
							const char*			iValueName
						) = 0;

	virtual GS::ErrCode	DeleteKey (
							const char*			iKeyPath
						) = 0;

	virtual	GS::ErrCode	HasKey (
							const char*			iKeyPath
						) = 0;

#ifdef WINDOWS
	virtual	GS::ErrCode	CreateKey (
							const char*			iKeyPath
						) = 0;

	virtual GS::ErrCode EnumerateSubKeys (
							const char*			iKeyPath,
							const std::function<void (const GS::UniString&)>& processor
						) = 0;
#endif


	void * operator new (size_t size);
	void operator delete (void * mem);

	virtual				~IRoot();
};


enum RootKeyDomain {						// Possible domains
	CurrentUserDebugDomain		= -1,		// for debugging
	CurrentUserRoamingDomain	= 0,		// Current user, roaming
	CurrentUserLocalDomain  	= 1,		// Current user, local machine
	LocalMachineDomain			= 2,		// Local machine, platform specific
	LocalMachine32Domain		= 3,		// Local machine, 32-bit specific data
	LocalMachine64Domain		= 4			// Local machine, 64-bit specific data
};

GSROOT_DLL_EXPORT
void		SetDefaultDomainPath (
				GSPref::RootKeyDomain			iDomain,
				const char*						domainPath
			);

GSROOT_DLL_EXPORT
IRoot*		OpenRootKey (
				GSPref::RootKeyDomain			iDomain
			);

GSROOT_DLL_EXPORT
IRoot*		OpenRootKey (
				GSPref::RootKeyDomain			iDomain,
				const char*						domainPath
			);

GSROOT_DLL_EXPORT
void		CloseRootKey (
				IRoot**							ppIRoot
			);


class GSROOT_DLL_EXPORT FixPathSession { // stack helper for manipulation of a fixed keyPath
	const char*	mPath;
	IRoot*		mRoot;
public:
	 explicit FixPathSession (const char* path, bool ignoreUninitializedRootKeyDomain = false);
	~FixPathSession ();

	bool IsValid () const { return !!mRoot; }

	GS::ErrCode	SetLongValue (
		const char*			iValueName,
		const Int32 		iData
		) { return mRoot ? mRoot->SetLongValue (mPath, iValueName, iData) : Error; }

	GS::ErrCode	GetLongValue (
		const char*				iValueName,
		Int32*					oValue,
		const Int32				iDefValue,
		IRoot::WriteBackMode	iWriteBack
		) { return mRoot ? mRoot->GetLongValue (mPath, iValueName, oValue, iDefValue, iWriteBack) : Error; }

	GS::ErrCode	SetDoubleValue (
		const char*			iValueName,
		const double 		iData
		) { return mRoot ? mRoot->SetDoubleValue (mPath, iValueName, iData) : Error; }

	GS::ErrCode	GetDoubleValue (
		const char*				iValueName,
		double*					oValue,
		const double			iDefValue,
		IRoot::WriteBackMode	iWriteBack
		) { return mRoot ? mRoot->GetDoubleValue (mPath, iValueName, oValue, iDefValue, iWriteBack) : Error; }

	GS::ErrCode	SetBoolValue (
		const char*			iValueName,
		const bool 			iData
		) { return mRoot ? mRoot->SetBoolValue (mPath, iValueName, iData) : Error; }

	GS::ErrCode	GetBoolValue (
		const char*				iValueName,
		bool*					oValue,
		const bool				iDefValue,
		IRoot::WriteBackMode	iWriteBack
		) { return mRoot ? mRoot->GetBoolValue (mPath, iValueName, oValue, iDefValue, iWriteBack) : Error; }

	GS::ErrCode	SetStringValue (
		const char*			iValueName,
		const GS::uchar_t*	iData
		) { return mRoot ? mRoot->SetStringValue (mPath, iValueName, iData) : Error; }

	GS::ErrCode	SetStringValue (
		const char*             iValueName,
		const GS::UniString&	iData
		) { return mRoot ? mRoot->SetStringValue (mPath, iValueName, iData) : Error; }

	GS::ErrCode	GetStringValue (
		const char*				iValueName,
		GS::uchar_t*			oValue,
		unsigned int			iBufferByteSize,
		const GS::uchar_t*		iDefValue,
		IRoot::WriteBackMode	iWriteBack
		) { return mRoot ? mRoot->GetStringValue (mPath, iValueName, oValue, iBufferByteSize, iDefValue, iWriteBack) : Error; }

	GS::ErrCode	GetStringValue (
		const char*             iValueName,
		GS::UniString*          oValue,
		const GS::UniString&	iDefValue,
		IRoot::WriteBackMode	iWriteBack
		) { return mRoot ? mRoot->GetStringValue (mPath, iValueName, oValue, iDefValue, iWriteBack) : Error; }

	// Delete Key/Value
	GS::ErrCode	DeleteValue (
		const char*			iValueName
		) { return mRoot ? mRoot->DeleteValue (mPath, iValueName) : Error; }
};

// Easy getter functions
GSROOT_DLL_EXPORT
Int32				GetLongValue	   (const char*				path, 
										const char*				iValueName, 
										const Int32				iDefValue, 
										IRoot::WriteBackMode	iWriteBack);

GSROOT_DLL_EXPORT
double				GetDoubleValue	   (const char*				path, 
										const char*				iValueName, 
										const double			iDefValue, 
										IRoot::WriteBackMode	iWriteBack);

GSROOT_DLL_EXPORT
bool				GetBoolValue	   (const char*				path, 
										const char*				iValueName, 
										const bool				iDefValue, 
										IRoot::WriteBackMode	iWriteBack);

GSROOT_DLL_EXPORT
GS::UniString		GetStringValue	   (const char*				path, 
										const char*				iValueName, 
										const GS::UniString&	iDefValue, 
										IRoot::WriteBackMode	iWriteBack);

}	// namespace GSPref


#endif // GSPREF_HPP
