// *********************************************************************************************************************
// Description:		Inherited polygon identifier in elem
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	BeA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODEL3D_POLYGONID_HPP)
#define GS_MODEL3D_POLYGONID_HPP

#include "Model3D/Model3DExport.h"

// from GSRoot
#include "Definitions.hpp"
#include "Channel.hpp"

namespace Modeler {

	class MODEL3D_DLL_EXPORT PolygonId {
	public:
		typedef Int32	ValueType;
	private:
		ValueType	val;
	public:
		PolygonId () : val (0)
		{
			static_assert (
				sizeof (PolygonId) == sizeof (val),
				"PolygonId binary layout!"); // The structure should have no padding. It is written as binary from body checksum.
		}
		PolygonId (const ValueType& v) : val (v)					{}

		bool			operator== (const PolygonId& rhs) const		{ return val == rhs.val;		}
		bool			operator!= (const PolygonId& rhs) const		{ return !operator== (rhs);		}
		bool			IsUndefined (void) const					{ return val == 0;				}
		PolygonId&		operator++ (void)							{ ++val; return *this;			}

		ValueType		GetValue (void) const						{ return val;					}

		ULong			GenerateHashValue (void) const				{ return val;					}

		GSErrCode		QuickRead (GS::IChannel& ic);
		GSErrCode		QuickWrite (GS::OChannel& oc) const;

		static const PolygonId Invalid;
	};

}

#endif
