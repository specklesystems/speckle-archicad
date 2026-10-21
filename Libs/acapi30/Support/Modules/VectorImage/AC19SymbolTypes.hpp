#ifndef AC19SYMBOLTYPES
#define AC19SYMBOLTYPES

#pragma once

#include "DrawIndex.hpp"
#include "Point2D.hpp"
#include "Box2DData.h"
#include "GSPix.h"
#include "Plane3DData.h"
#include "HatchTran.hpp"
#include "IV.hpp"

namespace AC19Symbol {
	struct Sy_HatchType {
		Int32				item_Len;			// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
		unsigned char		item_Typ;			// = SyHatch (6)
		DrawIndex			drwIndex;			// index in drawing order or 0
		unsigned short		syFlags;			// See SyHatchFlag need for visualiztion
		unsigned short		buildMatFlags;		// See SyHatchBuildingMaterialFlag need for conversion only
		short				fillFgPen;			// Hatching color (0 if not hatched)
		short				sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
		short				fillIdx;			// Index of Fill attributum (0 if not hatched) when SyHatchFlag_FillHatch
		short				buildMatIdx;		// Index of Building Material attributum when SyHatchFlag_BuildingMaterialHatch
		short				contPen;			// Contour line color
		bool				contVis;			// Contour line visibility
		GS::UInt8			filler1;
		short				contLType;			// Contour line type
		short				fillBkgPen;			// if 0 transparent
		short				determine;			// It is always 0 in the library part files
		char				specFor3D;			//
		char				sy2dRenovationStatus;
		GS_RGBColor			bkgColorRGB;		// It is set if "SyHatchFlag_MillionColorBkg" set
		GS_RGBColor			fgColorRGB;			// 3 * sizeof (unsigend short) 3 * 2
		GS::UInt16			filler2;
		Int32				nCoords;			// Number of vertices
		Int32				nSubPolys;			// Number of closed sub polygons including the first one
		Int32				nArcs;				// Number of curves in the polygon
		Int32				coorLen;			// Polygon coordinate data length
		Int32				coorOff;			// Offset of the Polygon coordinate from record start					// = sizeof(Sy_HatchType)
		Int32				endsLen;			// Subpolygon endpoints data length
		Int32				endsOff;			// Offset of the Subpolygon endpoints from record start					// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
		Int32				arcsLen;			// Polygon curves data length
		Int32				arcsOff;			// Offset of the Polygon curves from record start						// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
		Int32				addInfoLen;			// Additional info for profile data length
		Int32				addInfoOff;			// Offset of the additional info for profile data from record start		// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
		UInt32				displayOrder;		// Display order
		GS::UInt32			filler3;
		PlaneEq				origPlane;
		GX::Pattern::HatchTran	hatchTrafo;		// Transformation of hatch. (offset, 2x2 matrix, innerRadius, useGlobalOrigo)

		void SetFragmentIndex (short inFragmentIndex) 
		{ 
			DBASSERT (inFragmentIndex >= 1);  
			DBASSERT (inFragmentIndex <= 16); 
			sy_fragmentIdx = inFragmentIndex; 
		}

		void SetContVis (const bool newVal) 
		{
			contVis = newVal;
		}

		void SetContPen (const short newPenVal) 
		{
			contPen = newPenVal; 
			contVis = (newPenVal != 0);
		}
		
		void SetContLType (short lType)
		{
			DBASSERT (lType > 0);
			contLType = lType;
		}

		void IVDisplayOrder (GS::PlatformSign from, GS::PlatformSign to) 
		{ 
			IVULong (from, to, &displayOrder); 
		}

		bool GetContVis () const 
		{ 
			return (contVis != 0); 
		}

		short GetContPenVal () const 
		{ 
			return contPen; 
		}

		short GetContLType (void) const
		{
			return contLType;
		}
		
		bool CheckAndRepairFragmentIndex(void)
		{
			if (sy_fragmentIdx < 1 || sy_fragmentIdx > 16) {
				sy_fragmentIdx = 1;
			}
			return true;
		}

