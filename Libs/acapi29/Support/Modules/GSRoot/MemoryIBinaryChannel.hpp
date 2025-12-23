
// *****************************************************************************
//
// Declaration of MemoryIBinaryChannel class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_MEMORYIBINARYCHANNEL_HPP
#define GS_MEMORYIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "IBinaryChannel.hpp"



// --- MemoryIBinaryChannel class ----------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT MemoryIBinaryChannel : public IBinaryChannel {

// Data members:
private:
	const char*				m_buffer;
	USize					m_bufferSize;
	bool					m_bufferOwnership;
	USize					m_position;
	bool					m_closed;

// Construction / destruction:
public:
			 MemoryIBinaryChannel (const char* buffer, USize bufferSize, bool passBufferOwnership = false);
			 MemoryIBinaryChannel (const MemoryIBinaryChannel&) = delete;
	virtual	~MemoryIBinaryChannel ();

// Operator overloading:
public:
	MemoryIBinaryChannel&	operator = (const MemoryIBinaryChannel&) = delete;

// IBinaryChannel interface implementation:
public:
	virtual UInt64			GetAvailable () const override;

	virtual USize			Read (char* target, USize targetSize, ReadSomeModeSelector readSomeMode = ReadSomeMode) override;

	virtual void			Close () override;

// Implementation:
private:
	void					CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

};

}

#endif // GS_MEMORYIBINARYCHANNEL_HPP
