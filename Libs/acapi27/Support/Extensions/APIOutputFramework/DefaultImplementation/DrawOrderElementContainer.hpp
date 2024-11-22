#ifndef __DRAWORDERELEMENTCONTAINER_HPP__
#define __DRAWORDERELEMENTCONTAINER_HPP__

#include "IAPIPseudoContainer.hpp"
#include "IAPIPseudoIterator.hpp"
#include "IAPIAttributeAdapter.hpp"

#pragma warning (push)
#pragma warning (disable: 4127) // conditional expression is constant

namespace GSAPI {

template <class Iterator>
class DrawOrderElementContainer : public GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, Iterator>
{
private:
	API_DatabaseInfo	currentDBInfo;
	mutable bool		drawOrderNeedTerm;

private:
	template<class IteratorType, class ElemType>
    void CheckTemplateType (IAPIPseudoIterator<GSAPI::IteratorElem <GSAPI::Element<ElemType> >, IteratorType>*) {}

	API_ElementMemo* GetMemo (const API_Elem_Head& elemHead) const;

public:
    DrawOrderElementContainer (IAPIAttributeAdapterFactory* factory = nullptr);
	~DrawOrderElementContainer ();

	typedef typename GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, Iterator>::PseudoIterator PseudoIterator;

	virtual void GetNext (GSAPI::IteratorElem <GSAPI::Element<API_Element> >& iteratorElem) const;
    virtual PseudoIterator Begin() const;
    virtual const PseudoIterator End() const;
};

}

template <class Iterator>
GSAPI::DrawOrderElementContainer<Iterator>::DrawOrderElementContainer (GSAPI::IAPIAttributeAdapterFactory* factory /*= nullptr*/) :
	GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, Iterator> (factory)
{
	CheckTemplateType ((Iterator*) nullptr);

	BNFillMemory (&(this->typeFilter), sizeof (this->typeFilter), 1);
	this->typeFilter[API_GroupID] = false;

	ACAPI_Database_GetCurrentDatabase (&currentDBInfo);

	drawOrderNeedTerm = false;
}

template <class Iterator>
GSAPI::DrawOrderElementContainer<Iterator>::~DrawOrderElementContainer ()
{
	if (drawOrderNeedTerm)
		ACAPI_DrawOrder_DrawOrderTerm ();
}

