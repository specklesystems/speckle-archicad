#if !defined(NURBSVERTEXATTRIBUTES_HPP)
#define NURBSVERTEXATTRIBUTES_HPP

#pragma once

#include "Model3D/Model3DExport.h"

namespace GS {
	class XMLIChannel;
	class XMLOChannel;
	class IChannel;
	class OChannel;
}

struct TRANMAT;

namespace Modeler {


class MODEL3D_DLL_EXPORT NurbsVertexAttributes {
public:
	enum class Hardness : GS::UChar {
		Soft,
		Hard	// vertex defines a break in shading
	};
private:
	Hardness hardness;
public:
	NurbsVertexAttributes (Hardness hardnessIn) : hardness (hardnessIn) { /* do nothing*/ }
	NurbsVertexAttributes (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName);  }

	Hardness GetHardness () const { return hardness; }

	bool operator== (const NurbsVertexAttributes& other) const { return hardness == other.hardness; }

	void			Read	(GS::IChannel& ic);			
	void			Write	(GS::OChannel& oc) const;	

	void			WriteXML (GS::XMLOChannel& outXML, const char* tagName)	const;
	void			ReadXML (GS::XMLIChannel& inXML, const char* tagName);
};


}		// namespace Modeler

#endif	// NURBSVERTEXATTRIBUTES_HPP
