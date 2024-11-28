#ifndef ANCHOR_HPP
#define ANCHOR_HPP

#include "HatchVertexId.hpp"
#include "HatchEdgeId.hpp"
#include "VectorImageTypedefs.hpp"

#include "VectorImageExport.h"

namespace Geometry {
class Transformation2D;
}

namespace PVI { // ProfileVectorImage

	//the following list is the standard IDS for static anchors -anchors of predefined role-  
	
	//Bounding box associated anchors:
	VI_DLL_EXPORT extern const ProfileAnchorId BoundingBoxULAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId BoundingBoxURAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId BoundingBoxLLAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId BoundingBoxLRAnchorID;

	//stretch zone/level associated anchors (fixed coord anchors)
	VI_DLL_EXPORT extern const ProfileAnchorId StretchZoneVerticalUAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId StretchZoneVerticalLAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId StretchZoneHorizontalUAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId StretchZoneHorizontalLAnchorID;

	//nominal SIZE setters
	VI_DLL_EXPORT extern const ProfileAnchorId NominalSizeVerticalUAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId NominalSizeVerticalLAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId NominalSizeHorizontalUAnchorID;
	VI_DLL_EXPORT extern const ProfileAnchorId NominalSizeHorizontalLAnchorID;



class VI_DLL_CLASS_EXPORT Anchor : public GS::Object
{
	DECLARE_CLASS_INFO

public:
	enum class AnchorType {
		Undefined,
		VertexAssociative,
		EdgeAssociative,
		FixedToStretchCanvas,
		BoundBoxUpperLeftCorner,
		BoundBoxUpperRightCorner,
		BoundBoxLowerLeftCorner,
		BoundBoxLowerRightCorner,
		StretchZoneLeft,
		StretchZoneRight,
		StretchZoneBottom,
		StretchZoneTop
	};

private:
	AnchorType					anchorType;
	HatchVertexId				associativeVertexId;
	HatchEdgeId					associativeEdgeId;
	bool						edgePosSideOnRightOfEdge;
	Coord						fixAnchorPosition;

	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

public:
	Anchor (); //undefined!

	const Anchor& SetAssociative (const HatchVertexId& vertID);
	const Anchor& SetAssociative (const HatchEdgeId& edgeID, const bool edgePosSideOnRightOfEdge);
	const Anchor& SetFixed (const Coord& nominalPosition);
	const Anchor& SetFixed (const double x, const double y);

	const Anchor& SetBoundBoxUpperLeftCorner ();
	const Anchor& SetBoundBoxUpperRightCorner ();
	const Anchor& SetBoundBoxLowerLeftCorner ();
	const Anchor& SetBoundBoxLowerRightCorner ();

	const Anchor& SetStretchZoneLeft ();
	const Anchor& SetStretchZoneRight ();
	const Anchor& SetStretchZoneBottom ();
	const Anchor& SetStretchZoneTop ();





	bool operator== (const Anchor& other) const;
	bool operator!= (const Anchor& other) const;

	bool Compare (const Anchor& other) const;
	bool Compare (const Anchor& other, double eps) const;

	GSErrCode WriteForChecksum (GS::OChannel& oc, double eps) const;

	void Transform (const Geometry::Transformation2D& tran);


	const AnchorType&					GetAnchorType () const;
	const HatchVertexId&				GetAssociatedVertexId () const;
	const HatchEdgeId&					GetAssociatedEdgeId () const;
	bool								GetEdgePosSideOnRightOfEdge () const;
	const Coord&						GetFixAnchorPosition () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
			GSErrCode	ReadXML (GS::XMLIChannel& ic);
			GSErrCode	WriteXML (GS::XMLOChannel& oc) const;
};

}

#endif
