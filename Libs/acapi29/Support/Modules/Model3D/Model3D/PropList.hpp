// *********************************************************************************************************************
// Description:		PropList.hpp
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

#ifndef PROPLIST_HPP
#define PROPLIST_HPP

#include "GDLPropertyList.hpp"
#include "Model3D/Model3DExport.h"

#include "GDLProc.h"

namespace Modeler {

struct MODEL3D_CPP_DLL_EXPORT PropListUserData
{
	void Write (GS::OChannel&, const GS::ClassVersion&) const;
	void Read (GS::IChannel&, const GS::ClassVersion&);

	void CheckIntegrity () const;

	static const GS::ClassInfo* GetClassInfo ();
};

class MODEL3D_CPP_DLL_EXPORT PropertyList : public GDL::PropertyList<PropListUserData>
{
public:
	PropertyList ();
	PropertyList (const GDLGen::PropertyList& gdlPropList);
};


void GS_FORCE_INLINE PropListUserData::Write (GS::OChannel&, const GS::ClassVersion&) const
{
}

void GS_FORCE_INLINE PropListUserData::CheckIntegrity () const
{
}

GS_FORCE_INLINE PropertyList::PropertyList ()
{
}

GS_FORCE_INLINE PropertyList::PropertyList (const GDLGen::PropertyList& gdlPropList) :
	GDL::PropertyList<PropListUserData> (*reinterpret_cast<const PropertyList*> (&gdlPropList))
{
}

}


#endif
