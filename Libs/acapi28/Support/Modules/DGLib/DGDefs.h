// *********************************************************************************************************************
// File:			DGDefs.h
//
// Description:		Common constants of the GRAPHISOFT Dialog Manager
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Contact person:	BM, HG
// *********************************************************************************************************************

#ifndef DGDEFS_H
#define DGDEFS_H

#pragma once


// --- Default Application MDID ----------------------------------------------------------------------------------------

#define DG_APP_DEFAULT_MDID_DEVELOPER_ID	0
#define DG_APP_DEFAULT_MDID_LOCAL_ID		0


// --- Dialog alert and icon Ids ---------------------------------------------------------------------------------------

#define DG_TOP_MODAL				0
#define DG_ALL_DIALOGS				-32768

#define DG_ERROR					-1
#define DG_WARNING					-2
#define DG_INFORMATION				-3

// DG_NO_ICON must be used with InvalidResModule resource module identifier
#define DG_NO_ICON					-1
#define DG_NO_IMAGE					-1

// The following DG system icons must be used with SysResModule resource module identifier
#define DG_ERROR_ICON				0
#define DG_INFORMATION_ICON			1
#define DG_WARNING_ICON				2

#define DG_FILE_ICON				3
#define DG_TEXTFILE_ICON			4
#define DG_FOLDER_ICON				5
#define DG_FOLDEROPEN_ICON			6
#define DG_MYDOCFOLDER_ICON			7
#define DG_FAVORITES_ICON			8
#define DG_FLOPPY_ICON				9
#define DG_CDDRIVE_ICON				10
#define DG_HDD_ICON					11
#define DG_NETDRIVE_ICON			12
#define DG_DESKTOP_ICON				13
#define DG_RECYCLEBIN_ICON			14
#define DG_ENTIRENETWORK_ICON		15

#define DG_FILLED_LEFT_ICON			16
#define DG_FILLED_RIGHT_ICON		17
#define DG_FILLED_DOWN_ICON			18

#define DG_FISHBONE_LEFT_ICON		19
#define DG_FISHBONE_RIGHT_ICON		20
#define DG_FISHBONE_DOWN_ICON		21

#define DG_LAST_SYSTEM_ICON			21


// --- DG Messages -----------------------------------------------------------------------------------------------------

#define DG_MSG_NULL						0
#define DG_MSG_INIT						1
#define DG_MSG_CLOSEREQUEST				2
#define DG_MSG_CLOSE					3
#define DG_MSG_CLICK					4
#define DG_MSG_DOUBLECLICK				5
#define DG_MSG_CHANGE					6
#define DG_MSG_TRACK					7
#define DG_MSG_MOUSEMOVE				8
#define	DG_MSG_FOCUS					9
#define	DG_MSG_FILTERCHAR				10
#define	DG_MSG_HOTKEY					11
#define DG_MSG_GROW						12
#define DG_MSG_RESIZE					13
#define DG_MSG_ACTIVATE					14
#define DG_MSG_TOPSTATUSCHANGE			15
#define DG_MSG_UPDATE					16
#define DG_MSG_DRAGDROP					17
#define DG_MSG_CONTEXTMENU				18
#define DG_MSG_WHEELCLICK				19		// not used
#define DG_MSG_WHEELTRACK				20
#define DG_MSG_ITEMHELP					21
#define DG_MSG_BACKGROUNDPAINT			22
#define DG_MSG_LISTHEADERCLICK			23
#define DG_MSG_LISTHEADERDRAG			24
#define DG_MSG_LISTHEADERRESIZE			25
#define DG_MSG_LISTHEADERBUTTONCLICK	26
#define DG_MSG_SPLITTERDRAG				27
#define DG_MSG_RESOLUTIONCHANGE			28
#define DG_MSG_MOUSEDOWN				29
#define DG_MSG_MOUSEUP					30
#define DG_MSG_TREEITEMCLICK			31
#define DG_MSG_TABBARITEMDRAG			32
#define DG_MSG_SWITCHWND_BEGIN			33
#define DG_MSG_SWITCHWND_NEXT			34
#define DG_MSG_SWITCHWND_PREV			35
#define DG_MSG_SWITCHWND_END			36
#define DG_MSG_HOVER					37
#define DG_MSG_PRESSED					38
#define DG_MSG_UPDATEOVERLAY			39
#define DG_MSG_CHANGEREQUEST			40
#define DG_MSG_SCALECHANGE				41
#define DG_MSG_ACTIVATEPANEL			42
#define DG_MSG_CAPTURE					43
#define DG_MSG_MOUSEENTER				44
#define DG_MSG_MOUSELEAVE				45

#define DG_OF_MSG_FOLDERCHANGE			100
#define	DG_OF_MSG_SELCHANGE				101
#define DG_OF_MSG_TYPECHANGE			102

#define DG_MSG_USER						0x3FFF


// --- DGEnableMessage Modifiers ---------------------------------------------------------------------------------------

#define DG_EMM_NONE						0
#define DG_EMM_SENDFORINACTIVEAPP		1


// --- DG_MSG_TRACK submessages ----------------------------------------------------------------------------------------

#define DG_TSM_TRACKENTER		0
#define DG_TSM_TRACKING			1
#define DG_TSM_TRACKEXIT		2

