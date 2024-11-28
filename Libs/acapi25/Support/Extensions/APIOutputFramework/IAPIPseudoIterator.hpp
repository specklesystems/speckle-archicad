#ifndef __IAPIPSEUDOITERATOR_HPP__
#define __IAPIPSEUDOITERATOR_HPP__

namespace GSAPI {

/** @interface */
template <typename APIType, class FinalType>
class IAPIPseudoIterator {
public:
	virtual FinalType	operator++(int) = 0;
    virtual FinalType&	operator++() = 0;

    virtual bool operator== (const FinalType& it) const = 0;
    virtual bool operator!= (const FinalType& it) const = 0;

    virtual const APIType* operator-> () = 0;
    virtual const APIType& operator* () = 0;
};

}

#endif //__IAPIPSEUDOITERATOR_HPP__
