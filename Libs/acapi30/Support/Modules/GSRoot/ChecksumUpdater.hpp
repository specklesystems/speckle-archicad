// *****************************************************************************
// Description:		Interface for low level data transfer into any kind of Checksum generator 
//
// Namespaces:		GS
// Contact persons:	AACS
//
// [SG compatible]
// *****************************************************************************

#ifndef CHECKSUMUPDATER_HPP
#define CHECKSUMUPDATER_HPP

// --------- Includes ----------------------------------------------------------

#include	"GSRootExport.hpp"


namespace GS {

	class GSROOT_DLL_EXPORT ChecksumUpdater
	{
	public: 
		virtual ~ChecksumUpdater ();
		virtual void Update (const void* data, unsigned int size) = 0;
	};
}
#endif