#define DG_TSM_LINEUP			3
#define DG_TSM_LINELEFT			4
#define DG_TSM_LINEDOWN			5
#define DG_TSM_LINERIGHT		6
#define DG_TSM_PAGEUP			7
#define DG_TSM_PAGELEFT			8
#define DG_TSM_PAGEDOWN			9
#define DG_TSM_PAGERIGHT		10
#define DG_TSM_TOP				11
#define DG_TSM_LEFT				12
#define DG_TSM_BOTTOM			13
#define DG_TSM_RIGHT			14
#define DG_TSM_THUMBTRACK		15


// --- DG_MSG_RESIZE submessages ---------------------------------------------------------------------------------------

#define DG_RSM_RESIZEENTER		0
#define DG_RSM_RESIZING			1
#define DG_RSM_RESIZEEXIT		2
#define DG_RSM_ABOUTTORESIZE	3


// --- DG_MSG_TOPSTATUSCHANGE submessages ------------------------------------------------------------------------------

#define DG_TSM_TOPSTATUSLOST	0
#define DG_TSM_TOPSTATUSGAINED	1


// --- DG_MSG_UPDATE submessages ---------------------------------------------------------------------------------------

#define DG_UUT_NORMAL			0
#define DG_UUT_PARTIAL			1
#define DG_UUT_INUPDATE			2


// --- DG_MSG_ITEMHELP submessages -------------------------------------------------------------------------------------

#define DG_HSM_TOOLTIP			0
#define DG_HSM_CONTEXTHELP		1


// --- DG_MSG_BACKGROUNDPAINT submessages ------------------------------------------------------------------------------

#define DG_PSM_PAINT			0
#define DG_PSM_POSTPAINT		1


// --- DG_MSG_LISTHEADERRESIZE submessages -----------------------------------------------------------------------------

#define DG_LHM_RESIZEENTER	0
#define DG_LHM_RESIZING		1
#define DG_LHM_RESIZEEXIT	2


// --- DG_MSG_SPLITTERDRAG submessages ---------------------------------------------------------------------------------

#define DG_SPL_DRAGSTART	0
#define DG_SPL_DRAG			1
#define DG_SPL_DRAGEND		2


// --- Dialog types ----------------------------------------------------------------------------------------------------

#define DG_DT_TABPAGE			0x01
#define DG_DT_ALERT				0x02
#define DG_DT_MODAL				0x04
#define DG_DT_MODELESS			0x08
#define DG_DT_PALETTE			0x10


// --- Dialog and tab page flags ---------------------------------------------------------------------------------------

#define DG_DLG_NOGROW			0x0000
#define DG_DLG_HGROW			0x0001
#define DG_DLG_VGROW			0x0002

#define DG_DLG_NOCLOSE			0x0000
#define DG_DLG_CLOSE			0x0004

#define DG_DLG_NOMINIMIZE		0x0000
#define DG_DLG_NOMAXIMIZE		0x0000
#define DG_DLG_MINIMIZE			0x0008
#define DG_DLG_MAXIMIZE			0x0010

#define DG_DLG_TOPCAPTION		0x0000
#define DG_DLG_LEFTCAPTION		0x0020
#define DG_DLG_NOCAPTION		0x0040

#define DG_DLG_NORMALFRAME		0x0000
#define DG_DLG_THICKFRAME		0x0080
#define DG_DLG_NOFRAME			0x0100

#define DG_DLG_TABBARPARENT		0x0200


// --- Dialog item types -----------------------------------------------------------------------------------------------

#define	DG_ITM_BUTTON			1		// DG_MSG_CLICK
#define	DG_ITM_CHECKBOX			2		// DG_MSG_CHANGE, DG_MSG_DOUBLECLICK
#define DG_ITM_RADIOBUTTON		3		// DG_MSG_CHANGE, DG_MSG_DOUBLECLICK
#define	DG_ITM_LISTBOX			4		// DG_MSG_CLICK, DG_MSG_DOUBLECLICK, DG_MSG_CHANGE, DG_MSG_MOUSEMOVE, DG_MSG_FOCUS
#define	DG_ITM_POPUPCONTROL		5		// DG_MSG_CHANGE
#define	DG_ITM_TABCONTROL		6		// DG_MSG_CHANGE if subtype is DG_TT_NORMALTAB
#define	DG_ITM_SPINCONTROL		7		// DG_MSG_CHANGE, DG_MSG_TRACK
#define	DG_ITM_PROGRESSBAR		8
#define	DG_ITM_SCROLLBAR		9		// DG_MSG_CHANGE, DG_MSG_TRACK
#define	DG_ITM_SLIDER			10		// DG_MSG_CHANGE, DG_MSG_TRACK
#define	DG_ITM_DATETIME			11		// DG_MSG_CHANGE, DG_MSG_FOCUS
#define	DG_ITM_EDITTEXT			12		// DG_MSG_CHANGE, DG_MSG_FOCUS, DG_MSG_FILTERCHAR
#define	DG_ITM_STATICTEXT		13		// DG_MSG_CLICK, DG_MSG_DOUBLECLICK, DG_MSG_MOUSEMOVE
#define	DG_ITM_GROUPBOX			14
#define	DG_ITM_SEPARATOR		15
#define	DG_ITM_ICONITEM			16		// DG_MSG_CLICK, DG_MSG_DOUBLECLICK
#define	DG_ITM_PICTITEM			17		// DG_MSG_CLICK, DG_MSG_DOUBLECLICK
#define	DG_ITM_USERITEM			18		// DG_MSG_CLICK, DG_MSG_DOUBLECLICK, DG_MSG_MOUSEMOVE, DG_MSG_UPDATE
#define	DG_ITM_USERCONTROL		19		// DG_MSG_CHANGE, DG_MSG_DOUBLECLICK, DG_MSG_TRACK
#define	DG_ITM_TREEVIEW			20		// DG_MSG_CLICK, DG_MSG_CHANGE, DG_MSG_FOCUS
#define	DG_ITM_LISTVIEW			21		// DG_MSG_DOUBLECLICK, DG_MSG_CHANGE, DG_MSG_FOCUS
#define	DG_ITM_RULER			22		// DG_MSG_CHANGE, DG_MSG_DOUBLECLICK
#define	DG_ITM_SPLITTER			23		// DG_MSG_SPLITTERDRAG, DG_MSG_CLICK, DG_MSG_DOUBLECLICK
#define	DG_ITM_TABBAR			24		// DG_MSG_CHANGE
#define	DG_ITM_BROWSER			25
#define	DG_ITM_TABLEVIEW		26		// DG_MSG_CLICK, DG_MSG_CHANGE, DG_MSG_FOCUS


