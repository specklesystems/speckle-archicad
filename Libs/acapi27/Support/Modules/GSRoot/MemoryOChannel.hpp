
// *****************************************************************************
//
//	                          Class MemoryOChannel
//
// Module: GSRoot
// Namespace: GS
// Contact person: MB
//
//
// *****************************************************************************


#if !defined MEMORYOCHANNEL_HPP
#define MEMORYOCHANNEL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "OChannelAdapter.hpp"
#include "MemoryRange.hpp"

#include <cstddef>

// =========================== Class MemoryOChannel ============================

namespace GS {

class GSROOT_DLL_EXPORT MemoryOChannel : public OChannelAdapter,
										 public ConstMemoryRangeSource,
										 private OutputBuffer::BinOutput
{
public:
	enum OwnershipType { OriginalOwnership, PassOwnership, GrantOwnership };

private:
	char*	destination;	// destination buffer which receives the data
	UInt64	size;			// size of the data stored in the destination buffer in characters
	UInt64	sizeLimit;		// maximum allowed size of the data in characters
	UInt64	capacity;		// actual capacity of the destination buffer (in characters)
	bool	ownsDest;		// specifies whether this object owns the destination buffer

	MemoryOChannel (const MemoryOChannel& source);				// disabled
	MemoryOChannel&	operator= (const MemoryOChannel& source);	// disabled

	GSErrCode	Init (UInt64 initialCapacity, UInt64 maxSize);
	void		Init (char* destBuffer, UInt64 destBufferSize, UInt64 maxSize, OwnershipType ot);

	virtual GSErrCode	InternalWrite (const char* source, USize nOfCharToWrite, USize* written) override;


	char*	AllocateMemory (UInt64 size);
	void	DeleteMemory (char* ptr);
public:
	// Constructors

	explicit MemoryOChannel (UInt64 initialCapacity = 0, UInt64 maxSize = 0);
	MemoryOChannel (char* destBuffer, UInt64 destBufferSize, UInt64 maxSize = 0, OwnershipType ot = OriginalOwnership);
	MemoryOChannel (std::byte* destBuffer, UInt64 destBufferSize, UInt64 maxSize = 0, OwnershipType ot = OriginalOwnership);
	~MemoryOChannel ();

	// User interface

	GSErrCode	GetStatus () const;

	GSErrCode	SetDestination (UInt64 initialCapacity = 0, UInt64 maxSize = 0);
	void		SetDestination (char* destBuffer, UInt64 destBufferSize, UInt64 maxSize = 0, OwnershipType ot = OriginalOwnership);
	char*		GetDestination (OwnershipType ot = OriginalOwnership);
	const char*	GetDestination () const;
	UInt64		GetDataSize () const;
	GSErrCode   SetDataSize (UInt64 newSize);

	virtual GSErrCode   GetOutputPosition (UInt64* pos) const override;

	virtual	void	SetDefaultOutputProtocol () override;

	virtual ConstMemoryRange GetMemoryRange () const override;
};

} // namespace GS

// ___________________________ class MemoryOChannel ____________________________

#endif