		short GetFragmentIndex () const 
		{ 
			DBASSERT (sy_fragmentIdx >= 1);  
			DBASSERT (sy_fragmentIdx <= 16); 
			return sy_fragmentIdx; 
		}
	};

	struct Sy_FontType {	// 72 Bytes; Font record
		Int32			item_Len;				// length of the data record = sizeof(Sy_FontType) + RoundUp8(fontNameLen)
		unsigned char	item_Typ;				// = SyFont (8)
		char			dummyC;
		short			familytype;				// font family type: GDLFONTFAMILYNAME, GDLPLOTTERFONT, GDLPLOTMAKERFONT
		Int32			styleind;
		unsigned char	face;					// (Style) Style of text
		char			centre;					// Kind of text centre (1..9); if < 0 nonBreaking input mode
		short			just;					// Justification of text
		double			slant;					// Slant of text letters in rad (pi/2 is plain text)
		double			size;					// Letter size in mm independent of scale
		double			spac;					// Spacing between text lines in mm
		Int32			fontNameOffs;			// data offset of the font name
		Int32			fontNameLen;			// data length of the font name
	};

	struct Sy_LinType {			// 56 Bytes; Symbol Line record
		Int32			item_Len;					// length of the data record = sizeof(Sy_LinType)
		unsigned char	item_Typ;					// = SyLine (3)
		DrawIndex		drwIndex;					// index in drawing order or 0
		short			sy_pen;						// color information 0 if deleted
		short			sy_fragmentIdx;					// Fragment (layer) number: 1 - 16
		short			pattern;					// Pattern/lineType info
		Int32			sy_inIndex;					// use in VirtSy line index
		Coord			begC;						// Coordinate of the first Point
		Coord			endC;						// Coordinate of the second Point
		short			determine;					// Determines the type of line (contour - 0 / inner - 1)
		short			specForProfile;				// 0 standard line, 1 special lines for profile (status line or window placement)
		char			sy2dRenovationStatus;		//Sy2dRenovationStatusTypes
		char			specFor3D;					// 0: Sy3DInformation
		short			filler_2;
	};

	struct Sy_ArcType {		// 112 Bytes; Symbol Arc,Circ,Ellips record	
		Int32			item_Len;				// length of the data record = sizeof(Sy_ArcType)
		unsigned char	item_Typ;				// = SyArc (4)
		DrawIndex		drwIndex;				// index in drawing order or 0
		short			sy_pen;					// color information 0 if deleted
		short			sy_fragmentIdx;				// Fragment (layer) number: 1 - 16
		short			pattern;				// Pattern/lineType info.
		bool			whole;					// whole circle or arc?
		bool			elliptic;				// ratio != 1.0
		bool			reflected;				// on the smaller axis
		bool			filler_0;
		Coord			origC;					// Coordinate of the origin
		double			r;						// Radius !!!
		double			mainAxisDir;			// of the longer axis
		double			ratio;					// longer axis : smaller axis
		double			begAng;					// beginning angle of the arc
		double			endAng;					// ending angle of the arc
		Coord			begC;					// Coordinate of the first Point
		Coord			endC;					// Coordinate of the second Point
		short			determine;				// Determines the type of line (contour - 0 / inner - 1)
		char			sy2dRenovationStatus;	// Sy2dRenovationStatusTypes
		char			specFor3D;				// 0: Sy3DInformation
		Int32			filler_3;
	};

	struct Sy_TextType {	// 88 Bytes + content data; Text record
		Int32			item_Len;				// length of the data record = lStOff+RoundUp8(lStLen)
		unsigned char	item_Typ;				// = SyText (5)
		DrawIndex		drwIndex;				// index in drawing order or 0
		short			sy_pen;					// color information 0 if deleted
		short			sy_fragmentIdx;				// Fragment (layer) number: 1 - 16
		char			nonBreaking;			// 0: wrap around at dest rect; 1: wrap around at Cr only
		unsigned char	paramInd;				// Symbol parameter index (0: value from not text param)
		Int32			styleind;
		Coord			loc;					// Real coordinates of text centre
		double			angle;					// Angle of text letters in rad
		double			width;					// Horizontal size of text box in mm
		double			height;					// Vertical size of text box in mm
		double			size;					// Transformed letter size in mm
		double			spac;					// Transformed spacing between text lines in mm
		short			ind1;					// Indexes of an array type GDL parameter
		short			ind2;
		Int32			lines;					// Number of text lines
		Int32			conLen;					// Text content data length
		Int32			conOff;					// Offset of the Text content from record start		// = sizeof(Sy_TextType)
		Int32			lStLen;					// Text line starts data length
		Int32			lStOff;					// Offset of the linestarts from record start		// = sizeof(Sy_TextType)+RoundUp8(conLen)
		char			sy2dRenovationStatus;	//Sy2dRenovationStatusTypes
		char			filler_1;
		short			filler_2;
		Int32			filler_3;
	};

