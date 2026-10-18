#ifndef VERTEXFILLETPARAMETER_HPP
#define VERTEXFILLETPARAMETER_HPP

#include "VectorImageExport.h"
#include "HatchVertexId.hpp"

#ifdef CHAMFER

namespace PVI { // ProfileVectorImage

class VI_DLL_CLASS_EXPORT VertexParameter : public GS::Object
{
	DECLARE_CLASS_INFO

public:
	enum class Type {
		Undefined,
		Fillet,
		Chamfer
	};

private:
	Type			type;
	HatchVertexId	vertexId;
	double			defaultRadius;

	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

public:
	VertexParameter ();
	VertexParameter (Type inType, const HatchVertexId& inVertexId, double inDefaultRadius);

	bool operator== (const VertexParameter& other) const;
	bool operator!= (const VertexParameter& other) const;

	bool Compare (const VertexParameter& other) const;

	Type			GetType () const;
	HatchVertexId	GetHatchVertexId () const;
	double			GetDefaultRadius () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
			GSErrCode	ReadXML (GS::XMLIChannel& ic);
			GSErrCode	WriteXML (GS::XMLOChannel& oc) const;
};

}

#endif // CHAMFER

#endif
