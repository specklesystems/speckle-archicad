#ifndef SYARC_HPP
#define SYARC_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"
#include "Point2D.hpp"
#include "ExtendedPen.hpp"
#include "ADBAttributeIndex.hpp"

class Box2DData;
struct TRANMAT;

namespace Geometry {
class GenArc;
class Transformation2D;
}

class VI_DLL_CLASS_EXPORT Sy_ArcType {		// 112 Bytes; Symbol Arc,Circ,Ellips record
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);
	GSErrCode	Write_Version37 (GS::OChannel& oc) const;
	GSErrCode	Read_Version37 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:
	Int32			item_Len;				// length of the data record = sizeof(Sy_ArcType)
	unsigned char	item_Typ;				// = SyArc (4)
	DrawIndex		drwIndex;				// index in drawing order or 0
private:
	short			filler_0;
	VBAttr::ExtendedPen	sy_pen;				// color information 0 if deleted
	ADB::AttributeIndex	pattern;			// Pattern/lineType info.
public:
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
private:
	short			filler_1;
public:
	bool			whole;					// whole circle or arc?
	bool			elliptic;				// ratio != 1.0
	bool			reflected;				// on the smaller axis
private:
	bool			filler_2;
public:
	Coord			origC;					// Coordinate of the origin
	double			r;						// Radius !!!
	double			mainAxisDir;			// of the longer axis
	double			ratio;					// longer axis : smaller axis
	double			begAng;					// beginning angle of the arc
	double			endAng;					// ending angle of the arc
	Coord			begC;					// Coordinate of the first Point
	Coord			endC;					// Coordinate of the second Point
	short			determine;				// Determines the type of line (contour - 0 / inner - 1)
	char			sy2dRenovationStatus;	//Sy2dRenovationStatusTypes
	char			specFor3D;				// 0: Sy3DInformation
private:
	Int32			filler_3;
public:

	Sy_ArcType ();
	Sy_ArcType (const VBAttr::ExtendedPen&	inPen,
				const ADB::AttributeIndex&	inPattern,
				short						inFragmentIdx,
				DrawIndex					inDrwIndex,
				const Coord&				inOrigo,
				const Coord&				inBegC,
				const Coord&				inEndC,
				double*						inAlpha,
				double*						inBeta,
				double						inR,
				double						inRatio,
				double						inAngle,
				short						inDetermine = 0,
				char						inSpecFor3D = SySymbolic);

	bool operator== (const Sy_ArcType& other) const;
	bool				CompareGeometry (const Sy_ArcType& other, double eps) const;
	bool				CompareSettings (const Sy_ArcType& other) const;

	GSErrCode			WriteGeometryForChecksum (GS::OChannel& oc, double eps) const;
	GSErrCode			WriteSettingsForChecksum (GS::OChannel& oc) const;

	void				FixBegAndEndAng ();
	
	void						SetExtendedPen (const VBAttr::ExtendedPen& inPen);
	VBAttr::ExtendedPen			GetExtendedPen () const;
	void						SetPattern (const ADB::AttributeIndex& inPattern);
	const ADB::AttributeIndex&	GetPattern () const;


	void ToGenArc (Geometry::GenArc& genArc) const;
	void FromGenArc (const Geometry::GenArc& genArc);
	void GetBounds (Box2DData& box) const;
	void Transform (const Geometry::Transformation2D& tran);
	void Transform (const TRANMAT& tran);
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);
	
	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
	static Int32 GetConvertedSize (Int32 ac19ItemLen);
};

#endif // SYARC_HPP