	struct Sy_RichTextType {
		Int32			item_Len;		// length of the data record
		unsigned char	item_Typ;		// = SyRichText (11)
		DrawIndex		drwIndex;		// index in drawing order or 0
		short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
		Coord			loc;
		double			width;
		double			height;
		double			angle;
		double			widthFactor;
		double			charSpaceFactor;
		char			anchor;
		bool			fixedHeight;
		bool			nonBreaking;
		bool			canScale;
		Int32			paramInd;
		Int32			ind1;
		Int32			ind2;
		Int32			numParagraphs;
		Int32			numTextStyles;
		Int32			numLines;
		Int32			numTabs;
		char			sy2dRenovationStatus; // Sy2dRenovationStatusTypes
		char			filler_1;
		short			filler_2;
		Int32			filler_3;

		struct Paragraph;
		struct TextStyle;
		struct Eol_Width;
		struct Tab;		

		void GetPointers (Paragraph** par, TextStyle** stl, Eol_Width** ln, Tab** tab, GS::uchar_t** strings);
	};

	struct Sy_RichTextType::Paragraph {
		short			alignment;
		short			filler_1;
		Int32			filler_2;
		double			firstLineIndent;
		double			leftIndent;
		double			rightIndent;
		double			lineSpacing;

		Int32			firstTextStyleInd;
		Int32			numTextStyles;
		Int32			firstLineInd;
		Int32			numLines;
		Int32			firstTabInd;
		Int32			numTabs;

		Paragraph () :
		alignment (0),
				filler_1 (0),
			filler_2 (0),
			firstLineIndent (0.0),
			leftIndent (0.0),
			rightIndent (0.0),
			lineSpacing (0.0),
			firstTextStyleInd (0),
			numTextStyles (0),
			firstLineInd (0),
			numLines (0),
			firstTabInd (0),
			numTabs (0)
		{
		}
	};

	struct Sy_RichTextType::TextStyle {
		double			size;
		short			styleInd;		// contains fontname and face only
		short			penInd;
		Int32			stringOffset;

		TextStyle () :
			size (0.0),
			styleInd (0),
			penInd (0),
			stringOffset (0)
		{			
		}
	};

	struct Sy_RichTextType::Eol_Width {
		double			width;
		Int32			eolPosition;
		Int32			filler_1;

		Eol_Width () :
			width (0.0),
			eolPosition (0),
			filler_1 (0)
		{		
		}
	};

	struct Sy_RichTextType::Tab {
		double			position;
		Int32			type;
		Int32			filler_1;

		Tab () :
			position (0.0),
			type (0),
			filler_1 (0)
		{
		}
	};

	inline void Sy_RichTextType::GetPointers (Sy_RichTextType::Paragraph** par, TextStyle** stl, Eol_Width** ln, Tab** tab, GS::uchar_t** strings)
	{
		*par		= (Paragraph *)		(this + 1);
		*stl		= (TextStyle *)		(*par + numParagraphs);
		*ln			= (Eol_Width *)		(*stl + numTextStyles);
		*tab		= (Tab *)			(*ln + numLines);
		*strings	= (GS::uchar_t *)	(*tab + numTabs);
	}

	struct Sy_EndType {	
		Int32			item_Len;				// length of the data record = sizeof(Sy_EndType)
		unsigned char	item_Typ;				// = SyEnd (0)
		char			dummyC;
		short			dummyS;
	};

