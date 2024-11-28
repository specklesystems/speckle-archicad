/****************************************************************************
*  Description:	Basic data structures for symbol fill patterns				*
*																			*
*	Module:			Pattern													*
*	Namespace:		VBAttr (egyenlore)										*
*  Contact person:	KiP														*
****************************************************************************/

#ifndef		SYMBOLFILLDETAILS_HPP
#define		SYMBOLFILLDETAILS_HPP

#pragma once

// Pattern
#include "PatternExport.h"

// Geometry
#include "Point2D.hpp"
#include "Box2DData.h"


namespace GX {
	namespace Pattern {

		//============================ Class SFHotspot =============================

		class PATTERN_DLL_EXPORT SFHotspot {
		public:
			// data members

			Coord		c;				// coordinate of the hotspot

		public:
			// constructors

			SFHotspot ();

			// read / write methods

			GSErrCode			Read (GS::IChannel& ic);
			GSErrCode			Write (GS::OChannel& oc) const;
			GSErrCode			WriteXML (GS::XMLOChannel& oc) const;
			GSErrCode			ReadXML (GS::XMLIChannel& ic);
		};

		//============================= Class SFLine ===============================

		class PATTERN_DLL_EXPORT SFLine {
		public:
			// data members

			Coord		begC;			// begin coordinate of the line
			Coord		endC;			// end coordinate of the line

		public:
			// constructors

			SFLine ();

			// read / write methods

			GSErrCode			Read (GS::IChannel& ic);
			GSErrCode			Write (GS::OChannel& oc) const;
			GSErrCode			WriteXML (GS::XMLOChannel& oc) const;
			GSErrCode			ReadXML (GS::XMLIChannel& ic);
		};

		//============================== Class SFArc ===============================

		class PATTERN_DLL_EXPORT SFArc {
		public:
			// data members

			Coord		begC;			// begin coordinate of the arc
			Coord		origC;			// origin of the arc
			double		angle;			// angle of the arc

		public:
			// constructors

			SFArc ();

			// read / write methods

			GSErrCode			Read (GS::IChannel& ic);
			GSErrCode			Write (GS::OChannel& oc) const;
			GSErrCode			WriteXML (GS::XMLOChannel& oc) const;
			GSErrCode			ReadXML (GS::XMLIChannel& ic);
		};

		//============================= Struct SFFill ==============================

		struct SFFill {
			Int32		nCoords;			// number of coordinates in the hatch
			Int32		nSubPolys;			// number of subpolygons in the hatch
			Int32		nArcs;				// number of arcs in the hatch
			Int32		dummy;				// not used
		};

		//=========================== Struct SFPolyArc =============================

		struct SFPolyArc {
			Int32		begIndex;			// begin index of the hatch arc in the coordinate array
			Int32		endIndex;			// end index of the hatch arc in the coordinate array
			double		arcAngle;			// angle of hatch arc
		};

		//============================ Struct SFMotifs =============================

		struct SFMotifs {
			Int32		hotNumb;			// number of hotspots in the motif
			Int32		linNumb;			// number of lines in the motif
			Int32		arcNumb;			// number of arcs in the motif
			Int32		filNumb;			// number of fills in the motif
			GSHandle	sfHotsRecs;			// hotspots array
			GSHandle	sfLinRecs;			// lines array
			GSHandle	sfArcRecs;			// arcs array
			GSHandle	sfFillRecs;			// fills array
			Box2DData	boundbox;			// bounding box of the motif
			Coord		origo;				// origin of the motif
		};

		//==================== Class SymbolFillDetailsIterator =====================

		class SymbolFillDetails;

		class PATTERN_DLL_EXPORT SymbolFillDetailsIterator {
		private:
			// data members

			const SymbolFillDetails*	symbolFillDetails;
			short						count;
			Int32						nFills;
			SFFill*						fillPtr;
			Coord*						coordPtr;
			Int32*						subPoliesPtr;
			SFPolyArc*					polyArcsPtr;

		public:
			// constructors

			SymbolFillDetailsIterator (const SymbolFillDetails& symbolFillDetails);

			// get methods

			bool				HasNextFill () const;
			SFFill*				GetNextFill ();

			// get methods (for the current fill)

			Coord*				GetFillCoordsPtr () const;
			Int32*				GetSubPoliesPtr () const;
			SFPolyArc*			GetPolyArcsPtr () const;
		};

		//======================== Class SymbolFillDetails =========================

		class PATTERN_DLL_EXPORT SymbolFillDetails {
			static GS::ClassInfo classInfo;

		private:

			friend class SymbolFillDetailsIterator;

		public:
			// data members

			SFHotspot**		hotspots;
			SFLine**		lines;
			SFArc**			arcs;
			SFFill**		fills;
			Coord**			fillCoords;
			Int32**			subPolies;
			SFPolyArc**		polyArcs;

		public:
			// constructors

			SymbolFillDetails ();
			SymbolFillDetails (const SymbolFillDetails& source);
			~SymbolFillDetails ();

			// assigment

			SymbolFillDetails&	operator= (const SymbolFillDetails& source);

			// compare

			bool				operator== (const SymbolFillDetails& rhs) const;
			bool				operator!= (const SymbolFillDetails& rhs) const;

			// set methods

			GSErrCode	Set (SFMotifs& sfMotifsRec);

			// get methods

			Int32		GetHotSpots (const SFHotspot*& hotsArray) const;
			Int32		GetLines (const SFLine*& linesArray) const;
			Int32		GetArcs (const SFArc*& arcsArray) const;
			Int32		GetFills (const SFFill*& fillsArray) const;

			Int32		GetHotSpotNumber () const;
			Int32		GetLineNumber () const;
			Int32		GetArcNumber () const;
			Int32		GetFillNumber () const;

			// I/O
			GSErrCode	Write (GS::OChannel& oc) const;
			GSErrCode	Read (GS::IChannel& ic);

			GSErrCode	WriteXML (GS::XMLOChannel& oc) const;
			GSErrCode	ReadXML (GS::XMLIChannel& ic);

		private:
			void		CopyData (const SymbolFillDetails& source);
			void		FreeMemory (); 

			GSErrCode	ReadVersion1  (GS::IChannel& ic, const GS::InputFrame& frame);
			GSErrCode	WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
		};

		//==========================================================================

	}
}
#endif
