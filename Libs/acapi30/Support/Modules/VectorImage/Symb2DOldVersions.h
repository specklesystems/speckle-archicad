#ifndef	_Symb2DOldVersions_H_
#define _Symb2DOldVersions_H_

#include "ISymbol.hpp"
#include "ProfileAdditionalInfo.hpp"
#include "AC19SymbolTypes.hpp"
#include "SyHatch.hpp"
#include "VectorImageUtils.hpp"

// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------

#define	Info_5_Len	 8					// Elem ID length, till 4.16
#define	Info_9_Len	12					// Elem ID length


#if defined (_MSC_VER) || (defined (__SC__) && !defined (macintosh))
#pragma pack (1)
#endif

#if defined (macintosh)
#pragma pack (2)
#endif


//******************************************************************************
// Old Symbol2D structures
//******************************************************************************

typedef	char		Info_5_Type [Info_5_Len];

typedef	char		Info_9_Type [Info_9_Len];


#define SINGLE_ARG(...) __VA_ARGS__

#if defined (_MSC_VER)
#define DEF_STRUCT_CHECKALIGN(A, B)					\
	__pragma (pack(push))							\
	__pragma (pack (1))								\
struct A B;											\
	__pragma (pack (8))								\
struct A##_8 B;										\
	__pragma (pack(pop))							\
	static_assert (sizeof (A) == sizeof (A##_8), "Size equality error!")

#define DEF_STRUCT_WITH_DEFAULT_CONSTRUCTOR_CHECKALIGN(A, B)			\
	__pragma (pack(push))												\
	__pragma (pack (1))													\
struct A {B inline A(); };												\
	__pragma (pack (8))													\
struct A##_8 {B};														\
	__pragma (pack(pop))												\
	static_assert (sizeof (A) == sizeof (A##_8), "Size equality error!")

#else
#define DEF_STRUCT_CHECKALIGN(A, B)	 struct A B;
#define DEF_STRUCT_WITH_DEFAULT_CONSTRUCTOR_CHECKALIGN(A, B)	 struct A {B inline A(); }
#endif


//--- Symb2D Version 13 --------------------------------------------------------

DEF_STRUCT_CHECKALIGN (Sy_2DHeadType_13, {		// 88 Bytes; Symbol 2D handle header record
	Int32			item_Len;			// length of the data record = sizeof(Sy_2DHeadType_13)
	unsigned char	item_Typ;			// = SyHead (1)
	unsigned char	headVers;			// = 14 or 15
	unsigned short	platform;			// platform identifier sign: 'MM' or 'WW'
	Box2DData		box; 				// Boundaries of the Symbol's image
	short			reserved1;			// future use. MUST BE 0
	short			reserved2;			// future use. MUST BE 0
	Int32			defScale;			// default scale (not used yet)
	Int32			endOff;				// offset of the end record from section start
	Int32			nHots;				// Number of hotspots in the Symbol
	Int32			nLine;				// Number of lines in the Symbol
	Int32			nArc;				// Number of arcs in the Symbol
	Int32			nText;				// Number of Texts in the Symbol
	Int32			nHatc;				// Number of Hatches in the Symbol
	Int32			nSpline;			// Number of Splines in the Symbol
	Int32			nFonts;				// Number of Font data records in the Symbol
	Int32			nPicture;			// Number of Pictures in the Symbol
	Int32			filler_3;
});

DEF_STRUCT_CHECKALIGN (Sy_HotType_13, {			// 24 Bytes; Symbol Hotspot record
	Int32			item_Len;			// length of the data record = sizeof(Sy_HotType_13)
	unsigned char	item_Typ;			// = SyHots (2)
	char			pen;				// color information 0 if deleted
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	Coord			c; 					// Coordinate of the first Point
});

DEF_STRUCT_CHECKALIGN (Sy_LinType_13, {			// 48 Bytes; Symbol Line record
	Int32			item_Len;			// length of the data record = sizeof(Sy_LinType_13)
	unsigned char	item_Typ;			// = SyLine (3)
	char			pen;				// color information 0 if deleted
	short			pattern;			// Pattern/lineType info.
	Coord			begC; 				// Coordinate of the first Point
	Coord			endC;				// Coordinate of the second Point
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	short			filler_0;
	Int32			filler_1;
});

DEF_STRUCT_CHECKALIGN (Sy_ArcType_13, {			// 112 Bytes; Symbol Arc,Circ,Ellips record
	Int32			item_Len;			// length of the data record = sizeof(Sy_ArcType_13)
	unsigned char	item_Typ;			// = SyArc (4)
	char			pen;				// color information 0 if deleted
	short			pattern;			// Pattern/lineType info.
	Coord			origC;				// Coordinate of the origin
	double			r;					// Radius !!!
	double			angle;				// of the longer axis
	double			ratio;				// longer axis : smaller axis
	double			begAng;				// beginning angle of the arc
	double			endAng;				// ending angle of the arc
	Coord			begC;				// Coordinate of the first Point
	Coord			endC;				// Coordinate of the second Point
	bool			whole;				// whole circle or arc?
	bool			elliptic;			// ratio != 1.0
	bool			reflected;			// on the smaller axis
	bool			filler_0;
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	short			filler_1;
	Int32			filler_2;
	Int32			filler_3;
});

DEF_STRUCT_CHECKALIGN (Sy_TextType_13, {			// 80 Bytes + content data; Text record
	Int32			item_Len;			// length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char	item_Typ;			// = SyText (5)
	char			pen;				// Color information, 0 if deleted
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	char			nonBreaking;		// 0: wrap around at dest rect
	// 1:  wrap around at Cr only
	unsigned char	paramInd;			// Symbol parameter index (0: value from not text param)	// vv30
	unsigned char	face;				// (Style) Style of text
	char			centre;				// Kind of text centre (1..9);  if < 0 nonBreaking input mode
	short			font;				// ID number of the text font
	short			just;				// Justification of text
	Coord			loc;				// Real coordinates of text centre
	double			angle; 				// Angle of text letters in rad
	float			width;				// Horizontal size of text box in mm
	float			height;				// Vertical size of text box in mm
	float			size; 				// Letter size in mm independent of scale
	float			spac;				// Spacing between text lines in mm
	float			slant; 				// Slant of text letters in rad (pi/2 is plain text)
	Int32			lines;				// Number of text lines
	Int32			conLen;				// Text content data length
	Int32			conOff;				// Offset of the Text content from record start
	// = sizeof(Sy_TextType_13)
	Int32			lStLen;				// Text line starts data length
	Int32			lStOff;				// Offset of the linestarts from record start
	// = sizeof(Sy_TextType_13)+RoundUp8(conLen)
});

DEF_STRUCT_CHECKALIGN (Sy_HatchType_13, {						// 64 Byte + content data; Hatch record
	Int32			item_Len;			// length of the data record = endsOff+Round_UP_8(endsLen)
	unsigned char	item_Typ;			// = SyHatch (6)
	char			fillPen; 			// Hatching color  (0 if not hatched)
	short			fillPat;			// Hatching number (0 if not hatched)

	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	bool			global;				// TRUE if fill not linked to the element
	char			contPen; 			// Contour line color (0 if not framed hatch)
	short			contLType; 			// Contour line type
	short			filler_0;

	Coord			offset;				// base coordinate of fill reference vector if linked to the element
	double			angle;				// angle of fill reference vector if linked to the element

	Int32			nCoords; 			// Number of vertices
	Int32			nSubPolys;			// Number of closed sub polygons including the first one
	Int32			coorLen;			// Polygon coordinate data length
	Int32			coorOff;			// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType_13)
	Int32			endsLen;			// Subpolygon endpoints data length
	Int32			endsOff;			// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType_13)+RoundUp8(coorLen)
});

DEF_STRUCT_CHECKALIGN (Sy_SplineType_13, {		// 40 Bytes + content data; Spline record
	Int32			item_Len;			// length of the data record = endsOff+Round_UP_8(dirsLen)
	unsigned char	item_Typ;			// = SySpline (7)
	char			pen; 				// color information 0 if deleted
	short			pattern;			// Pattern/lineType info.
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	bool			autoSm;				// automatically calculated spline coeff from basic points
	bool			closed;				// closed between last-first pt
	Int32			filler_0;
	Int32			nCoords; 			// Number of Coords
	Int32			nDirs;				// Number of Dir data records
	Int32			coorLen;			// Spline coordinate data length
	Int32			coorOff;			// Offset of the Spline coordinate from record start
	// = sizeof(Sy_SplineType_13)
	Int32			dirsLen;			// Dir data length
	Int32			dirsOff;			// Offset of the Dir data from record start
	// = sizeof(Sy_SplineType_13)+Round_UP_8(coorLen)
});


//--- Symb2D Version 15 --------------------------------------------------------

typedef Sy_2DHeadType_13		Sy_2DHeadType_15;
typedef	AC19Symbol::Sy_EndType	Sy_EndType_15;
typedef Sy_HotType_13			Sy_HotType_15;
typedef Sy_LinType_13			Sy_LinType_15;
typedef Sy_ArcType_13			Sy_ArcType_15;
typedef Sy_TextType_13			Sy_TextType_15;

DEF_STRUCT_CHECKALIGN (Sy_HatchType_15, {		// 80 Bytes + content data; Hatch record
	Int32			item_Len;			// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;			// = SyHatch (6)
	char			fillPen; 			// Hatching color  (0 if not hatched)
	short			fillPat;			// Hatching number (0 if not hatched)

	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	bool			global;				// TRUE if fill not linked to the element
	char			contPen; 			// Contour line color (0 if not framed hatch)
	short			contLType; 			// Contour line type
	short			fillbkgPen;			// if 0 transparent

	Coord			offset;				// base coordinate of fill reference vector if linked to the element
	double			angle;				// angle of fill reference vector if linked to the element

	Int32			nCoords; 			// Number of vertices
	Int32			nSubPolys;			// Number of closed sub polygons including the first one
	Int32			coorLen;			// Polygon coordinate data length
	Int32			coorOff;			// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType_15)
	Int32			endsLen;			// Subpolygon endpoints data length
	Int32			endsOff;			// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType_15)+RoundUp8(coorLen)
	Int32			nArcs;				// Number of curves in the polygon
	Int32			arcsLen;			// Polygon curves data length
	Int32			arcsOff;			// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType_15)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32			filler_1;
});

DEF_STRUCT_CHECKALIGN (Sy_FontType_15, {			// 40 Bytes; Font record
	Int32			item_Len;			// length of the data record = sizeof(Sy_FontType_15)
	unsigned char	item_Typ;			// = SyFont (8)
	char			dummyC;
	short			fontID;				// font id (same as "Sy_TextType_15" font field)
	char			fontName [32];		// font name (C string)
});

typedef Sy_SplineType_13	Sy_SplineType_15;

typedef struct Sy_PictureType_BAD {		// 56 Bytes; Picture record
	Int32			item_Len;			// length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char	item_Typ;			// = SyPicture (9)
	char			pen; 				// color information 0 if deleted
	bool			mirrored;			// TRUE if mirrored to local vertical axis
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	Box2DData		destBox;			// Box in real coordinates
	double			rotAngle;			// Rotation around left bottom
	Int32			picHdlLen;			// PicHandle data length
	Int32			picHdlOff;			// Offset of the PicHandle from record start
	// = sizeof(Sy_PictureType_BAD)
} Sy_PictureType_BAD;					// vip73

DEF_STRUCT_CHECKALIGN (Sy_PictureType_15, {		// 72 Bytes; Picture record
	Int32			item_Len;			// length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char	item_Typ;			// = SyPicture (9)
	char			pen; 				// color information 0 if deleted
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	Box2DData		destBox;			// Box in real coordinates
	double			rotAngle;			// Rotation around left bottom
	bool			mirrored;			// TRUE if mirrored to local vertical axis
	bool			filler_0;
	short			filler_1;
	Int32			picHdlLen;			// PicHandle data length
	Int32			picHdlOff;			// Offset of the PicHandle from record start
	// = sizeof(Sy_PictureType_15)
	Int32			filler_2;
	Int32			filler_3;
	Int32			filler_4;
});

//--- Symb2D Version 16 --------------------------------------------------------

DEF_STRUCT_CHECKALIGN (Sy_2DHeadType_16, {		// 128 Bytes; Symbol 2D handle header record
	Int32			item_Len;		// length of the data record = sizeof(Sy_2DHeadType_16)
	unsigned char	item_Typ;		// = SyHead (1)
	unsigned char	headVers;		// = Curr_Sy2DVersion) (16)
	unsigned short	platform;		// platform identifier sign: 'MM' or 'WW'
	Box2DData		box;			// Boundaries of the Symbol's image
	short			reserved1;		// future use. MUST BE 0
	short			reserved2;		// future use. MUST BE 0
	Int32			defScale;		// default scale (not used yet)
	Int32			headBits;		// HeadBits_UseDrwQ, HeadBits_SortDrwQ, HeadBits_HangOutOfBox
	Int32			filler_0;
	Int32			filler_1;
	Int32			filler_2;
	ULong			endOff;			// offset of the end record from section start
	ULong			nHots;			// Number of hotspots			in the Symbol
	ULong			nLine;			// Number of lines				in the Symbol
	ULong			nArc;			// Number of arcs				in the Symbol
	ULong			nText;			// Number of Texts				in the Symbol
	ULong			nHatc;			// Number of Hatches			in the Symbol
	ULong			nSpline;		// Number of Splines			in the Symbol
	ULong			nFonts;			// Number of Font data records	in the Symbol
	ULong			nPicture;		// Number of Pictures			in the Symbol
	ULong			nPixMap;		// Number of PixMaps			in the Symbol
	ULong			nRichText;		// Number of RichTexts			in the Symbol
	Int32			filler_5;
	Int32			filler_6;
	Int32			filler_7;
	Int32			filler_8;
	Int32			filler_9;
});

typedef	Sy_EndType_15	Sy_EndType_16;

DEF_STRUCT_CHECKALIGN (Sy_HotType_16, {			// 40 Bytes; Symbol Hotspot record
	Int32			item_Len;		// length of the data record = sizeof(Sy_HotType_16)
	unsigned char	item_Typ;		// = SyHots (2)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			flags;			// flags (Hotspot_OutOfModelBox)
	Int32			connectionId;   // Endpoint of a status line
	short			hottype;		// The type of the hotspot
	short			subtype;		// The sub-type of the hotspot
	UInt32	supplUnId;		// The supplement unique ID of the hotspot (may be 0)
	Coord			c;				// Coordinate of the first Point
});

DEF_STRUCT_CHECKALIGN (Sy_LinType_16, {			// 56 Bytes; Symbol Line record
	Int32			item_Len;		// length of the data record = sizeof(Sy_LinType_16)
	unsigned char	item_Typ;		// = SyLine (3)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			pattern;		// Pattern/lineType info.
	Int32			sy_inIndex;		// use in VirtSy line index
	Coord			begC;			// Coordinate of the first Point
	Coord			endC;			// Coordinate of the second Point
	short			determine;		// Determines the type of line (contour - 0 / inner - 1)
	short			filler_1;
	Int32			filler_2;
});

DEF_STRUCT_CHECKALIGN (Sy_ArcType_16, {			// 112 Bytes; Symbol Arc,Circ,Ellips record
	Int32			item_Len;		// length of the data record = sizeof(Sy_ArcType_16)
	unsigned char	item_Typ;		// = SyArc (4)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			pattern;		// Pattern/lineType info.
	bool			whole;			// whole circle or arc?
	bool			elliptic;		// ratio != 1.0
	bool			reflected;		// on the smaller axis
	bool			filler_0;
	Coord			origC;			// Coordinate of the origin
	double			r;				// Radius !!!
	double			mainAxisDir;	// of the longer axis
	double			ratio;			// longer axis : smaller axis
	double			begAng;			// beginning angle of the arc
	double			endAng;			// ending angle of the arc
	Coord			begC;			// Coordinate of the first Point
	Coord			endC;			// Coordinate of the second Point
	short			determine;		// Determines the type of line (contour - 0 / inner - 1)
	short			filler_2;
	Int32			filler_3;
});

DEF_STRUCT_CHECKALIGN (Sy_TextType_16, { // 96 Bytes + content data; Text record
	Int32          item_Len;    // length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char item_Typ;    // = SyText (5)
	char          drwIndex;    // index in drawing order or 0
	short         sy_pen;      // color information 0 if deleted
	short         sy_fragmentIdx;    // Fragment (layer) number: 1 - 16
	char          nonBreaking; // 0: wrap around at dest rect; 1:  wrap around at Cr only
	unsigned char paramInd;    // Symbol parameter index (0: value from not text param)
	unsigned char face;        // (Style) Style of text
	char          centre;      // Kind of text centre (1..9);  if < 0 nonBreaking input mode
	short         fontId;	   // ID number of the text font
	short         just;        // Justification of text
	short         filler_0;
	Int32          filler_1;
	Coord         loc;         // Real coordinates of text centre
	double        angle;       // Angle of text letters in rad
	float         width;       // Horizontal size of text box in mm
	float         height;      // Vertical size of text box in mm
	float         size;        // Letter size in mm independent of scale
	float         spac;        // Spacing between text lines in mm
	float         slant;       // Slant of text letters in rad (pi/2 is plain text)
	short         ind1;        // Indexes of an array type GDL parameter
	short         ind2;
	Int32          filler_2;    // ind1, ind2 ==> short
	Int32          lines;       // Number of text lines
	Int32          conLen;      // Text content data length
	Int32          conOff;      // Offset of the Text content from record start
	// = sizeof(Sy_TextType_16)
	Int32          lStLen;      // Text line starts data length
	Int32          lStOff;      // Offset of the linestarts from record start
	// = sizeof(Sy_TextType_16)+RoundUp8(conLen)
});

DEF_STRUCT_CHECKALIGN (Sy_HatchType_16, {		// 96 Bytes + content data; Hatch record
	Int32			item_Len;		// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;		// = SyHatch (6)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fillPen;		// Hatching color (0 if not hatched)
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			fillPat;		// Hatching number (0 if not hatched)
	short			contPen;		// Contour line color (0 if not framed hatch)
	short			contLType;		// Contour line type
	short			fillbkgPen;		// if 0 transparent
	bool			global;			// TRUE if fill not linked to the element
	bool			filler_0;
	short			determine;		// It is always 0 in the library part files
	short			offsetType;		// It is always 0 in the library part files
	Coord			offset;			// base coordinate of fill reference vector if linked to the element
	double			angle;			// angle of fill reference vector if linked to the element
	Int32			nCoords;		// Number of vertices
	Int32			nSubPolys;		// Number of closed sub polygons including the first one
	Int32			nArcs;			// Number of curves in the polygon
	Int32			coorLen;		// Polygon coordinate data length
	Int32			coorOff;		// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType_16)
	Int32			endsLen;		// Subpolygon endpoints data length
	Int32			endsOff;		// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType_16)+RoundUp8(coorLen)
	Int32			arcsLen;		// Polygon curves data length
	Int32			arcsOff;		// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType_16)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32			filler_2;
	Int32			filler_3;
	Int32			filler_4;
});

DEF_STRUCT_CHECKALIGN (Sy_SplineType_16, {		// 48 Bytes + content data; Spline record
	Int32			item_Len;		// length of the data record = endsOff+Round_UP_8(dirsLen)
	unsigned char	item_Typ;		// = SySpline (7)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			pattern;		// Pattern/lineType info.
	bool			autoSm;			// automatically calculated spline coeff from basic points
	bool			closed;			// closed between last-first pt
	short			filler_0;
	Int32			nCoords;		// Number of Coords
	Int32			nDirs;			// Number of Dir data records
	Int32			coorLen;		// Spline coordinate data length
	Int32			coorOff;		// Offset of the Spline coordinate from record start
	// = sizeof(Sy_SplineType_16)
	Int32			dirsLen;		// Dir data length
	Int32			dirsOff;		// Offset of the Dir data from record start
	// = sizeof(Sy_SplineType_16)+Round_UP_8(coorLen)
	short			determine;		// Determines the type of line (contour - 0 / inner - 1)
	short			filler_1;
	Int32			filler_2;
});


DEF_STRUCT_CHECKALIGN (Sy_FontType_16, { // 40 Bytes; Font record
	Int32  item_Len;     // length of the data record = sizeof(Sy_FontType_16)
	unsigned char  item_Typ;     // = SyFont (8)
	char  dummyC;
	short fontID;       // font id (same as "Sy_TextType_16" font field)
	char  fontName[32]; // font name (C string)
});

typedef	AC19Symbol::Sy_PictureType	Sy_PictureType_16;

DEF_STRUCT_CHECKALIGN (Sy_PixMapType_16, {		// 160 Bytes; PixMap record
	Int32			item_Len;		// length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char	item_Typ;		// = SyPixMap (10)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	bool			mirrored;		// TRUE if mirrored to local vertical axis
	char			anchorPoint;	// Value: 1 - 9
	short			colorDepth;
	short			pixelSizeX;
	short			pixelSizeY;
	UInt32	pixMapFormat;
	Int32			filler_2;
	Box2DData		destBox;		// Box in real coordinates
	Box2DData		origBox;		// Box in real coordinates
	char			pixName[32];
	double			rotAngle;		// Rotation around left bottom
	Int32			pixHdlLen;		// PixMapHandle data length
	Int32			pixHdlOff;		// Offset of the PixMapHandle from record start
	// = sizeof(Sy_PixMapType_16)
	bool			transparent;	// #10158 TranspPict
	char			filler_3_1;
	short			filler_3;
	Int32			mimeTypeLen;	// data length of the mime-type
	Int32			mimeTypeOff;	// data offset of the mime-type
	Int32			filler_6;
});


//--- Symb2D Version 17 --------------------------------------------------------

typedef	Sy_2DHeadType_16	Sy_2DHeadType_17;
typedef	Sy_EndType_16		Sy_EndType_17;
typedef	Sy_HotType_16		Sy_HotType_17;
typedef	Sy_LinType_16		Sy_LinType_17;
typedef	Sy_ArcType_16		Sy_ArcType_17;

DEF_STRUCT_CHECKALIGN (Sy_TextType_17, {		// 88 Bytes + content data; Text record
	Int32			item_Len;		// length of the data record = lStOff+RoundUp8(lStLen)
	unsigned char	item_Typ;		// = SyText (5)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	char			nonBreaking;	// 0: wrap around at dest rect; 1: wrap around at Cr only
	unsigned char	paramInd;		// Symbol parameter index (0: value from not text param)
	Int32			styleind;
	Coord			loc;			// Real coordinates of text centre
	double			angle;			// Angle of text letters in rad
	double			width;			// Horizontal size of text box in mm
	double			height;			// Vertical size of text box in mm

	double			size;			// Transformed letter size in mm
	double			spac;			// Transformed spacing between text lines in mm

	short			ind1;			// Indexes of an array type GDL parameter
	short			ind2;
	Int32			lines;			// Number of text lines
	Int32			conLen;			// Text content data length
	Int32			conOff;			// Offset of the Text content from record start
	// = sizeof(Sy_TextType_17)
	Int32			lStLen;			// Text line starts data length
	Int32			lStOff;			// Offset of the linestarts from record start
	// = sizeof(Sy_TextType_17)+RoundUp8(conLen)
});

DEF_STRUCT_CHECKALIGN (Sy_RichTextType_17, {
	Int32			item_Len;		// length of the data record
	unsigned char	item_Typ;		// = SyRichText (11)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16

	Coord			loc;
	double			width;
	double			angle;
	double			widthFactor;
	double			charSpaceFactor;
	char			anchor;
	bool			fixedHeight;
	bool			nonBreaking;
	char			filler_1;
	Int32			filler_2;
	Int32			paramInd;
	Int32			ind1;
	Int32			ind2;

	Int32			numParagraphs;
	Int32			numTextStyles;
	Int32			numTabs;

});

DEF_STRUCT_CHECKALIGN (Sy_Paragraph_17, {
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

});

DEF_STRUCT_CHECKALIGN (Sy_TextStyle_17, {
	double			size;
	short			styleInd;		// contains fontname and face only
	short			penInd;

	Int32			stringOffset;

});

DEF_STRUCT_CHECKALIGN (Sy_Tab_17, {
	double			position;
	Int32			type;
	Int32			filler_1;

});

typedef	Sy_HatchType_16		Sy_HatchType_17;
typedef	Sy_SplineType_16	Sy_SplineType_17;

DEF_STRUCT_CHECKALIGN (Sy_FontType_17, {		// 72 Bytes; Font record
	Int32			item_Len;		// length of the data record = sizeof(Sy_FontType_17)
	unsigned char	item_Typ;		// = SyFont (8)
	char			dummyC;
	short			familytype;		// font family type: GDLFONTFAMILYNAME, GDLPLOTTERFONT, GDLPLOTMAKERFONT
	char			fontName[32];	// font name (C string)
	Int32			styleind;
	unsigned char	face;			// (Style) Style of text
	char			centre;			// Kind of text centre (1..9); if < 0 nonBreaking input mode
	short			just;			// Justification of text
	double			slant;			// Slant of text letters in rad (pi/2 is plain text)
	double			size;			// Letter size in mm independent of scale
	double			spac;			// Spacing between text lines in mm
});

typedef	Sy_PictureType_16	Sy_PictureType_17;
typedef	Sy_PixMapType_16	Sy_PixMapType_17;

DEF_STRUCT_CHECKALIGN (ExtPixMap_17, {
	GSSize						headerSize;			/*  4 */	/* size of this struct						*/
	GSSize						rowBytes;			/*  4 */	/* offset to next line						*/
	GSRect						bounds;				/* 16 */	/* encloses bitmap							*/
	Int32						hRes;				/*  4 */	/* horiz. resolution (ppi)					*/
	Int32						vRes;				/*  4 */	/* vert. resolution (ppi)					*/
	unsigned char				pixelType;			/*  1 */	/* pixel's type int the pixmap (GSPixelType)*/
	unsigned char				pmReserved0;		/*  1 */	/* for future use. MUST BE 0				*/
	short						pmReserved1;		/*  2 */	/* for future use. MUST BE 0				*/
	Int32						pmReserved2;		/*  4 */	/* for future use. MUST BE 0				*/
});


//--- Symb2D Version 18 --------------------------------------------------------

typedef	Sy_2DHeadType_17	Sy_2DHeadType_18;
typedef	Sy_EndType_17		Sy_EndType_18;
typedef	Sy_HotType_17		Sy_HotType_18;
typedef	Sy_LinType_17		Sy_LinType_18;
typedef	Sy_ArcType_17		Sy_ArcType_18;
typedef	Sy_TextType_17		Sy_TextType_18;
typedef ExtPixMap_17		ExtPixMap_18;

DEF_STRUCT_CHECKALIGN (Sy_RichTextType_18, {
	Int32			item_Len;		// length of the data record
	unsigned char	item_Typ;		// = SyRichText (11)
	char			drwIndex;		// index in drawing order or 0
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
});

typedef	Sy_Paragraph_17		Sy_Paragraph_18;
typedef	Sy_TextStyle_17		Sy_TextStyle_18;

DEF_STRUCT_CHECKALIGN (Sy_Eol_Width_18, {
	double			width;
	Int32			eolPosition;
	Int32			filler_1;

});

typedef	Sy_Tab_17			Sy_Tab_18;
typedef	Sy_HatchType_17		Sy_HatchType_18;
typedef	Sy_SplineType_17	Sy_SplineType_18;
typedef	Sy_FontType_17		Sy_FontType_18;
typedef	Sy_PictureType_17	Sy_PictureType_18;
typedef	Sy_PixMapType_17	Sy_PixMapType_18;


//--- Actual Symb2D Version (19) -----------------------------------------------
typedef	Sy_2DHeadType_18	Sy_2DHeadType_19;
typedef	Sy_EndType_18		Sy_EndType_19;
typedef	Sy_HotType_18		Sy_HotType_19;
typedef	Sy_ArcType_18		Sy_ArcType_19;
typedef	Sy_TextType_18		Sy_TextType_19;
typedef Sy_RichTextType_18	Sy_RichTextType_19;
typedef	Sy_Paragraph_18		Sy_Paragraph_19;
typedef	Sy_TextStyle_18		Sy_TextStyle_19;
typedef	Sy_Tab_18			Sy_Tab_19;
typedef	Sy_SplineType_18	Sy_SplineType_19;
typedef	Sy_FontType_18		Sy_FontType_19;
typedef	Sy_PictureType_18	Sy_PictureType_19;
typedef	Sy_PixMapType_18	Sy_PixMapType_19;
typedef Sy_Eol_Width_18		Sy_Eol_Width_19;
typedef ExtPixMap_18		ExtPixMap_19;

DEF_STRUCT_CHECKALIGN (Sy_LinType_19, {			// 56 Bytes; Symbol Line record
	Int32			item_Len;		// length of the data record = sizeof(Sy_LinType)
	unsigned char	item_Typ;		// = SyLine (3)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			pattern;		// Pattern/lineType info.
	Int32			sy_inIndex;		// use in VirtSy line index
	Coord			begC;			// Coordinate of the first Point
	Coord			endC;			// Coordinate of the second Point
	short			determine;		// Determines the type of line (contour - 0 / inner - 1)
	short			specForProfile;	// 0 standard line, 1 special lines for profile (status line or window placement)
	Int32			filler_2;

});

DEF_STRUCT_CHECKALIGN (Sy_HatchType_19, {		// 96 Bytes + content data; Hatch record
	Int32			item_Len;		// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;		// = SyHatch (6)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fillPen;		// Hatching color (0 if not hatched)
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			fillPat;		// Hatching number (0 if not hatched)
	short			contPen;		// Contour line color (0 if not framed hatch)
	short			contLType;		// Contour line type
	short			fillbkgPen;		// if 0 transparent
	bool			global;			// TRUE if fill not linked to the element
	bool	        filler_0;
	short			determine;		// It is always 0 in the library part files
	short			offsetType;		// It is always 0 in the library part files
	Coord			offset;			// base coordinate of fill reference vector if linked to the element
	double          angle;			// angle of fill reference vector if linked to the element
	Int32			nCoords;		// Number of vertices
	Int32			nSubPolys;		// Number of closed sub polygons including the first one
	Int32			nArcs;			// Number of curves in the polygon
	Int32			coorLen;		// Polygon coordinate data length
	Int32			coorOff;		// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType)
	Int32			endsLen;		// Subpolygon endpoints data length
	Int32			endsOff;		// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
	Int32			arcsLen;		// Polygon curves data length
	Int32			arcsOff;		// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32			addInfoLen;		// Additional info for profile data length
	Int32			addInfoOff;		// Offset of the additional info for profile data from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
	Int32			filler_4;

});

DEF_STRUCT_CHECKALIGN (ProfileItem_19, SINGLE_ARG ( // 16 Bytes
{
	Int32	profileItemVersion;
	Int32	connectionPriority;
private:
	Int32	flags;
public:
	Int32	filler;

	Int32	GetFlags (void) { return flags; }

	void	IV (GS::PlatformSign from, GS::PlatformSign to)
	{
		IVLong (from, to, &profileItemVersion);
		IVLong (from, to, &connectionPriority);
		IVLong (from, to, &flags);
	}
}));

//--- Actual Symb2D Version (20) -----------------------------------------------
typedef	Sy_2DHeadType_19	Sy_2DHeadType_20;
typedef	Sy_EndType_19		Sy_EndType_20;
typedef	Sy_HotType_19		Sy_HotType_20;
typedef	Sy_LinType_19		Sy_LinType_20;
typedef	Sy_ArcType_19		Sy_ArcType_20;
typedef	Sy_TextType_19		Sy_TextType_20;
typedef Sy_RichTextType_19	Sy_RichTextType_20;
typedef	Sy_Paragraph_19		Sy_Paragraph_20;
typedef	Sy_TextStyle_19		Sy_TextStyle_20;
typedef	Sy_Tab_19			Sy_Tab_20;
typedef	Sy_SplineType_19	Sy_SplineType_20;
typedef	Sy_PictureType_19	Sy_PictureType_20;
typedef	Sy_PixMapType_19	Sy_PixMapType_20;
typedef ExtPixMap_19		ExtPixMap_20;
typedef Sy_Eol_Width_19		Sy_Eol_Width_20;
typedef ProfileItem_19		ProfileItem_20;

DEF_STRUCT_CHECKALIGN (Sy_HatchType_20, {			// 120 Bytes + content data; Hatch record
	Int32			item_Len;		// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;		// = SyHatch (6)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fillPen;		// Hatching color (0 if not hatched)
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			fillPat;		// Hatching number (0 if not hatched)
	short			contPen;		// Contour line color (0 if not framed hatch)
	short			contLType;		// Contour line type
	short			fillbkgPen;		// if 0 transparent
	bool			global;			// TRUE if fill not linked to the element
	bool			distorted;
	short			determine;		// It is always 0 in the library part files
	short			offsetType;		// It is always 0 in the library part files
	Coord			offset;			// base coordinate of fill reference vector if linked to the element
	bool			millionColorBkg;
	bool			filler;			//
	GS_RGBColor		bkgColorRGB;	// It is set if "millionColorBkg" is true
	Int32			nCoords;		// Number of vertices
	Int32			nSubPolys;		// Number of closed sub polygons including the first one
	Int32			nArcs;			// Number of curves in the polygon
	Int32			coorLen;		// Polygon coordinate data length
	Int32			coorOff;		// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType)
	Int32			endsLen;		// Subpolygon endpoints data length
	Int32			endsOff;		// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType)+ROUND_UP_8(coorLen)
	Int32			arcsLen;		// Polygon curves data length
	Int32			arcsOff;		// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType)+ROUND_UP_8(coorLen)+ROUND_UP_8(endsLen)
	Int32			addInfoLen;		// Additional info for profile data length
	Int32			addInfoOff;		// Offset of the additional info for profile data from record start
	// = sizeof(Sy_HatchType)+ROUND_UP_8(coorLen)+ROUND_UP_8(endsLen)+ROUND_UP_8(addInfoLen)
	Int32			filler_4;
	double			matrix00;
	double			matrix10;
	double			matrix01;
	double			matrix11;
});

//--- Actual Symb2D Version (21) -----------------------------------------------

DEF_STRUCT_CHECKALIGN (Sy_FontType_20, {
	Int32			item_Len;		// length of the data record = sizeof(Sy_FontType)
	unsigned char	item_Typ;		// = SyFont (8)
	char			dummyC;
	short			familytype;		// font family type: GDLFONTFAMILYNAME, GDLPLOTTERFONT, GDLPLOTMAKERFONT
	char			fontName[32];	// font name (C string)
	Int32			styleind;
	unsigned char	face;			// (Style) Style of text
	char			centre;			// Kind of text centre (1..9); if < 0 nonBreaking input mode
	short			just;			// Justification of text
	double			slant;			// Slant of text letters in rad (pi/2 is plain text)
	double			size;			// Letter size in mm independent of scale
	double			spac;			// Spacing between text lines in mm
});

typedef	Sy_2DHeadType_20	Sy_2DHeadType_21;
typedef	Sy_EndType_20		Sy_EndType_21;
typedef	Sy_HotType_20		Sy_HotType_21;
typedef	Sy_LinType_20		Sy_LinType_21;
typedef	Sy_ArcType_20		Sy_ArcType_21;
typedef	Sy_TextType_20		Sy_TextType_21;
typedef Sy_RichTextType_20	Sy_RichTextType_21;
typedef	Sy_Paragraph_20		Sy_Paragraph_21;
typedef	Sy_TextStyle_20		Sy_TextStyle_21;
typedef	Sy_Tab_20			Sy_Tab_21;
typedef	Sy_HatchType_20		Sy_HatchType_21;
typedef	AC19Symbol::Sy_FontType			Sy_FontType_21;
typedef	Sy_SplineType_20	Sy_SplineType_21;
typedef	Sy_PictureType_20	Sy_PictureType_21;
typedef	Sy_PixMapType_20	Sy_PixMapType_21;
typedef ExtPixMap_20		ExtPixMap_21;
typedef Sy_Eol_Width_20		Sy_Eol_Width_21;
typedef ProfileItem_20		ProfileItem_21;

//--- Actual Symb2D Version (22) -----------------------------------------------

typedef	Sy_2DHeadType_21	Sy_2DHeadType_22;
typedef	Sy_EndType_21		Sy_EndType_22;

DEF_STRUCT_CHECKALIGN (Sy_HotType_22, {				// 40 Bytes; Symbol Hotspot record
	Int32			item_Len;		// length of the data record = sizeof(Sy_HotType)
	unsigned char	item_Typ;		// = SyHots (2)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			flags;			// flags (Hotspot_OutOfModelBox)
	Int32			connectionId;   // Endpoint of a status line
	short			hottype;		// The type of the hotspot
	short			subtype;		// The sub-type of the hotspot
	UInt32	supplUnId;				// The supplement unique ID of the hotspot (may be 0)
	Coord			c;				// Coordinate of the first Point
});

typedef	Sy_LinType_21		Sy_LinType_22;
typedef	Sy_ArcType_21		Sy_ArcType_22;
typedef	Sy_TextType_21		Sy_TextType_22;
typedef Sy_RichTextType_21	Sy_RichTextType_22;
typedef	Sy_Paragraph_21		Sy_Paragraph_22;
typedef	Sy_TextStyle_21		Sy_TextStyle_22;
typedef	Sy_Tab_21			Sy_Tab_22;

DEF_STRUCT_CHECKALIGN (Sy_HatchType_22, {			// 120 Bytes + content data; Hatch record
	Int32			item_Len;		// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;		// = SyHatch (6)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fillPen;		// Hatching color (0 if not hatched)
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			fillPat;		// Hatching number (0 if not hatched)
	short			contPen;		// Contour line color (0 if not framed hatch)
	short			contLType;		// Contour line type
	short			fillbkgPen;		// if 0 transparent
	bool			global;			// TRUE if fill not linked to the element
	bool			distorted;
	short			determine;		// It is always 0 in the library part files
	short			offsetType;		// It is always 0 in the library part files
	Coord			offset;			// base coordinate of fill reference vector if linked to the element
	bool			millionColorBkg;
	bool			filler;			//
	GS_RGBColor		bkgColorRGB;	// It is set if "millionColorBkg" is true
	Int32			nCoords;		// Number of vertices
	Int32			nSubPolys;		// Number of closed sub polygons including the first one
	Int32			nArcs;			// Number of curves in the polygon
	Int32			coorLen;		// Polygon coordinate data length
	Int32			coorOff;		// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType)
	Int32			endsLen;		// Subpolygon endpoints data length
	Int32			endsOff;		// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
	Int32			arcsLen;		// Polygon curves data length
	Int32			arcsOff;		// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32			addInfoLen;		// Additional info for profile data length
	Int32			addInfoOff;		// Offset of the additional info for profile data from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
	Int32			filler_4;
	double			matrix00;
	double			matrix10;
	double			matrix01;
	double			matrix11;
});

typedef	Sy_FontType_21		Sy_FontType_22;
typedef	Sy_SplineType_21	Sy_SplineType_22;
typedef	Sy_PictureType_21	Sy_PictureType_22;
typedef	Sy_PixMapType_21	Sy_PixMapType_22;
typedef Sy_Eol_Width_21		Sy_Eol_Width_22;
typedef ProfileItem_21		ProfileItem_22;

//--- Actual Symb2D Version (23) -----------------------------------------------

DEF_STRUCT_CHECKALIGN (Sy_2DHeadType_23, {		// 128 Bytes; Symbol 2D handle header record
	Int32			item_Len;		// length of the data record = sizeof(Sy_2DHeadType_23)
	unsigned char	item_Typ;		// = SyHead (1)
	unsigned char	headVers;		// = Curr_Sy2DVersion) (23)
	unsigned short	platform;		// platform identifier sign: 'MM' or 'WW'
	Box2DData		box;			// Boundaries of the Symbol's image
	unsigned char	isBoundBoxValid;
	unsigned char	reserved1;		// future use. MUST BE 0
	short			reserved2;		// future use. MUST BE 0
	Int32			defScale;		// default scale (not used yet)
	Int32			headBits;		// HeadBits_UseDrwQ, HeadBits_SortDrwQ, HeadBits_HangOutOfBox
	Int32			filler_0;
	Int32			filler_1;
	Int32			filler_2;
	ULong			endOff;			// offset of the end record from section start
	ULong			nHots;			// Number of hotspots			in the Symbol
	ULong			nLine;			// Number of lines				in the Symbol
	ULong			nArc;			// Number of arcs				in the Symbol
	ULong			nText;			// Number of Texts				in the Symbol
	ULong			nHatc;			// Number of Hatches			in the Symbol
	ULong			nSpline;		// Number of Splines			in the Symbol
	ULong			nFonts;			// Number of Font data records	in the Symbol
	ULong			nPicture;		// Number of Pictures			in the Symbol
	ULong			nPixMap;		// Number of PixMaps			in the Symbol
	ULong			nRichText;		// Number of RichTexts			in the Symbol
	Int32			filler_5;
	Int32			filler_6;
	Int32			filler_7;
	Int32			filler_8;
	Int32			filler_9;
});

typedef	Sy_EndType_22		Sy_EndType_23;

DEF_STRUCT_CHECKALIGN ( Sy_HotType_23, {					// 44 Bytes; Symbol Hotspot record
	Int32			item_Len;		// length of the data record = sizeof(Sy_HotType)
	unsigned char	item_Typ;		// = SyHots (2)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			flags;			// flags (Hotspot_OutOfModelBox)
	Int32			connectionId;   // Endpoint of a status line
	short			hottype;		// The type of the hotspot
	short			subtype;		// The sub-type of the hotspot
	UInt32	supplUnId;		// The supplement unique ID of the hotspot (may be 0)
	Coord			c;				// Coordinate of the first Point
	double			z;				// z coordinate (for 3D Document)
});

typedef	Sy_LinType_22		Sy_LinType_23;
typedef	Sy_ArcType_22		Sy_ArcType_23;
typedef	Sy_TextType_22		Sy_TextType_23;
typedef Sy_RichTextType_22	Sy_RichTextType_23;
typedef	Sy_Paragraph_22		Sy_Paragraph_23;
typedef	Sy_TextStyle_22		Sy_TextStyle_23;
typedef	Sy_Tab_22			Sy_Tab_23;

DEF_STRUCT_CHECKALIGN (Sy_HatchType_23, {		// 120 Bytes + content data; Hatch record
	Int32			item_Len;		// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;		// = SyHatch (6)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fillPen;		// Hatching color (0 if not hatched)
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			fillPat;		// Hatching number (0 if not hatched)
	short			contPen;		// Contour line color (0 if not framed hatch)
	short			contLType;		// Contour line type
	short			fillbkgPen;		// if 0 transparent
	bool			global;			// TRUE if fill not linked to the element
	bool			distorted;
	short			determine;		// It is always 0 in the library part files
	short			offsetType;		// It is always 0 in the library part files
	Coord			offset;			// base coordinate of fill reference vector if linked to the element
	bool			millionColorBkg;
	bool			filler;			//
	GS_RGBColor		bkgColorRGB;	// It is set if "millionColorBkg" is true
	Int32			nCoords;		// Number of vertices
	Int32			nSubPolys;		// Number of closed sub polygons including the first one
	Int32			nArcs;			// Number of curves in the polygon
	Int32			coorLen;		// Polygon coordinate data length
	Int32			coorOff;		// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType)
	Int32			endsLen;		// Subpolygon endpoints data length
	Int32			endsOff;		// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
	Int32			arcsLen;		// Polygon curves data length
	Int32			arcsOff;		// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32			addInfoLen;		// Additional info for profile data length
	Int32			addInfoOff;		// Offset of the additional info for profile data from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
	Int32			filler_4;
	double			matrix00;
	double			matrix10;
	double			matrix01;
	double			matrix11;
	PlaneEq			origPlane;
});

typedef	Sy_FontType_22		Sy_FontType_23;
typedef	Sy_SplineType_22	Sy_SplineType_23;
typedef	Sy_PictureType_22	Sy_PictureType_23;
typedef	Sy_PixMapType_22	Sy_PixMapType_23;
typedef ProfileItem_22		ProfileItem_23;

//--- Actual Symb2D Version (24) -----------------------------------------------

typedef	Sy_2DHeadType_23	Sy_2DHeadType_24;
typedef	Sy_EndType_23		Sy_EndType_24;
typedef	Sy_HotType_23		Sy_HotType_24;
typedef	Sy_LinType_23		Sy_LinType_24;
typedef	Sy_ArcType_23		Sy_ArcType_24;
typedef	Sy_TextType_23		Sy_TextType_24;
typedef Sy_RichTextType_23	Sy_RichTextType_24;
typedef	Sy_Paragraph_23		Sy_Paragraph_24;
typedef	Sy_TextStyle_23		Sy_TextStyle_24;
typedef	Sy_Tab_23			Sy_Tab_24;

DEF_STRUCT_CHECKALIGN(Sy_HatchType_24, {				// 144 Bytes + content data; Hatch record
	Int32			item_Len;		// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;		// = SyHatch (6)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fillPen;		// Hatching color (0 if not hatched)
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			fillPat;		// Hatching number (0 if not hatched)
	short			contPen;		// Contour line color (0 if not framed hatch)
	short			contLType;		// Contour line type
	short			fillbkgPen;		// if 0 transparent
	bool			global;			// TRUE if fill not linked to the element
	bool			distorted;
	short			determine;		// It is always 0 in the library part files
	short			offsetType;		// It is always 0 in the library part files
	Coord			offset;			// base coordinate of fill reference vector if linked to the element
	bool			millionColorBkg;
	bool			filler;			//
	GS_RGBColor		bkgColorRGB;	// It is set if "millionColorBkg" is true
	Int32			nCoords;		// Number of vertices
	Int32			nSubPolys;		// Number of closed sub polygons including the first one
	Int32			nArcs;			// Number of curves in the polygon
	Int32			coorLen;		// Polygon coordinate data length
	Int32			coorOff;		// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType)
	Int32			endsLen;		// Subpolygon endpoints data length
	Int32			endsOff;		// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType)+ROUND_UP_8(coorLen)
	Int32			arcsLen;		// Polygon curves data length
	Int32			arcsOff;		// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType)+ROUND_UP_8(coorLen)+ROUND_UP_8(endsLen)
	Int32			addInfoLen;		// Additional info for profile data length
	Int32			addInfoOff;		// Offset of the additional info for profile data from record start
	// = sizeof(Sy_HatchType)+ROUND_UP_8(coorLen)+ROUND_UP_8(endsLen)+ROUND_UP_8(addInfoLen)
	Int32			filler_4;
	double			matrix00;
	double			matrix10;
	double			matrix01;
	double			matrix11;
	PlaneEq			origPlane;
	bool			millionColorFg;	// sizeof (unsigned char) 1
	bool			filler_5;		//
	GS_RGBColor		fgColorRGB;		// 3 * sizeof (unsigend short) 3 * 2
	double			gradientInnerRadius;
});

typedef	Sy_FontType_23		Sy_FontType_24;
typedef	Sy_SplineType_23	Sy_SplineType_24;
typedef	Sy_PictureType_23	Sy_PictureType_24;
typedef	Sy_PixMapType_23	Sy_PixMapType_24;
typedef ProfileItem_23		ProfileItem_24;

//--- Actual Symb2D Version (25) -----------------------------------------------

typedef	Sy_2DHeadType_24	Sy_2DHeadType_25;
typedef	Sy_EndType_24		Sy_EndType_25;
typedef	Sy_HotType_24		Sy_HotType_25;
typedef	Sy_LinType_24		Sy_LinType_25;
typedef	Sy_ArcType_24		Sy_ArcType_25;
typedef	Sy_TextType_24		Sy_TextType_25;
typedef Sy_RichTextType_24	Sy_RichTextType_25;
typedef	Sy_Paragraph_24		Sy_Paragraph_25;
typedef	Sy_TextStyle_24		Sy_TextStyle_25;
typedef	Sy_Tab_24			Sy_Tab_25;
typedef	Sy_HatchType_24		Sy_HatchType_25;
typedef	Sy_FontType_24		Sy_FontType_25;
typedef	Sy_SplineType_24	Sy_SplineType_25;
typedef	Sy_PictureType_24	Sy_PictureType_25;
typedef	Sy_PixMapType_24	Sy_PixMapType_25;
typedef ProfileItem_24		ProfileItem_25;

//--- Actual Symb2D Version (26) -----------------------------------------------

typedef	Sy_2DHeadType_25	Sy_2DHeadType_26;
typedef	Sy_EndType_25		Sy_EndType_26;
typedef	Sy_HotType_25		Sy_HotType_26;
typedef	Sy_LinType_25		Sy_LinType_26;
typedef	Sy_ArcType_25		Sy_ArcType_26;
typedef	Sy_TextType_25		Sy_TextType_26;
typedef Sy_RichTextType_25	Sy_RichTextType_26;
typedef	Sy_Paragraph_25		Sy_Paragraph_26;
typedef	Sy_TextStyle_25		Sy_TextStyle_26;
typedef	Sy_Tab_25			Sy_Tab_26;

DEF_STRUCT_CHECKALIGN(Sy_HatchType_26, {				// 144 Bytes + content data; Hatch record
	Int32			item_Len;		// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;		// = SyHatch (6)
	char			drwIndex;		// index in drawing order or 0
	short			sy_fillPen;		// Hatching color (0 if not hatched)
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			fillPat;		// Hatching number (0 if not hatched)
	short			contPen;		// Contour line color (0 if not framed hatch)
	short			contLType;		// Contour line type
	short			fillbkgPen;		// if 0 transparent
	short			determine;		// It is always 0 in the library part files
	bool			millionColorBkg;
	bool			filler_1;		//
	GS_RGBColor		bkgColorRGB;	// It is set if "millionColorBkg" is true
	Int32			nCoords;		// Number of vertices
	Int32			nSubPolys;		// Number of closed sub polygons including the first one
	Int32			nArcs;			// Number of curves in the polygon
	Int32			coorLen;		// Polygon coordinate data length
	Int32			coorOff;		// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType)
	Int32			endsLen;		// Subpolygon endpoints data length
	Int32			endsOff;		// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
	Int32			arcsLen;		// Polygon curves data length
	Int32			arcsOff;		// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32			addInfoLen;		// Additional info for profile data length
	Int32			addInfoOff;		// Offset of the additional info for profile data from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
	PlaneEq			origPlane;
	bool			millionColorFg;	// sizeof (unsigned char) 1
	bool			filler_2;		//
	GS_RGBColor		fgColorRGB;		// 3 * sizeof (unsigend short) 3 * 2
	GX::Pattern::HatchTran	hatchTrafo;	// Transzformation of hatch. (offset, 2x2 matrix, innerRadius, useGlobalOrigo)
});

typedef	Sy_FontType_25		Sy_FontType_26;
typedef	Sy_SplineType_25	Sy_SplineType_26;
typedef	Sy_PictureType_25	Sy_PictureType_26;
typedef	Sy_PixMapType_25	Sy_PixMapType_26;
typedef ProfileItem_25		ProfileItem_26;

//--- Actual Symb2D Version (27) -----------------------------------------------

typedef	Sy_2DHeadType_26	Sy_2DHeadType_27;
typedef	Sy_EndType_26		Sy_EndType_27;
DEF_STRUCT_CHECKALIGN(Sy_HotType_27, {
	Int32			item_Len;		// length of the data record = sizeof(Sy_HotType)
	unsigned char	item_Typ;		// = SyHots (2)
	char			drwIndex;		// index in drawing order or 0
	short			sy_pen;			// color information 0 if deleted
	short			sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short			flags;			// flags (Hotspot_OutOfModelBox)
	Int32			connectionId;   // Endpoint of a status line
	short			hottype;		// The type of the hotspot
	short			subtype;		// The sub-type of the hotspot
	UInt32			supplUnId;		// The supplement unique ID of the hotspot (may be 0)
	Coord			c;				// Coordinate of the first Point
	double			z;				// z coordinate (for 3D Document)
	char			sy2dRenovationStatus; //Sy2dRenovationStatusTypes
	char			filler_1;
	short			filler_2;
	Int32			filler_3;
});
typedef	AC19Symbol::Sy_LinType			Sy_LinType_27;//26->27, meret nem valtozott.
typedef	AC19Symbol::Sy_ArcType			Sy_ArcType_27;//26->27, meret nem valtozott.
typedef	AC19Symbol::Sy_TextType			Sy_TextType_27;//26->27, 27->26
typedef AC19Symbol::Sy_RichTextType		Sy_RichTextType_27;//26->27, 27->26
typedef	Sy_Paragraph_26					Sy_Paragraph_27;
typedef	Sy_TextStyle_26					Sy_TextStyle_27;
typedef	Sy_Tab_26						Sy_Tab_27;

//26->27, 27->26
DEF_STRUCT_WITH_DEFAULT_CONSTRUCTOR_CHECKALIGN (Sy_HatchType_27, SINGLE_ARG (					// 144 Bytes + content data; Hatch record
	Int32				item_Len;		// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char		item_Typ;		// = SyHatch (6)
	char				drwIndex;		// index in drawing order or 0
	short				sy_fillPen;		// Hatching color (0 if not hatched)
	short				sy_fragmentIdx;		// Fragment (layer) number: 1 - 16
	short				fillPat;		// Hatching number (0 if not hatched)
	short				contPen;		// Contour line color (0 if not framed hatch)
	short				contLType;		// Contour line type
	short				fillbkgPen;		// if 0 transparent
	short				determine;		// It is always 0 in the library part files
	bool				millionColorBkg;
	char				specFor3D;			//
	GS_RGBColor			bkgColorRGB;	// It is set if "millionColorBkg" is true
	Int32				nCoords;		// Number of vertices
	Int32				nSubPolys;		// Number of closed sub polygons including the first one
	Int32				nArcs;			// Number of curves in the polygon
	Int32				coorLen;		// Polygon coordinate data length
	Int32				coorOff;		// Offset of the Polygon coordinate from record start
	// = sizeof(Sy_HatchType)
	Int32				endsLen;		// Subpolygon endpoints data length
	Int32				endsOff;		// Offset of the Subpolygon endpoints from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
	Int32				arcsLen;		// Polygon curves data length
	Int32				arcsOff;		// Offset of the Polygon curves from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32				addInfoLen;		// Additional info for profile data length
	Int32				addInfoOff;		// Offset of the additional info for profile data from record start
	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
	PlaneEq				origPlane;
	bool				millionColorFg;	// sizeof (unsigned char) 1
	char				sy2dRenovationStatus;
	GS_RGBColor			fgColorRGB;		// 3 * sizeof (unsigend short) 3 * 2
	GX::Pattern::HatchTran	hatchTrafo;	// Transzformation of hatch. (offset, 2x2 matrix, innerRadius, useGlobalOrigo)
));


inline Sy_HatchType_27::Sy_HatchType_27 () :
	item_Len (0),
	item_Typ (0),
	drwIndex (0),
	sy_fillPen (0),
	sy_fragmentIdx (0),
	fillPat (0),
	contPen (0),
	contLType (0),
	fillbkgPen (0),
	determine (0),
	millionColorBkg (false),
	specFor3D (SySymbolic),
	nCoords (0),
	nSubPolys (0),
	nArcs (0),
	coorLen (0),
	coorOff (0),
	endsLen (0),
	endsOff (0),
	arcsLen (0),
	arcsOff (0),
	addInfoLen (0),
	addInfoOff (0),
	millionColorFg (false),
	sy2dRenovationStatus (VI::SyUndefinedRenovationStatus)
{
	bkgColorRGB.red = bkgColorRGB.green = bkgColorRGB.blue = 0;
	fgColorRGB.red = fgColorRGB.green = fgColorRGB.blue = 0;
}

typedef	Sy_FontType_26		Sy_FontType_27;
typedef	AC19Symbol::Sy_SplineType		Sy_SplineType_27;//26->27, meret nem valtozott.
typedef	Sy_PictureType_26	Sy_PictureType_27;
typedef	AC19Symbol::Sy_PixMapType		Sy_PixMapType_27;//26->27, meret nem valtozott.
typedef ProfileItem_26		ProfileItem_27;

//--- Actual Symb2D Version (28) -----------------------------------------------

typedef	AC19Symbol::Sy_2DHeadType		Sy_2DHeadType_28;
typedef	Sy_EndType_27		Sy_EndType_28;
typedef Sy_HotType_27		Sy_HotType_28;
typedef	Sy_LinType_27		Sy_LinType_28;
typedef	AC19Symbol::Sy_PolyLinType		Sy_PolyLinType_28;
typedef	Sy_ArcType_27		Sy_ArcType_28;
typedef	Sy_TextType_27		Sy_TextType_28;
typedef Sy_RichTextType_27	Sy_RichTextType_28;
typedef	Sy_Paragraph_27		Sy_Paragraph_28;
typedef	Sy_TextStyle_27		Sy_TextStyle_28;
typedef	Sy_Tab_27			Sy_Tab_28;
typedef	Sy_HatchType_27		Sy_HatchType_28;
typedef	Sy_FontType_27		Sy_FontType_28;
typedef	Sy_SplineType_27	Sy_SplineType_28;
typedef	Sy_PictureType_27	Sy_PictureType_28;
typedef	Sy_PixMapType_27	Sy_PixMapType_28;
typedef ProfileItem_27		ProfileItem_28;

//--- Actual Symb2D Version (29) -----------------------------------------------

typedef	Sy_2DHeadType_28	Sy_2DHeadType_29;
typedef	Sy_EndType_28		Sy_EndType_29;
typedef	AC19Symbol::Sy_HotType			Sy_HotType_29;
typedef	Sy_LinType_28		Sy_LinType_29;
typedef	Sy_PolyLinType_28	Sy_PolyLinType_29;
typedef	Sy_ArcType_28		Sy_ArcType_29;
typedef	Sy_TextType_28		Sy_TextType_29;
typedef Sy_RichTextType_28	Sy_RichTextType_29;
typedef	Sy_Paragraph_28		Sy_Paragraph_29;
typedef	Sy_TextStyle_28		Sy_TextStyle_29;
typedef	Sy_Tab_28			Sy_Tab_29;
typedef	Sy_HatchType_28		Sy_HatchType_29;
typedef	Sy_FontType_28		Sy_FontType_29;
typedef	Sy_SplineType_28	Sy_SplineType_29;
typedef	Sy_PictureType_28	Sy_PictureType_29;
typedef	Sy_PixMapType_28	Sy_PixMapType_29;
typedef ProfileItem_28		ProfileItem_29;

//--- Actual Symb2D Version (30) -----------------------------------------------
DEF_STRUCT_WITH_DEFAULT_CONSTRUCTOR_CHECKALIGN (Sy_HatchType_30, SINGLE_ARG (
											// 144 Bytes + content data; Hatch record
	Int32				item_Len;			// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char		item_Typ;			// = SyHatch (6)
	char				drwIndex;			// index in drawing order or 0
	unsigned short		syFlags;			// See SyHatchFlag need for visualiztion
	unsigned short		buildMatFlags;		// See SyHatchBuildingMaterialFlag need for conversion only
	short				fillFgPen;			// Hatching color (0 if not hatched)
	short				sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	short				fillIdx;			// Index of Fill attributum (0 if not hatched) when SyHatchFlag_FillHatch
	short				buildMatIdx;		// Index of Building Material attributum when SyHatchFlag_BuildingMaterialHatch
	short				contPen;			// Contour line color (0 if not framed hatch)
	short				contLType;			// Contour line type
	short				fillBkgPen;			// if 0 transparent
	short				determine;			// It is always 0 in the library part files
	char				specFor3D;			//
	char				sy2dRenovationStatus;

	GS_RGBColor			bkgColorRGB;		// It is set if "SyHatchFlag_MillionColorBkg" set
	GS_RGBColor			fgColorRGB;			// 3 * sizeof (unsigend short) 3 * 2

	Int32				nCoords;			// Number of vertices
	Int32				nSubPolys;			// Number of closed sub polygons including the first one
	Int32				nArcs;				// Number of curves in the polygon
	Int32				coorLen;			// Polygon coordinate data length
	Int32				coorOff;			// Offset of the Polygon coordinate from record start
											// = sizeof(Sy_HatchType)
	Int32				endsLen;			// Subpolygon endpoints data length
	Int32				endsOff;			// Offset of the Subpolygon endpoints from record start
											// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
	Int32				arcsLen;			// Polygon curves data length
	Int32				arcsOff;			// Offset of the Polygon curves from record start
											// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32				addInfoLen;			// Additional info for profile data length
	Int32				addInfoOff;			// Offset of the additional info for profile data from record start
											// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
private:
	[[maybe_unused]] UInt32 filler;
public:
	PlaneEq				origPlane;
	GX::Pattern::HatchTran	hatchTrafo;			// Transzformation of hatch. (offset, 2x2 matrix, innerRadius, useGlobalOrigo)
));


Sy_HatchType_30::Sy_HatchType_30 () :
	item_Len (0),
	item_Typ (0),
	drwIndex (0),
	syFlags (0),
	buildMatFlags (SyHatchFlag_FillHatch),
	fillFgPen (0),
	sy_fragmentIdx (0),
	fillIdx (0),
	buildMatIdx (0),
	contPen (0),
	contLType (0),
	fillBkgPen (0),
	determine (0),
	specFor3D (SySymbolic),
	nCoords (0),
	nSubPolys (0),
	nArcs (0),
	coorLen (0),
	coorOff (0),
	endsLen (0),
	endsOff (0),
	arcsLen (0),
	arcsOff (0),
	addInfoLen (0),
	addInfoOff (0),
	sy2dRenovationStatus (VI::SyUndefinedRenovationStatus),
	filler (0)
{
	bkgColorRGB.red = bkgColorRGB.green = bkgColorRGB.blue = 0;
	fgColorRGB.red = fgColorRGB.green = fgColorRGB.blue = 0;
}


DEF_STRUCT_CHECKALIGN (ProfileItem_30, SINGLE_ARG ( // 16 Bytes
{
	Int32	profileItemVersion;
	Int32	obsoletePriorityValue;
private:
	Int32	flags;
public:
	Int32	filler;

	void	SetFlag (short flag) { flags |= flag; }

	void	IV (GS::PlatformSign from, GS::PlatformSign to)
	{
		IVLong (from, to, &profileItemVersion);
		IVLong (from, to, &obsoletePriorityValue);
		IVLong (from, to, &flags);
	}
}));


typedef	Sy_2DHeadType_29	Sy_2DHeadType_30;
typedef	Sy_EndType_29		Sy_EndType_30;
typedef	Sy_HotType_29		Sy_HotType_30;
typedef	Sy_LinType_29		Sy_LinType_30;
typedef	Sy_PolyLinType_29	Sy_PolyLinType_30;
typedef	Sy_ArcType_29		Sy_ArcType_30;
typedef	Sy_TextType_29		Sy_TextType_30;
typedef Sy_RichTextType_29	Sy_RichTextType_30;
typedef	Sy_Paragraph_29		Sy_Paragraph_30;
typedef	Sy_TextStyle_29		Sy_TextStyle_30;
typedef	Sy_Tab_29			Sy_Tab_30;
typedef	Sy_FontType_29		Sy_FontType_30;
typedef	Sy_SplineType_29	Sy_SplineType_30;
typedef	Sy_PictureType_29	Sy_PictureType_30;
typedef	Sy_PixMapType_29	Sy_PixMapType_30;

//--- Actual Symb2D Version (31) -----------------------------------------------
DEF_STRUCT_WITH_DEFAULT_CONSTRUCTOR_CHECKALIGN (Sy_HatchType_31, SINGLE_ARG (		// 144 Bytes + content data; Hatch record
	Int32				item_Len;			// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char		item_Typ;			// = SyHatch (6)
	char				drwIndex;			// index in drawing order or 0
	unsigned short		syFlags;			// See SyHatchFlag need for visualiztion
	unsigned short		buildMatFlags;		// See SyHatchBuildingMaterialFlag need for conversion only
	short				fillFgPen;			// Hatching color (0 if not hatched)
	short				sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	short				fillIdx;			// Index of Fill attributum (0 if not hatched) when SyHatchFlag_FillHatch
	short				buildMatIdx;		// Index of Building Material attributum when SyHatchFlag_BuildingMaterialHatch
	short				contPen;			// Contour line color (0 if not framed hatch)
	short				contLType;			// Contour line type
	short				fillBkgPen;			// if 0 transparent
	short				determine;			// It is always 0 in the library part files
	char				specFor3D;			//
	char				sy2dRenovationStatus;
	GS_RGBColor			bkgColorRGB;		// It is set if "SyHatchFlag_MillionColorBkg" set
	GS_RGBColor			fgColorRGB;			// 3 * sizeof (unsigend short) 3 * 2
	Int32				nCoords;			// Number of vertices
	Int32				nSubPolys;			// Number of closed sub polygons including the first one
	Int32				nArcs;				// Number of curves in the polygon
	Int32				coorLen;			// Polygon coordinate data length
	Int32				coorOff;			// Offset of the Polygon coordinate from record start	// = sizeof(Sy_HatchType)
	Int32				endsLen;			// Subpolygon endpoints data length
	Int32				endsOff;			// Offset of the Subpolygon endpoints from record start	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
	Int32				arcsLen;			// Polygon curves data length
	Int32				arcsOff;			// Offset of the Polygon curves from record start	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32				addInfoLen;			// Additional info for profile data length
	Int32				addInfoOff;			// Offset of the additional info for profile data from record start	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
private:
	UInt32				displayOrder;		// Display order
public:
	PlaneEq				origPlane;
	GX::Pattern::HatchTran	hatchTrafo;			// Transformation of hatch. (offset, 2x2 matrix, innerRadius, useGlobalOrigo)

public:

	void	SetDisplayOrder (UInt32 value)								{ displayOrder = value; }
	void	IVDisplayOrder (GS::PlatformSign from, GS::PlatformSign to) { IVULong (from, to, &displayOrder); }
));

Sy_HatchType_31::Sy_HatchType_31 () :
item_Len (0),
	item_Typ (0),
	drwIndex (0),
	syFlags (0),
	buildMatFlags (SyHatchFlag_FillHatch),
	fillFgPen (0),
	sy_fragmentIdx (0),
	fillIdx (0),
	buildMatIdx (0),
	contPen (0),
	contLType (0),
	fillBkgPen (0),
	determine (0),
	specFor3D (SySymbolic),
	nCoords (0),
	nSubPolys (0),
	nArcs (0),
	coorLen (0),
	coorOff (0),
	endsLen (0),
	endsOff (0),
	arcsLen (0),
	arcsOff (0),
	addInfoLen (0),
	addInfoOff (0),
	sy2dRenovationStatus (VI::SyUndefinedRenovationStatus),
	displayOrder (DefaultDisplayOrder)
{
	bkgColorRGB.red = bkgColorRGB.green = bkgColorRGB.blue = 0;
	fgColorRGB.red = fgColorRGB.green = fgColorRGB.blue = 0;
}


DEF_STRUCT_CHECKALIGN (ProfileItem_31, SINGLE_ARG ( // 16 Bytes
{
	Int32	profileItemVersion;
	Int32	obsoletePriorityValue;
private:
	Int32	flags;
public:
	Int32	filler;

	enum {
		VisibleCutEndLinesFlag		= 0x00000100
	};

	void	SetVisibleCutEndLines	(bool value)	{ flags = (value) ? flags | VisibleCutEndLinesFlag	: flags & ~VisibleCutEndLinesFlag;	}

	void	IV						(GS::PlatformSign from, GS::PlatformSign to)
	{
		IVLong (from, to, &profileItemVersion);
		IVLong (from, to, &obsoletePriorityValue);
		IVLong (from, to, &flags);
	}
}));


typedef	Sy_2DHeadType_30	Sy_2DHeadType_31;
typedef	Sy_EndType_30		Sy_EndType_31;
typedef	Sy_HotType_30		Sy_HotType_31;
typedef	Sy_LinType_30		Sy_LinType_31;
typedef	Sy_PolyLinType_30	Sy_PolyLinType_31;
typedef	Sy_ArcType_30		Sy_ArcType_31;
typedef	Sy_TextType_30		Sy_TextType_31;
typedef Sy_RichTextType_30	Sy_RichTextType_31;
typedef	Sy_Paragraph_30		Sy_Paragraph_31;
typedef	Sy_TextStyle_30		Sy_TextStyle_31;
typedef	Sy_Tab_30			Sy_Tab_31;
typedef	Sy_FontType_30		Sy_FontType_31;
typedef	Sy_SplineType_30	Sy_SplineType_31;
typedef	Sy_PictureType_30	Sy_PictureType_31;
typedef	Sy_PixMapType_30	Sy_PixMapType_31;

//--- Actual Symb2D Version (32) -----------------------------------------------

DEF_STRUCT_CHECKALIGN (ProfileItem_32, SINGLE_ARG ( // 16 Bytes
{
public:
	Int32	profileItemVersion;
	Int32	obsoletePriorityValue;
private:
	Int32	flags;
	short	cutEndLinePen;
	short	cutEndLineType;

public:
	Int32	GetFlags				(void)						const	{ return flags; }
	void	SetFlags				(Int32 newFlags)					{ flags = newFlags; }

	short	GetCutEndLinePen		(void)						const	{ return cutEndLinePen; }
	void	SetCutEndLinePen		(short value)						{ cutEndLinePen = value; }

	short	GetCutEndLineType		(void)						const	{ return cutEndLineType; }
	void	SetCutEndLineType		(short value)						{ cutEndLineType = value; }

	void	IV						(GS::PlatformSign from, GS::PlatformSign to)
	{
		IVLong (from, to, &profileItemVersion);
		IVLong (from, to, &obsoletePriorityValue);
		IVLong (from, to, &flags);
		IVShort (from, to, &cutEndLinePen);
		IVShort (from, to, &cutEndLineType);
	}
}));

typedef	Sy_2DHeadType_31	Sy_2DHeadType_32;
typedef	Sy_EndType_31		Sy_EndType_32;
typedef	Sy_HotType_31		Sy_HotType_32;
typedef	Sy_LinType_31		Sy_LinType_32;
typedef	Sy_PolyLinType_31	Sy_PolyLinType_32;
typedef	Sy_ArcType_31		Sy_ArcType_32;
typedef	Sy_TextType_31		Sy_TextType_32;
typedef Sy_RichTextType_31	Sy_RichTextType_32;
typedef	Sy_Paragraph_31		Sy_Paragraph_32;
typedef	Sy_TextStyle_31		Sy_TextStyle_32;
typedef	Sy_Tab_31			Sy_Tab_32;
DEF_STRUCT_WITH_DEFAULT_CONSTRUCTOR_CHECKALIGN (Sy_HatchType_32, SINGLE_ARG (	// 144 Bytes + content data; Hatch record
	Int32				item_Len;			// length of the data record = endsOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char		item_Typ;			// = SyHatch (6)
	char				drwIndex;			// index in drawing order or 0
	unsigned short		syFlags;			// See SyHatchFlag need for visualiztion
	unsigned short		buildMatFlags;		// See SyHatchBuildingMaterialFlag need for conversion only
	short				fillFgPen;			// Hatching color (0 if not hatched)
	short				sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
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
	Int32				coorOff;			// Offset of the Polygon coordinate from record start	// = sizeof(Sy_HatchType)
	Int32				endsLen;			// Subpolygon endpoints data length
	Int32				endsOff;			// Offset of the Subpolygon endpoints from record start	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)
	Int32				arcsLen;			// Polygon curves data length
	Int32				arcsOff;			// Offset of the Polygon curves from record start	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)
	Int32				addInfoLen;			// Additional info for profile data length
	Int32				addInfoOff;			// Offset of the additional info for profile data from record start	// = sizeof(Sy_HatchType)+RoundUp8(coorLen)+RoundUp8(endsLen)+RoundUp8(addInfoLen)
	UInt32				displayOrder;		// Display order
	GS::UInt32			filler3;
	PlaneEq				origPlane;
	GX::Pattern::HatchTran	hatchTrafo;			// Transformation of hatch. (offset, 2x2 matrix, innerRadius, useGlobalOrigo)

public:
	  void	SetFragmentIndex (short inFragmentIndex) { DBASSERT(inFragmentIndex >= 1);  DBASSERT(inFragmentIndex <= 16); sy_fragmentIdx = inFragmentIndex; }
	  short GetContPenVal () const { return contPen; }
	  short GetContPen () const { return contVis ? contPen : 0; }
	  bool  GetContVis () const { return (contVis != 0); }
	  void  SetContPen (const short newPenVal) 
	  {
		  contPen = newPenVal; 
		  contVis = (newPenVal != 0);
	  }

	  void  SetContVis (const bool newVal) 								{ contVis = newVal; }
	  void	SetContLType (short lType)									{ DBASSERT (lType > 0); contLType = lType; }
	  short GetContLType (void) const									{ return contLType; }
	  void	SetDisplayOrder (UInt32 value)								{ displayOrder = value; }
	  void	IVDisplayOrder (GS::PlatformSign from, GS::PlatformSign to) { IVULong (from, to, &displayOrder); }
));

typedef	Sy_FontType_31		Sy_FontType_32;
typedef	Sy_SplineType_31	Sy_SplineType_32;
typedef	Sy_PictureType_31	Sy_PictureType_32;
typedef	Sy_PixMapType_31	Sy_PixMapType_32;

//--- Actual Symb2D Version (33) -----------------------------------------------

typedef	Sy_2DHeadType_32	Sy_2DHeadType_33;
typedef	Sy_EndType_32		Sy_EndType_33;
typedef	Sy_HotType_32		Sy_HotType_33;
typedef	Sy_LinType_32		Sy_LinType_33;
typedef	Sy_PolyLinType_32	Sy_PolyLinType_33;
typedef	Sy_ArcType_32		Sy_ArcType_33;
typedef	Sy_TextType_32		Sy_TextType_33;
typedef Sy_RichTextType_32	Sy_RichTextType_33;
typedef	Sy_Paragraph_32		Sy_Paragraph_33;
typedef	Sy_TextStyle_32		Sy_TextStyle_33;
typedef	Sy_Tab_32			Sy_Tab_33;
typedef	AC19Symbol::Sy_HatchType		Sy_HatchType_33;
typedef	Sy_FontType_32		Sy_FontType_33;
typedef	Sy_SplineType_32	Sy_SplineType_33;
typedef	Sy_PictureType_32	Sy_PictureType_33;
typedef	Sy_PixMapType_32	Sy_PixMapType_33;
typedef ProfileItem_32		ProfileItem_33;

//--- Actual Symb2D Version (34) -----------------------------------------------

typedef	Sy_2DHeadType_33	Sy_2DHeadType_34;
typedef	Sy_EndType_33		Sy_EndType_34;
typedef	Sy_HotType_33		Sy_HotType_34;
typedef	Sy_LinType_33		Sy_LinType_34;
typedef	Sy_PolyLinType_33	Sy_PolyLinType_34;
typedef	Sy_ArcType_33		Sy_ArcType_34;
typedef	Sy_TextType_33		Sy_TextType_34;
typedef Sy_RichTextType_33	Sy_RichTextType_34;
typedef	Sy_Paragraph_33		Sy_Paragraph_34;
typedef	Sy_TextStyle_33		Sy_TextStyle_34;
typedef	Sy_Tab_33			Sy_Tab_34;
typedef	Sy_HatchType_33		Sy_HatchType_34;
typedef	Sy_FontType_33		Sy_FontType_34;
typedef	Sy_SplineType_33	Sy_SplineType_34;
typedef	Sy_PictureType_33	Sy_PictureType_34;
typedef	Sy_PixMapType_33	Sy_PixMapType_34;
typedef ProfileItem_33		ProfileItem_34;

//--- Actual Symb2D Version (35) -----------------------------------------------

typedef	Sy_2DHeadType_34	Sy_2DHeadType_35;
typedef	Sy_EndType_34		Sy_EndType_35;
typedef	Sy_HotType_34		Sy_HotType_35;
typedef	Sy_LinType_34		Sy_LinType_35;
typedef	Sy_PolyLinType_34	Sy_PolyLinType_35;
typedef	Sy_ArcType_34		Sy_ArcType_35;
typedef	Sy_TextType_34		Sy_TextType_35;
typedef Sy_RichTextType_34	Sy_RichTextType_35;
typedef	Sy_Paragraph_34		Sy_Paragraph_35;
typedef	Sy_TextStyle_34		Sy_TextStyle_35;
typedef	Sy_Tab_34			Sy_Tab_35;
typedef	Sy_HatchType_34		Sy_HatchType_35;
typedef	Sy_FontType_34		Sy_FontType_35;
typedef	Sy_SplineType_34	Sy_SplineType_35;
typedef	Sy_PictureType_34	Sy_PictureType_35;
typedef	Sy_PixMapType_34	Sy_PixMapType_35;
typedef AC22HatchAddInfo::ProfileItem	ProfileItem_35;

////////////////////////////////////////////////////////////////////////////////////

#if defined (_MSC_VER) || (defined (__SC__) && !defined (macintosh))	// mm-sc7
#pragma pack ()
#endif

#if defined (macintosh)
#pragma options align=reset
#endif


#endif /*_Symb2DOldVersions_H_*/
