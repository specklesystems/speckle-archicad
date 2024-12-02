// *****************************************************************************
// File:			UCDefs.h
//
// Description:		General external definitions header file.
//
// Project:			GRAPHISOFT User Controls (UCLib)
//
// Contact person:	VM
// *****************************************************************************

#ifndef	UCDEFS_H
#define	UCDEFS_H

#pragma once


// --- CallBack Actions for UC257 and UC261 ------------------------------------

#define	ACT_GETITEMSIZE			1			// get size of one item data
#define	ACT_GETITEM				2			// get one item data
#define	ACT_GETLISTSIZE			3			// get size of list data
#define	ACT_GETLIST				4			// get list data
#define	ACT_DRAWITEM			5			// draw one item
#define	ACT_DRAWBUTTON			6			// draw one item into button


// --- Methods for UC257 -------------------------------------------------------

#define	T257_PEN				0x0001		// pen palette method
#define	T257_FILL				0x0002		// fill palette method
#define	T257_CFILL				0x0003		// comp. fill palette method
#define	T257_MATERIAL			0x0004		// material palette method
#define	T257_TEXT				0x0005		// text list method
#define	T257_ICONTEXT			0x0006		// layer(!) list method
#define	T257_MENU				0x0007		// text menu method
#define	T257_ZONECAT			0x0008		// zone categories method
#define	T257_LAYER				0x0009		// layer control method
#define	T257_PROFILE			0x000A		// profile control method
#define	T257_BUILDINGMAT		0x000B		// building material control method


// --- Control Styles for UC257 ------------------------------------------------

#define	CS257_HEADER			0x01		// show palette header
#define	CS257_SMALLBUTTON		0x02		// small button
#define	CS257_PLAINPALETTE		0x04		// plain palette
#define	CS257_SMALLFONT			0x10		// small font text
#define	CS257_TEXTPEN			0x20		// text pen color
#define	CS257_NOMATERICONS		0x40		// omit material fill and texture icons


// --- Cell Text flags for UC257 ----------------------------------------------

#define	CF257_BOLD				0x00000001	// bold text style
#define	CF257_ITALIC			0x00000002	// italic text style
#define	CF257_UNDERLINE			0x00000004	// underline text style
#define	CF257_GRAY				0x00000008	// gray text


// --- Cell Format flags for UC257 ---------------------------------------------

#define	CF257_SHOWTEXT			0x00010000	// show item text
#define	CF257_SHOWICON			0x00020000	// show icon
#define	CF257_SHOWCOLOR			0x00040000	// use rgb values (CF257_BKGNDCOLOR and CF257_ADDITIONALPEN are omitted)
#define	CF257_SHOWPATTERN		0x00080000	// show pattern
#define	CF257_BKGNDCOLOR		0x00100000	// if (!CF257_SHOWCOLOR) bkgndPen
#define	CF257_ADDITIONALPEN		0x00200000	// if (!CF257_SHOWCOLOR) invalid pen


// --- Cell Type flags for UC257 ----------------------------------------------

#define	CF257_NOSELECT			0x01000000	// can't select this item
#define	CF257_NOBUTTONTRACK		0x02000000	// not drawn into button
#define	CF257_DUMMY				0x04000000	// dummy item
#define	CF257_SEPARATOR			0x08000000	// spearator item
#define	CF257_VALID				0x80000000	// valid item


// --- Fill Color codes for UC257 ----------------------------------------------

#define	FC257_FORECOLOR			0x00		// Foreground color
#define	FC257_BACKCOLOR			0x01		// Background color
#define	FC257_FRAMECOLOR		0x02		// Frame (contour) color	// #24094 TCS 2003.06.19
#define	FC257_SEPARATORCOLOR	0x03		// Separator (inner line/frame) color


// --- Control Styles for UC258 ------------------------------------------------

#define	CS258_HEADER			0x01		// show palette header
#define	CS258_MOUSEPOSOPEN		0x02		// palette relative to mouse position
#define	CS258_SIMPLEFRAME		0x04		// palette frame (MAC:no WIN:simple)
#define	CS258_BUTTONCENTERED	0x08		// the image centered on the whole button


// --- Control Styles for Roll Down control (UC260) ----------------------------

