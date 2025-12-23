
#include "IAPIOutputAdapter.hpp"


GSAPI::IAPIOutputAdapterBase::~IAPIOutputAdapterBase ()
{
	outputManager			= nullptr;
	outputAdapterFactory	= nullptr;
	dbInfo					= nullptr;
	attributeProxy			= nullptr;
	attributeOutputType		= GSAPI::DoNotOutput;
}
