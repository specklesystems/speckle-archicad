
// *****************************************************************************
//
//	                          Class MemoryIChannel
//
// Module: GSRoot
// Namespace: GS
// Contact person: MB
//
//
//
// *****************************************************************************


#if !defined MEMORYICHANNEL_HPP
#define MEMORYICHANNEL_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"
#include "IChannelAdapter.hpp"
#include "MemoryRange.hpp"

#include <cstddef>


// =========================== Class MemoryIChannel ============================

namespace GS {

class GSROOT_DLL_EXPORT MemoryIChannel : public IChannelAdapter,
										 private InputBuffer::BinInput
{
public:
	enum OwnershipType { OriginalOwnership, PassOwnership };

private:
	const char*		source;		// source of the data
	UInt64			length;		// length of the source in characters
	bool			ownsSrc;	// specifies whether this object owns the source
	UInt64			srcPos;		// position in the source

	MemoryIChannel (const MemoryIChannel& source);				// disabled
	MemoryIChannel&	operator= (const MemoryIChannel& source);	// disabled

	void	Init ();
	void	Init (const char* sourceData, UInt64 sourceDataLength, OwnershipType ot);

	virtual GSErrCode	InternalRead (char* destination, USize nOfCharToRead, USize* read) override;

	void DeleteMemory (char* src);

public:
		// Types

	struct InputBuffer {
		char* buffer;
		USize capacity;

		InputBuffer (): buffer (nullptr), capacity (0) {}
		InputBuffer (char* buffer, USize capacity): buffer (buffer), capacity (capacity) {}
	};

		// Constructors

	MemoryIChannel (const InputBuffer& inputBuffer = InputBuffer ());
	MemoryIChannel (const char* sourceData, UInt64 sourceDataLength, OwnershipType ot = OriginalOwnership, const InputBuffer& inputBuffer = InputBuffer ());
	MemoryIChannel (const std::byte* sourceData, UInt64 sourceDataLength, OwnershipType ot = OriginalOwnership, const InputBuffer& inputBuffer = InputBuffer ());
	explicit MemoryIChannel (const ConstMemoryRange& range);
	explicit MemoryIChannel (const ConstMemoryRangeSource& rangeSource);
   ~MemoryIChannel ();

		// User interface

	void			SetSource	  (const char* sourceData, UInt64 sourceDataLength, OwnershipType ot = OriginalOwnership);
	const char*		GetSource	  () const;
	UInt64			GetDataLength () const;
	void			RemoveSource  ();
	void			ResetSource	  ();

	virtual GSErrCode	GetInputPosition (UInt64* position) const override;
	virtual GSErrCode	GetAvailable     (UInt64* available) const override;

	virtual void	SetDefaultInputProtocol () override;
};

}	// namespace GS

// ___________________________ Class MemoryIChannel ____________________________

#endif
