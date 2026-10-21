// *********************************************************************************************************************
// Description:		UserDataContainer to store multiple userdata of Modeler::MeshBody and Modeler::Elem.
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	SD
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_USERDATACONTAINER_HPP)
#define GS_MODELER_USERDATACONTAINER_HPP

#include "Model3D/Model3DExport.h"
#include "Model3D/BaseUserData.hpp"

#include "Array.hpp"
#include "Pair.hpp"
#include "Algorithms.hpp"
#include "Cloneable.hpp"


namespace Modeler {

class MODEL3D_DLL_EXPORT UserDataContainer {
private:
	typedef GS::Pair<GS::Guid, GS::Cloneable<BaseUserData>> UserDataContainerElem;
	static const UInt32	UserDataArrayDefaultSize = 1;
	GS::ArrayFB<UserDataContainerElem, UserDataArrayDefaultSize> userDataArray; //Guid alapjan rendezve

	static bool MyLessComparator (const UserDataContainerElem& lElem, const UserDataContainerElem& rElem)
	{
		return lElem.first < rElem.first;
	}

public:
	UserDataContainer () = default;
	UserDataContainer (const UserDataContainer&) = default;
	UserDataContainer (const UserDataContainer& other, const TRANMAT& trafo);
	UserDataContainer (UserDataContainer&&) = default;
	UserDataContainer (UserDataContainer&& other, const TRANMAT& trafo);

	UserDataContainer& operator= (const UserDataContainer&) = default;
	UserDataContainer& operator= (UserDataContainer&&) = default;

	bool operator== (const UserDataContainer& other) const;
	bool operator!= (const UserDataContainer& other) const;

	void					Clear ();
	void					SetUserData (const GS::Guid& guid, const BaseUserData* bodyUserData_in); // nullptr torli
	const BaseUserData*		GetUserData (const GS::Guid& guid) const;
	UIndex					GetSize (void) const;

	void					PutUserDataFromContainer (const UserDataContainer& other);

	ULong					GetUsedBytes		() const;
	ULong					GetHeapUsedBytes	() const;

	GSErrCode				QuickWrite (GS::OChannel& oc) const; //kiirni hany darab van majd a guid-t majd a class guidjat mint bodyban van mar az irogatas
	GSErrCode				QuickRead (GS::IChannel& ic); //visszafele ua. mint bodyban.
	void					PrintAsTestCase (GS::OChannel& oc, const char* iVarName) const;
	void					WriteXML (GS::XMLOChannel& outXML) const;
	void					ReadXML (GS::XMLIChannel& inXML);

};


inline const BaseUserData* UserDataContainer::GetUserData (const GS::Guid& guid) const
{
	UserDataContainerElem uElem (guid, GS::Cloneable<BaseUserData> ());
	GS::ArrayFB<UserDataContainerElem, 1>::ConstFastIterator it = GS::LowerBound (userDataArray.BeginFast (), userDataArray.EndFast (), uElem, MyLessComparator);
	if (it != userDataArray.EndFast () && it->first == guid) {
		return it->second.Get ();
	}

	return nullptr;
}


inline UIndex UserDataContainer::GetSize (void) const
{
	return userDataArray.GetSize ();
}


}

#endif //GS_MODELER_USERDATACONTAINER_HPP
