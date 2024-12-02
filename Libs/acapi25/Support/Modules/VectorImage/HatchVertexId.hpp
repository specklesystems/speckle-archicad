#ifndef HATCHVERTEXID_HPP
#define HATCHVERTEXID_HPP

#include "VectorImageExport.h"

namespace PVI { // ProfileVectorImage

class VI_DLL_CLASS_EXPORT HatchVertexId : public GS::Object
{
	DECLARE_CLASS_INFO

	GS::Guid	hatchId;
	UIndex		vertexIndex;

	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

public:
	HatchVertexId ();
	HatchVertexId (const GS::Guid& inHatchId, UIndex inVertexIndex);

	bool operator== (const HatchVertexId& other) const;
	bool operator!= (const HatchVertexId& other) const;

	const GS::Guid&		GetHatchId () const;
	UIndex				GetVertexIndex () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
			GSErrCode	ReadXML (GS::XMLIChannel& ic);
			GSErrCode	WriteXML (GS::XMLOChannel& oc) const;

			ULong		GenerateHashValue () const;
};

}

#endif
