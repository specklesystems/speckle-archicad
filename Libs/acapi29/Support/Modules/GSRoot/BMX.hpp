/********************************************************************************/
/*																				*/
/*						 Archicad Memory Manager extensions						*/
/*																				*/
/********************************************************************************/

#ifndef	BMX_HPP
#define	BMX_HPP

#pragma once

#include	"GSException.hpp"
#include	"GSDebug.hpp"
#include	"BM.hpp"

namespace GS {

DECLARE_EXCEPTION_CLASS (BMException,			RootException, Error, GSROOT_DLL_EXPORT)

DECLARE_EXCEPTION_CLASS2 (BMLogicErrorException,		BMException, LogicErrorException,		Error, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS2 (BMIllegalArgumentException,	BMException, IllegalArgumentException,	ErrParam, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS2 (BMNullPointerException,	BMException, NullPointerException,		ErrNilPtr, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS2 (BMNullHandleException,	BMException, NullHandleException,		ErrNilHandle, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS2 (BMEmptyHandleException,	BMException, EmptyHandleException,		ErrEmptyHandle, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS2 (BMOutOfMemoryException,		BMException, RunTimeErrorException,		ErrMemoryFull, GSROOT_DLL_EXPORT)


inline void RaiseExceptionFromBMError (GSErr err)
{
	switch (err) {
		case NoError:
			/* why we are here? */
			break;

		case ErrParam:
			throw BMIllegalArgumentException ("BM: illegal argument!");

		case ErrMemoryFull:
			throw BMOutOfMemoryException ("BM: cannot allocate the needed memory!");

		case ErrNilHandle:
			throw BMNullHandleException ("BM: nullptr handle!");

		case ErrNilPtr:
			throw BMNullPointerException ("BM: Null pointer!");

		case ErrEmptyHandle:
			throw BMEmptyHandleException ("BM: empty handle!");

		default:
			throw BMLogicErrorException ("BMX internal error!");
	}
}

inline Int32 BMXCheck (void)
{
	Int32 ret = BMCheckHeap ();
	GSErr bmError = BMError ();
	if (bmError != NoError) {
		RaiseExceptionFromBMError (bmError);
	}
	return ret;
}


inline GSHandle BMX_hAll (GSSize nBytes, GSFlags flags)
{
	GSHandle ret = BMAllocateHandle (nBytes, flags, 0);
	if (ret == nullptr) {
		RaiseExceptionFromBMError (BMError ());
	}
	return ret;
}

inline void BMXhFree (GSHandle handle)
{
	BMKillHandle (&handle);
	GSErr bmError = BMError ();
	if (bmError != NoError) {
		RaiseExceptionFromBMError (bmError);
	}
}

inline void BMXhKill (GSHandle* handle)
{
	BMKillHandle (handle);
	GSErr bmError = BMError ();
	if (bmError != NoError) {
		RaiseExceptionFromBMError (bmError);
	}
}

inline GSSize BMXhGetSize (GSHandle handle)
{
	GSSize ret = BMGetHandleSize (handle);
	GSErr bmError = BMError ();
	if (bmError != NoError) {
		RaiseExceptionFromBMError (bmError);
	}	return ret;
}

inline GSHandle BMX_hSetSize (GSHandle handle, GSSize nBytes, GSFlags reallocFlags, short actionCode)
{
	GSHandle ret = BMReallocHandle (handle, nBytes, reallocFlags, actionCode);
	if (ret == nullptr) {
		RaiseExceptionFromBMError (BMError ());
	}
	return ret;
}

inline GSSize BMXhClear (GSHandle handle)
{
	GSSize ret = BMClearHandle (handle);
	if (ret == 0) {
		RaiseExceptionFromBMError (BMError ());
	}
	return ret;
}


inline GSPtr BMX_pAll (GSSize nBytes, GSFlags flags)
{
	GSPtr ret = BMAllocatePtr (nBytes, flags, 0);
	if (ret == nullptr) {
		RaiseExceptionFromBMError (BMError ());
	}
	return ret;
}

inline void BMXpFree (GSPtr ptr)
{
	BMKillPtr (&ptr);
	GSErr bmError = BMError ();
	if (bmError != NoError) {
		RaiseExceptionFromBMError (bmError);
	}
}

inline void BMXpKill (GSPtr* ptr)
{
	BMKillPtr (ptr);
	GSErr bmError = BMError ();
	if (bmError != NoError) {
		RaiseExceptionFromBMError (bmError);
	}
}

inline GSSize BMXpGetSize (GSPtr ptr)
{
	GSSize ret = BMGetPtrSize (ptr);
	if (ret == 0) {
		RaiseExceptionFromBMError (BMError ());
	}
	return ret;
}

inline void BMX_hToHandle (GSHandle ihandle, GSHandle* ohandle)
{
	GSErr ret = BMHandleToHandle (ihandle, ohandle);
	if (ret != NoError) {
		RaiseExceptionFromBMError (BMError ());
	}
}

inline void BMX_hAndHandle (GSHandle ihandle, GSHandle ohandle)
{
	GSErr ret = BMHandleAndHandle (ihandle, ohandle);
	if (ret != NoError) {
		RaiseExceptionFromBMError (BMError ());
	}
}

inline void BMX_pToHandle (const GSConstPtr ptr, GSHandle* handle, GSSize nBytes)
{
	GSErr ret = BMPtrToHandle (ptr, handle, nBytes);
	if (ret != NoError) {
		RaiseExceptionFromBMError (BMError ());
	}
}

inline void BMX_pAndHandle (const GSConstPtr ptr, GSHandle handle, GSSize nBytes)
{
	GSErr ret = BMPtrAndHandle (ptr, handle, nBytes);
	if (ret != NoError) {
		RaiseExceptionFromBMError (BMError ());
	}
}


#define		BMXhAll(n)					(GS::BMX_hAll (n, 0))
#define		BMXhAllClear(n)				(GS::BMX_hAll (n, ALLOCATE_CLEAR))
#define		BMXhSetSize(h, n)			(GS::BMX_hSetSize (h, n, 0, 0))
#define		BMXhSetSizeClear(h, n)		(GS::BMX_hSetSize (h, n, REALLOC_CLEAR, 0))
#define		BMXhSetSizeFullClear(h, n)	(GS::BMX_hSetSize (h, n, REALLOC_FULLCLEAR, 0))
#define		BMXhReal(h, n)				(GS::BMX_hSetSize (h, n, REALLOC_DISPOSE, 0))
#define		BMXhReal1(h, n)				(GS::BMX_hSetSize (h, n, REALLOC_SHRINK, 0))
#define		BMXhAllSetSizeClear(h, n)	(GS::BMX_hSetSize (h, n, REALLOC_CLEAR, 0))


#define		BMXpAll(n)					(GS::BMX_pAll (n, 0))
#define		BMXpAllClear(n)				(GS::BMX_pAll (n, ALLOCATE_CLEAR))

#define		BMXhToHandle(ih, oh)		(GS::BMX_hToHandle (ih, oh))
#define		BMXpToHandle(p, h, n)		(GS::BMX_pToHandle (p, h, n))
#define		BMXhAndHandle(ih, oh)		(GS::BMX_hAndHandle (ih, oh))
#define		BMXpAndHandle(p, h, n)		(GS::BMX_pAndHandle (p, h, n))



/*------------------------------------------------------------------------------*/
/*					Pointer and handle guard utility classes					*/
/*------------------------------------------------------------------------------*/

class GuardedHandle {
private:
	GSHandle	handle;

	GuardedHandle (const GuardedHandle& source);				// disabled
	GuardedHandle& operator= (const GuardedHandle& source);	// disabled

public:
	inline GuardedHandle (void);
	inline explicit GuardedHandle (GSHandle src);
	inline explicit GuardedHandle (GSSize bytesNum);
	inline ~GuardedHandle ();

	inline void		Allocate (GSSize bytesNum);
	inline GSHandle	GetHandle (void);
};


inline GuardedHandle::GuardedHandle (void) : handle (nullptr)
{
}

inline GuardedHandle::GuardedHandle (GSHandle src) : handle (src)
{
}

inline GuardedHandle::GuardedHandle (GSSize bytesNum) : handle (BMXhAll (bytesNum))
{
}


inline GuardedHandle::~GuardedHandle ()
{
	try {
		BMXhKill (&handle);
	} catch (...) {
	}
}

inline void GuardedHandle::Allocate (GSSize bytesNum)
{
	if (handle == nullptr) {
		handle = BMXhAll (bytesNum);
	} else {
		DBBREAK ();
	}
}

inline GSHandle GuardedHandle::GetHandle (void)
{
	return handle;
}

}	// namespace GS

#endif