	struct Sy_PictureType {
		Int32			item_Len;					// length of the data record = lStOff+RoundUp8(lStLen)
		unsigned char	item_Typ;					// = SyPicture (9)
		DrawIndex		drwIndex;					// index in drawing order or 0
		short			sy_fragmentIdx;					// Fragment (layer) number: 1 - 16
		bool			mirrored;					// TRUE if mirrored to local vertical axis
		char			anchorPoint;				// Value: 1 - 9
		short			colorDepth;
		short			pixelSizeX;
		short			pixelSizeY;
		short			storageFormat;
		unsigned short	pictPlatform;				// 'MM' or 'WW' (picHdl platfor PICT Or BMAP)
		Int32			filler_2;
		Box2DData		destBox;					// Box in real coordinates
		Box2DData		origBox;					// Box in real coordinates
		char			pictName[32];
		double			rotAngle;					// Rotation around left bottom
		Int32			picHdlLen;					// PicHandle data length
		Int32			picHdlOff;					// Offset of the PicHandle from record start
		// = sizeof(Sy_PictureType)
		Int32			figHdlLen;
		Int32			figHdlOff;
		bool			transparent;				// #10158 TranspPict
		char			filler_3_1;
		short			filler_3;
		Int32			filler_4;
		Int32			filler_5;
		Int32			filler_6;
	};

	struct Sy_2DHeadType {
		Int32			item_Len;				// length of the data record = sizeof(Sy_2DHeadType)
		unsigned char	item_Typ;				// = SyHead (1)
		unsigned char	headVers;				// = Curr_Sy2DVersion
		unsigned short	platform;				// platform identifier sign: 'MM' or 'WW'
		Box2DData		box;					// Boundaries of the Symbol's image
		unsigned char	isBoundBoxValid;
		unsigned char	reserved1;				// future use. MUST BE 0
		short			reserved2;				// future use. MUST BE 0
		Int32			defScale;				// default scale (not used yet)
		Int32			headBits;				// HeadBits_UseDrwQ, HeadBits_SortDrwQ, HeadBits_HangOutOfBox
		Int32			filler_0;
		Int32			filler_1;
		Int32			filler_2;
		ULong			endOff;					// offset of the end record from section start
		ULong			nHots;					// Number of hotspots			in the Symbol
		ULong			nLine;					// Number of lines				in the Symbol
		ULong			nArc;					// Number of arcs				in the Symbol
		ULong			nText;					// Number of Texts				in the Symbol
		ULong			nHatc;					// Number of Hatches			in the Symbol
		ULong			nSpline;				// Number of Splines			in the Symbol
		ULong			nFonts;					// Number of Font data records	in the Symbol
		ULong			nPicture;				// Number of Pictures			in the Symbol
		ULong			nPixMap;				// Number of PixMaps			in the Symbol
		ULong			nRichText;				// Number of RichTexts			in the Symbol
		ULong			nPolyLine;				// Number of polyLines			in the Symbol
		ULong			nObject;
		Int32			filler_7;
		Int32			filler_8;
		Int32			filler_9;
	};

	struct Sy_HotType {							// 64 Bytes; Symbol Hotspot record	
		Int32			item_Len;				// length of the data record = sizeof(Sy_HotType)
		unsigned char	item_Typ;				// = SyHots (2)
		DrawIndex		drwIndex;				// index in drawing order or 0
		short			sy_pen;					// color information 0 if deleted
		short			sy_fragmentIdx;				// Fragment (layer) number: 1 - 16
		short			flags;					// flags (Hotspot_OutOfModelBox)
		Int32			connectionId;			// Endpoint of a status line
		short			hottype;				// The type of the hotspot
		short			subtype;				// The sub-type of the hotspot
		UInt32			supplUnId;				// The supplement unique ID of the hotspot (may be 0)
		Coord			c;						// Coordinate of the first Point
		double			z;						// z coordinate (for 3D Document)
		char			sy2dRenovationStatus;	//Sy2dRenovationStatusTypes
		char			filler_1;
		short			filler_2;
		Int32			filler_3;
		double			arcParam;
	};

