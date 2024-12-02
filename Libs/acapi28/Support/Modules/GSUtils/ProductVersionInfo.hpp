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

class GSUTILS_PRIVATE_EXPORT ProductVersionInfo
{
public:
	enum AutomaticDownloadMode {
		Latest = 0,
		LatestWithPreview = 1,
		LatestHotfixOnly = 2
	};

			ProductVersionInfo ();
			ProductVersionInfo (const IO::Location& xmlLocation);
	virtual ~ProductVersionInfo ();

	virtual GS::UniString 						GetCodeName () const;
	virtual GS::UniString 						GetProductFamilyId () const;
	virtual GS::UniString						GetGSLanguageCode () const;
	virtual GS::UniString						GetGSProductType () const;
	virtual GS::UniString						GetVersionString () const;
	virtual GS::UniString						GetUpdateVersionString () const;
	virtual GS::UniString						GetHotfixVersionString () const;
	virtual GS::UniString						GetShortVersionString () const;
	virtual GS::UniString						GetPlatform () const;
	virtual GS::UniString						GetCpuArchitecture () const;
	virtual Int32								GetBuildNum () const;
	virtual Int32								GetProjectBuildNum () const;
	virtual Int32								GetPackageNum () const;
	virtual GS::UniString       				GetInternalProjectName () const;
	virtual GS::UniString       				GetPreferencesPostfix () const;
	virtual bool                				IsPrivateBuild () const;
	virtual bool                				IsReferenceBuild () const;
	virtual GS::UniString						GetInstallIDString () const;
	virtual bool								GetEnableAutomaticDownload () const;
	virtual AutomaticDownloadMode				GetAutomaticDownloadMode () const;
	virtual Int32								GetVersionNum1 () const;
	virtual Int32								GetVersionNum2 () const;
	virtual Int32								GetVersionNum3 () const;
	virtual GS::Guid							GetGuid () const;
	virtual bool								GetCollapseLongBranches () const;
	virtual GS::UniString						GetUpdatesLibrary () const;
	virtual GS::Guid							GetUpdatesGuid () const;
	virtual const GS::Array<GS::UniString>&		GetNeedsLibrary () const;
	virtual const GS::Array<GS::Guid>&			GetNeedsGuid () const;
	virtual const GS::Array<GS::UniString>&		GetSupersedesLibrary () const;
	virtual const GS::Array<GS::Guid>&			GetSupersedesGuid () const;

	static void									DestroyGeneralInfo (void);
private:
	class ProductVersionInfoImpl;
	ProductVersionInfoImpl*	impl;
	bool					toDelete;

	static GS::Owner<ProductVersionInfoImpl>	generalProductVersionInfoImpl;
};

} // SU

#endif // GS_PRODUCTVERSION_HPP