// --- Button checkbox and radiobutton subtypes ------------------------------------------------------------------------

#define DG_BT_TEXT				1
#define DG_BT_ICON				2
#define DG_BT_PUSHTEXT			3
#define DG_BT_PUSHICON			4
#define DG_BT_PUSHMENUICON		5
#define DG_BT_SPLIT				6
#define DG_BT_ICONTEXT			7


// --- Button appearance types -----------------------------------------------------------------------------------------

#define DG_BA_TYPEMASK			0x000F
#define DG_BA_NORMAL			0
#define DG_BA_BEVEL				1
#define DG_BA_ROUNDEDBEVEL		2

// --- Button frame types ----------------------------------------------------------------------------------------------

#define DG_BF_FRAMEMASK			0x0010
#define DG_BF_FRAME				0x0000
#define DG_BF_NOFRAME			0x0010


// --- Split Button types ----------------------------------------------------------------------------------------------

#define	DG_SBT_ICONTEXT			0
#define	DG_SBT_ICONONLY			1
#define	DG_SBT_TEXTONLY			2


// --- Button content alignment types ----------------------------------------------------------------------------------

#define DG_BTA_CENTER			0
#define DG_BTA_LEFT				1
#define DG_BTA_RIGHT			2


// --- PushCheck arrow types ----------------------------------------------------------------------------------

#define DG_PCA_NONE				0
#define DG_PCA_RIGHT			1
#define DG_PCA_DOWN				2


// --- Listbox subtypes and constants ----------------------------------------------------------------------------------

#define DG_LT_SINGLESELECT		1
#define DG_LT_MULTISELECT		2
#define DG_LT_NOPARTIALITEMS	4
#define DG_LT_NOSCROLL			8
#define DG_LT_VSCROLL			16
#define DG_LT_HSCROLL			32
#define DG_LT_HEADER			64
#define DG_LT_FRAME				128

#define DG_LIST_TOP				1			// it is also referenced in GSAutoTester.cpp !!!!!!!!!!!!
#define DG_LIST_BOTTOM			-1

#define DG_LIST_NORMALITEM		0
#define DG_LIST_SEPARATOR		-1

#define DG_LIST_NOSPECAREA		0
#define DG_LIST_INDRAGAREA		1
#define DG_LIST_INUSERAREA		2

#define DG_LIST_DRAGICON		-2

#define DG_LIST_CHECKEDICON				-3		//black frame	, black tick
#define DG_LIST_UNCHECKEDICON			-4		//black frame
#define DG_LIST_MIXEDCHECKEDICON		-5		//black frame	, black dash
#define DG_LIST_GRAYCHECKEDICON			-6		//gray frame	, gray tick
#define DG_LIST_GRAYUNCHECKEDICON		-7		//gray frame
#define DG_LIST_GRAYMIXEDCHECKEDICON	-8		//gray frame	, gray dash
#define DG_LIST_FRAMELESSCHECKICON		-9		//black tick
#define DG_LIST_FRAMELESSGRAYCHECKICON	-10		//gray tick


#define DG_LISTHS_NORMAL		0
#define DG_LISTHS_FORITEM		1

#define DG_TREEHS_NORMAL		0
#define DG_TREEHS_FORITEM		1
#define DG_TREEHS_UNDERCONTENT	2

#define DG_LHA_NONE				0
#define DG_LHA_UP				1
#define DG_LHA_DOWN				2
#define DG_LHA_DOUBLEUP			3
#define DG_LHA_DOUBLEDOWN		4


// --- Popup control constants -----------------------------------------------------------------------------------------

#define DG_POPUP_TOP			1
#define DG_POPUP_BOTTOM			-1

#define DG_POPUP_SEPARATOR		-1


// --- Tab control subtypes and constants ------------------------------------------------------------------------------

#define DG_TT_NORMALTAB			0
#define DG_TT_SIMPLETAB			1

#define DG_STS_NOFRAME			0
#define DG_STS_FRAME			1

#define DG_TAB_ALLITEMS			0
#define DG_TAB_FIRSTITEM		1
#define DG_TAB_LASTITEM			-1


// --- Spin control subtypes -------------------------------------------------------------------------------------------

#define DG_ST_SINGLESPIN		0
#define DG_ST_EDITSPIN			1


// --- Scrollbar control subtypes --------------------------------------------------------------------------------------

#define DG_SB_NORMAL			1
#define DG_SB_PROPORTIONAL		2
#define DG_SB_NONFOCUSABLE		4
#define DG_SB_NOAUTOSCROLL		8


