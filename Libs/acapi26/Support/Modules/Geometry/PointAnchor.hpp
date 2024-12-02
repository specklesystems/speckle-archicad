#ifndef GEOM_PPE_POINTANCHOR_HPP
#define GEOM_PPE_POINTANCHOR_HPP
#pragma once

#include "GeometricDefinitions.h"
#include "ModelIDs.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class AnchorType
{
	AssociatedToVertex,
	AssociatedToEdge,		//GeneralAnchor Only!
	AssocToBBox_LL,
	AssocToBBox_UL,
	AssocToBBox_UR,
	AssocToBBox_LR,
	FixedPoint,
	Undefined
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT PointAnchor
{
public:
	PointAnchor ();

	virtual AnchorType GetType () const;
	VertexIDType GetVertID () const;
	void GetFixedPoint (double& fixedPointXRetVal, double& fixedPointYRetVal) const;

	static PointAnchor CreateAssociatedAnchor (const VertexIDType vertIDInit);
	static PointAnchor CreateFixedAnchor (const double fixedPointXInit, const double fixedPointYInit);
	static PointAnchor CreateBBoxLLAnchor ();
	static PointAnchor CreateBBoxULAnchor ();
	static PointAnchor CreateBBoxURAnchor ();
	static PointAnchor CreateBBoxLRAnchor ();

protected:
	PointAnchor (AnchorType typeInit);

	AnchorType m_type;

	VertexIDType vertID;		//AssociatedToVertex

	double fixedPointX;			//FixedPoint
	double fixedPointY;			//FixedPoint
};



#endif //GEOM_PPE_POINTANCHOR_HPP