#define	CS_ROLLDOWN_LARGE		0x0000		// Large control (resizable)
#define	CS_ROLLDOWN_SMALL		0x0001		// Small control (nonresizeable)

#define	CS_ROLLDOWN_ACTIVE		0x0000		// Active control accepts mouse click
#define	CS_ROLLDOWN_INACTIVE	0x0002		// Inactive control refuses mouse click

#define	CS_ROLLDOWN_DRAWELLIPSIS	0x0000	// Ellipses are drawn if text does not fit in
#define	CS_ROLLDOWN_TRUNCATED		0x0004	// Text is truncated


// --- Control Styles for UC261 ------------------------------------------------

#define	CS261_HEADER			0x01		// show palette header
#define	CS261_SMALLBUTTON		0x02		// small button
#define	CS261_DYNAMIC			0x04		// dynamic data


// --- Cell Text flags for UC261 -----------------------------------------------

#define	CF261_BOLD				0x00000001	// bold text style
#define	CF261_ITALIC			0x00000002	// italic text style
#define	CF261_UNDERLINE			0x00000004	// underline text style


// --- Cell Type flags for UC261 -----------------------------------------------

#define	CF261_NOSELECT			0x01000000	// can't select this item
#define	CF261_SEPARATOR			0x08000000	// spearator item
#define CF261_HEADER			0x04000000  // header item (~separator with text)
#define	CF261_VALID				0x80000000	// valid item


// --- Cell color flags forUC262 -----------------------------------------------

#define CCF262_USEDPEN			0x01
#define CCF262_COLORCONFLICT	0x02

// --- Popup Control (UC263) control kinds -------------------------------------

#define	CK_POPUP_MENU			0
#define CK_POPUP_CONTROL		1

// --- Button Types for Popup Control (UC263) ----------------------------------

#define	BT_POPUP_ICONTEXT		0
#define	BT_POPUP_ICONONLY		1
#define	BT_POPUP_TEXTONLY		2
#define	BT_POPUP_ARROWONLY		3

// --- Text and icon alignment for Popup Control (UC263) -------------------------

#define TA_POPUP_LEFT           0x01
#define TA_POPUP_RIGHT          0x02
#define TA_POPUP_CENTER         0x03

// --- Item Height Selection for Popup Control (UC263) -------------------------

#define IH_POPUP_DEFAULT		0


// --- Image Id-s for User controls - UC Special Icons------------------------------------------------------------------

#define UCIMG_OPENLOCK			32001
#define UCIMG_CLOSEDLOCK		32002
#define UCIMG_OPENEYE			32003
#define UCIMG_CLOSEDEYE			32004
#define UCIMG_TEAM				32005
#define UCIMG_LARGECHECK		32006
#define UCIMG_SMALLCHECK		32007
#define UCIMG_HASTEXTURE		32008
#define UCIMG_OPENCLOSEDEYE		32009	// UNUSED
#define UCIMG_SMALLARROW		32010
#define UCIMG_BIGARROW			32011	// UNUSED
#define UCIMG_NULLPEN			32012
#define UCIMG_PENINDICATOR		32013	// UNUSED
#define UCIMG_BKGNDPEN			32014
#define UCIMG_WIREFRAME			32015
#define UCIMG_SHADED			32016
#define UCIMG_TEXTPEN			32017
#define UCIMG_USEWALL			32018
#define UCIMG_USEBEAM			32019
#define UCIMG_USECOLU			32020
#define UCIMG_FILL				32022
#define UCIMG_MATERIAL			32023
#define UCIMG_CWUSEWALL			32024
#define UCIMG_CWUSESLAB			32025
#define UCIMG_CWUSEROOF			32026
#define UCIMG_CWUSESHELL		32027
#define UCIMG_CWTHICKNESS		32028
#define UCIMG_CWHASCORE			32029
#define UCIMG_CWHASNOCORE		32030
#define UCIMG_BMPRIORITY		32031
#if defined (WINDOWS)
#define UCIMG_WIN_LARGECHECK_WHITE	32032
#define UCIMG_WIN_HASTEXTURE_WHITE	32034
#endif
#define UCIMG_USEHANDRAIL		32035
#define UCIMG_USEOTHERGDLOBJ	32036


#endif
