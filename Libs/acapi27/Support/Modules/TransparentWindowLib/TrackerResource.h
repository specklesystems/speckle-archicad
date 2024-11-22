#ifndef	TRACKERRESOURCE_H
#define	TRACKERRESOURCE_H

// Tracker Icon IDs
#define ID_ACCEPTINPUT			1001
#define ID_RETURNTORUNNINGMODE	1002
#define ID_MAXIMALIZEDTRACKER	1003
#define ID_VALUELIST			1004

// Tracker Stringlist IDs
#define ID_MINIMALTEXTSTRLIST	2000
#define ID_TOOLTIPTEXTSTRLIST	2001

#if !defined (PREPROCESS_GRC)

enum {
	MinimalTextID		=	1,
	MinimalEditTextID	=	2
};

enum {
	AcceptInputID			=	1,
	ReturnToRunningModeID	=	2,
	ShowHiddenItemsID		=	3
};

#endif	// PREPROCESS_GRC

#endif
