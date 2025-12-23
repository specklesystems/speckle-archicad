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
/**
 * @brief Callback interface object to register with @ref ACAPI_Navigator_RegisterCallbackInterface.
 * @ingroup Navigator
 * @struct INavigatorCallbackInterface
 * @since Archicad 26
 */
class __APIEXPORT INavigatorCallbackInterface : public GS::AppExportInterfaceBase {
public:
	/**
	 * @brief The possible Teamwork modes for the navigator item in case of icon requests.
	 * @enum IconTWMode
	 */
	enum IconTWMode {
		TWNormal,
		TWReserved,
		TWBeforeSend,
		TWNotMineBeforeSend
	};

	/**
	 * @brief The possible linkness modes for the Navigator item in case of icon requests.
	 * @enum IconLinkness
	 */
	enum IconLinkness {
		Normal,
		Link,
		Shortcut,
		PDFShortcut,
		DWGShortcut,
		DXFShortcut,
		IFCShortcut
	};

	/**
	 * @brief The possible sizes of the requested icon.
	 * @enum IconSize
	 */
	enum IconSize {
		NormalSize,
		Small
	};

	/**
	 * @brief The possible contexts of the requested icon.
	 * @enum IconContext
	 */
	enum IconContext {
		Model,
		Layout
	};

	/**
	 * @brief The possible commands of the context menu.
	 * @enum ContextMenuCommand
	 */
	enum ContextMenuCommand {
		NewItemCommand,
		DeleteItemCommand,
		RenameItemCommand,
		OpenSettingsCommand
	};

	/**
	 * @brief The possible Teamwork-related commands of the context menu.
	 * @enum TWCommandMenu
	 */
	enum TWCommandMenu {
		ReserveNode,
		ReserveGroupChildren,
		ReleaseNode,
		ReleaseGroupChildren,
		RequestNode
	};

	/**
	 * @brief The possible Teamwork interactions.
	 * @enum TWCommandMail
	 */
	enum TWCommandMail {
		Request1Mail,
		RequestNMail,
		Grant1Mail,
		GrantNMail
	};

	/**
	 * @brief Used for internal purposes only. Do not override.
	 * @return Indicates whether the installed navigator interface is a dummy one.
	 */
	virtual bool		IsDummyInterface			(void) const;

	/**
	 * @brief This function is called the when user wants to open the view.
	 * @param viewPointID Navigator item's guid which user wants to open.
	 * @param newWindow Indicates whether 'Open' or 'Open in New Tab' was requested.
	 * @return Returns NoError if the view opening was succeeded otherwise with an error code.
	 */
	virtual GSErrCode	OpenView					(const API_Guid& viewPointID, bool newWindow) const = 0;

	/**
	 * @brief This function is called when the user wants to open the navigator item's settings.
	 * @param viewPointID Navigator item's guid for which settings opening is requested.
	 * @return Returns NoError if the opening settings was successful otherwise with an error code.
	 */
	virtual GSErrCode	OpenSettings				(const API_Guid& viewPointID) const = 0;

	/**
	 * @brief This function is called when there are some conflicts in Teamwork mode which needs to be resolved.
	 * @return Returns NoError if all conflicts are resolved.
	 */
	virtual GSErrCode	ExecuteMergePostProcess		() const = 0;

	/**
	 * @brief This function is called when a drawing is created or updated.
	 * @param viewPointID Navigator item's guid from which the drawing will be made.
	 * @param scale Defines the scaling from paper to model. For example, for 1:100 scaling, pass 100.
	 * @param clipBoxWidth [out] Clip box width.
	 * @param clipBoxHeight [out] Clip box height.
	 * @param idfStore [out] An opaque data stream containing the drawing database in a serialized form.
	 * @param boundingBox [out] The bounding box of the created drawing.
	 * @param paddingX [out] Padding in the X axis.
	 * @param paddingY [out] Padding in the Y axis.
	 * @param elems [out] Elements in the navigator item.
	 * @return Returns NoError if the drawing creation was successful otherwise return with an error code.
	 */
	virtual GSErrCode	CreateIDFStore				(const API_Guid& viewPointID, double scale, double& clipBoxWidth, double& clipBoxHeight, GSPtr& idfStore, API_Box& boundingBox, double& paddingX, double& paddingY, GS::Array<API_Guid>& elems) const = 0;

