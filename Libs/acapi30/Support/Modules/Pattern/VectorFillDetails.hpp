/**
 * **************************************************************************
 *  Description:	Basic data structures for vector fill patterns			*
 *																			*
 *	Module:			Pattern													*
 *	Namespace:		VBAttr (egyelore)										*
 *  Contact person:	KiP														*
 */

#ifndef		VECTORFILLDETAILS_HPP
#define		VECTORFILLDETAILS_HPP

#pragma once

// Pattern
#include "PatternExport.h"

// Geometry
#include "Point2D.hpp"


namespace GX {
	namespace Pattern {

		//========================= Struct OffsetedFillLine =========================

		struct OffsetedFillLine {
			double		lFreq;			// frequency of the line
			double		lDir;			// angle of the line
			double		lOffsetLine;	// offset of the line (parallel...)
			Coord		lOffset;		// offset of the line
			short		lPartNumb;		// number of the line parts
			short		dummy1;			// not used
			Int32		lPartOffset;	// line part offset in double array
		};

		//========================= Class VectorFillDetails =========================

		class PATTERN_DLL_EXPORT VectorFillDetails {
			static GS::ClassInfo classInfo;

		private:
			// data members

			Int32				nLines;
			OffsetedFillLine**	lines;
			double**			linePartLengths;

		public:
			// constructor and destructor

			VectorFillDetails ();
			VectorFillDetails (const VectorFillDetails& source);
			~VectorFillDetails ();

			// assigment

			VectorFillDetails&	operator= (const VectorFillDetails& source);

			// compare

			bool				operator== (const VectorFillDetails& rhs) const;
			bool				operator!= (const VectorFillDetails& rhs) const;

			// get methods

			Int32				GetLineNumber () const { DBASSERT ((lines == nullptr) == (nLines == 0)); return lines != nullptr ? nLines : 0; };
			OffsetedFillLine*	GetLinesPtr () const { return lines != nullptr ? *lines : nullptr; }
			double*				GetLinePartLengthsPtr () const { return linePartLengths != nullptr ? *linePartLengths : nullptr; }

			//ideiglenes megoldas, amig a VectorFillData egy GSMemoData
			void				GetForMemo (GSHandle dataHdl[3]) const;
			void				GetForMemo (Int32 lengthArray[3], GSConstPtr dataPtr[3]) const;

			void				Set (Int32 newNLines, OffsetedFillLine** newLines, double** newLinePartLengths);

			// I/O methods
			GSErrCode			Write (GS::OChannel& oc) const;
			GSErrCode			Read (GS::IChannel& ic);

			GSErrCode			WriteXML (GS::XMLOChannel& oc) const;
			GSErrCode			ReadXML (GS::XMLIChannel& ic);

		private:
			void				CopyData (const VectorFillDetails& source);

			GSErrCode			ReadVersion1  (GS::IChannel& ic, const GS::InputFrame& frame);
			GSErrCode			WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;

		};

		//===========================================================================

	}
}

#endif
