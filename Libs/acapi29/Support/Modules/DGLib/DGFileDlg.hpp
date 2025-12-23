// *****************************************************************************
// File:			DGFileDlg.hpp
//
// Description:		Common File Open, File Save and Folder Browser dialogs
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		-
//
// Contact person:	MD
//
// SG compatible
// *****************************************************************************

#ifndef DGFILEDLG_HPP
#define DGFILEDLG_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "FileTypeManager.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace IO {
	class Location;
}


// --- Type definitions --------------------------------------------------------

struct DGTypePopupItem {
	GS::UniString text;
	GS::UniString extensions;
	Int32 macType;

	void Init (void)
	{
		text.Clear ();
		extensions.Clear ();
		macType = 0;
	}

	DGTypePopupItem ()
	{
		Init ();
	}
};


// --- C interface -------------------------------------------------------------

DG_DLL_EXPORT bool CCALL	DGGetOpenFile (IO::Location* retLocation,
										   Int32 popupItemCount = 0, DGTypePopupItem* popupItems = nullptr,
										   const IO::Location* defLocation = nullptr,
										   const GS::UniString& title = GS::UniString(), Int32 flags = 0);

DG_DLL_EXPORT Int32 CCALL	DGGetOpenFile (IO::Location** retLocationArray,
										   Int32 popupItemCount = 0, DGTypePopupItem* popupItems = nullptr,
										   const IO::Location* defLocation = nullptr,
										   const GS::UniString& title = GS::UniString(), Int32 flags = 0);

DG_DLL_EXPORT bool CCALL	DGGetSaveFile (IO::Location* retLocation, Int32* retType,
										   Int32 popupItemCount, DGTypePopupItem* popupItems,
										   const IO::Location* defLocation = nullptr,
										   const GS::UniString& title = GS::UniString(), Int32 flags = 0);

DG_DLL_EXPORT bool CCALL	DGBrowseForFolder (IO::Location* retLocation, const IO::Location* defLocation = nullptr,
											   const GS::UniString& title = GS::UniString(), Int32 flags = 0,
											   IO::Location* rootLocation = nullptr);

#endif
