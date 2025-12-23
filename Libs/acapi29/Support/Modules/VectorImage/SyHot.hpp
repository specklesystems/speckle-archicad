#ifndef SYHOT_HPP
#define SYHOT_HPP

#pragma once

#include "ISymbol.hpp"
#include "DrawIndex.hpp"
#include "Point2D.hpp"

// from CADInfrastructureBase
#include "ADBAttributeIndex.hpp"

class Box2DData;

namespace Geometry {
class Transformation2D;
}

#define Hotspot_OutOfModelBox	0x0001	// The hotspot is out of the model box
#define Hotspot_SpecForProfile	0x0002	// Special hotspot for Profile Data (anchor for column, ref line for wall/beam)
#define Hotspot_Border			0x0004


class VI_DLL_CLASS_EXPORT Sy_HotType {
	
	GSErrCode	Write_Version36 (GS::OChannel& oc) const;
	GSErrCode	Read_Version36 (GS::IChannel& ic);
	GSErrCode	Write_Version37 (GS::OChannel& oc) const;
	GSErrCode	Read_Version37 (GS::IChannel& ic);

	static const short actVersion;
	static const short previousVersion;

public:	
	Int32			item_Len;				// length of the data record = sizeof(Sy_HotType)
	unsigned char	item_Typ;				// = SyHots (2)
	DrawIndex		drwIndex;				// index in drawing order or 0
	short			sy_pen;					// color information 0 if deleted
	short			sy_fragmentIdx;			// Fragment (layer) number: 1 - 16
	short			flags;					// flags (Hotspot_OutOfModelBox)
	Int32			connectionId;			// Endpoint of a status line
	short			hottype;				// The type of the hotspot
	short			subtype;				// The sub-type of the hotspot
	UInt32			supplUnId;				// The supplement unique ID of the hotspot (may be 0)
	Coord			c;						// Coordinate of the first Point
	double			z;						// z coordinate (for 3D Document)
	char			sy2dRenovationStatus;	//Sy2dRenovationStatusTypes
private:
	char			filler_1;
	short			filler_2;
	Int32			filler_3;
	GS::Guid		uniqueId;
public:
	double			arcParam;	// Pure magic. In case of CWBaseArc-s hotspots, the first hotspot's arcParam is the arcs mainAxisDir, the second's arcParam is the axisLengthRatio.

	Sy_HotType ();
	Sy_HotType (GS::Guid requiredId);
	Sy_HotType (short inType, short inSubtype, ULong inSupplUnId, const Coord& inC, double inZ);
	Sy_HotType (short pen, short layer, DrawIndex drwIndex, UInt32 inSupplUnId, short inType, short inSubtype, const Coord& inC, Int32 inConnectionId, const GS::Optional<GS::Guid>& requiredId = GS::NoValue);

	bool IsNear (const Sy_HotType& other) const;
	void GetBounds (Box2DData& box) const;
	void Transform (const Geometry::Transformation2D& tran);
	bool operator== (const Sy_HotType& other) const;
	bool operator!= (const Sy_HotType& other) const;

	bool	CompareGeometry (const Sy_HotType& other, double eps) const;
	bool	CompareSettings (const Sy_HotType& other) const;

	GSErrCode	WriteGeometryForChecksum (GS::OChannel& oc, double eps) const;
	GSErrCode	WriteSettingsForChecksum (GS::OChannel& oc) const;
	
	SyEnum		GetType () const;
	GSErrCode	ReadBin (GS::IChannel& oc, short version);

	GSErrCode	Write (GS::OChannel& oc, short version) const;
	GSErrCode	Read (GS::IChannel& oc, short version);

	const GS::Guid&	GetUniqueId () const;
	void			SetNewUniqueId ();

	static short GetActVersion () { return actVersion; }
	static short GetPreviousVersion () { return previousVersion; }
	static Int32 GetConvertedSize (Int32 ac19ItemLen);
};



#endif // SYHOT_HPP