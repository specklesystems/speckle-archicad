#ifndef __INDEXEDELEMENTCONTAINER_HPP__
#define __INDEXEDELEMENTCONTAINER_HPP__

#include "IAPIPseudoContainer.hpp"
#include "IAPIPseudoIterator.hpp"
#include "IAPIAttributeAdapter.hpp"

#pragma warning (push)
#pragma warning (disable: 4127) // conditional expression is constant

namespace GSAPI {

template <class Iterator>
class IndexedElementContainer : public GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, Iterator>
{
private:
    UInt32	 typeCounters[API_LastElemType + 1];
	GS::HashTable<Int32, GS::Array<API_Guid> > elemSet;
	API_DatabaseInfo currentDBInfo;
	mutable UInt32	 currentIndex;

private:
    template<class IteratorType, class ElemType>
    void CheckTemplateType (IAPIPseudoIterator<GSAPI::IteratorElem <GSAPI::Element<ElemType> >, IteratorType>*) {}

	API_ElementMemo* GetMemo (const API_Elem_Head& elemHead) const;

public:
    IndexedElementContainer (IAPIAttributeAdapterFactory* factory = nullptr);

	typedef typename GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, Iterator>::PseudoIterator	PseudoIterator;

	virtual void SetFilter (const API_ElemFilter& filter);

    virtual void GetNext (GSAPI::IteratorElem <GSAPI::Element<API_Element> >& iteratorElem) const;
    virtual PseudoIterator Begin () const;
    virtual const PseudoIterator End () const;
};

}

template <class Iterator>
GSAPI::IndexedElementContainer<Iterator>::IndexedElementContainer (GSAPI::IAPIAttributeAdapterFactory* factory /*= nullptr*/) :
	GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element>>, API_ElemFilter, Iterator> (factory)
{
	CheckTemplateType ((Iterator*) nullptr);

	BNZeroMemory (&(this->typeFilter), sizeof (this->typeFilter));
	BNZeroMemory (typeCounters, sizeof (typeCounters));

    for (API_ElemTypeID typeID = API_FirstElemType; typeID <= API_LastElemType; typeID = static_cast<API_ElemTypeID> (static_cast<int> (typeID) + 1)) {
    	if (typeID == API_GroupID)
    		continue;

        UInt32 count = 0;

		GS::Array<API_Guid>  elemList;
		if (ACAPI_Element_GetElemList (typeID, &elemList) == NoError) {
			count = elemList.GetSize ();
			elemSet.Add (typeID, elemList);
		}

        typeCounters[static_cast<UInt32> (typeID)] = count;
        typeCounters[0] += count;

		this->typeFilter[typeID] = true;
	}

	currentIndex = 0;

	ACAPI_Database_GetCurrentDatabase (&currentDBInfo);
}

template <class Iterator>
void GSAPI::IndexedElementContainer<Iterator>::SetFilter (const API_ElemFilter& filter)
{
	Copy (this->typeFilter, filter);
	this->typeFilter[API_GroupID] = false;

	BNZeroMemory (typeCounters, sizeof (typeCounters));
	for (API_ElemTypeID typeID = API_FirstElemType; typeID <= API_LastElemType; typeID = static_cast<API_ElemTypeID> (static_cast<int> (typeID) + 1)) {
		if (!this->typeFilter[typeID]) {
			continue;
		}

		Int32 count = 0;
        GS::Array<API_Guid>  elemList;
		if (ACAPI_Element_GetElemList (typeID, &elemList) == NoError) {
			count = elemList.GetSize ();
			elemSet.Add (typeID, elemList);
		}

        typeCounters[static_cast<UInt32> (typeID)] = count;
        typeCounters[0] += count;
    }

	currentIndex = 0;
}

