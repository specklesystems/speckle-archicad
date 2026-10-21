#ifndef EDGEOFFSETPARAMETER_HPP
#define EDGEOFFSETPARAMETER_HPP

#include "AssociatedEdgeId.hpp"

#include "VectorImageExport.h"
#include "VectorImageTypedefs.hpp"

namespace PVI { // ProfileVectorImage
	
class VI_DLL_CLASS_EXPORT EdgeOffsetParameter : public GS::Object
{
	DECLARE_CLASS_INFO

private:
	GS::Array<AssociatedEdge>	associatedEdges;
	ProfileDimControlToolId		dimControlId;


	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

public:
	EdgeOffsetParameter ();

	bool operator== (const EdgeOffsetParameter& other) const;
	bool operator!= (const EdgeOffsetParameter& other) const;

	bool Compare (const EdgeOffsetParameter& other) const;

	void								SetDimControlToolID (const ProfileDimControlToolId& dimControlIdInit);
	const ProfileDimControlToolId& 		GetDimControlToolID () const;

	void								AddAssociatedEdge (const AssociatedEdge& edgeToAdd);
	void								AddAssociatedEdges (const GS::Array<AssociatedEdge>& edgesToAdd);
	const GS::Array<AssociatedEdge>&	GetAssociatedEdges () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
			GSErrCode	ReadXML (GS::XMLIChannel& ic);
			GSErrCode	WriteXML (GS::XMLOChannel& oc) const;

};

}

#endif
