/****************************************************************
*  Desrciption:	LineData class									*
*																*
*  Contact person:	KiP											*
****************************************************************/

#ifndef LINEDATA_HPP
#define LINEDATA_HPP

// Pattern
#include "PatternExport.h"
#include "LineTypeDefinitions.hpp"
#include "LineItems.hpp"
#include "DashedLinePattern.hpp"

// GSRoot
#include "UniString.hpp"

namespace GX {
	namespace Pattern {

		//-------------------------------  Predeclarations -----------------------------

		class LineData;

		//============================ LineItemsIterator Class =========================

		class PATTERN_DLL_EXPORT LineItemsIterator {

		private:
			// data members

			LineItems**		lineItems;
			LineItems*		lineItemsPtr;
			short			count;
			short			nLineItems;

		public:
			// constructors

			LineItemsIterator (const LineData& lineData);
			~LineItemsIterator ();


			// get methods

			bool			HasNextLineItems (void) const;
			LineItems*		GetNextLineItems (void);
		};

		//================================ LineData Class ==============================

		class PATTERN_DLL_EXPORT LineData {

		private:
			// friend classes

			friend class LineItemsIterator;


			// data members

			GS::UniString				name;
			short						flags;
			double						defineScale;			/* the scale (0.0 for fixed scale) */
			double						linePeriod;				/* the length of a period, don't care for solid */
			double						lineHeight;				/* the height of the line (0.0 for solid and dashed lines) */
			LineTypes					lineType;				/* SolidLine, DashedLine, SymbolLine (0: invalid) */
			short						lineFlags;				/* FixScale, ScaleWithPlan (0: invalid) */
			short						nLineItems;
			Int32**						itemTypeOffsets;
			LineItems**					lineItems;
			bool						visible;
			DashedLinePattern			dashedLinePattern;
				

		public:
			// constructors

			LineData ();
			LineData (const LineData& source);
			// LineData (LineTypeConstRef lineRef, bool visible);
			~LineData ();


			// assigment

			LineData&					operator= (const LineData& source);

			bool						operator== (const LineData& source) const;
			bool						operator!= (const LineData& source) const { return !operator== (source); }

			// get methods

			inline	GS::UniString		GetName (void) const { return name; }
			inline	short				GetFlags (void) const { return flags; }
			inline	double				GetScale (void) const { return defineScale; }
			inline	double				GetPeriodLength (void) const { return linePeriod; }
			inline	double				GetHeight (void) const { return lineHeight; }
			inline	LineTypes			GetType (void) const { return lineType; }
			inline	bool				IsSolidLine (void) const { return (lineType == SolidLine); }
			inline	bool				IsDashedLine (void) const { return (lineType == DashedLine); }
			inline	bool				IsSymbolLine (void) const { return (lineType == SymbolLine); }
			inline	short				GetLineFlags (void) const { return lineFlags; }
			inline	bool				IsFixScaledLine (void) const { return (lineFlags & FixScale) > 0; }
			inline	bool				IsScaledWithPlanLine (void) const { return (lineFlags & ScaleWithPlan) > 0; }
			inline	bool				IsVisible (void) const { return visible; }
			inline	short				GetLineItemsNumber (void) const { return nLineItems; }
			inline const LineItems * const *			
										GetLineItems (void) const { return lineItems; }
			bool						HasItemType (LineItemTypes itemType) const;
			LineItems*					GetItemTypePtr (LineItemTypes itemType) const;
			inline const DashedLinePattern&
										GetDashedLinePattern () const { return dashedLinePattern; }


			// set methods

			inline	void				SetName (const GS::UniString newName) { name = newName; }
			inline	void				SetFlags (short newFlags) { flags = newFlags; }
			inline	void				SetScale (double newScale) { defineScale = newScale; }
			inline	void				SetPeriodLength (double newPeriodLength) { linePeriod = newPeriodLength; }
			inline	void				SetHeight (double newHeight) { lineHeight = newHeight; }
			inline	void				SetType (LineTypes newType) { lineType = newType; }
			inline	void				SetLineFlags (short newFlags) { lineFlags = newFlags; }
			void						SetLineItems (const LineItems* const * newLineItems, short newLineItemsNumber);
			inline	void				SetVisibility (bool newVisibility) { visible = newVisibility; }
			void						SetDefaultLine (bool isVisible);
			inline	void				SetDashedLinePattern (const DashedLinePattern& newDashedLinePattern) { dashedLinePattern = newDashedLinePattern; }
			
			void						ComputeDashedLinePattern ();

			// I/O methods

			GSErrCode					WriteXML (GS::XMLOChannel& oc) const;
			GSErrCode					ReadXML  (GS::XMLIChannel& ic);

			GSErrCode					Read  (GS::IChannel& ic);
			GSErrCode					Write (GS::OChannel& oc) const;

			// check methods TODO megírni

			GSErrCode					Check (void) { return NoError; }

		private:
			// other methods
			GSErrCode					CreateOffsets (void);

			template <class ReaderType>
			GSErrCode					Read	(ReaderType& ic);

			template <class WriterType>
			GSErrCode					Write	(WriterType& oc) const;

		};

	} 
}

#endif // LINEDATA_HPP