// --- Slider control subtypes -----------------------------------------------------------------------------------------

#define DG_SL_BOTTOMRIGHT		0
#define DG_SL_TOPLEFT			1


// --- Date/Time control subtypes --------------------------------------------------------------------------------------

#define DG_DT_DATE				0
#define DG_DT_TIME				1
#define DG_DT_CALENDAR			2


// --- Edittext subtypes -----------------------------------------------------------------------------------------------

#define DG_ET_TYPEMASK			0x001F
#define DG_ET_TEXT				0x0000
#define DG_ET_MULTILINETEXT		0x0001
#define DG_ET_PASSWORD			0x0002
#define DG_ET_REAL				0x0003
#define DG_ET_ANGLE				0x0004
#define DG_ET_POLARANGLE		0x0005
#define DG_ET_LENGTH			0x0006
#define DG_ET_MM_OR_PT			0x0007
#define DG_ET_MM_OR_INCH		0x0008
#define DG_ET_INT				0x0009
#define DG_ET_POSINT			0x000A
#define DG_ET_RICHEDITTEXT		0x000B
#define DG_ET_SHORTCUT			0x000C
#define DG_ET_UNIRICHEDIT		0x000D
#define DG_ET_AREA				0x000E
#define DG_ET_VOLUME			0x000F
#define DG_ET_SEARCH			0x0010
#define DG_ET_SAM_PTSTIFFNESS	0x0011
#define DG_ET_SAM_PRSTIFFNESS	0x0012
#define DG_ET_SAM_LTSTIFFNESS	0x0013
#define DG_ET_SAM_LRSTIFFNESS	0x0014
#define DG_ET_SAM_STSTIFFNESS	0x0015
#define DG_ET_SAM_TRFORCE		0x0016
#define DG_ET_SAM_RRMOMENT		0x0017

#define DG_ET_SAM_PLFORCE		0x0018
#define DG_ET_SAM_PLMOMENT		0x0019
#define DG_ET_SAM_ELFORCE		0x001A
#define DG_ET_SAM_ELMOMENT		0x001B
#define DG_ET_SAM_SLFORCE		0x001C

#define DG_ET_FRAMEMASK			0x0020
#define DG_ET_FRAME				0x0000
#define DG_ET_NOFRAME			0x0020

#define DG_ET_ABSRELMASK		0x0040
#define DG_ET_ABSOLUTE			0x0000
#define DG_ET_RELATIVE			0x0040

#define DG_ET_CHANGEFONTMASK	0x0080
#define DG_ET_CHANGEFONT		0x0000
#define DG_ET_NOCHANGEFONT		0x0080

#define DG_ET_UPDATEMASK		0x0600
#define DG_ET_UPDATE			0x0000
#define DG_ET_NOUPDATE			0x0200
#define DG_ET_NODELAY			0x0400

#define DG_ET_SCROLLMASK		0x9800
#define DG_ET_NOSCROLL			0x0000
#define DG_ET_HSCROLL			0x0800
#define DG_ET_VSCROLL			0x1000
#define DG_ET_HAUTOSCROLL		0x8000

#define DG_ET_READONLYMASK		0x0100
#define DG_ET_EDITABLE			0x0000
#define DG_ET_READONLY			0x0100

#define DG_ET_RESIZEMASK		0x2000
#define DG_ET_AUTORESIZE		0x0000
#define DG_ET_NOAUTORESIZE		0x2000

#define DG_ET_WRAPMASK			0x4000
#define DG_ET_EOFWRAP			0x0000
#define DG_ET_WORDWRAP			0x4000


// --- Multiline edittext constants ------------------------------------------------------------------------------------

#define DG_EOL_DEFAULT			0
#define DG_EOL_CR				1
#define DG_EOL_CRLF				2

#if defined (WINDOWS)
	#define DG_EOL				"\r\n"
#endif

#if defined (macintosh)
	#define DG_EOL				"\x0D"
#endif

// --- Richedittext constants ------------------------------------------------------------------------------------------

#define DG_REP_TEXTBEGIN		0
#define DG_REP_TEXTEND			GS::MaxInt32

#define DG_RFT_DOWN				0
#define DG_RFT_UP				1
#define DG_RFT_WHOLEWORD		2
#define DG_RFT_MATCHCASE		4

#define DG_RECF_CONTENT			0
#define DG_RECF_SELECTION		1
#define DG_RECF_RESIZEREQUEST	2
#define DG_RECF_SCROLLBARPOS	3


// --- Unicode Richedit constants --------------------------------------------------------------------------------------

// New UniCode end-of-line markers
#define DG_UNI_LS				0x2028
#define DG_UNI_PS				0x2029
#define DG_UNI_NEL				0x0085

// CharStyle Flags
#define DG_STY_COLOR				0x0001
#define DG_STY_SIZE					0x0002
#define DG_STY_FONT					0x0040
#define 	DG_STY_VSHIFT_EFFECT	0x0100		// sub- or superscript
#define 	DG_STY_STRIKE_EFFECT	0x0200
#define		DG_STY_PROTECTED_EFFECT	0x0400
#define DG_STY_ALLEFFECT			0x0700
#define 	DG_STY_NORMAL_STYLE		0x1000
#define 	DG_STY_BOLD_STYLE		0x2000
#define 	DG_STY_ITALIC_STYLE		0x4000
#define 	DG_STY_UNDERLINE_STYLE	0x8000
#define DG_STY_ALLSTYLE				0xF000
#define DG_STY_ALL					0xFFFF

