#ifndef	GEOMELEMID_HPP
#define	GEOMELEMID_HPP

#pragma once
#include "GSGuid.hpp"
#include "Object.hpp"
#include "HashCommon.hpp"
// from VectorImage
#include "VectorImageExport.h"

class VI_DLL_CLASS_EXPORT GeomElemID : public GS::Object   //edge or vertex ID
{
public:
	GeomElemID (const GS::Guid& hostGUIDInit, const UInt32 elemMarkerInit);
	GeomElemID (const GS::Guid& hostGUIDInit);
	GeomElemID (); 
	virtual ~GeomElemID ();

	GS::Guid				hostGUID;		//host is the polygon/multipolygon/hatch etc...
	UInt32					elemMarker;		//it is Geometry::PolyId. It is a marker, when there exists more than one of it, but gets to be unique by renumbering

	inline bool				operator < (const GeomElemID& rhs) const
	{
		if (hostGUID < rhs.hostGUID) return true;
		if (hostGUID > rhs.hostGUID) return false;
		return elemMarker < rhs.elemMarker;
	}

	inline bool				operator == (const GeomElemID& rhs) const
	{
		return hostGUID == rhs.hostGUID && elemMarker == rhs.elemMarker;
	}

	inline ULong			GenerateHashValue () const
	{
		return hostGUID.GetHashValue () * elemMarker;
	}
};

#endif //GEOMELEMID_HPP
