// *********************************************************************************************************************
// Description:		Inherited vertex identifier in elem
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	BeA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODEL3D_VERTEXID_HPP)
#define GS_MODEL3D_VERTEXID_HPP

#pragma once


#include "Definitions.hpp"
#include "Model3D/Model3DExport.h"

// from GSRoot
#include	"Channel.hpp"

namespace Modeler {

	class MODEL3D_DLL_EXPORT VertexId {
	private:
		Int32	val;
	public:
		VertexId () : val (0)
		{
			static_assert (
			sizeof (VertexId) == sizeof (val),
			"VertexId binary layout!"); // The structure should have no padding. It is written as binary from body checksum.
		}
		VertexId (const Int32& v) : val (v)					{}

		bool			operator== (const VertexId& rhs) const	{ return val == rhs.val;	}
		bool			operator!= (const VertexId& rhs) const  { return !operator== (rhs); }
		bool			IsUndefined (void) const				{ return val == 0;			}
		VertexId&		operator++ (void)						{ ++val; return *this;		}

		Int32			GetValue (void) const					{ return val;				}
		ULong			GenerateHashValue () const				{ return val;				}

		GSErrCode		QuickRead (GS::IChannel& ic);
		GSErrCode		QuickWrite (GS::OChannel& oc) const;

		static VertexId Invalid;
	};

}

#endif
