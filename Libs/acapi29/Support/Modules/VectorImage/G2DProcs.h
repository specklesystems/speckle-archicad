#if !defined (G2DPROCS_H)
#define G2DPROCS_H

#pragma once

#include	"VectorImageExport.h"
#include	"SyRichText.hpp"

// --------------------------- Forward declarations ----------------------------
struct GS_RGBColor;
struct GSPattern;
struct GSPixMap;

using GSPixMapHandle = GSPixMap**;

class Guid;

namespace VBAttr {
class ExtendedPen;
}

namespace ADB {
class AttributeIndex;
}

/****************************************************************************/
/*																			*/
/*						2D SYMBOL DRAWING FUNCTIONS							*/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/
/*																			*/
/*							ExportLineProc									*/
/*																			*/
/****************************************************************************/
/*
Call-back function to export the projected lines from 3D engine.
It is called by VISAllElems function which can be activated after the
projection of the 3D model. It is also called when G2DDrawSymbols is executed.
----------------------------------------------------------------------------*/

typedef	GSErr	VI_CALL	ExportLineProc (void* userDataPtr,
										double x1, double y1, double z1,
										double x2, double y2, double z2,
										const VBAttr::ExtendedPen& ePen,
										const ADB::AttributeIndex& linetype,
										Int32 *longvals, short *shrtvals,
										bool shadowElem,
										GS::Guid* elemGuid);

/*----------------------------------------------------------------------------
Arguments:
	x1:
	y1:
	z1:
	x2:
	y2:
	z2:			the projected coordinates of the line,
	ePen:		the pen index of the line,
	linetype:	the type index of the line,
	longvals:
	shortvals:	pointer to a long array with three values (longvals) and
				pointer to a short array with four values (shortvals) which
				were defined with the seven parameters of the VOCA statement
				in GDL script.
				These additional informations are stored in the body record of
				3D data structure. (see the SetVocaProc in GDLlib2.h)
				These values can be used to manage your own group.
*/


/****************************************************************************/
/*																			*/
/*							ExportPolyProc									*/
/*																			*/
/****************************************************************************/
/*
Call-back function to export the projected polygons from 3D engine.
It is called by VISAllElems function which can be activated after the
projection of the 3D model. It is also called when G2DDrawSymbols is executed.
----------------------------------------------------------------------------*/

typedef	GSErr	VI_CALL	ExportPolyProc (void* userDataPtr,
										Int32 nends, const UInt32 *pends, Int32 ncoos, const Coord *pcoos,
										const VBAttr::ExtendedPen& fpen, const GS_RGBColor *forecolor,
										short bpenind, const GS_RGBColor *backcolor,
										const ADB::AttributeIndex& fillind, GSPattern *pattern, Int32 *longvals, short *shrtvals,
										bool shadowElem /* = false*/, GS::Guid* elemGuid);	//vc7.1

/*----------------------------------------------------------------------------
Arguments:
	nends:		the number of contours of the polygon,
	pends:		pointer to a long array indexed from 0 to 'nends',
				including the indexes of the last vertexes of each contour.
	ncoos:		the number of vertexes of the polygon,
	pcoos:		pointer to a double array including the projected coordinates
				of the vertexes of the polygon,
				pcoos [2 * i]:		the 'X' coordinate of the i-th vertex,
				pcoos [2 * i + 1]:	the 'Y' coordinate of the i-th vertex,
	fpen:		the pen of the polygon pattern foreground,
	forecolor:
				the 'GS_RGBColor' of the polygon pattern foreground,
	bpenind:	the pen index of the polygon pattern background,
	backcolor:
				the 'GS_RGBColor' of the polygon pattern background,
	surfaceColor:
				the 'GS_RGBColor' of the polygon,
	fillind:	the fill index of the polygon pattern
	GSPattern:
				Fill Pattern,
	longvals:
	shortvals:	pointer to a long array with three values (longvals) and
				pointer to a short array with four values (shortvals) which
				were defined with the seven parameters of the VOCA statement
				in GDL script.
				These additional informations are stored in the body record of
				3D data structure. (see the SetVocaProc in GDLlib2.h)
				These values can be used to manage your own group.
*/


/****************************************************************************/
/*																			*/
/*								ExportHotspot2Proc							*/
/*																			*/
/****************************************************************************/
/*
Called when G2DDrawSymbols is executed.
----------------------------------------------------------------------------*/


typedef	GSErr	VI_CALL	ExportHotspotProc (void* userDataPtr,
										   double x, double y, double z,
										   short penind,
										   Int32 *longvals, short *shrtvals);


/****************************************************************************/
/*																			*/
/*								ExportTextProc								*/
/*																			*/
/****************************************************************************/
/*
Called when G2DDrawSymbols is executed.
----------------------------------------------------------------------------*/

typedef short FaceStyle;
enum {
		FaceNormal	=  0,
		FaceBold		=  1,
		FaceItalic		=  2,
		FaceUnderline	=  4,
		FaceOutline	=  8,
		FaceShadow	= 16
};

typedef enum {
		TopLeft = 1, TopMiddle, TopRight,
		MiddleLeft, MiddleMiddle, MiddleRight,
		BottomLeft, BottomMiddle, BottomRight, BaseLine
} AnchorPos;

typedef	GSErr	VI_CALL	ExportTextProc (
								void*					userDataPtr,
								short					pen,	  	/* Color information, 0 if deleted */
								FaceStyle				face,		/* (Style) Style of text */
								AnchorPos				anchor,		/* Kind of text centre (1..9);*/
								char					*fontname,	/* font name */
								Coord					loc,		/* Real coordinates of text centre */
								double					angle, 		/* Angle of text letters in rad */
								float					size, 		/* Letter size in mm independent of scale */
								float					spac,		/* Spacing between text lines in mm */
								float					slant, 		/* Slant of text letters in rad (pi/2 is plain text) */
								float					width,		/* Width of the text */
								const GS::UniString&	content,	/* Exported text	*/
								Int32 *					longvals,
								short *					shrtvals
							);

/****************************************************************************/
/*																			*/
/*							ExportRichTextProc								*/
/*																			*/
/****************************************************************************/
/*
Called when G2DDrawSymbols is executed.
----------------------------------------------------------------------------*/

typedef GSErr	VI_CALL	ExportRichTextProc (
								void*								userDataPtr,
								const Sy_RichTextType*				richText,
								const Sy_RichTextType::Paragraph*	paragraphs,
								const Sy_RichTextType::TextStyle*	textStyles,
								const Sy_RichTextType::Eol_Width*	eolWidth,
								const Sy_RichTextType::Tab*			tabs,
								const GS::uchar_t*					text
							);

/****************************************************************************/
/*																			*/
/*							ExportPixMapProc								*/
/*																			*/
/****************************************************************************/
/*
Called when G2DDrawSymbols is executed.
----------------------------------------------------------------------------*/

typedef GSErr	VI_CALL	ExportPixMapProc (
								  void*					userDataPtr,
								  const GSPixMapHandle	pixMap,		/* the pixmap to be drawn */
								  const Box2DData*		dstBox,		/* the seen size of the pixMap to be drawn */
								  bool					isMirrored,	/* PixMap is mirrored - must be done before rotation*/
								  double				angle 		/* Angle of PixMap in rad */
								);

#endif
