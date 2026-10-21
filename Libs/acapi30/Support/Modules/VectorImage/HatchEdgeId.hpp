#ifndef HATCHEDGEID_HPP
#define HATCHEDGEID_HPP

#include "VectorImageExport.h"

// from GSRoot
#include "Object.hpp"

namespace PVI { // ProfileVectorImage

class VI_DLL_CLASS_EXPORT HatchEdgeId : public GS::Object
{
	DECLARE_CLASS_INFO

	GS::Guid			hatchId;
	UIndex				edgeIndex;

	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

public:
	HatchEdgeId ();
	HatchEdgeId (const GS::Guid& inHatchid, UIndex inEdgeIndex);

	bool operator== (const HatchEdgeId& other) const;
	bool operator!= (const HatchEdgeId& other) const;

	const GS::Guid&		GetHatchId () const;
	UIndex				GetEdgeIndex () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
			GSErrCode	ReadXML (GS::XMLIChannel& ic);
			GSErrCode	WriteXML (GS::XMLOChannel& oc) const;

			ULong		GenerateHashValue () const;
};

}

#endif
