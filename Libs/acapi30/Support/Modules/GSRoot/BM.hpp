// *********************************************************************************************************************
// Description:		GRAPHISOFT Memory Manager
//
// Namespace:		-
// Contact person:	MM
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef	BM_HPP
#define	BM_HPP

#pragma once

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "TypeTraits.hpp"
#include "GSAssertCore.hpp"

#ifndef GS_BUILD_MODULE
// from Standard Library
#include <cstddef>
#include <span>
#endif


// ---------------------------------------------------------------------------------------------------------------------
//											Function tables
// ---------------------------------------------------------------------------------------------------------------------

inline constexpr GSFlags ALLOCATE_ACTION		= 0x0001;				// User action enabled
inline constexpr GSFlags ALLOCATE_CLEAR			= 0x0002;				// Data block is zerod
inline constexpr GSFlags ALLOCATE_ESSENTIAL		= 0x0004;				// minMem / 4 is allowed
inline constexpr GSFlags ALLOCATE_EMPTY			= 0x0008;				// Empty handle is allocated
inline constexpr GSFlags ALLOCATE_INSYSHEAP		= 0x0010;				// Allocate in System heap

inline constexpr GSFlags REALLOC_ACTION			= ALLOCATE_ACTION;		// User action enabled
inline constexpr GSFlags REALLOC_CLEAR			= ALLOCATE_CLEAR;		// New area is zerod
inline constexpr GSFlags REALLOC_ESSENTIAL		= ALLOCATE_ESSENTIAL;	// minMem / 4 is allowed
inline constexpr GSFlags REALLOC_FULLCLEAR		= 0x0008;				// Full handle is zerod
inline constexpr GSFlags REALLOC_SHRINK			= 0x0010;				// new size <= old size
inline constexpr GSFlags REALLOC_DISPOSE		= 0x0020;				// Dispose if unsuccesfull
inline constexpr GSFlags REALLOC_MOVEABLE		= 0x0040;				// Ptr is moveable

inline constexpr short ABORT_ALLOCATE_PTR		= 1;					// Codes for BMAbortProc
inline constexpr short ABORT_ALLOCATE_HANDLE	= 2;
inline constexpr short ABORT_KILL_PTR			= 5;
inline constexpr short ABORT_KILL_HANDLE		= 6;
inline constexpr short ABORT_GET_PTR_SIZE		= 18;
inline constexpr short ABORT_GET_HANDLE_SIZE	= 17;
inline constexpr short ABORT_REALLOC_PTR		= 19;
inline constexpr short ABORT_REALLOC_HANDLE		= 4;

inline constexpr GSFlags DUMP_SMALLBLOCKS		= 0x00000001;
inline constexpr GSFlags DUMP_BM				= 0x00000002;
inline constexpr GSFlags DUMP_CRT				= 0x00000004;
inline constexpr GSFlags DUMP_STACK				= 0x00000008;
inline constexpr GSFlags DUMP_APPEND			= 0x00000010;

inline constexpr GSFlags DUMP_DEFAULT			= DUMP_CRT | DUMP_SMALLBLOCKS;

typedef short STDCALL	BMAbortProc (short c, Int32 n, short e, short action);


// ---------------------------------------------------------------------------------------------------------------------
//											New	Functions
// ---------------------------------------------------------------------------------------------------------------------

void		GSROOT_DLL_EXPORT STDCALL	BMSetAbortProc (BMAbortProc* bmAbort);

GSErr		GSROOT_DLL_EXPORT STDCALL	BMError (void);

GSPtr		GSROOT_DLL_EXPORT STDCALL	BMAllocatePtr (GSSize nBytes, GSFlags allocFlags, short actionCode);
GSHandle	GSROOT_DLL_EXPORT STDCALL	BMAllocateHandle (GSSize nBytes, GSFlags allocFlags, short actionCode);
void		GSROOT_DLL_EXPORT STDCALL	BMKillPtr (GSPtr* p);
void		GSROOT_DLL_EXPORT STDCALL	BMKillHandle (GSHandle* h);

