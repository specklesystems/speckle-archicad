// *********************************************************************************************************************
// Description:		GDLPropertyList.hpp
//
// Module:			GDL
// Namespace:		GDL
// Contact person:	HK
//
// *********************************************************************************************************************

#ifndef GDLPROPERTYLIST_HPP
#define GDLPROPERTYLIST_HPP

#include "GDLParamTypes.hpp"
#include "PropertyList.hpp"


namespace GDL {

template<class UserDataType>
class PropertyList : public GS::PropertyList<UserDataType>
{
public:
	void Create (ULong nr);

	GDL::Parameters WriteToParameters () const;
	void ReadFromParameters (const GDL::ParameterGetter& addPar);
};

}


#include "GDLPropertyListImp.hpp"

#endif