	/**
	 * @brief This function is called when Archicad wants to check if the drawing is up-to-date.
	 * @param viewPointID Navigator item's guid from which the drawing is made.
	 * @param elems [out] Elements in the navigator item.
	 * @return Returns NoError if the element collection is successful otherwise return with an error code.
	 */
	virtual GSErrCode	GetElemsForDrawingCheck		(const API_Guid& viewPointID, GS::Array<API_Guid>& elems) const = 0;

	/**
	 * @brief This function is called when the user clicks the "New viewpoint" command in the navigator or the identical command in the context menu.
	 * @param viewPointID Guid of the selected navigator item.
	 * @return Returns NoError if the item creation is succeeded.
	 */
	virtual GSErrCode	NewItem						(const API_Guid& viewPointID) const = 0;

	/**
	 * @brief This function is called when the user clicks the "Delete" command in the navigator or the identical command in the context menu.
	 * @param viewPointIDList List of guid of the selected navigator item which the user wants to delete.
	 * @return Returns NoError if the deletion of the items is succeeded.
	 */
	virtual GSErrCode	DeleteItem					(const GS::Array<API_Guid>& viewPointIDList) const = 0;
	
	/**
	 * @brief This function is called when the user changes the name of the view point.
	 * @param viewPointID Guid of the selected navigator item.
	 * @return Returns NoError if the item renaming is succeeded.
	 */
	virtual GSErrCode	RenameItem					(const API_Guid& viewPointID) const = 0;

	/**
	 * @brief This function is called when an icon is requested by the Navigator to be put next to the handled view by AddOn.
	 * @param iconId The type of the navigator item. Its value comes from @ref API_NavigatorAddOnViewPointTypeID.
	 * @param iconTWMode The TeamWork mode for the requested icon.
	 * @param linkness Linkness for the requested icon.
	 * @param size Requested size of the icon.
	 * @param context Context of the requested icon.
	 * @return Returns with the requested icon based on the input parameters.
	 */
	virtual DG::Icon	GetIcon						(Int32 iconId, IconTWMode iconTWMode, IconLinkness linkness, IconSize size, IconContext context) const = 0;

	/**
	 * @brief Get the string of the context menu command for the specified navigator item in case of the context menu is requested.
	 * @param cmd Command of the context menu.
	 * @param viewPointId Navigator item's guid for which the context menu is requested.
	 * @param text [out] The string of the context menu command.
	 * @return Indicates whether the string request was successful.
	 */
	virtual bool		GetContextMenuCommandString (ContextMenuCommand cmd, const API_Guid& viewPointId, GS::UniString& text) const;

	/**
	 * @brief Returns whether the given menu command is enabled for the given navigator item.
	 * @param cmd Command to be enabled.
	 * @param viewPointId Navigator item's guid for which commands enabling is defined.
	 * @return Returns true if the command is enabled otherwise false.
	 */
	virtual bool		IsContextMenuCommandEnabled (ContextMenuCommand cmd, const API_Guid& viewPointId) const;

	/**
	 * @brief Returns the given Teamwork-related menu command's string for the given navigator item.
	 * @param cmd Teamwork command of the context menu.
	 * @param viewPointId Navigator item's guid for which the context menu is requested.
	 * @param text [out] The string of the context menu command.
	 * @return Indicates whether the string request was successful.
	 */
	virtual bool		GetTWCommandMenuString		(TWCommandMenu cmd, const API_Guid& viewPointId, GS::UniString& text) const;

	/**
	 * @brief Get the text of the automatic teamwork message in case the user is granted access to the navigator item or requests it from another teamwork user.
	 * @param cmd Command of the interaction.
	 * @param viewPointId Navigator item's guid for which the interaction is requested.
	 * @param text [out] Mail string of the command.
	 * @return Indicates whether the string request was successful.
	 */
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
