#ifndef MODSTAMP_HPP
#define MODSTAMP_HPP

#include "Definitions.hpp"
#include "Channel.hpp"
#include "HashCommon.hpp"

#include "Model3D/Model3DExport.h"

namespace Modeler {

class MODEL3D_DLL_EXPORT ModStamp {
private:
	UInt64 val;
	ModStamp (UInt64 val);
public:
	ModStamp ();
	void Generate (void);	
	void Reset (void);
	bool IsZero () const {
		return val == 0;
	}
	bool operator < (const ModStamp& rhs) const {
		return val  < rhs.val;
	}
	bool operator > (const ModStamp& rhs) const {
		return val > rhs.val;
	}
	bool operator == (const ModStamp& rhs) const {
		return val == rhs.val;
	}
	bool operator >= (const ModStamp& rhs) const {
		return val >= rhs.val;
	}
	bool operator <= (const ModStamp& rhs) const {
		return val <= rhs.val;
	}
	bool operator != (const ModStamp& rhs) const {
		return val != rhs.val;
	}
	ULong	GenerateHashValue () const {
		return GS::CalculateHashValue (val);
	}

	GSErrCode	Read	(GS::IChannel& ic);
	GSErrCode	Write	(GS::OChannel& oc) const;

	static ModStamp GetLast ();
	static ModStamp GenerateNew ();
	static ModStamp GetMaxStamp ();
};

}
#endif //MODSTAMP_HPP