// Paragraph Flags
#define DG_PARA_JUSTIFICATION	0x0001
#define DG_PARA_FIRSTINDENT		0x0002
#define DG_PARA_LEFTINDENT		0x0004
#define DG_PARA_RIGHTINDENT		0x0008
#define DG_PARA_TABULATORS		0x0010
#define DG_PARA_LEADING			0x0020
#define DG_PARA_ALL				0xFFFF

// Effect flags
#define DG_FX_STRIKEOUT			0x0001
#define DG_FX_SUPERSCRIPT		0x0002
#define DG_FX_SUBSCRIPT			0x0004
#define DG_FX_FRACTIONAL		0x0008
#define DG_FX_PROTECTED			0x0010

// Style Flags
#define DG_CHSTY_NORMAL			0x0000
#define DG_CHSTY_BOLD			0x0001
#define DG_CHSTY_ITALIC			0x0002
#define DG_CHSTY_UNDERLINE		0x0004

// Justification Flags
#define DG_JSTY_LEFT			0x0001
#define DG_JSTY_CENTER			0x0002
#define DG_JSTY_RIGHT			0x0003
#define DG_JSTY_FULL			0x0004

// Tab Alignment Flags
#define DG_TAB_LEFT				0x0001
#define DG_TAB_CENTER			0x0002
#define DG_TAB_RIGHT			0x0003
#define DG_TAB_DECIMAL			0x0004


// --- Maximum allowed double value in DG ------------------------------------------------------------------------------

#define DG_DBL_MAX				1.0E+35


// --- Groupbox subtypes -----------------------------------------------------------------------------------------------

#define DG_GT_PRIMARY			0
#define DG_GT_SECONDARY			1


// --- Separator subtypes ----------------------------------------------------------------------------------------------

#define DG_SP_HORIZONTAL		0
#define DG_SP_VERTICAL			1
#define DG_SP_RECT				2


// --- Useritem subtypes -----------------------------------------------------------------------------------------------

#define DG_UT_NORMALUPDATE		0
#define DG_UT_PARTIALUPDATE		1
#define DG_UT_DRAWINGUPDATE		2


// --- Treeview subtypes and constants ---------------------------------------------------------------------------------

#define DG_TVT_SUBTYPEMASK		1
#define DG_TVT_SINGLESELECT		0
#define DG_TVT_MULTISELECT		1
#define DG_TVT_LABELEDIT		2
#define DG_TVT_DRAGDROP			4
#define DG_TVT_ROOTBUTTON		8
#define DG_TVT_FRAME			16

#define DG_TVI_ROOT				0
#define DG_TVI_NONE				-1

#define DG_TVI_TOP				-65535
#define DG_TVI_BOTTOM			-65534

#define DG_TVG_FIRST			0
#define DG_TVG_NEXT				1
#define DG_TVG_PREVIOUS			2
#define DG_TVG_PARENT			3
#define DG_TVG_CHILD			4
#define DG_TVG_FIRSTLISTED		DG_TVG_FIRST
#define DG_TVG_LASTLISTED		5
#define DG_TVG_NEXTLISTED		6
#define DG_TVG_PREVLISTED		7

#define DG_TVR_NOTLISTED		   -1
#define DG_TVR_LISTED				0
#define DG_TVR_PARTIALLY_VISIBLE	1
#define DG_TVR_FULLY_VISIBLE		2


#define DG_TVIT_NORMAL			0
#define DG_TVIT_STATE			1
#define DG_TVIT_OVERLAY			2

#define DG_TVCF_SELECTION		0
#define DG_TVCF_EDITBEGIN		1
#define DG_TVCF_EDITEND			2
#define DG_TVCF_EXPAND			3
#define DG_TVCF_COLLAPSE		4

#define DG_TVCR_SETNEWTEXT		0
#define DG_TVCR_KEEPOLDTEXT		1
#define DG_TVCR_EDITTEXT		2

#define DG_TVIC_CHECKED				DG_LIST_CHECKEDICON
#define DG_TVIC_UNCHECKED			DG_LIST_UNCHECKEDICON
#define DG_TVIC_GRAYCHECKED			DG_LIST_GRAYCHECKEDICON
#define DG_TVIC_MIXEDCHECKED		DG_LIST_MIXEDCHECKEDICON
#define DG_TVIC_GRAYCHECKED			DG_LIST_GRAYCHECKEDICON
#define DG_TVIC_GRAYUNCHECKED		DG_LIST_GRAYUNCHECKEDICON
#define DG_TVIC_GRAYMIXEDCHECKED	DG_LIST_GRAYMIXEDCHECKEDICON
#define DG_TVIC_FRAMELESSCHECK		DG_LIST_FRAMELESSCHECKICON
#define DG_TVIC_FRAMELESSGRAYCHECK	DG_LIST_FRAMELESSGRAYCHECKICON

#define DG_TVPI_STATEICON		0
#define DG_TVPI_NORMALICON		1


// --- Listview subtypes and constants ---------------------------------------------------------------------------------

#define DG_LVT_SINGLESELECT		0
#define DG_LVT_MULTISELECT		1

#define DG_LVVM_VIEWMODEMASK	0x000F
#define DG_LVVM_BOTTOMTEXT		0
#define DG_LVVM_RIGHTTEXT		1
#define DG_LVVM_SINGLECOLUMN	2

#define DG_LVST_SCROLLTYPEMASK	0x00F0
#define DG_LVST_HIDESCROLLBAR	16
#define DG_LVST_FORCESCROLLBAR	32

