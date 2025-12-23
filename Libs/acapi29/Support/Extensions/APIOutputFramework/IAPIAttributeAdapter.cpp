
#include "IAPIAttributeAdapter.hpp"


GSAPI::IAPIAttributeAdapterBase::~IAPIAttributeAdapterBase ()
{
	attributeProxy			= nullptr;
	attributeAdapterFactory	= nullptr;
	dbInfo					= nullptr;
}
