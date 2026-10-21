#ifndef SYPOLYLINE_HPP
#define SYPOLYLINE_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"
#include "Poly2DTypes.hpp"
#include "ExtendedPen.hpp"
#include "ADBAttributeIndex.hpp"

class Box2DData;
struct TRANMAT;
struct PolyArcRec;

class VI_DLL_CLASS_EXPORT Sy_PolyLinType {
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);
	GSErrCode	Write_Version37 (GS::OChannel& oc) const;
	GSErrCode	Read_Version37 (GS::IChannel& ic);
	GSErrCode	Write_Version38 (GS::OChannel& oc) const;
	GSErrCode	Read_Version38 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;					// length of the data record = coorOff+Round_UP_8(endsLen)+Round_UP_8(arcsLen)
	unsigned char	item_Typ;					// = SyPolyLine (12)
	DrawIndex		drwIndex;					// index in drawing order or 0
	char			sy2dRenovationStatus;		//Sy2dRenovationStatusTypes
	char			specFor3D;					// 0: Sy3DInformation
private:
	VBAttr::ExtendedPen	sy_pen;					// color information 0 if deleted
	ADB::AttributeIndex pattern;					// Pattern/lineType info.
	short			drawSegmentMode;
public:
	short			sy_fragmentIdx;				// Fragment (layer) number: 1 - 16
private:
	short			filler_0;
public:
	short			determine;					// Determines the type of line (contour - 0 / inner - 1)

	Int32			nCoords;					// Number of Coords
	Int32			nArcs;						// Number of curves in the polygon

	Int32			coorLen;					// PolyLine coordinate data length
	Int32			coorOff;					// Offset of the PolyLine coordinate from record start
												// = sizeof(Sy_SplineType)
	Int32			arcsLen;					// Polygon curves data length
	Int32			arcsOff;					// Offset of the Polygon curves from record start
												// = sizeof(Sy_SplineType)+RoundUp8(coorLen)
	Sy_PolyLinType ();
	
	void						SetExtendedPen (const VBAttr::ExtendedPen& inPen);
	VBAttr::ExtendedPen			GetExtendedPen () const;

	void						SetPattern (const ADB::AttributeIndex& inPattern);
	const ADB::AttributeIndex&  GetPattern () const;

	void						SetDrawSegmentMode (short newDrawSegmentMode);
	short						GetDrawSegmentMode () const;

	bool						CompareGeometry (const Sy_PolyLinType& other, double eps) const;
	bool						CompareSettings (const Sy_PolyLinType& other) const;

	GSErrCode					WriteGeometryForChecksum (GS::OChannel& oc, double eps) const;
	GSErrCode					WriteSettingsForChecksum (GS::OChannel& oc) const;

	Coord*						GetCoords (void);
	const Coord*				GetCoords (void) const;
	PolyArcRec*					GetArcs (void);
	const PolyArcRec*			GetArcs (void) const;

	GSErrCode					ToPolyline2D (Geometry::Polyline2D& polyline) const;
	void						FromPolyline2D (const Geometry::Polyline2D& polyline);

	static void CopyData (	const Sy_PolyLinType&			srcSyPolyLine,
							const Geometry::Polyline2D&		srcPolyline,
							char*							dstSyPolyLine,
							char*							dstCoords,
							char*							dstArcs);

	GSErrCode	GetBounds	(Box2DData& box) const;
	bool		CheckCoords	(void) const;
	bool		CheckArcs	(void) const;
	bool		Check		(void) const;
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
	static Int32 GetConvertedSize (Int32 ac19ItemLen);
};



#endif // SYPOLYLINE_HPP