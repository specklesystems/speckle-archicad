// *********************************************************************************************************************
// Description:		Stack Information
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MM
//
// SG compatible
// *********************************************************************************************************************

#if !defined (STACKINFO_HPP)
#define STACKINFO_HPP

#pragma once

// from GSRoot
#include	"Definitions.hpp"

#if defined (WINDOWS)
	#include "IntelStackWalkWin.hpp"
#endif

#include	"LoadedModuleListDefs.hpp"


namespace StackInfoPrivate {

GSROOT_DLL_EXPORT	UInt32		CalculateStackHash (void* const addresses[], UInt32 MaxStackDepth, UInt32* pSigIndex);

GSROOT_DLL_EXPORT	UInt16		GetCallStack (Int32 ignoreDepth, UInt16 maxDepth, void* address[]);

GSROOT_DLL_EXPORT	void*		RVAToVA (const LoadedModuleListDefs::RVAOrVA& rva);

GSROOT_DLL_EXPORT	GS::IntPtr	GetCurrentUsageDebugInfo ();

GSROOT_DLL_EXPORT	UInt16		CaptureStackBackTr (Int32 ignoreDepth, UInt16 maxDepth, void* address[]);

} // namespace StackInfoPrivate

namespace GS {

// ---------------------------------------------------------------------------------------------------------------------
// StackInfo struct, saved into the allocated memory blocks
// ---------------------------------------------------------------------------------------------------------------------

template <UInt16 MaxCallDepth>
class StackInfoCustomDepth {
public:
	typedef UInt8 WalkType;

	enum WalkTypes {
		FastWalkRVA,	// Store relative addresses, plus module IDs
		FastWalk,		// Store absolute addresses
		DbgHelpWalk		// Rely on dbghelp.dll's stack walk (absolute addresses)
	};

private:
	enum {
		Signature		= 'STCK'
	};

	union AddressReference {
		LoadedModuleListDefs::RVAOrVA	rva;
		void*							absoluteAddress;
	};

	UInt32							signature;
	UInt16							depth;
	WalkType						type;
	AddressReference				addresses[MaxCallDepth];
	GS::UIntPtr						usageDebugInfo;

public:
	explicit StackInfoCustomDepth (Int32 ignoreDepth = 0, UInt16 maxDepth = MaxCallDepth, WalkType walkType = FastWalk);

	bool		IsValid () const						{ return  signature == Signature;	}
	UInt32		GetStackHashCode (UInt32* pSigIndex) const;
	UInt32		GetDepth () const						{ return depth;						}
	void*		GetAbsoluteAddress (Int32 i) const;
	GS::UIntPtr	GetUsageDebugInfo () const				{ return usageDebugInfo;			}
};

typedef StackInfoCustomDepth<20> StackInfo;

}	// namespace GS

// ---------------------------------------------------------------------------------------------------------------------
// StackInfo class implementation
// ---------------------------------------------------------------------------------------------------------------------

template <UInt16 MaxCallDepth>
GS::StackInfoCustomDepth<MaxCallDepth>::StackInfoCustomDepth (Int32 ignoreDepth, UInt16 maxDepth, WalkType walkType) :
	signature (Signature),
	depth (maxDepth),
	type (walkType)
{
	memset (addresses, 0, sizeof addresses);

	usageDebugInfo = StackInfoPrivate::GetCurrentUsageDebugInfo ();

	if (maxDepth == 0) {
		return;
	}

#if defined (WINDOWS)
	switch (type) {
		case FastWalkRVA:
			depth = GS::IntelStackWalk (nullptr, ignoreDepth, maxDepth, &addresses->rva, Relative);
			break;
		case FastWalk:
			depth = StackInfoPrivate::CaptureStackBackTr (ignoreDepth, maxDepth, &addresses->absoluteAddress);
			break;
		case DbgHelpWalk:
			depth = StackInfoPrivate::GetCallStack (ignoreDepth, maxDepth, &addresses->absoluteAddress);
			break;
	}
#elif defined (macintosh) || defined (__linux__)
	UNUSED_PARAMETER (ignoreDepth);
#endif
}


template <UInt16 MaxCallDepth>
void* GS::StackInfoCustomDepth<MaxCallDepth>::GetAbsoluteAddress (Int32 i) const
{
	return type == FastWalkRVA ? StackInfoPrivate::RVAToVA (addresses[i].rva) : addresses[i].absoluteAddress;
}


template <UInt16 MaxCallDepth>
UInt32	GS::StackInfoCustomDepth<MaxCallDepth>::GetStackHashCode (UInt32* pSigIndex) const
{
	if (type == FastWalkRVA) {
		void* absoluteAddresses[MaxCallDepth];
		for (UInt32 i = 0; i < MaxCallDepth; ++i)
			absoluteAddresses[i] = StackInfoPrivate::RVAToVA (addresses[i].rva);

		return StackInfoPrivate::CalculateStackHash (absoluteAddresses, MaxCallDepth, pSigIndex);
	} else {
		return StackInfoPrivate::CalculateStackHash (&addresses->absoluteAddress, MaxCallDepth, pSigIndex);
	}
}

#endif