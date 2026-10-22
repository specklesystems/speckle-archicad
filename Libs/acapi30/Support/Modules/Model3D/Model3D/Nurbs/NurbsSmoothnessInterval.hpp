#if !defined(NURBSSMOOTHNESSINTERVAL_HPP)
#define NURBSSMOOTHNESSINTERVAL_HPP

#pragma once

#include "Model3D/Model3DExport.h"

#include "ClassInfo.hpp"

namespace GS {
	class XMLIChannel;
	class XMLOChannel;
	class IChannel;
	class OChannel;
}


namespace Modeler {


class MODEL3D_DLL_EXPORT NurbsSmoothnessInterval {
	static	GS::ClassInfo	classInfo;

	double lowerLimit;
	double upperLimit;

	void ReadVersion1(GS::IChannel &ic);
	void WriteVersion1(GS::OChannel &oc) const;
public:
	static const double Min;	// = 0.0
	static const double Max;	// = 1.0

	NurbsSmoothnessInterval () : lowerLimit (Min), upperLimit (Max) { /* do nothing */ }
	NurbsSmoothnessInterval (double b, double e);

	double GetLowerLimit () const { return lowerLimit; }
	double GetUpperLimit () const { return upperLimit; }

	bool operator== (const NurbsSmoothnessInterval& other) const {
		return lowerLimit == other.lowerLimit && upperLimit == other.upperLimit;
	}
	bool operator!= (const NurbsSmoothnessInterval& other) const {
		return !operator== (other);
	}

	void QuickRead	(GS::IChannel& ic);			// no version, no check
	void QuickWrite	(GS::OChannel& oc) const;	// no version, no check
	void Read		(GS::IChannel& ic);
	void Write		(GS::OChannel& oc) const;
	void ReadXML	(GS::XMLIChannel& inXML, const char* xmlTagName);
	void WriteXML	(GS::XMLOChannel& outXML, const char* xmlTagName) const;
};


}	// namespace Modeler


#endif	// NURBSSMOOTHNESSINTERVAL_HPP
