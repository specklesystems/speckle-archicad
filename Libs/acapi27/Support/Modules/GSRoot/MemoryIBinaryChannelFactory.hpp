
// *****************************************************************************
//
// Declaration of MemoryIBinaryChannelFactory class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_MEMORYIBINARYCHANNELFACTORY_HPP
#define GS_MEMORYIBINARYCHANNELFACTORY_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "IBinaryChannelFactory.hpp"
#include "MemoryIBinaryChannel.hpp"



// --- MemoryIBinaryChannelFactory class ---------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT MemoryIBinaryChannelFactory : public IBinaryChannelFactory {

// Data members:
private:
	const char*						m_buffer;
	USize							m_bufferSize;
	bool							m_bufferOwnership;

// Construction / destruction:
public:
			 MemoryIBinaryChannelFactory (const char* buffer, USize bufferSize, bool passBufferOwnership = false);
			 MemoryIBinaryChannelFactory (const MemoryIBinaryChannelFactory&) = delete;
	virtual ~MemoryIBinaryChannelFactory ();

// Operator overloading:
public:
	MemoryIBinaryChannelFactory&	operator = (const MemoryIBinaryChannelFactory&) = delete;

// IBinaryChannelFactory interface implementation:
public:
	virtual MemoryIBinaryChannel*	GetInputChannel () const override;

};

}

#endif // GS_MEMORYIBINARYCHANNELFACTORY_HPP