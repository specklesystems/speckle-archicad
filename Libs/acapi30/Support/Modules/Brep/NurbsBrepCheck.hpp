#ifndef NURBS_BREP_CHECK_HPP
#define NURBS_BREP_CHECK_HPP

#pragma once

#include	"BrepExport.hpp"

namespace Brep
{

// ---------------------------------------------------------------------------------------------------------------------
// Tells if certain kinds of checks need to be performed on a body.
// ---------------------------------------------------------------------------------------------------------------------
struct BREP_DLL_EXPORT NurbsBrepCheckControl {
	bool checkIndices : 1;
	bool checkBackRefs : 1;
	bool checkTopology : 1;
	bool checkGeometry : 1;
	bool checkDoubleClass : 1;
	bool checkTrimParameterCurveValidity : 1;

	NurbsBrepCheckControl ();
	NurbsBrepCheckControl IndicesOn () const;
	NurbsBrepCheckControl IndicesOff () const;
	NurbsBrepCheckControl BackRefsOn () const;
	NurbsBrepCheckControl BackRefsOff () const;
	NurbsBrepCheckControl TopologyOn () const;
	NurbsBrepCheckControl TopologyOff () const;
	NurbsBrepCheckControl GeometryOn () const;
	NurbsBrepCheckControl GeometryOff () const;
	NurbsBrepCheckControl DoubleClassOn () const;
	NurbsBrepCheckControl DoubleClassOff () const;
	NurbsBrepCheckControl CheckTrimParameterCurveValidityOn () const;
	NurbsBrepCheckControl CheckTrimParameterCurveValidityOff () const;

	static NurbsBrepCheckControl All ();

	bool Includes (const NurbsBrepCheckControl& other) const;

};

} // namespace Brep


#endif // NURBS_BREP_CHECK_HPP