// *****************************************************************************
// Description: VectorPrimitives contains the methods of graphical primitives.
//
// Module:			VectorImage, Platform independent
// Namespace:
// Contact person:	FGY
//
// SG compatible
//
// *****************************************************************************
#if !defined (VECTORPRIMITIVES_H)
#define VECTORPRIMITIVES_H

#pragma once

#include	"G2DProcs.h"	// VIDrawContext
#include	"VectorImageExport.h"
#include	"IrregularPolygon2D.hpp"

#include	"ProfileAdditionalInfo.hpp"

#define		HOTS_P1			2001
#define		HOTS_P2			2002
#define		HOTS_ARCCENTER  2003
#define		HOTS_ARCR1		2004
#define		HOTS_ARCR2		2005
#define		HOTS_ARCHALF	2006

#define HOTS_BL_LINE		1470
#define HOTS_BL_ARC			1471

// --------------------------- Forward declarations ----------------------------

class Sy_TextType;


// ---------------------------- Class declaration ------------------------------

struct FILL3DREC {
	GSHandle	h;
	Int32*		nLins;
	GSHandle	hPoly;
	Int32*		nPolys;
};

struct OWNLINEREC {
	Coord	beg, end;
};


class WordAnchor;
struct TRANMAT;

struct VIDrawContext {
	ExportHotspotProc		*exporthotspot;
	ExportLineProc			*exportline;
	ExportLineProc			*exporthatchline;
	ExportPolyProc			*exportpoly;
	ExportTextProc			*exporttext;
	ExportRichTextProc		*exportrichtext;
	ExportPixMapProc		*exportpixmap;

	double	scalePaperToModel;	// (x unit on the paper) * scalePaperToModel = y unit in the model
								// 1:100 means 100 (not affected by current magnification)
	double	maxArcDifference;	// the max difference between the arc and its segmented version (in the model)
								// the lesser it is the smaller segments generated
	Box2DData				*drawBox;		//the drawing box: this should cut the drawing lines, and only the inside part have to be drawn.

	void*	userDataPtr;

	VIDrawContext () :
		exporthotspot		(nullptr),
		exportline			(nullptr),
		exporthatchline		(nullptr),
		exportpoly			(nullptr),
		exporttext			(nullptr),
		exportrichtext		(nullptr),
		exportpixmap		(nullptr),
		scalePaperToModel	(0.0),
		maxArcDifference	(0.0),
		drawBox				(nullptr),
		userDataPtr			(nullptr)
	{
	}
};

struct InternalDrawLineData {
	void*			userDataPtr;
	ExportLineProc*	exportLine;
	short			thePen;
	ProfileEdgeDataTable profileEdgeData;
};

struct FillDataHeader {
	Int32		nCoords;
	Int32		nEnds;
	Int32		endOffs;
	Int32		nextOffs;
};


VI_DLL_EXPORT
GSErrCode	CCALL		InternalDrawLine (void* polyUserDataPtr, const Geometry::PolyId* edgeId, const Sector* linePiece);

VI_DLL_EXPORT
GSErrCode				Fill3DLinesHandle (FILL3DREC* fill3DRecPtr, const Coord begC, const Coord endC);

VI_DLL_EXPORT
GSErrCode				FillesHandle (FILL3DREC* fill3DRecPtr, const Geometry::IrregularPolygon2D& polygon, double /*percent*/);

VI_DLL_EXPORT
GSErrCode	VI_CALL		G2DGetWord_cSquare (
						Box2DData*			bounds,
						Coord				corners[], /* 4 items 0..3 */
						const WordAnchor&	centre,
						double				width,
						double				height,
						double				angle,
						const Coord*		loc,
						double				planScale);

// Why it is here ???
VI_DLL_EXPORT
GSErrCode	VI_CALL		Sy_WordSizeCalc (
						double*			wSize,
						double*			wWidth,
						double*			wHeight,
						double*			wSpac,
						double			wAngle,
						double			xs,
						double			ys);

VI_DLL_EXPORT
GSErrCode	VI_CALL FillSyText (
						Sy_TextType*		word,
						GSPtr*				conPtr,
						short**				lstPtr,
						short				pen,
						short				layer,
						DrawIndex			drwIndex,
						Int32				styleind,
						const Coord&		loc,
						double				angle,
						unsigned char		paramInd,
						Int32				ind1,
						Int32				ind2,
						const char*			text);

VI_DLL_EXPORT
GS::CmpFunction	CmpForHatchesFirst;


VI_DLL_EXPORT
GS::CmpFunction	CmpForSortQueue;

#endif
