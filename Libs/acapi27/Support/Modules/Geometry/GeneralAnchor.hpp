#ifndef GEOM_PPE_GENERALANCHOR_HPP
#define GEOM_PPE_GENERALANCHOR_HPP
#pragma once

#include "PointAnchor.hpp"

#include "GeometricDefinitions.h"
#include "ModelIDs.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT GeneralAnchor : public PointAnchor
{
public:
	GeneralAnchor ();
	GeneralAnchor (const PointAnchor& src); 

	virtual AnchorType GetType () const override final;

	EdgeIDType	GetEdgeID () const;
	bool		IsEdgePosSideOnRightOfEdge () const;

	static GeneralAnchor CreateAssociatedAnchor (const EdgeIDType edgeIDInit, const bool edgePosSideOnRightOfEdgeInit);

private:
	EdgeIDType edgeID;					//AssociatedToEdge
	bool edgePosSideOnRightOfEdge;		//and in this association the edge has a pos side on right if true.
};



#endif //GEOM_PPE_GENERALANCHOR_HPP

