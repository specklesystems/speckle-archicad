// *********************************************************************************************************************
// Description:		Inherited edge identifier in elem
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	FAG
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODEL3D_EDGEID_HPP)
#define GS_MODEL3D_EDGEID_HPP

#pragma once


#include "Definitions.hpp"
#include "Model3D/Model3DExport.h"

// from GSRoot
#include	"Channel.hpp"

namespace Modeler {

	class MODEL3D_DLL_EXPORT EdgeId {
	private:
		Int32	val;
	public:
		EdgeId () : val (0)
		{
			static_assert (
				sizeof (EdgeId) == sizeof (val),
				"EdgeId binary layout!"); // The structure should have no padding. It is written as binary from body checksum.
		}
		EdgeId (const Int32& v) : val (v)					{}

		bool			operator== (const EdgeId& rhs) const	{ return val == rhs.val;		}
		bool			operator!= (const EdgeId& rhs) const	{ return !operator== (rhs);		}
		bool			IsUndefined (void) const				{ return val == 0;				}
		EdgeId&			operator++ (void)						{ ++val; return *this;			}

		Int32			GetValue (void) const					{ return val;					}

		ULong			GenerateHashValue () const				{ return val;					}

		GSErrCode		QuickRead (GS::IChannel& ic);
		GSErrCode		QuickWrite (GS::OChannel& oc) const;

		static EdgeId Invalid;
	};

}

#endif
