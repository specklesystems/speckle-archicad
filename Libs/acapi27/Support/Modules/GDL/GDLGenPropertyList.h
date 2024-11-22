#ifndef	_GDLGenPropertyList_H_
#define _GDLGenPropertyList_H_

#include	"GDLExport.h"
#include	"GDLPropertyList.hpp"

namespace GDLGen {

struct GDL_DLL_EXPORT PropListUserData
{
	void Write (GS::OChannel&, const GS::ClassVersion&) const;
	void Read (GS::IChannel&, const GS::ClassVersion&) const;

	void CheckIntegrity () const;

	static const GS::ClassInfo* GetClassInfo ();
};

class GDL_DLL_EXPORT PropertyList : public GDL::PropertyList<PropListUserData>
{
};

void GS_FORCE_INLINE PropListUserData::Write (GS::OChannel&, const GS::ClassVersion&) const
{
}

void GS_FORCE_INLINE PropListUserData::CheckIntegrity () const
{
}

}

#endif