template <class Iterator>
API_ElementMemo* GSAPI::DrawOrderElementContainer<Iterator>::GetMemo (const API_Elem_Head& elemHead) const
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
void GSAPI::DrawOrderElementContainer<Iterator>::GetNext (GSAPI::IteratorElem <GSAPI::Element<API_Element> >& iteratorElem) const
{
	if (iteratorElem.elem.memo != nullptr) {
		ACAPI_DisposeElemMemoHdls (iteratorElem.elem.memo);
		delete (iteratorElem.elem.memo);
		iteratorElem.elem.memo = nullptr;
	}

    bool elemFound = false;
    API_Elem_Head elemHead;
    BNZeroMemory (&elemHead, sizeof (API_Elem_Head));
    elemHead = iteratorElem.elem.element.header;

	while (!elemFound) {
		if (elemHead.type == API_WallID) {
			if (this->typeFilter[API_WindowID] && (iteratorElem.elem.element.wall.hasWindow)) {
				API_ElementMemo wallMemo;
				BNZeroMemory (&wallMemo, sizeof (API_ElementMemo));
				GSErrCode memoErr = ACAPI_Element_GetMemo (iteratorElem.elem.element.header.guid, &wallMemo, APIMemoMask_WallWindows);
				if (memoErr == NoError && wallMemo.wallWindows != nullptr) {
					GSAPI::Element<API_Element> newElem;
					BNZeroMemory (&newElem, sizeof (newElem));
					newElem.element.header.guid = wallMemo.wallWindows[0];
					if (ACAPI_Element_Get (&(newElem.element)) == NoError) {
						newElem.elemType = newElem.element.header.type;
						newElem.guid = newElem.element.header.guid;
						newElem.memo = GetMemo (newElem.element.header);
						iteratorElem.elem = newElem;
						elemFound = true;
					}
				}
				ACAPI_DisposeElemMemoHdls (&wallMemo);
			}
			if (!elemFound && this->typeFilter[API_DoorID] && (iteratorElem.elem.element.wall.hasDoor)) {
				API_ElementMemo wallMemo;
				BNZeroMemory (&wallMemo, sizeof (API_ElementMemo));
				GSErrCode memoErr = ACAPI_Element_GetMemo (iteratorElem.elem.element.header.guid, &wallMemo, APIMemoMask_WallDoors);
				if (memoErr == NoError && wallMemo.wallDoors != nullptr) {
					GSAPI::Element<API_Element> newElem;
					BNZeroMemory (&newElem, sizeof (newElem));
					newElem.element.header.guid = wallMemo.wallDoors[0];
					if (ACAPI_Element_Get (&(newElem.element)) == NoError) {
						newElem.elemType = newElem.element.header.type;
						newElem.guid = newElem.element.header.guid;
						newElem.memo = GetMemo (newElem.element.header);
						iteratorElem.elem = newElem;
						elemFound = true;
					}
				}
				ACAPI_DisposeElemMemoHdls (&wallMemo);
			}
		} else if (elemHead.type == API_WindowID) {
			API_ElementMemo wallMemo;													// search for the next window
			BNZeroMemory (&wallMemo, sizeof (API_ElementMemo));
			GSErrCode memoErr = ACAPI_Element_GetMemo (iteratorElem.elem.element.window.owner, &wallMemo, APIMemoMask_WallWindows | APIMemoMask_WallDoors);
			if (memoErr == NoError) {
				if (wallMemo.wallWindows != nullptr) {
					GSSize windNum = BMGetPtrSize (reinterpret_cast<GSPtr> (wallMemo.wallWindows))  / sizeof (API_Guid);
					GSIndex ind = 0;
					while (ind < windNum) {
						// when it first arrives here, index 0 should have already been processed
						if (iteratorElem.elem.element.header.guid == wallMemo.wallWindows[ind++])
							break;
					}
					if (ind < windNum) {
						GSAPI::Element<API_Element> newElem;
						BNZeroMemory (&newElem, sizeof (newElem));
						newElem.element.header.type = API_WindowID;
						newElem.element.header.guid = wallMemo.wallWindows[ind];		// next window found
						if (ACAPI_Element_Get (&(newElem.element)) == NoError) {
							newElem.elemType = newElem.element.header.type;
							newElem.guid = newElem.element.header.guid;
							newElem.memo = GetMemo (newElem.element.header);
							iteratorElem.elem = newElem;
							elemFound = true;
						}
					}
				}
				if (!elemFound && wallMemo.wallDoors != nullptr) {
					if (BMGetPtrSize (reinterpret_cast<GSPtr> (wallMemo.wallDoors)) >= sizeof (API_Guid)) {
						GSAPI::Element<API_Element> newElem;
						BNZeroMemory (&newElem, sizeof (newElem));
						newElem.element.header.type = API_DoorID;
						newElem.element.header.guid = wallMemo.wallDoors[0];			// continue with the first door
						if (ACAPI_Element_Get (&(newElem.element)) == NoError) {
							newElem.elemType = newElem.element.header.type;
							newElem.guid = newElem.element.header.guid;
							newElem.memo = GetMemo (newElem.element.header);
							iteratorElem.elem = newElem;
							elemFound = true;
						}
						ACAPI_DisposeElemMemoHdls (&wallMemo);
						break;
					}
				}
			}
			if (!elemFound) {															// if no more windows, back to parent wall and continue from there
				API_Element parentWall;
				BNZeroMemory (&parentWall, sizeof (parentWall));
				parentWall.header.type = API_WallID;
				parentWall.header.guid = iteratorElem.elem.element.window.owner;
				if (ACAPI_Element_Get (&parentWall) == NoError) {
					elemHead = parentWall.header;
				}
			}
			ACAPI_DisposeElemMemoHdls (&wallMemo);
		} else if (elemHead.type == API_DoorID) {
			API_ElementMemo wallMemo;													// search for the next door
			BNZeroMemory (&wallMemo, sizeof (API_ElementMemo));
			GSErrCode memoErr = ACAPI_Element_GetMemo (iteratorElem.elem.element.door.owner, &wallMemo, APIMemoMask_WallDoors);
			if (memoErr == NoError) {
				if (wallMemo.wallDoors != nullptr) {
					GSSize doorNum = BMGetPtrSize (reinterpret_cast<GSPtr> (wallMemo.wallDoors))  / sizeof (API_Guid);
					GSIndex ind = 0;
					while (ind < doorNum) {
						// when it first arrives here, index 0 should have already been processed
						if (iteratorElem.elem.element.header.guid == wallMemo.wallDoors[ind++])
							break;
					}
					if (ind < doorNum) {
						GSAPI::Element<API_Element> newElem;
						BNZeroMemory (&newElem, sizeof (newElem));
						newElem.element.header.type = API_DoorID;
						newElem.element.header.guid = wallMemo.wallDoors[ind];	// next door found
						if (ACAPI_Element_Get (&(newElem.element)) == NoError) {
							newElem.elemType = newElem.element.header.type;
							newElem.guid = newElem.element.header.guid;
							newElem.memo = GetMemo (newElem.element.header);
							iteratorElem.elem = newElem;
							elemFound = true;
						}
					}
				}
			}
			if (!elemFound) {															// if no more doors, back to parent wall and continue from there
				API_Element parentWall;
				BNZeroMemory (&parentWall, sizeof (parentWall));
				parentWall.header.type = API_WallID;
				parentWall.header.guid = iteratorElem.elem.element.door.owner;
				if (ACAPI_Element_Get (&parentWall) == NoError) {
					elemHead = parentWall.header;
				}
			}
			ACAPI_DisposeElemMemoHdls (&wallMemo);
		}

		if (!elemFound) {
			if (ACAPI_DrawOrder_DrawOrderGetNext (0, &elemHead) != NoError) {
				BNZeroMemory (&iteratorElem.elem, sizeof (iteratorElem.elem)); // End element
				break;
			}

			if (this->typeFilter[elemHead.type.typeID]) {
				GSAPI::Element<API_Element> newElem;
				BNZeroMemory (&newElem, sizeof (newElem));
				newElem.element.header.guid = elemHead.guid;
				if (ACAPI_Element_Get (&newElem.element) == NoError) {
					newElem.elemType = newElem.element.header.type;
					newElem.guid = newElem.element.header.guid;
					newElem.memo = GetMemo (newElem.element.header);
					iteratorElem.elem = newElem;
					elemFound = true;
				}
			}
		}
    }
}