	struct Sy_PixMapType {	
		Int32			item_Len;				// length of the data record = lStOff+RoundUp8(lStLen)
		unsigned char	item_Typ;				// = SyPixMap (10)
		DrawIndex		drwIndex;				// index in drawing order or 0
		short			sy_fragmentIdx;				// Fragment (layer) number: 1 - 16
		bool			mirrored;				// TRUE if mirrored to local vertical axis
		char			anchorPoint;			// Value: 1 - 9
		short			colorDepth;
		short			pixelSizeX;
		short			pixelSizeY;
		UInt32			pixMapFormat;
		Int32			filler_2;
		Box2DData		destBox;				// Box in real coordinates
		Box2DData		origBox;				// Box in real coordinates
		char			pixName[32];
		double			rotAngle;				// Rotation around left bottom
		Int32			pixHdlLen;				// PixMapHandle data length
		Int32			pixHdlOff;				// Offset of the PixMapHandle from record start						// = sizeof(Sy_PixMapType)
		bool			transparent;			// #10158 TranspPict
		char			sy2dRenovationStatus;	//Sy2dRenovationStatusTypes
		short			filler_3;
		Int32			mimeTypeLen;			// data length of the mime-type
		Int32			mimeTypeOff;			// data offset of the mime-type
		Int32			filler_6;
	};

	struct Sy_PointCloudType {			// 56 Bytes; Symbol Line record
		Int32			item_Len;
		unsigned char	item_Typ;
		DrawIndex		drwIndex;
		short			sy_fragmentIdx;
		UIndex			iInObjectArray;
		Int32			filler;
	};

	struct Sy_PolyLinType {		
		Int32			item_Len;					// length of the data record = coorOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
		unsigned char	item_Typ;					// = SyPolyLine (12)
		DrawIndex		drwIndex;					// index in drawing order or 0
		char			sy2dRenovationStatus;		//Sy2dRenovationStatusTypes
		char			specFor3D;					// 0: Sy3DInformation
		short			sy_pen;						// color information 0 if deleted
		short			sy_fragmentIdx;					// Fragment (layer) number: 1 - 16
		short			pattern;					// Pattern/lineType info.
		short			determine;					// Determines the type of line (contour - 0 / inner - 1)
		Int32			nCoords;					// Number of Coords
		Int32			nArcs;						// Number of curves in the polygon
		Int32			coorLen;					// PolyLine coordinate data length
		Int32			coorOff;					// Offset of the PolyLine coordinate from record start		// = sizeof(Sy_SplineType)
		Int32			arcsLen;					// Polygon curves data length
		Int32			arcsOff;					// Offset of the Polygon curves from record start			// = sizeof(Sy_SplineType)+RoundUp8(coorLen)
	};

	struct Sy_SplineType {				// 48 Bytes + content data; Spline record	
		Int32			item_Len;				// length of the data record = endsOff+Round_UP_8(dirsLen)
		unsigned char	item_Typ;				// = SySpline (7)
		DrawIndex		drwIndex;				// index in drawing order or 0
		short			sy_pen;					// color information 0 if deleted
		short			sy_fragmentIdx;				// Fragment (layer) number: 1 - 16
		short			pattern;				// Pattern/lineType info.
		bool			autoSm;					// automatically calculated spline coeff from basic points
		bool			closed;					// closed between last-first pt
		short			filler_0;
		Int32			nCoords;				// Number of Coords
		Int32			nDirs;					// Number of Dir data records
		Int32			coorLen;				// Spline coordinate data length
		Int32			coorOff;				// Offset of the Spline coordinate from record start
												// = sizeof(Sy_SplineType)
		Int32			dirsLen;				// Dir data length
		Int32			dirsOff;				// Offset of the Dir data from record start
												// = sizeof(Sy_SplineType)+Round_UP_8(coorLen)
		short			determine;				// Determines the type of line (contour - 0 / inner - 1)
		char			sy2dRenovationStatus;	//Sy2dRenovationStatusTypes
		char			filler_1;
		Int32			filler_2;
	};
}


#endif
