// *********************************************************************************************************************
// Description:		Loaded module list
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	EP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (LOADMODULELISTDEFS_HPP)
#define LOADMODULELISTDEFS_HPP

#pragma once

// from GSRoot
#include	"Definitions.hpp"
#include	"GSDebug.hpp"


namespace LoadedModuleListDefs {

typedef UInt32 ModuleOffset;	// We expect no image offset to be > 2GB (MSB is reserved: see RVAOrVA::AbsoluteAddressOverrideFlag)
typedef UInt32 ModuleID;		// 32-bit hash of module name

struct RVAOrVA {
private:
	/* If offset's MSB is set, contents should be interpreted as an absolute address.
	 * This can be done, because:
	 *								1.) on Win64, addresses > 0x7FFFFFFFFFFFFFFF are either invalid, or reserved for the kernel
	 *								2.) on Win32, an absolute address is 32-bit wide, so it can be stored in moduleID altogether
	 */
	static const ModuleOffset AbsoluteAddressOverrideFlag = static_cast<ModuleOffset> (1 << ((sizeof (ModuleOffset) * 8) - 1));	// MSB is set

	void	SetAsVA ()	{ offset |= AbsoluteAddressOverrideFlag; }
	void	SetAsRVA ()	{ offset &= ~AbsoluteAddressOverrideFlag; }

public:
	ModuleOffset offset;
	ModuleID	 moduleID;

	inline bool	IsVA ()	 const	{ return (offset & AbsoluteAddressOverrideFlag) != 0; }
	inline bool	IsRVA () const	{ return !IsVA (); }

	inline void	SetVA (const void* address);
	inline void	SetVA (GS::UIntPtr address);
	inline void*GetVA () const;
};

void RVAOrVA::SetVA (const void* address)
{
#ifdef WINDOWS
	#ifdef _M_AMD64
		offset = *(reinterpret_cast<const UInt32*> (&address) + 1);
		moduleID = static_cast<UInt32> (reinterpret_cast<GS::UIntPtr> (address));
	#else
		#error Unknown architecture!
	#endif

	SetAsVA ();
#elif defined (macintosh) || defined (__linux__)
	UNUSED_PARAMETER (address);
	DBBREAK_STR("Not implemented on mac and linux");
#endif
}


void	RVAOrVA::SetVA (GS::UIntPtr address)
{
	SetVA (reinterpret_cast<void*> (address));
}


void* RVAOrVA::GetVA () const
{
#ifdef WINDOWS
	#ifdef _M_AMD64
		GS::UIntPtr retValue = moduleID;
		GS::UIntPtr temp = offset & ~AbsoluteAddressOverrideFlag;
		temp = temp << 32;
		retValue |= temp;

		return reinterpret_cast<void*> (retValue);
	#else
		#error Unknown architecture!
	#endif
#elif defined (macintosh) || defined (__linux__)
	DBBREAK_STR("Not implemented on mac and linux");
	return nullptr;
#endif
};

}	// namespace LoadedModuleListDefs

#endif
