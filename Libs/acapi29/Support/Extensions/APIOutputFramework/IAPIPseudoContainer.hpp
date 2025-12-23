#ifndef __IAPIPSEUDOCONTAINER_HPP__
#define __IAPIPSEUDOCONTAINER_HPP__

#include "GlobalOperators.hpp"

namespace GSAPI {

class IAPIAttributeAdapterFactory;


/** @interface */
template <typename APIType, typename FilterType, class Iterator>
class IAPIPseudoContainer {
public:
    typedef Iterator PseudoIterator;

protected:
	FilterType typeFilter;
	IAPIAttributeAdapterFactory* attributeFactory;

protected:
    Iterator CreateIterator (const typename Iterator::Parameters& params) const { return Iterator (params); }

public:
	IAPIPseudoContainer (IAPIAttributeAdapterFactory* factory = nullptr) { attributeFactory = factory; }

	virtual void SetFilter (const FilterType& filter) { Copy (typeFilter, filter); }

	virtual void GetNext (APIType&) const = 0;
    virtual PseudoIterator Begin () const = 0;
    virtual const PseudoIterator End () const = 0;
};

}	// namespace GSAPI

#endif //__IAPIPSEUDOCONTAINER_HPP__
