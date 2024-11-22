#ifndef __CREATIONORDERELEMENTCONTAINER_HPP__
#define __CREATIONORDERELEMENTCONTAINER_HPP__

#include "IAPIPseudoContainer.hpp"
#include "IAPIPseudoIterator.hpp"
#include "IAPIAttributeAdapter.hpp"

#pragma warning (push)
#pragma warning (disable: 4127) // conditional expression is constant

namespace GSAPI {

template <class Iterator>
class CreationOrderElementContainer : public GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem<GSAPI::Element<API_Element>>, API_ElemFilter, Iterator> {
private:
	API_DatabaseInfo currentDBInfo;

private:
    template<class IteratorType, class ElemType>
    void CheckTemplateType (IAPIPseudoIterator<GSAPI::IteratorElem <GSAPI::Element<ElemType>>, IteratorType>*) {}

	API_ElementMemo* GetMemo (const API_Elem_Head& elemHead) const;

public:
    CreationOrderElementContainer (IAPIAttributeAdapterFactory* factory = nullptr);
    virtual ~CreationOrderElementContainer (void);

	typedef typename GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element>>, API_ElemFilter, Iterator>::PseudoIterator PseudoIterator;

	virtual void SetFilter (const API_ElemFilter& filter);

    virtual void GetNext (GSAPI::IteratorElem<GSAPI::Element<API_Element>>& iteratorElem) const;
    virtual PseudoIterator Begin() const;
    virtual const PseudoIterator End() const;
};

}	// namespace GSAPI

template <class Iterator>
GSAPI::CreationOrderElementContainer<Iterator>::CreationOrderElementContainer (IAPIAttributeAdapterFactory* factory /*= nullptr*/) :
	GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element>>, API_ElemFilter, Iterator> (factory)
{
    CheckTemplateType ((Iterator*) nullptr);

	BNFillMemory (&(this->typeFilter), sizeof (this->typeFilter), 1);
	this->typeFilter[API_GroupID] = false;

    ACAPI_DrawOrder_InitCreationOrderTable (&(this->typeFilter));
	ACAPI_Database_GetCurrentDatabase (&currentDBInfo);
}

template <class Iterator>
void GSAPI::CreationOrderElementContainer<Iterator>::SetFilter (const API_ElemFilter& filter)
{
	Copy (this->typeFilter, filter);
	this->typeFilter[API_GroupID] = false;

    ACAPI_DrawOrder_DisposeCreationOrderTable ();
    ACAPI_DrawOrder_InitCreationOrderTable (&(this->typeFilter));
}

template <class Iterator>
GSAPI::CreationOrderElementContainer<Iterator>::~CreationOrderElementContainer (void)
{
    ACAPI_DrawOrder_DisposeCreationOrderTable ();
}

template <class Iterator>
API_ElementMemo* GSAPI::CreationOrderElementContainer<Iterator>::GetMemo (const API_Elem_Head& elemHead) const
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
void GSAPI::CreationOrderElementContainer<Iterator>::GetNext (GSAPI::IteratorElem<GSAPI::Element<API_Element>>& iteratorElem) const
{
	if (iteratorElem.elem.memo != nullptr) {
		ACAPI_DisposeElemMemoHdls (iteratorElem.elem.memo);
		delete (iteratorElem.elem.memo);
		iteratorElem.elem.memo = nullptr;
	}

	API_Guid nextGuid = iteratorElem.elem.element.header.guid;
	bool     hasNext  = false;

	while ((!hasNext) &&
		   (ACAPI_DrawOrder_CreationOrderGetNext (&nextGuid) == NoError))
	{
		GSAPI::Element<API_Element> newElem = {};
		newElem.element.header.guid = nextGuid;
		ACAPI_Element_GetHeader (&newElem.element.header);
		if (newElem.element.header.type != API_ZombieElemID && ACAPI_Element_Get (&newElem.element) == NoError) {
			newElem.elemType = newElem.element.header.type;
			if (newElem.element.header.type != API_GroupID) {
				newElem.memo = GetMemo (newElem.element.header);
				newElem.guid = newElem.element.header.guid;
				iteratorElem.elem = newElem;
			}
			hasNext = true;
		}
	}
	if (!hasNext) {
	    BNZeroMemory (&(iteratorElem.elem), sizeof (iteratorElem.elem)); // End element
	}
}

template <class Iterator>
typename GSAPI::CreationOrderElementContainer<Iterator>::PseudoIterator GSAPI::CreationOrderElementContainer<Iterator>::Begin () const
{
	GSAPI::IteratorElem <GSAPI::Element<API_Element> > iteratorElem;
	BNZeroMemory (&iteratorElem, sizeof (iteratorElem));

	iteratorElem.databaseInfo = currentDBInfo;
	iteratorElem.elem.element.header.guid = APINULLGuid;
    GetNext (iteratorElem);

	GSAPI::IteratorElem <GSAPI::Element<API_Element> > endElem;
	BNZeroMemory (&endElem, sizeof (endElem));
	endElem.databaseInfo = currentDBInfo;

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
const typename GSAPI::CreationOrderElementContainer<Iterator>::PseudoIterator GSAPI::CreationOrderElementContainer<Iterator>::End () const
{
	GSAPI::IteratorElem <GSAPI::Element<API_Element> > iteratorElem;
	BNZeroMemory (&iteratorElem, sizeof (iteratorElem)); // End element

	iteratorElem.databaseInfo = currentDBInfo;
    typename PseudoIterator::Parameters parameters ((*this), iteratorElem, this->attributeFactory);
    return this->CreateIterator (parameters);
}

#pragma warning (pop)

#endif //__CREATIONORDERELEMENTCONTAINER_HPP__
