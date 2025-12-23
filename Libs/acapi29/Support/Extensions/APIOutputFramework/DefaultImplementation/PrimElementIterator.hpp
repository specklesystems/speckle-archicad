#ifndef __PRIMELEMENTITERATOR_HPP__
#define __PRIMELEMENTITERATOR_HPP__

#include "IAPIPseudoIterator.hpp"
#include "GlobalOperators.hpp"
#include "IAPIPseudoContainer.hpp"
#include "Array.hpp"

namespace GSAPI {

class PrimElementIterator : public IAPIPseudoIterator<GSAPI::IteratorElem <GSAPI::Element<GSAPI::PrimElement> >, PrimElementIterator> {

	friend class GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, PrimElementIterator>;

public:
	class Parameters {

		friend class GSAPI::PrimElementIterator;

	private:
		const GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, PrimElementIterator>& container;
		GSAPI::IteratorElem <GSAPI::Element<API_Element> >                                                                         currentElement;
		IAPIAttributeAdapterFactory*                                                                                               attributeFactory;

	public:
		Parameters (const GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <GSAPI::Element<API_Element> >, API_ElemFilter, PrimElementIterator>& pseudoContainer,
					const GSAPI::IteratorElem <GSAPI::Element<API_Element> >&                                                                  element,
					IAPIAttributeAdapterFactory*                                                                                               factory = nullptr) :
			container (pseudoContainer),
			currentElement (element),
			attributeFactory (factory) {}

		Parameters (const Parameters&) = default;

		Parameters& operator= (const Parameters& params) = delete;
	};

	class PrimElementLessThanOperator {
	public:
		bool operator() (const GSAPI::PrimElement& primElem1, const GSAPI::PrimElement& primElem2) const;
	};

private:
	static PrimElementIterator* shapePrimsCallerObject;

private:
    Parameters												  parameters;
    GS::Array<GSAPI::PrimElement>							  primElements;
    GS::UIndex												  primIndex;
	GSAPI::IteratorElem <GSAPI::Element<GSAPI::PrimElement> > currentElement;

private:
    static GSErrCode ShapePrimsCallBack (const API_PrimElement *primElem,
                                                      const void *par1,
                                                      const void *par2,
                                                      const void *par3);
private:
    PrimElementIterator& operator= (const PrimElementIterator& it); // disabled

	void DeletePrimElements ();
	USize BuildPrimElementList ();

protected:
	PrimElementIterator (const Parameters& params);

public:
	PrimElementIterator (const PrimElementIterator& it) :
		parameters (it.parameters),
		primElements (it.primElements),
		primIndex (it.primIndex),
		currentElement (it.currentElement)
	{}

	~PrimElementIterator ();

    PrimElementIterator  operator++ (int) override;
    PrimElementIterator& operator++ () override;

    bool operator== (const PrimElementIterator& it) const override;
    bool operator!= (const PrimElementIterator& it) const override;

    const GSAPI::IteratorElem <GSAPI::Element<GSAPI::PrimElement> >* operator-> () override;
    const GSAPI::IteratorElem <GSAPI::Element<GSAPI::PrimElement> >& operator* () override;
};

}

#endif //__PRIMELEMENTITERATOR_HPP__
