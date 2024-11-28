#ifndef __ATTRIBUTEITERATOR_HPP__
#define __ATTRIBUTEITERATOR_HPP__

#include "IAPIPseudoIterator.hpp"
#include "IAPIPseudoContainer.hpp"
#include "GSAPIWrappers.hpp"
#include "GlobalOperators.hpp"

namespace GSAPI {

class AttributeIterator : public IAPIPseudoIterator<GSAPI::IteratorElem <API_Attribute>, AttributeIterator> {

	friend class GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <API_Attribute>, AttributeFilter, AttributeIterator>;

public:
	class Parameters {

		friend class GSAPI::AttributeIterator;

	private:
		const GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <API_Attribute>, AttributeFilter, AttributeIterator>& container;
		GSAPI::IteratorElem <API_Attribute>                                                                        currentAttribute;

	public:
		Parameters (const GSAPI::IAPIPseudoContainer<GSAPI::IteratorElem <API_Attribute>, AttributeFilter, AttributeIterator>& pseudoContainer,
					GSAPI::IteratorElem <API_Attribute>& attribute) :
			container (pseudoContainer),
			currentAttribute (attribute) {}

		Parameters (const Parameters&) = default;

		Parameters& operator= (const Parameters&) = delete;
	};

private:
    Parameters parameters;

protected:
	AttributeIterator (const Parameters& params) : parameters (params) {}

public:
	AttributeIterator (const AttributeIterator& it) : parameters (it.parameters) {}

	AttributeIterator& operator= (const AttributeIterator& it) = delete;

	virtual AttributeIterator  operator++(int)   override { AttributeIterator temp = *this; ++(*this); return temp; }
	virtual AttributeIterator& operator++()      override { parameters.container.GetNext (parameters.currentAttribute); return (*this); }

    virtual bool operator== (const AttributeIterator& it) const override;
	virtual bool operator!= (const AttributeIterator& it) const  override { return (!((*this)==it)); }

	virtual const GSAPI::IteratorElem <API_Attribute>* operator-> ()  override { return &(parameters.currentAttribute); }
	virtual const GSAPI::IteratorElem <API_Attribute>& operator* ()   override { return parameters.currentAttribute; }
};

}	// namespace GSAPI


#endif //__ATTRIBUTEITERATOR_HPP__
