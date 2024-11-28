#ifndef __NULLTYPEATTRIBUTEADAPTER_HPP__
#define __NULLTYPEATTRIBUTEADAPTER_HPP__

#include "IAPIAttributeAdapter.hpp"

namespace GSAPI {

template <typename ParentType>
class NullTypeAttributeAdapter : public IAPIAttributeAdapter<ParentType> {
public:
    NullTypeAttributeAdapter (IAttributeProxy* proxy, IAPIAttributeAdapterFactory* factory) : IAPIAttributeAdapter<ParentType> (proxy, factory) {}
	NullTypeAttributeAdapter (const NullTypeAttributeAdapter& adapter) : IAPIAttributeAdapter<ParentType> (adapter) {}

    NullTypeAttributeAdapter& operator= (const NullTypeAttributeAdapter& adapter)
	{
		static_cast<IAPIAttributeAdapter<ParentType>&> (*this) = adapter;
		return (*this);
	}

    virtual void CacheAttributes ()  override {}
};

}

#endif //__NULLTYPEATTRIBUTEADAPTER_HPP__
