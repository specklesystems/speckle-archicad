// Contact person : KiP

#ifndef LINEPATTERN_H
#define LINEPATTERN_H

#pragma once

// GSRoot
#include	"HashTable.hpp"
#include	"NonThreadSafeCounter.hpp"

// Geometry
#include	"Polyline2D.hpp"
#include	"IrregularPolygon2D.hpp"

// Pattern
#include	"PatternExport.h"
#include	"LineData.hpp"
#include	"PolygonDrawingDirection.hpp"
#include	"LinePatternPrimitivesDrawer.hpp"


//============================== LineInfo Class ================================

namespace GX {
namespace Pattern {

typedef GS::Ref<LineData, GS::NonThreadSafeCounter> LineDataRef;

class PATTERN_DLL_EXPORT LineInfo {

public:
	enum DataMemberFlag {
		LineMember			= 0x0001,
		ScaleMember			= 0x0002,
		WeightDataMember	= 0x0004
	};

protected:
	// data members

	UInt32							filledDataMember;
	LineDataRef						lineData;
	double							scalePaperToModel;
	double							weightFromIndex;
	GS::Ref<GS::Object>				additionalData;

public:
	// constructor

	LineInfo ();
	LineInfo (	LineDataRef		aLinedata,
		double					aScalePaperToModel,
		double					weightFromIndex);  

	LineInfo (const LineInfo& source);  
	virtual	~LineInfo ();


	// assignment

	LineInfo&			operator= (const LineInfo& source);	

	bool				operator== (const LineInfo& source) const;	

	// set/get methods

	const LineDataRef&	GetLineData (void) const { return lineData; }

	double				GetScalePaperToModel (void) const { return scalePaperToModel; }
	void				SetScalePaperToModel (double newScalePaperToModel) { scalePaperToModel = newScalePaperToModel; filledDataMember |= ScaleMember; }

	double				GetWeightFromIndex (void) const { return weightFromIndex; }
	void				SetWeightFromIndex (double newWeightFromIndex) { weightFromIndex = newWeightFromIndex; filledDataMember |= WeightDataMember; }

	bool				DataMemberFilled (DataMemberFlag memberId) const { return ((filledDataMember & memberId) != 0); }  	

	void						SetAdditionalData (const GS::Ref<GS::Object>& additionalDataP) { additionalData = additionalDataP; }
	const GS::Ref<GS::Object>&	GetAdditionalData (void) const { return additionalData; }

	void				LeaveThread ();


	// I/O methods

	GSErrCode			WriteXML (GS::XMLOChannel& oc) const;
	GSErrCode			ReadXML (GS::XMLIChannel& ic);

	GSErrCode			Read	(GS::IChannel& ic);
	GSErrCode			Write	(GS::OChannel& oc) const;

	// virtual methods	
		
	virtual void		UpdateLineData (const Geometry::PolyId) {};
	virtual bool		IsNear	(const LineInfo& source) const;
};

inline	LineInfo::LineInfo ():
filledDataMember (0),
	lineData (),
	scalePaperToModel (1.0),
	weightFromIndex (0.0)
{
}


inline	LineInfo::LineInfo (LineDataRef		aLineData,
	double					aScalePaperToModel = 1.0, 
	double					weightFromIndex = 0.0):
lineData (aLineData),
	weightFromIndex (weightFromIndex)
{ 
	filledDataMember = 0;
	if (lineData != nullptr) {
		filledDataMember |= LineMember;
	}
	scalePaperToModel = aScalePaperToModel;
	filledDataMember |= ScaleMember;
}


inline	LineInfo::LineInfo (const LineInfo& source):
lineData (source.lineData)
{
	filledDataMember = source.filledDataMember;
	scalePaperToModel = source.scalePaperToModel;
}

//============================= Funcion Prototypes =============================

bool DrawLineInternal (const Coord&					begPt,
					   const Coord&					endPt,
					   const LineInfo&				lineInfo,
					   double						tolerance,
					   const Box2DData*				drawBox,
					   LinePatternPrimitivesDrawer*	drawLine);

PATTERN_DLL_EXPORT
bool DrawLine (const Coord&					begPt,
			   const Coord&					endPt,
			   const LineInfo&				lineInfo,
			   double						tolerance,
			   const Box2DData*				drawBox,
			   LinePatternPrimitivesDrawer*	drawLine);

//------------------------------------------------------------------------------

void DrawPolyLineInternal (const Geometry::Polyline2D&	polyline,
						   const LineInfo&				lineInfo,
						   double						tolerance,
						   const Box2DData*				drawBox,
						   PolyLinePerSegmentDrawMode	perSegmentDrawMode,
						   LinePatternPrimitivesDrawer*	drawLine);

PATTERN_DLL_EXPORT
void DrawPolyLine (const Geometry::Polyline2D&	polyline,
				   const LineInfo&				lineInfo,
				   double						tolerance,
				   const Box2DData*				drawBox,
				   PolyLinePerSegmentDrawMode	perSegmentDrawMode,
				   LinePatternPrimitivesDrawer*	drawLine);

//------------------------------------------------------------------------------

void DrawArcInternal (const Coord*					pOrigC,
					  const Coord*					pBegC,
					  double						arcAngle,
					  const LineInfo&				lineInfo,
					  double						tolerance,
					  const Box2DData*				drawBox,
					  LinePatternPrimitivesDrawer*	drawLine);

PATTERN_DLL_EXPORT
void DrawArc (const Coord*					pOrigC,
			  const Coord*					pBegC,
			  double						arcAngle,
			  const LineInfo&				lineInfo,
			  double						tolerance,
			  const Box2DData*				drawBox,
			  LinePatternPrimitivesDrawer*	drawLine);

}
}

#endif