#define DG_LVFT_FRAMEMASK		0x0100
#define DG_LVFT_FRAME			0x0100

#define DG_LVIT_NOIMAGE			-1
#define DG_LVIT_ICON			0
#define DG_LVIT_PICTURE			1
#define DG_LVIT_DIBITMAP		2
#define DG_LVIT_ICONID			3
#define DG_LVIT_PICTUREID		4
#define DG_LVIT_IMAGEINDEX		5
#define DG_LVIT_OWNERDRAW		6
#define DG_LVIT_ICONIMAGEREF	7

#define DG_LVBG_NORMAL			0
#define DG_LVBG_BUTTONFACE		1

#define DG_LVSS_NORMAL			0
#define DG_LVSS_PUSH			1

#define DG_LVHS_NORMAL			0
#define DG_LVHS_FORITEM			1


// --- TableView subtypes and constants --------------------------------------------------------------------------------

#define DG_TAV_SUBTYPEMASK		1
#define DG_TAV_HIERARCHICAL		0

// --- Ruler subtypes and change message constants ---------------------------------------------------------------------

#define		DG_RT_TYPEMASK		0x000F
#define DG_RT_EDITOR			0x0000
#define DG_RT_2DWINDOW			0x0001
#define DG_RT_TABLE				0x0002

#define		DG_RT_DIRMASK		0x0010
#define DG_RT_VERTICAL			0x0010

#define DG_RUPT_FIRSTLINEINDENT		0
#define DG_RUPT_LEFTINDENT			1
#define DG_RUPT_RIGHTINDENT			2
#define DG_RUPT_TAB					3
#define DG_RUPT_NONSPECIFICPART		4


// --- Splitter control subtypes ---------------------------------------------------------------------------------------

#define DG_SPLT_HORIZONTAL		0
#define DG_SPLT_VERTICAL		1
#define DG_SPLT_TRANSPARENT		2


// --- Tabbar control type defines -------------------------------------------------------------------------------------

#define DG_TBT_ICONTEXT		0
#define DG_TBT_TEXTONLY		1
#define DG_TBT_ICONONLY		2


// --- Tabbar control item alignment types -----------------------------------------------------------------------------

#define DG_TBA_LEFT			0
#define DG_TBA_CENTER		1
#define DG_TBA_RIGHT		2


// --- Tabbar control status -------------------------------------------------------------------------------------------

#define DG_TBS_NORMAL			0	// Enable context menu and icon button event processing
#define DG_TBS_PARTLYDISABLED	1	// Disable context menu click, and icon button click

// --- Tabbar control part and special item indexes. These values must be negative -------------------------------------

#define DG_TB_CONTROL		-1		// Empty area on the control
#define DG_TB_ICONBUTTON	-2		// Icon button
#define DG_TB_MENUPOPUP		-3		// Menu popup for invisible items
#define DG_TB_NONE			-4		// Area outside of the control
#define DG_TB_FIRSTVISIBLE	-5		// Identifier of the first visible item
#define DG_TB_LASTVISIBLE	-6		// Identifier of the last visible item
#define DG_TB_LASTTAB		-7		// Identifier of the last tab item


// --- Tabbar close button visibility mode -----------------------------------------------------------------------------

#define DG_TBITEM_CLOSEBTNDEPENDSONTABBAR	0
#define DG_TBITEM_CLOSEBTNSWITCHEDOFF		1


// --- Tabbar item close button visibility modifier --------------------------------------------------------------------

#define DG_TBITEM_USEVERTALIGNRULESOFTABBAR	0
#define DG_TBITEM_VERTALIGNRULESSWITCHEDOFF	1

// --- Tabbar item control state ---------------------------------------------------------------------------------------

#define DG_TBITEM_CONTROLSTATE_NORMAL			0
#define DG_TBITEM_CONTROLSTATE_HOVERED			1
#define DG_TBITEM_CONTROLSTATE_HOVEREDCLOSEBTN	2
#define DG_TBITEM_CONTROLSTATE_CLICKED			3
#define DG_TBITEM_CONTROLSTATE_CLICKEDCLOSEBTN	4

// --- Dialog item text parameters -------------------------------------------------------------------------------------

#define DG_IS_DEFAULT			-1

#define DG_IS_STATUSMASK		0x0003
#define DG_IS_ENABLE			0x0000
#define DG_IS_GRAY				0x0001
#define DG_IS_DISABLE			0x0002

#define DG_IS_SIZEMASK			0x000C
#define DG_IS_LARGE				0x0000
#define DG_IS_SMALL				0x0004
#define DG_IS_EXTRASMALL		0x0008

#define DG_IS_STYLEMASK			0x00F0
#define DG_IS_PLAIN				0x0000
#define DG_IS_BOLD				0x0010
#define DG_IS_ITALIC			0x0020
#define DG_IS_UNDERLINE			0x0030
#define DG_IS_SHADOW			0x0040
#define DG_IS_OUTLINE			0x0050

#define DG_IS_HJUSTMASK			0x0300
#define DG_IS_LEFT				0x0000
#define DG_IS_CENTER			0x0100
#define DG_IS_RIGHT				0x0200

#define DG_IS_VJUSTMASK			0x0C00
#define DG_IS_VTOP				0x0000
#define DG_IS_VCENTER			0x0400
#define DG_IS_VBOTTOM			0x0800

#define DG_IS_TRUNCMASK			0x3000
#define DG_IS_NOTRUNC			0x0000
#define DG_IS_TRUNCEND			0x1000
#define DG_IS_TRUNCMIDDLE		0x2000


