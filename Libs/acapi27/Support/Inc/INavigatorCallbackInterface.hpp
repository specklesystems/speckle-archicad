// *********************************************************************************************************************
//
//
// Module:			ACPM
// Namespace:		-
// Contact person:	TBa
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef INAVIGATORAPI_HPP
#define INAVIGATORAPI_HPP

#pragma once

#include "AppExportInterfaceBase.hpp"
#include "API_Guid.hpp"
#include "APIdefs_Base.h"
#include "DGUtility.hpp"
#include "APICalls.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif


// === class INavigatorCallbackInterface ===============================================================================
/** @brief Callback interface object to register with @ref ACAPI_Navigator_RegisterCallbackInterface.
	@ingroup Navigator
	@struct INavigatorCallbackInterface
	@since Archicad 26
*/
class __APIEXPORT INavigatorCallbackInterface : public GS::AppExportInterfaceBase {
public:
	enum IconTWMode {
		TWNormal,
		TWReserved,
		TWBeforeSend,
		TWNotMineBeforeSend
	};

	enum IconLinkness {
		Normal,
		Link,
		Shortcut,
		PDFShortcut,
		DWGShortcut,
		DXFShortcut,
		IFCShortcut
	};

	enum IconSize {
		NormalSize,
		Small
	};

	enum IconContext {
		Model,
		Layout
	};

	enum ContextMenuCommand {
		NewItemCommand,
		DeleteItemCommand,
		RenameItemCommand,
		OpenSettingsCommand
	};

	enum TWCommandMenu {
		ReserveNode,
		ReserveGroupChildren,
		ReleaseNode,
		ReleaseGroupChildren,
		RequestNode
	};

	enum TWCommandMail {
		Request1Mail,
		RequestNMail,
		Grant1Mail,
		GrantNMail
	};

	virtual bool		IsDummyInterface			(void) const;
	virtual GSErrCode	OpenView					(const API_Guid& viewPointID, bool newWindow) const = 0;
	virtual GSErrCode	OpenSettings				(const API_Guid& viewPointID) const = 0;
	virtual GSErrCode	ExecuteMergePostProcess		() const = 0;
	virtual GSErrCode	CreateIDFStore				(const API_Guid& viewPointID, double scale, double& clipBoxWidth, double& clipBoxHeight, GSPtr& idfStore, API_Box& boundingBox, double& paddingX, double& paddingY, GS::Array<API_Guid>& elems) const = 0;
	virtual GSErrCode	GetElemsForDrawingCheck		(const API_Guid& viewPointID, GS::Array<API_Guid>& elems) const = 0;
	virtual GSErrCode	NewItem						(const API_Guid& viewPointID) const = 0;
	virtual GSErrCode	DeleteItem					(const GS::Array<API_Guid>& viewPointIDList) const = 0;
	virtual GSErrCode	RenameItem					(const API_Guid& viewPointID) const = 0;
	virtual DG::Icon	GetIcon						(Int32 iconId, IconTWMode iconTWMode, IconLinkness linkness, IconSize size, IconContext context) const = 0;
	virtual bool		GetContextMenuCommandString (ContextMenuCommand cmd, const API_Guid& viewPointId, GS::UniString& text) const;
	virtual bool		IsContextMenuCommandEnabled (ContextMenuCommand cmd, const API_Guid& viewPointId) const;
	virtual bool		GetTWCommandMenuString		(TWCommandMenu cmd, const API_Guid& viewPointId, GS::UniString& text) const;
	virtual bool		GetTWCommandMailString		(TWCommandMail cmd, const API_Guid& viewPointId, GS::UniString& text) const;

	virtual ~INavigatorCallbackInterface ();
};


// === INavigatorCallbackInterface methods =============================================================================

inline bool		INavigatorCallbackInterface::IsDummyInterface () const
{
	return false;
}


inline bool		INavigatorCallbackInterface::GetContextMenuCommandString (ContextMenuCommand /*cmd*/, const API_Guid& /*viewPointId*/, GS::UniString& /*text*/) const
{
	return false;
}


inline bool		INavigatorCallbackInterface::IsContextMenuCommandEnabled (ContextMenuCommand /*cmd*/, const API_Guid& /*viewPointId*/) const
{
	return true;
}


inline bool		INavigatorCallbackInterface::GetTWCommandMenuString (TWCommandMenu /*cmd*/, const API_Guid& /*viewPointId*/, GS::UniString& /*text*/) const
{
	return false;
}


inline bool		INavigatorCallbackInterface::GetTWCommandMailString (TWCommandMail /*cmd*/, const API_Guid& /*viewPointId*/, GS::UniString& /*text*/) const
{
	return false;
}


inline INavigatorCallbackInterface::~INavigatorCallbackInterface ()
{
}


#ifdef __clang__
#pragma clang diagnostic pop
#endif


#endif // INAVIGATOR_API