GSSize		GSROOT_DLL_EXPORT STDCALL	BMGetPtrSize (GSConstPtr p);
GSSize		GSROOT_DLL_EXPORT STDCALL	BMGetHandleSize (GSConstHandle h);
GSPtr		GSROOT_DLL_EXPORT STDCALL	BMReallocPtr (GSPtr p, GSSize nBytes, GSFlags reallocFlags, short actionCode);
GSHandle	GSROOT_DLL_EXPORT STDCALL	BMReallocHandle (GSHandle h, GSSize nBytes, GSFlags reallocFlags, short actionCode);

Int32		GSROOT_DLL_EXPORT STDCALL	BMCheckHeap (void);

GSSize		GSROOT_DLL_EXPORT STDCALL	BMClearHandle (GSHandle h);
GSErr		GSROOT_DLL_EXPORT STDCALL	BMHandleToHandle (GSConstHandle inpH, GSHandle* outH);
GSErr		GSROOT_DLL_EXPORT STDCALL	BMPtrToHandle (const void* pSource, GSHandle* hDest, GSSize nBytes);
GSErr		GSROOT_DLL_EXPORT STDCALL	BMHandleAndHandle (GSHandle inpH, GSHandle outH);
GSErr		GSROOT_DLL_EXPORT STDCALL	BMPtrAndHandle (const void* pSource, GSHandle hDest, GSSize nBytes);
Int32		GSROOT_DLL_EXPORT STDCALL	BMMunger(GSHandle h, Int32 offset, const void* ptr1, Int32 len1, const void* ptr2, Int32 len2);
bool		GSROOT_DLL_EXPORT STDCALL	BMCompareHandle (GSConstHandle handle1, GSConstHandle handle2);

GSErr		GSROOT_DLL_EXPORT STDCALL	BMErrorNotClear (void);

void		GSROOT_DLL_EXPORT STDCALL	BMDumpHeap (const char* pFilePath, GSFlags dumpFlags = DUMP_DEFAULT);

bool		GSROOT_DLL_EXPORT STDCALL	BNValidReadPtr (const void* memPtr, GSSize len);
bool		GSROOT_DLL_EXPORT STDCALL	BNValidWritePtr (void* memPtr, GSSize len);
void		GSROOT_DLL_EXPORT STDCALL	BNFillMemory (void* destPtr, GSSize length, unsigned char value = 0);
void		GSROOT_DLL_EXPORT STDCALL	BNCopyMemory (void* destPtr, const void* srcPtr, GSSize length);
void		GSROOT_DLL_EXPORT STDCALL	BNMoveMemory (void* destPtr, const void* srcPtr, GSSize length);
GSSize		GSROOT_DLL_EXPORT STDCALL	BNCompareMemory (const void* strc1Ptr, const void* strc2Ptr, GSSize length);


template <typename Type>
void	BNZeroMemory (Type* dest, GSSize length)
{
	static_assert (GS::IsVoid<Type> || GS::IsTriviallyCopyable<Type>, "The parameter of BNZeroMemory should be trivially copyable.");

	BNFillMemory (dest, length, 0);
}


template <class Type>
void	BNClear (Type& dest)
{
	static_assert (GS::IsTriviallyCopyable<Type>);
	static_assert (!GS::IsPointer<Type>);

	BNFillMemory (&dest, sizeof (Type), 0);
}


template<typename T, typename U>
void	BNCopyMemory (T* dest, const U* src, GSSize lengthInBytes)
{
	static_assert (GS::IsVoid<T> || GS::IsTriviallyCopyable<T>);
	static_assert (GS::IsVoid<U> || GS::IsTriviallyCopyable<U>);

	::BNCopyMemory (static_cast<void*> (dest), static_cast<const void*> (src), lengthInBytes);
}


