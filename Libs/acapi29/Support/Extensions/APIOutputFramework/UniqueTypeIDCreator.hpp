#ifndef __UNIQUETYPEIDCREATOR_HPP__
#define __UNIQUETYPEIDCREATOR_HPP__

#include "Definitions.hpp"

namespace GSAPI {

class UniqueTypeIDCreatorBase {
protected:
	static UInt32 seed;
};

template <typename APIType>
class UniqueTypeIDCreator : public UniqueTypeIDCreatorBase {
private:
	static UInt32 id;

public:
	static UInt32 GetUniqueTypeID ();
};

}	// namespace GSAPI

template <typename APIType>
UInt32 GSAPI::UniqueTypeIDCreator<APIType>::id = GSAPI::UniqueTypeIDCreatorBase::seed++;

template <typename APIType>
UInt32 GSAPI::UniqueTypeIDCreator<APIType>::GetUniqueTypeID ()
{
	return id;
}

#endif	// __UNIQUETYPEIDCREATOR_HPP__