// --- Item frame types ------------------------------------------------------------------------------------------------

#define DG_FT_NONE				0
#define DG_FT_STATIC			1
#define DG_FT_CLIENT			2
#define DG_FT_MODAL				3


// --- DG unit constants -----------------------------------------------------------------------------------------------

#define DG_UNIT_MM				1
#define DG_UNIT_CM				2
#define DG_UNIT_DM				3
#define DG_UNIT_M				4
#define DG_UNIT_KM				5
#define DG_UNIT_DECINCH			6
#define DG_UNIT_FOOT_INCH		7
#define DG_UNIT_INCH			8
#define DG_UNIT_FOOT_DECINCH	9
#define DG_UNIT_DECFOOT			10

#define DG_UNIT_DECDEGREE		11
#define DG_UNIT_DEGMINSEC		12
#define DG_UNIT_GRAD			13
#define DG_UNIT_RADIAN			14
#define DG_UNIT_SURVEYORS		15

#define DG_UNIT_MM2				15
#define DG_UNIT_CM2				16
#define DG_UNIT_DM2				17
#define DG_UNIT_M2				18
#define DG_UNIT_SQ_INCH			19
#define DG_UNIT_SQ_FOOT			20

#define DG_UNIT_CM3				21
#define DG_UNIT_DM3_LITER		22
#define DG_UNIT_M3				23
#define DG_UNIT_CU_INCH			24
#define DG_UNIT_CU_FOOT			25
#define DG_UNIT_CU_YARD			26
#define DG_UNIT_US_GALLON		27

#define DG_ANGLE_DD				0
#define DG_ANGLE_DDMM			1
#define DG_ANGLE_DDMMSS			2
#define DG_ANGLE_DDMMSSss		3


// --- Predefined dialog item IDs --------------------------------------------------------------------------------------

#define DG_ABORT				-2
#define DG_CLOSEBOX				-1
#define DG_OK					1
#define DG_CANCEL				2
#define DG_THIRD				3

#define DG_ALL_ITEMS			0
#define DG_NO_ITEM				-1


// --- Hotkey constants ------------------------------------------------------------------------------------------------

#define DG_MOD_COMMAND			1
#define DG_MOD_OPTION			2
#define DG_MOD_SHIFT			4
#define DG_MOD_CTRL				8

#define DG_KEY_EMPTY			0
#define DG_KEY_FIRST			-1
#define DG_KEY_BACK				-1			// these values MUST be negative, and must be continues between
#define DG_KEY_TAB				-2			// DG_KEY_FIRST and DG_KEY_LAST
#define DG_KEY_ENTER			-3
#define DG_KEY_RETURN			-4
#define DG_KEY_ESCAPE			-5

#define DG_KEY_LEFT				-6
#define DG_KEY_RIGHT			-7
#define DG_KEY_UP				-8
#define DG_KEY_DOWN				-9

#define DG_KEY_INSERT			-10
#define DG_KEY_DELETE			-11
#define DG_KEY_HOME				-12
#define DG_KEY_END				-13
#define DG_KEY_PAGEUP			-14
#define DG_KEY_PAGEDOWN			-15

#define DG_KEY_F1				-16
#define DG_KEY_F2				-17
#define DG_KEY_F3				-18
#define DG_KEY_F4				-19
#define DG_KEY_F5				-20
#define DG_KEY_F6				-21
#define DG_KEY_F7				-22
#define DG_KEY_F8				-23
#define DG_KEY_F9				-24
#define DG_KEY_F10				-25
#define DG_KEY_F11				-26
#define DG_KEY_F12				-27
#define DG_KEY_F13				-28
#define DG_KEY_F14				-29
#define DG_KEY_F15				-30

#define DG_KEY_HELP				-31
#define DG_KEY_LAST				-31


// --- Mouse button constants ------------------------------------------------------------------------------------------

#define DG_BUTTON_LEFT			1
#define DG_BUTTON_RIGHT			2
#define DG_BUTTON_WHEEL			4


// --- Constants for DG_MSG_INIT message -------------------------------------------------------------------------------

#define DG_POS_SAVED			0
#define DG_POS_DEFAULT			1
#define DG_POS_ADJUSTED			2


// --- Dialog rect type constants --------------------------------------------------------------------------------------

#define DG_CLIENT				0
#define DG_FRAME				1
#define DG_ORIGCLIENT			2
#define DG_ORIGFRAME			3
#define DG_RESTCLIENT			4
#define DG_RESTFRAME			5


// --- Dialog grow box format constants --------------------------------------------------------------------------------

#define DG_GROWBOX_TRIANGLE		0
#define DG_GROWBOX_SQUARE		1


// --- Dialog position coordinates constants ---------------------------------------------------------------------------

#define DG_GLOBAL				0
#define DG_SCREEN				1


// --- Constants for DGGetDialogId and DGSetDialogZPosition ------------------------------------------------------------

#define DG_DF_FIRST				-32768
#define DG_DF_FIRSTVISIBLE		-32767
#define DG_DF_LAST				-32766
#define DG_DF_LASTVISIBLE		-32765
#define DG_DF_NEXT				-32764
#define DG_DF_NEXTVISIBLE		-32763
#define DG_DF_PREV				-32762
#define DG_DF_PREVVISIBLE		-32761


// --- Constants for DGSetModelessDialogStatus -------------------------------------------------------------------------

