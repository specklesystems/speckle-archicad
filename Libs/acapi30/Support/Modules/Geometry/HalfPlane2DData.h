#if !defined (HALFPLANE2DDATA_H)
#define HALFPLANE2DDATA_H

#pragma once

#include "GeometricDefinitions.h"

namespace GS {
	class XMLIChannel;
	class XMLOChannel;
}


struct HalfPlane2DData {
	double		ca;
	double		cb;
	double		cc;				/* ca*x + cb*y > cc => outside		*/

	GSSize		sizeOfInhEdgeInfo;	// The size of ONE inhEdgeInfo struct
	void*		inhEdgeInfo;		// Edge info

	HalfPlane2DData () : ca (0.0), cb (0.0), cc (0.0), sizeOfInhEdgeInfo (0), inhEdgeInfo (nullptr) { /* do nothing */ }
	HalfPlane2DData (double ca, double cb, double cc, GSSize sizeOfInhEdgeInfo = 0, void* inhEdgeInfo = nullptr) :
		ca (ca),
		cb (cb),
		cc (cc),
		sizeOfInhEdgeInfo (sizeOfInhEdgeInfo),
		inhEdgeInfo (inhEdgeInfo)
	{ /* do nothing */ }
};

namespace Geometry {
	GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLHalfPlane2DData (GS::XMLIChannel& ic, HalfPlane2DData& hp);
	GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLHalfPlane2DData (GS::XMLOChannel& oc, const HalfPlane2DData& hp);
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, HalfPlane2DData& hp)	{ return Geometry::ReadXMLHalfPlane2DData (ic, hp); }
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const HalfPlane2DData& hp)	{ return Geometry::WriteXMLHalfPlane2DData  (oc, hp); }
}


#endif