template <class Iterator>
API_ElementMemo* GSAPI::IndexedElementContainer<Iterator>::GetMemo (const API_Elem_Head& elemHead) const
{
	API_ElementMemo* memo = nullptr;
	if (elemHead.hasMemo) {
		memo = new API_ElementMemo;
		BNZeroMemory (memo, sizeof (API_ElementMemo));

		GSErrCode memoErr = ACAPI_Element_GetMemo (elemHead.guid, memo);
		if (memoErr != NoError) {
			delete memo;
			memo = nullptr;
		}
	}
	return memo;
}

template <class Iterator>
void GSAPI::IndexedElementContainer<Iterator>::GetNext (GSAPI::IteratorElem <GSAPI::Element<API_Element>>& iteratorElem) const
{
	if (iteratorElem.elem.memo != nullptr) {
		ACAPI_DisposeElemMemoHdls (iteratorElem.elem.memo);
		delete (iteratorElem.elem.memo);
		iteratorElem.elem.memo = nullptr;
	}

	API_ElemTypeID currentType  = iteratorElem.elem.element.header.type.typeID;

	while ((currentType <= API_LastElemType) && (typeCounters[currentType] == 0 || currentIndex >= typeCounters[currentType])) {
		currentType = static_cast<API_ElemTypeID> (static_cast<int> (currentType) + 1);
		currentIndex = 0;
	}

	if (currentType > API_LastElemType) {
		BNZeroMemory (&iteratorElem.elem, sizeof (iteratorElem.elem)); // End element
		return;
	}

	GSAPI::Element<API_Element> newElem;
	BNZeroMemory (&newElem, sizeof (newElem));
	newElem.element.header.type = currentType;
	newElem.element.header.guid = elemSet.Get (currentType)[currentIndex];
	if (ACAPI_Element_Get (&newElem.element) == NoError) {
		newElem.elemType = currentType;
		newElem.guid = newElem.element.header.guid;
		newElem.memo = GetMemo (newElem.element.header);
		iteratorElem.elem = newElem;
	}

	currentIndex++;
}

template <class Iterator>
typename GSAPI::IndexedElementContainer<Iterator>::PseudoIterator GSAPI::IndexedElementContainer<Iterator>::Begin () const
{
	GSAPI::IteratorElem <GSAPI::Element<API_Element> > iteratorElem;
	BNZeroMemory (&iteratorElem, sizeof (iteratorElem));

	iteratorElem.databaseInfo = currentDBInfo;
	iteratorElem.elem.element.header.type.typeID = API_FirstElemType;
	currentIndex = 0;
	GetNext (iteratorElem);

	GSAPI::IteratorElem <GSAPI::Element<API_Element> > endElem;
	BNZeroMemory (&endElem, sizeof (endElem));

	// if not end element cache its attributes
	if ((BNCompareMemory (&iteratorElem, &endElem, sizeof (endElem)) != 0) && (this->attributeFactory != nullptr)) {
		GSAPI::IAPIAttributeAdapterBase* adapter = this->attributeFactory->GetTypeAdapter (iteratorElem.elem.element, iteratorElem.databaseInfo, iteratorElem.elem.memo);
		adapter->CacheAttributes ();
		if (!(this->attributeFactory->GetManagedAdapters ())) {
			delete (adapter);
		}
	}

	typename PseudoIterator::Parameters parameters ((*this), iteratorElem, this->attributeFactory);
    return this->CreateIterator (parameters);
}

template <class Iterator>
const typename GSAPI::IndexedElementContainer<Iterator>::PseudoIterator GSAPI::IndexedElementContainer<Iterator>::End () const
{
	GSAPI::IteratorElem <GSAPI::Element<API_Element> > iteratorElem;
	BNZeroMemory (&iteratorElem, sizeof (iteratorElem)); // End element

	iteratorElem.databaseInfo = currentDBInfo;
    typename PseudoIterator::Parameters parameters ((*this), iteratorElem, this->attributeFactory);
    return this->CreateIterator (parameters);
}

#pragma warning (pop)

#endif //__INDEXEDELEMENTCONTAINER_HPP__