#define DG_DS_NORMAL			0
#define DG_DS_ENABLED			1
#define DG_DS_DISABLED			2
#define DG_DS_EDITED			3	// undocumented


// --- Constants for DGSetModelessDialogState --------------------------------------------------------------------------

#define DG_DST_RESTORED			0
#define DG_DST_MINIMIZED		1
#define DG_DST_MAXIMIZED		2


// --- Constants for DGSetModelessDialogDockState ----------------------------------------------------------------------

#define DG_DKS_DOCKED			0
#define DG_DKS_UNDOCKED			1


// --- Constants for DGSetDialogSize and DGSetTabPageSize --------------------------------------------------------------

#define DG_CENTER				0
#define DG_TOPLEFT				1
#define DG_CENTERLEFT			2
#define DG_BOTTOMLEFT			3
#define DG_BOTTOMCENTER			4
#define DG_BOTTOMRIGHT			5
#define DG_CENTERRIGHT			6
#define DG_TOPRIGHT				7
#define DG_TOPCENTER			8


// --- Constants for DG_MSG_DRAGDROP message ---------------------------------------------------------------------------

#define DG_DRAG_STARTING		0
#define DG_DRAG_START			1
#define DG_DRAG_END				2
#define DG_DRAG_SETDELAYEDDATA	3
#define DG_DRAG_ENTER			4
#define DG_DRAG_OVER			5
#define DG_DRAG_LEAVE			6
#define DG_DRAG_DROP			7

#define DG_DRAG_REJECT			0x0000
#define DG_DRAG_ACCEPT_COPY		0x0001
#define DG_DRAG_ACCEPT_MOVE		0x0002
#define DG_DRAG_ACCEPT_LINK		0x0004
#define DG_DRAG_ACCEPT			0x0007
#define DG_DRAG_DELETE			0x0010

#define DG_DRAG_REJECT_SEL		0x0100
#define DG_DRAG_REJECT_INS		0x0200

#define DG_DRAG_INSERT_ON		0
#define DG_DRAG_INSERT_BELOW	1
#define DG_DRAG_INSERT_ABOVE	2

#define DG_DRAG_SCOPE_ITEM		0
#define DG_DRAG_SCOPE_DIALOG	1
#define DG_DRAG_SCOPE_MODULE	2
#define DG_DRAG_SCOPE_APP		3
#define DG_DRAG_SCOPE_SYSTEM	4


// --- Cursor IDs ------------------------------------------------------------------------------------------------------

#define UI_CURS_ARROW					-1
#define UI_CURS_WAIT					-2
#define UI_CURS_IBEAM					-3
#define UI_CURS_CROSS					-4
#define UI_CURS_POINTINGHAND			-5
#define UI_CURS_DRAGMOVE				-6
#define UI_CURS_DRAGCOPY				-7
#define UI_CURS_DRAGLINK				-8
#define UI_CURS_DRAGNO					-9
#define UI_CURS_LISTDRAG				-10
#define UI_CURS_DRAGDELETE				-11
#define	UI_CURS_TABLEDRAGHORIZ			-12
#define	UI_CURS_TABLEDRAGVERT			-13
#define	UI_CURS_LISTDRAGVERT			-14
#define	UI_CURS_LISTDRAGVERTSEPARATE	-15


// --- Constants for DGGetOpenFile -------------------------------------------------------------------------------------

#define DG_OF_NO_ALL_FILES				0x0001
#define DG_OF_NO_ROOT_GROUP				0x0002
#define DG_OF_GROUPS_FIRST				0x0004
#define DG_OF_DISPLAY_EXTENSIONS		0x0008
#define DG_OF_DONT_DISPLAY_EXTENSIONS	0x0010
#define DG_OF_LIST_SINGLE_CHILD_GROUPS	0x0020


// --- Constants for DGDisablePaletteDock ------------------------------------------------------------------------------

#define DG_DOCK_NONE			0
#define DG_DOCK_HORIZONTAL		1
#define DG_DOCK_VERTICAL		2
#define DG_DOCK_ALL				3


// --- Coordinate system and unit types --------------------------------------------------------------------------------

#define DG_CS_SCREEN			0	// Coordinate system with screen origin
#define DG_CS_GLOBAL			1	// Coordinate system with application client window origin
#define DG_CS_LOCAL				2	// Coordinate system with dialog or window origin
#define DG_CU_LOGICAL			4	// Logical coordinate unit
#define DG_CU_NATIVE			8	// Native coordinate unit


// --- User control messages -------------------------------------------------------------------------------------------

#if defined (WINDOWS)

#define DG_CM_SETMIN			(WM_APP + 0)
#define DG_CM_SETMAX			(WM_APP + 1)
#define DG_CM_SETVAL			(WM_APP + 2)

#define DG_CM_GETMIN			(WM_APP + 3)
#define DG_CM_GETMAX			(WM_APP + 4)
#define DG_CM_GETVAL			(WM_APP + 5)

#define DG_CM_SETDATA			(WM_APP + 6)
#define DG_CM_GETDATA			(WM_APP + 7)
#define DG_CM_DATACHANGED		(WM_APP + 8)

#define DG_CM_SETUCDATA			(WM_APP + 9)
#define DG_CM_GETUCDATA			(WM_APP + 10)

#define DG_CN_CHANGE			(WM_APP + 100)
#define DG_CN_CLICK				(WM_APP + 101)
#define DG_CN_TRACK				(WM_APP + 102)

#define DG_COMMAND_EVENT		(WM_APP + 103)

#endif

#endif
