/****************************************************************
*  Description:	LineItem types class for Pattern			*
*																*
*	Module:			Pattern										*
*	Namespace:		VBAttr										*
*  Contact person:	KiP											*
****************************************************************/

#ifndef LINEITEMS_HPP
#define LINEITEMS_HPP

#pragma once 

// Pattern
#include "PatternExport.h"

// Geometry
#include "Point2D.hpp"


namespace GX {
	namespace Pattern {

		//-------------------------------------------------------------------------

		enum LineItemTypes {
			IllegalItemType		= 0,
			SeparatorItemType	= 1,
			CenterDotItemType	= 2,
			CenterLineItemType	= 3,
			DotItemType			= 4,
			RightAngleItemType	= 6,
			ParallelItemType	= 7,
			LineItemType		= 9,
			CircItemType		= 11,
			ArcItemType			= 12
		};

		//========================== Struct SeparatorItem =========================

		struct SeparatorItem {
			double		separatorParameter;	// center offset of the separator line item
		};

		//========================== Struct CenterDotItem =========================

		struct CenterDotItem {
			double		dotParameter;		// center offset of the dotted line item
		};

		//========================= Struct CenterLineItem =========================

		struct CenterLineItem {
			double		beginParameter;		// begin coordinate of the center line item
			double		lengthParameter;	// length of the center line item
		};

		//============================= Struct DotItem ============================

		struct DotItem {
			Point2dData		itemPosition;		// begin coordinate of the dotted line item
		};

		//=========================== Struct RightAngleItem =======================

		struct RightAngleItem {
			Point2dData		itemPosition;		// begin coordinate of the vertical line item
			double			lengthParameter;	// length of the vertical line item
		};

		//============================ Struct ParallelItem ========================

		struct ParallelItem {
			Point2dData		itemPosition;		// begin coordinate of the parallel line item
			double			lengthParameter;	// length of the parallel line item
		};

		//============================= Struct LineItem ===========================

		struct LineItem {
			Point2dData		itemPosition;		// begin coordinate of the line item
			Point2dData		lineEndC;			// end coordinate of the line item
		};

		//============================ Struct CircleItem ==========================

		struct CircleItem {
			Point2dData		itemPosition;		// begin coordinate of the circle item
			double			radius;				// radius of the circle item
		};

		//============================= Struct ArcItem ============================

		struct ArcItem {
			Point2dData		itemPosition;		// begin coordinate of the arc item
			double			radius;				// radius of the arc item
			double			begAng;				// begin angle of the arc item
			double			endAng;				// end angle of the arc item
		};

		//========================== Struct GeneralLineItem =======================

		struct GeneralLineItem {			// "base" class of line-type items (separator, center dot ...)
			Coord		begC;				// begin coordinate of the line
			Coord		endC;				// end coordinate of the line
		};

		//========================== Struct GeneralArcItem ========================

		struct GeneralArcItem {						// "base" class of arc-type items (circle, arc)
			Coord		origC;				// origin of the arc
			double		radius;				// radius of the arc
			double		begAng;				// begin angle of the arc
			double		endAng;				// end angle of the arc
		};

		//========================= Struct LineItemStruct =========================

		struct LineItemStruct {
			GeneralLineItem**	sepItemHdl;			// separator items array
			GeneralLineItem**	cDotItemHdl;		// center dot items array
			GeneralLineItem**	cLineItemHdl;		// center line items array
			GeneralLineItem**	dotItemHdl;			// dot items array
			GeneralLineItem**	rAngleItemHdl;		// right angle items array
			GeneralLineItem**	parallItemHdl;		// parallel items array
			GeneralLineItem**	lineItemHdl;		// line items array
			GeneralArcItem**	circItemHdl;		// circle items array
			GeneralArcItem**	arcItemHdl;			// arc items array
			void**				dummy1;				// not used
			Int32				nSepItem;			// number of separator items
			Int32				ncDotItem;			// number of center dot items
			Int32				ncLineItem;			// number of center line items
			Int32				nDotItem;			// number of dot items
			Int32				nrAngleItem;		// number of right angle items
			Int32				nParallItem;		// number of parallel items
			Int32				nLineItem;			// number of line items
			Int32				nCircItem;			// number of circle items
			Int32				nArcItem;			// number of arc items
			Int32				dummy2;				// not used
			Coord				origo;				// origin of the item
			bool				validOrigo;			// is it a valid origin or not
			char				dummy3;				// not used
			short				dummy4;				// not used
			Int32				dummy5;				// not used
		};

		//======================== Union LineItemDoubles ==========================

		union PATTERN_DLL_EXPORT LineItemDoubles {
			/* 0 */	double				doubles[8];
			/* 1 */	SeparatorItem		separatorItems[1];
			/* 2 */	CenterDotItem		centerDotItems[1];
			/* 3 */	CenterLineItem		centerLineItems[1];
			/* 4 */	DotItem				dotItems[1];
			/* 6 */	RightAngleItem		rightAngleItems[1];
			/* 7 */	ParallelItem		parallelItems[1];
			/* 9 */	LineItem			lineItems[1];
			/* B */	CircleItem			circItems[1];
			/* C */	ArcItem				arcItems[1];
		};

		//========================== Struct LineItemHead ==========================

		struct LineItemHead {
			Int32		filler_0;	// "checkSum" <-- not used after 6.0
			short		typ;		// SeparatorItem, CenterDotItem, CenterLineItem, DotItem, RightAngleItem, ParallelItem, LineItem, CircleItem, ArcItem
			short		num;		// number of the doubles in the itemArray
		};

		//========================== Struct LineItems =============================

		struct LineItems {
			LineItemHead		lineItemHead;
			LineItemDoubles		itemArray;
		};

		//-------------------------------------------------------------------------

	}
}

extern "C" {
	PATTERN_DLL_EXPORT Int32	GetLineItemSize (short itemType);
}

#endif
