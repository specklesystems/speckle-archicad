// *********************************************************************************************************************
// Description:		Hotspot class
//
// Module:			GSModeler
// Namespace:
// Contact person:	KV
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_HOTSPOT_HPP)
#define GS_MODELER_HOTSPOT_HPP

#pragma once

//from Geometry
#include "TRANMAT.h"

#include "ClassInfo.hpp"
#include "Model3D/Model3DExport.h"

class MODEL3D_DLL_EXPORT HOTS {
	static GS::ClassInfo classInfo;

public:
	double	x, y, z;		/* 24 */
	short	type;			/*  2 */
	short	subtype;		/*  2 */
	UInt32	unID;			/*  4 */

	HOTS	() : x (0.0), y (0.0), z (0.0), type (0), subtype (0), unID (0)
	{
		static_assert (
			sizeof (HOTS) == sizeof (x) + sizeof (y) + sizeof (z) + sizeof (type) + sizeof (subtype) + sizeof (unID),
			"HOTS binary layout!"); // The structure should have no padding. It is written as binary from body checksum.
	}

	void	Transform (const TRANMAT *tran);

	void	WriteXML (GS::XMLOChannel& outXML) const;
	void	ReadXML	 (GS::XMLIChannel& inXML);

	bool	operator== (const HOTS& hotspot) const;
	bool	operator!= (const HOTS& hotspot) const;

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);
	GSErrCode Write (GS::OChannel& oc) const;
	GSErrCode Read (GS::IChannel& ic);
};							/* 32 */

#endif
