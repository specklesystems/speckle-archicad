#ifndef PROFILEVECTORIMAGEPARAMETER_HPP
#define PROFILEVECTORIMAGEPARAMETER_HPP

#include "VectorImageExport.h"
#include "VectorImageTypedefs.hpp"
#include "EdgeOffsetParameter.hpp"
#include "VertexFilletParameter.hpp"

namespace PVI {

class VI_DLL_CLASS_EXPORT ProfileVectorImageParameter : public GS::Object
{
	DECLARE_CLASS_INFO

public:
	enum class ParameterType  {
		Undefined,
		Vertex,
		EdgeOffset
	};

private:
	ParameterType					type;
	EdgeOffsetParameter				edgeParam;
#ifdef CHAMFER
	VertexParameter					vertexParam;
#endif // CHAMFER

	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

public:
	ProfileVectorImageParameter ();
	ProfileVectorImageParameter (const EdgeOffsetParameter& inEdgeParam);
#ifdef CHAMFER
	ProfileVectorImageParameter (const VertexParameter& inVertexParam);
#endif
	virtual ~ProfileVectorImageParameter ();
	
	bool operator== (const ProfileVectorImageParameter& other) const;
	bool operator!= (const ProfileVectorImageParameter& other) const;

	bool Compare (const ProfileVectorImageParameter& other) const;

	ParameterType					GetType () const;
	const EdgeOffsetParameter&		GetEdgeOffsetParameter () const;
#ifdef CHAMFER
	const VertexParameter&			GetVertexParameter () const;
#endif // CHAMFER

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
	GSErrCode			ReadXML (GS::XMLIChannel& ic);
	GSErrCode			WriteXML (GS::XMLOChannel& oc) const;
};

}

#endif
