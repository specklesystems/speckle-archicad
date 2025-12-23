#ifndef __NULLTYPEOUTPUTADAPTER_HPP__
#define __NULLTYPEOUTPUTADAPTER_HPP__

#include "IAPIOutputAdapter.hpp"

namespace GSAPI {

template <typename ParentType>
class NullTypeOutputAdapter : public IAPIOutputAdapter<ParentType> {
public:
    NullTypeOutputAdapter (IAPIOutputManager* manager, IAPIOutputAdapterFactory* factory) : IAPIOutputAdapter<ParentType> (manager, factory) {}
	NullTypeOutputAdapter (const NullTypeOutputAdapter& adapter) : IAPIOutputAdapter<ParentType> (adapter) {}

    NullTypeOutputAdapter& operator= (const NullTypeOutputAdapter& adapter)
	{
		static_cast<IAPIOutputAdapter<ParentType>&> (*this) = adapter;
		return (*this);
	}

    virtual void Output (GS::OChannel& /*oChannel*/)  override {}
    virtual void operator>> (GS::OChannel& /*oChannel*/)  override {}
};

}

#endif //__NULLTYPEOUTPUTADAPTER_HPP__
