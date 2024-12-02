// ****************************************************************************
//
// Win Native VersionInfo resource reader
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzA
//
// ****************************************************************************


// --------------------------------- Includes ---------------------------------

#include <stdlib.h>
#include <Strsafe.h>

// from GSRoot
#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "HashTable.hpp"

#if !defined _GS_Version_Info_hpp
#define _GS_Version_Info_hpp

// -------------------------------- Constants ---------------------------------


// -------------------------------- Namespace ---------------------------------

namespace GS {


class GSROOT_DLL_EXPORT VersionInfoWin {
public:

	struct TranslationData {
	public:
		UInt32			languageCodeNumber;
		UInt32			characterSetIdNumber;
		GS::UniString	comments;
		GS::UniString	companyName;
		GS::UniString	fileDescription;
		GS::UniString	fileVersion;
		GS::UniString	internalName;
		GS::UniString	legalCopyright;
		GS::UniString	legalTrademarks;
		GS::UniString	originalFilename;
		GS::UniString	productName;
		GS::UniString	productVersion;
		GS::UniString	privateBuild;
		GS::UniString	specialBuild;

	public:
		TranslationData ();
		~TranslationData () {};
	};

	UInt32	majorFileVersionNumber;
	UInt32	minorFileVersionNumber;
	UInt32	maintananceFileVersionNumber;
	UInt32	fileBuildNumber;
			
	UInt32	majorProductVersionNumber;
	UInt32	minorProductVersionNumber;
	UInt32	maintananceProductVersionNumber;
	UInt32	productBuildNumber;

	/* Translation data for available languages */
	GS::HashTable<UInt32, TranslationData>	translationData;
	
public:
	VersionInfoWin ();
	~VersionInfoWin () {};

	GS::UniString ToString () const;
};


class GSROOT_DLL_EXPORT VersionInfoReaderWin {
public:
	enum VersionType {
		Simple,
		Neutral,
		Localised
	};

private:
	GS::UniString	filePath;
	VersionType		versionInfoType;

	DWORD			lastErrorCode;
	GSPtr			pVerInfo;

private:
	GS::UniString	GetVersionInfoField				(const GS::UniString& queryString, const GS::UniString& fieldName) const;
	DWORD			GetNativeTypeFlag				(void) const;
	GSErrCode		GetVersionInfoSize				(DWORD& verInfoSize) const;
	GSErrCode		GetVersionInfo					(const DWORD& verInfoSize) const;
	GSErrCode		ReadVersionInfoBinaryData		(VersionInfoWin& versionInfo) const;
	GSErrCode		GetVersionInfoTranslationData	(GS::Array<GS::Pair<GS::Pair<UInt32, UInt32>, GS::UniString>>& translationDataList) const;
	void			GetStringTypeData				(const GS::UniString& queryString, VersionInfoWin::TranslationData& versionInfoTranslationData) const;

public:
	VersionInfoReaderWin	(const GS::UniString& path, VersionType type);
	~VersionInfoReaderWin	();

	GSErrCode Read			(VersionInfoWin& versionInformation);
};


};		// namespace GS

#endif	// _GS_Version_Info_hpp
