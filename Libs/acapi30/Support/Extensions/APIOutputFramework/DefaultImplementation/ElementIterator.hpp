#ifndef __ELEMENTITERATOR_HPP__
#define __ELEMENTITERATOR_HPP__

#include "IAPIPseudoIterator.hpp"
#include "IAPIPseudoContainer.hpp"
#include "IAPIAttributeAdapter.hpp"
#include "IAPIAttributeAdapterFactory.hpp"
#include "APIdefs_Elements.h"

namespace GSAPI {

class ElementIterator : public IAPIPseudoIterator<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, ElementIterator> {

	friend class GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, ElementIterator>;

public:
	class Parameters {

		friend class GSAPI::ElementIterator;

	private:
		const GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, ElementIterator>& container;
		GSAPI::IteratorElem <GSAPI::Element<API_Element> >                                                                     currentElement;
		IAPIAttributeAdapterFactory*                                                                                           attributeFactory;

	public:
		Parameters (const GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, ElementIterator>& pseudoContainer,
					const GSAPI::IteratorElem <GSAPI::Element<API_Element> >&                                                              element,
					IAPIAttributeAdapterFactory*                                                                                           factory = nullptr) :
			container (pseudoContainer),
			currentElement (element),
			attributeFactory (factory) {}

		Parameters (const Parameters&) = default;

		Parameters& operator= (const Parameters&) = delete;
	};

private:
    Parameters parameters;

protected:
	ElementIterator (const Parameters& params) : parameters (params) {}

public:
			ElementIterator (const ElementIterator& it) : parameters (it.parameters) {}
	virtual ~ElementIterator ();

	ElementIterator& operator= (const ElementIterator&) = delete;

	virtual ElementIterator& operator++ () override;
	virtual ElementIterator operator++ (int)  override { ElementIterator temp = *this; ++(*this); return temp; }

    virtual bool operator== (const ElementIterator& it) const override;
	virtual bool operator!= (const ElementIterator& it) const  override { return (!((*this)==it)); }

	virtual const GSAPI::IteratorElem <GSAPI::Element<API_Element> >* operator-> ()  override { return &(parameters.currentElement); }
	virtual const GSAPI::IteratorElem <GSAPI::Element<API_Element> >& operator* ()   override { return parameters.currentElement; }
};

}


inline bool GSAPI::ElementIterator::operator== (const GSAPI::ElementIterator& it) const
{
    if (((&(it.parameters.container)) == (&((*this).parameters.container))) &&
        (it.parameters.currentElement.elem.elemType == (*this).parameters.currentElement.elem.elemType) &&
        (it.parameters.currentElement.elem.guid == (*this).parameters.currentElement.elem.guid))
    {
        return true;
    } else {
        return false;
    }
}

inline GSAPI::ElementIterator& GSAPI::ElementIterator::operator++ ()
{
	parameters.container.GetNext (parameters.currentElement);

	if ((parameters.attributeFactory != nullptr) && ((*this) != parameters.container.End ())) {
		GSAPI::IAPIAttributeAdapterBase* adapter = parameters.attributeFactory->GetTypeAdapter (parameters.currentElement.elem.element, parameters.currentElement.databaseInfo, parameters.currentElement.elem.memo);
		adapter->CacheAttributes ();
		if (!(parameters.attributeFactory->GetManagedAdapters ())) {
			delete (adapter);
		}
	}

	return *this;
}

#endif //__ELEMENTITERATOR_HPP__
