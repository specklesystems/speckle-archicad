
// *****************************************************************************
//
// Declaration of MemoryManager abstract class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_MEMORYMANAGER_HPP
#define GS_MEMORYMANAGER_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Definitions.hpp"


// --- Utility -----------------------------------------------------------------
namespace GS {

class MemoryAllocationFailureHandler;
template <class Type> class Array;

extern GSROOT_DLL_EXPORT const GS::Utf8Char* MemoryManagerSpecificErrorGUID;
extern GSROOT_DLL_EXPORT const GS::Utf8Char* MemoryManagerSpecificErrorName;

extern GSROOT_DLL_EXPORT const GS::Utf8Char* AllocationFailureGUID;
extern GSROOT_DLL_EXPORT const GS::Utf8Char* AllocationFailureName;
extern GSROOT_DLL_EXPORT const GS::Utf8Char* SignatureMismatchGUID;
extern GSROOT_DLL_EXPORT const GS::Utf8Char* SignatureMismatchName;


// --- MemoryManager class -----------------------------------------------------

namespace MemoryManagerUtil {
	GSROOT_DLL_EXPORT extern bool flagsInitialized;
	GSROOT_DLL_EXPORT extern bool debugAllocationOverridden;

	GSROOT_DLL_EXPORT void InitializeFlags ();
}


// --- MemoryManager class -----------------------------------------------------

class GSROOT_DLL_EXPORT MemoryManager {

// Construction / destruction:
protected:
			 MemoryManager ();
			 MemoryManager (const MemoryManager&); // disabled
public:
	virtual ~MemoryManager ();

// Operator overloading:
protected:
	const MemoryManager&	operator = (const MemoryManager&); // disabled

// Operations:
public:
	virtual USize			GetAttachedAllocationFailureHandlers (Array<MemoryAllocationFailureHandler*>& memoryAllocationFailureHandlers) const = 0;

	virtual bool			IsAllocationFailureHandlerAttached (MemoryAllocationFailureHandler* memoryAllocationFailureHandler) const = 0;

	virtual void			AttachAllocationFailureHandler (MemoryAllocationFailureHandler* memoryAllocationFailureHandler) = 0;
	virtual void			DetachAllocationFailureHandler (MemoryAllocationFailureHandler* memoryAllocationFailureHandler) = 0;

	virtual bool			AllocationFailed (size_t size) = 0;

// Static operations:
public:
	static MemoryManager&	GetInstance ();

	enum ExceptionBehaviour { ThrowGSMemoryFull, ReturnNullPointer };

	static void*			Allocate (size_t size, ExceptionBehaviour exc = ReturnNullPointer, bool logFailure = true);
	static void*			AlignedAllocate (size_t size, size_t alignment, ExceptionBehaviour exc = ReturnNullPointer, bool logFailure = true);
	static void*			Reallocate (void* memory, size_t size, ExceptionBehaviour exc = ReturnNullPointer, bool logFailure = true);
	static void				Free (void* memory);
	static void				AlignedFree (void* memory);
	static size_t			MSize (void* memory);
	static size_t			AlignedMsize (void* memory, size_t alignment);
	static int				HeapCheck (void);

public:
	static bool				IsDebugAllocationEnabled (void);
};


}	// namespace GS

#endif // GS_MEMORYMANAGER_HPP
