// *****************************************************************************
// 
//		PolyArcRec struct for polygons and some basic functions
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// [SG compatible]
// *****************************************************************************
// *****************************************************************************
#if !defined (POLYARCREC_H)
#define POLYARCREC_H

#include "GeometricDefinitions.h"

#pragma once


struct GEOMETRY_DLL_EXPORT PolyArcRec {			/* record for polygons' arcs */
	UIndex	begIndex;		/* arc between begIndex, endIndex in poly */
	UIndex	endIndex;		/* endIndex = begIndex + 1, but we like redundancy, anyway aline (!) */
	double	arcAngle;		/* maybe +/- as in Curved Wall */

	PolyArcRec () : begIndex (), endIndex (), arcAngle ()
	{
	}

	PolyArcRec (UIndex begIndex, UIndex endIndex, double arcAngle) : begIndex (begIndex), endIndex (endIndex), arcAngle (arcAngle)
	{
	}

	bool operator== (const PolyArcRec& other) const;
	bool operator!= (const PolyArcRec& other) const;

	GSErrCode Read	(GS::IChannel& ic);
	GSErrCode Write (GS::OChannel& oc) const;

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);
	
};


template <class PolyArcIterator>
inline PolyArcIterator FindArcImp (
			const	PolyArcIterator		begin,
			const	PolyArcIterator		end,
			UIndex						node)
{
	for (PolyArcIterator i = begin; i != end; ++i)
		if (i->begIndex == node && i->endIndex == node + 1)		/* sm311 check endIndex for safety */
			return (i);
	return end;
}

namespace Geometry {

	GEOMETRY_DLL_EXPORT void	IVPolyArc (GS::PlatformSign inplatform,PolyArcRec *paRec);

	GEOMETRY_DLL_EXPORT Int32	FindArc (const	PolyArcRec	*myPolyArcsPtr, USize nArcs, UIndex node);
	inline Int32				FindArc (const GS::Array<PolyArcRec>& arcs, UIndex node) { return FindArc (arcs.GetContent (), arcs.GetSize (), node); }

	GEOMETRY_DLL_EXPORT GSErrCode 	ReadXMLPolyArcRec (GS::XMLIChannel& ic, PolyArcRec& paRec);
	GEOMETRY_DLL_EXPORT GSErrCode 	WriteXMLPolyArcRec (GS::XMLOChannel& oc, const PolyArcRec& paRec);
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, PolyArcRec& paRec)	{ return Geometry::ReadXMLPolyArcRec (ic, paRec); }
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const PolyArcRec& paRec)	{ return Geometry::WriteXMLPolyArcRec (oc, paRec); }
}
	
	
#endif
