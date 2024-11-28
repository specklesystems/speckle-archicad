/****************************************************************
*  Description:	Line type definitions class for Pattern		*
*																*
*	Module:			Pattern										*
*	Namespace:		VBAttr										*
*  Contact person:	KiP											*
****************************************************************/

#ifndef LINETYPEDEFINITIONS_HPP
#define LINETYPEDEFINITIONS_HPP

#pragma once 


namespace GX {
	namespace Pattern {

		//-------------------------------------------------------------------------

		const short		MaxLineTypes		= 24;
		const short		MaxDashedLengths	= 12;
		const double	SolidLineLength		= 200000000000.0;

		//-------------------------------------------------------------------------

		enum LineTypes {
			SolidLine	= 1,
			DashedLine	= 2,
			SymbolLine	= 3
		};

		//-------------------------------------------------------------------------

		enum LineFlags {
			FixScale		= 1,
			ScaleWithPlan	= 2
		};

		//-------------------------------------------------------------------------

		enum LineDrawMethods {
			DrawFromLeftSide	= 0,
			DrawFromMiddle		= 1
		};

		//-------------------------------------------------------------------------

		enum PolyLinePerSegmentDrawMode {
			DrawPerSegment	= 0,
			DrawInOnePiece	= 1
		};

		//-------------------------------------------------------------------------
	}
}

#endif
