// *********************************************************************************************************************
// File:			ProductVersionInfo.hpp
//
// Description:		Product information (readed from programdir/ProductVersion.xml)
//
// Project:			ARCHICAD & PlotMaker
//
// Namespace:		SU
//
// Contact person:	FM
//
// SG compatible
// *********************************************************************************************************************

#ifndef GS_PRODUCTVERSION_HPP
#define GS_PRODUCTVERSION_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Array.hpp"
#include	"Owner.hpp"

// from GSUtils
#include	"GSUtilsPrivExp.h"

// --- Predefinitions --------------------------------------------------------------------------------------------------

namespace GS { class UniString; class Guid; }
namespace IO { class Location; }

// --- Class ProductVersionInfo ----------------------------------------------------------------------------------------

namespace SU {

class GSUTILS_PRIVATE_EXPORT ProductVersionInfo final
{
public:
	enum AutomaticDownloadMode {
		Latest = 0,
		LatestWithPreview = 1,
		LatestHotfixOnly = 2,
		None = 3
	};

	ProductVersionInfo ();
	ProductVersionInfo (const IO::Location& xmlLocation);
	~ProductVersionInfo ();

	GS::UniString 						GetCodeName () const;
	GS::UniString 						GetReleaseName () const;
	GS::UniString 						GetProductFamilyId () const;
	GS::UniString						GetGSLanguageCode () const;
	GS::UniString						GetGSProductType () const;
	GS::UniString						GetVersionString () const;
	GS::UniString						GetUpdateVersionString () const;
	GS::UniString						GetHotfixVersionString () const;
	GS::UniString						GetShortVersionString () const;
	GS::UniString						GetAppVersionString () const;
	GS::UniString						GetPlatform () const;
	GS::UniString						GetCpuArchitecture () const;
	Int32								GetBuildNum () const;
	Int32								GetProjectBuildNum () const;
	Int32								GetPackageNum () const;
	GS::UniString						GetInternalProjectName () const;
	GS::UniString						GetPreferencesPostfix () const;
	bool								IsPrivateBuild () const;
	bool								IsReferenceBuild () const;
	GS::UniString						GetInstallIDString () const;
	bool								GetEnableAutomaticDownload () const;
	bool								GetEnableRestrictedUpdateLevel () const;
	AutomaticDownloadMode				GetAutomaticDownloadMode () const;
	Int32								GetVersionNum1 () const;
	Int32								GetVersionNum2 () const;
	Int32								GetVersionNum3 () const;
	GS::Guid							GetGuid () const;
	bool								GetCollapseLongBranches () const;
	GS::UniString						GetUpdatesLibrary () const;
	GS::Guid							GetUpdatesGuid () const;
	const GS::Array<GS::UniString>&		GetNeedsLibrary () const;
	const GS::Array<GS::Guid>&			GetNeedsGuid () const;
	const GS::Array<GS::UniString>&		GetSupersedesLibrary () const;
	const GS::Array<GS::Guid>&			GetSupersedesGuid () const;

private:
	class ProductVersionInfoImpl;
	ProductVersionInfoImpl*	impl;
	bool					toDelete;

	static GS::Owner<ProductVersionInfoImpl>	generalProductVersionInfoImpl;
};

} // SU

#endif // GS_PRODUCTVERSION_HPP
