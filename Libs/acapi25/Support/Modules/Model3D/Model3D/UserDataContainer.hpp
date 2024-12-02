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

#include "Array.hpp"		//ArrayFB
#include "Pair.hpp"			//GS::Pair
#include "Algorithms.hpp"	//FindIf

#include "Model3D/BaseUserData.hpp" //GSUserData

#include "Model3D/Model3DExport.h" //MODEL3D_DLL_EXPORT

namespace Modeler {

class MODEL3D_DLL_EXPORT UserDataContainer : public GS::Object
{
	DECLARE_DYNAMIC_CLASS_INFO (UserDataContainer)
private:
	typedef GS::Pair<GS::Guid, BaseUserData*> UserDataContainerElem;
	static const UInt32	UserDataArrayDefaultSize = 1;
	GS::ArrayFB<UserDataContainerElem, UserDataArrayDefaultSize> userDataArray; //Guid alapjan rendezve

	static bool MyLessComparator (const Modeler::UserDataContainer::UserDataContainerElem& lElem, const Modeler::UserDataContainer::UserDataContainerElem& rElem) {
		return lElem.first < rElem.first;
	}

	class MyEqualsComparator {
	public:
		MyEqualsComparator (const GS::Guid& guid): mGuid (guid) {}
		bool operator () (const UserDataContainerElem& aUserDataContainerElem) {
			return aUserDataContainerElem.first == mGuid;
		}
	private:
		GS::Guid mGuid;
	};

	void CloneAndPushUserDataContainerElem (const UserDataContainerElem& elem);
	void CloneAndPushUserDataContainerElem (const UserDataContainerElem& elem, const TRANMAT& trafo);

public:
	UserDataContainer (void);
	UserDataContainer (const UserDataContainer& other);
	UserDataContainer (const UserDataContainer& other, const TRANMAT& trafo);
	UserDataContainer (UserDataContainer&& other);
	UserDataContainer (UserDataContainer&& other, const TRANMAT& trafo);
	~UserDataContainer (void);
	
	void Clear ();
	void SetUserData (const GS::Guid& guid, const BaseUserData* bodyUserData_in); // nullptr torli
	inline const BaseUserData* GetUserData (const GS::Guid& guid) const;
	inline UIndex GetSize (void) const;

	void PutUserDataFromContainer (const UserDataContainer& other);
	UserDataContainer& operator= (const UserDataContainer& other);
	UserDataContainer& operator= (UserDataContainer&& other);
	bool operator== (const UserDataContainer& other) const;
	bool operator!= (const UserDataContainer& other) const;

	virtual UserDataContainer*	Clone (void) const override;
	virtual UserDataContainer*	Clone (const TRANMAT& trafo) const;

	ULong GenerateHashValue (void) const; //((adattag hash value*prim) + hash value*prim)+ +......mint a unistringnel

	ULong GetUsedBytes		() const;
	ULong GetHeapUsedBytes	() const;

	virtual GSErrCode		QuickWrite (GS::OChannel& oc) const; //kiirni hany darab van majd a guid-t majd a class guidjat mint bodyban van mar az irogatas
	virtual GSErrCode		QuickRead (GS::IChannel& ic); //visszafele ua. mint bodyban.
	virtual void			PrintAsTestCase (GS::OChannel& oc, const char* iVarName)	const;
	virtual void			WriteXML (GS::XMLOChannel& outXML) const;
	virtual void			ReadXML (GS::XMLIChannel& inXML);

};

const BaseUserData* UserDataContainer::GetUserData (const GS::Guid& guid) const
{
	UserDataContainerElem uElem (guid, nullptr);
	GS::ArrayFB<UserDataContainerElem, 1>::ConstIterator it = GS::LowerBound (userDataArray.Begin (), userDataArray.End (), uElem, MyLessComparator);
	if (it != nullptr && it->first == guid) {
		return it->second;
	} else {
		return nullptr;
	}
}

UIndex UserDataContainer::GetSize (void) const
{
	return userDataArray.GetSize ();
}

}

#endif //GS_MODELER_USERDATACONTAINER_HPP

