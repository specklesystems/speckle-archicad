#ifndef ASSOCIATEDEDGEID_HPP
#define ASSOCIATEDEDGEID_HPP

#include "VectorImageExport.h"
#include "HatchEdgeId.hpp"

// from GSRoot
#include "Object.hpp"

namespace PVI { // ProfileVectorImage
	
class VI_DLL_CLASS_EXPORT AssociatedEdge : public GS::Object
{
	DECLARE_CLASS_INFO

public:
	enum class DirectionFlag {
		Left,
		Right
	};

private:
	HatchEdgeId		hatchEdgeId;
	DirectionFlag	dirFlag;

	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

public:
	AssociatedEdge ();
	AssociatedEdge (HatchEdgeId inHatchEdgeId, DirectionFlag inDirFlag);
	bool operator== (const AssociatedEdge& other) const;
	bool operator!= (const AssociatedEdge& other) const;

	const GS::Guid&			GetHatchId () const;
	UIndex					GetEdgeIndex () const;
	DirectionFlag			GetDirectionFlag () const;
	const HatchEdgeId&		GetHatchEdgeId () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
			GSErrCode	ReadXML (GS::XMLIChannel& ic);
			GSErrCode	WriteXML (GS::XMLOChannel& oc) const;
};

}

#endif