template <class Iterator>
typename GSAPI::DrawOrderElementContainer<Iterator>::PseudoIterator GSAPI::DrawOrderElementContainer<Iterator>::Begin () const
{
	GSAPI::IteratorElem <GSAPI::Element<API_Element> > iteratorElem;
	BNZeroMemory (&iteratorElem, sizeof (iteratorElem));

	GSErrCode err = NoError;
	if (drawOrderNeedTerm) {
		err = ACAPI_DrawOrder_DrawOrderTerm ();
		if (err == NoError)
			drawOrderNeedTerm = false;
	}
	DBASSERT (err == NoError);
    if (ACAPI_DrawOrder_DrawOrderInit () == NoError)
		drawOrderNeedTerm = true;
	iteratorElem.databaseInfo = currentDBInfo;
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
const typename GSAPI::DrawOrderElementContainer<Iterator>::PseudoIterator GSAPI::DrawOrderElementContainer<Iterator>::End () const
{
	GSAPI::IteratorElem <GSAPI::Element<API_Element> > iteratorElem;
	BNZeroMemory (&iteratorElem, sizeof (iteratorElem)); // End element

	iteratorElem.databaseInfo = currentDBInfo;
    typename PseudoIterator::Parameters parameters ((*this), iteratorElem, this->attributeFactory);
    return this->CreateIterator (parameters);
}

#pragma warning (pop)

#endif //__DRAWORDERELEMENTCONTAINER_HPP__