template<typename T = std::byte>
std::span<const T>	BMHandleToSpan (GSConstHandle handle)
{
	static_assert (GS::IsTriviallyCopyable<T>);

	if (const GSSize hsize = BMGetHandleSize (handle); hsize > 0) {
		const std::size_t size = static_cast<std::size_t> (hsize);
		PRECOND (size % sizeof (T) == 0);
		return std::span { reinterpret_cast<const T*> (*handle), size / sizeof (T) };
	}

	return std::span<const T> {};
}


template<typename T = std::byte>
std::span<T>	BMHandleToSpan (GSHandle handle)
{
	static_assert (GS::IsTriviallyCopyable<T>);

	if (const GSSize hsize = BMGetHandleSize (handle); hsize > 0) {
		const std::size_t size = static_cast<std::size_t> (hsize);
		PRECOND (size % sizeof (T) == 0);
		return std::span { reinterpret_cast<T*> (*handle), size / sizeof (T) };
	}

	return std::span<T> {};
}


// ---------------------------------------------------------------------------------------------------------------------
//											Old	Functions
// ---------------------------------------------------------------------------------------------------------------------

/* BMAllocateHandle */
inline GSHandle	BMhAll (GSSize n)									{ return BMAllocateHandle (n, 0, 0); }
inline GSHandle	BMhAllClear (GSSize n)								{ return BMAllocateHandle (n, ALLOCATE_CLEAR, 0); }
inline GSSize	BMhGetSize (GSConstHandle h)						{ return BMGetHandleSize (h); }
inline void		BMhFree (GSHandle h)								{ GSHandle aH = h; BMKillHandle (&aH); }
inline void		BMhKill (GSHandle* ph)								{ BMKillHandle (ph); }
/* BMAllocatePtr */
inline GSPtr	BMpAll (GSSize nBytes)								{ return BMAllocatePtr (nBytes, 0, 0); }
inline GSPtr	BMpAllClear (GSSize nBytes)							{ return BMAllocatePtr (nBytes, ALLOCATE_CLEAR, 0); }
inline GSSize	BMpGetSize (GSConstPtr p)							{ return BMGetPtrSize (p); }
inline void		BMpFree (GSPtr p)									{ GSPtr aP = p; BMKillPtr (&aP); }
inline void		BMpKill (GSPtr* p)									{ BMKillPtr (p); }
/* BMReallocHandle */
inline void		BMhSetSize (GSHandle h, GSSize n)					{ BMReallocHandle (h, n, 0, 0); }
inline GSErr	BMhSetSizeClear (GSHandle h, GSSize n)				{ BMReallocHandle (h, n, REALLOC_CLEAR, 0); return BMErrorNotClear (); }
inline GSErr	BMhSetSizeFullClear (GSHandle h, GSSize n)			{ BMReallocHandle (h, n, REALLOC_FULLCLEAR, 0); return BMErrorNotClear (); }
inline GSHandle	BMhReal (GSHandle h, GSSize n)						{ return BMReallocHandle (h, n, REALLOC_DISPOSE, 0); }
inline GSHandle	BMhReal1 (GSHandle h, GSSize n)						{ return BMReallocHandle (h, n, REALLOC_SHRINK, 0); }
inline GSErr	BMhAllSetSizeClear (GSHandle h, GSSize n)			{ BMReallocHandle (h, n, REALLOC_CLEAR, 0); return BMErrorNotClear (); }

inline Int32	BMCheck (void)										{ return BMCheckHeap (); }

inline GSSize	BMhClear (GSHandle h)								{ return BMClearHandle (h); }

inline GSErr	BMhToHandle (GSConstHandle ih, GSHandle* oh)		{ return BMHandleToHandle (ih, oh); }
inline GSErr	BMpToHandle (const void* p, GSHandle* h, GSSize n)	{ return BMPtrToHandle (p, h, n); }
inline GSErr	BMhAndHandle (GSHandle ih, GSHandle oh)				{ return BMHandleAndHandle (ih, oh); }
inline GSErr	BMpAndHandle (const void* p, GSHandle h, GSSize n)	{ return BMPtrAndHandle (p, h, n); }


#endif