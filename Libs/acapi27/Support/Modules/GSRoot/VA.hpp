/********************************************************************************/
/*																				*/
/*								Virtual Array Manager							*/
/*																				*/
/********************************************************************************/

#ifndef	VA_HPP
#define	VA_HPP

#pragma once

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "BM.hpp"

/*------------------------------------------------------------------------------*/
/*									Manager identifier							*/
/*------------------------------------------------------------------------------*/

#define	IDVA01Manager	'VA01'
#define	IDVA02Manager	'VA02'		// deleteItems, insertItem added
#define	IDVAManager		'VA03'		// option to avoid REALLOC_DISPOSE method in allocation

#define	IDVATManager	'VT01'

/*------------------------------------------------------------------------------*/
/*									Type definitions							*/
/*------------------------------------------------------------------------------*/

#if !defined (DESC_DEFINED)
#define	DESC_DEFINED
struct DESC {
	Int32		lastind;
	Int32		maxind;
	Int32		npage;
	Int32		size;
	GSHandle	arrhdl;
};		/* 20 */
#endif

struct VATDESC {
	Int32		freeind;
	Int32		lastind;
	Int32		maxind;
	Int32		npage;
	Int32		size;
	GSHandle	arrhdl;
};	/* 24 */

/*------------------------------------------------------------------------------*/
/*									Function tables								*/
/*------------------------------------------------------------------------------*/

struct TVAManager {
	void		(STDCALL* unused) (DESC *dptr);
	GSErr		(STDCALL* init) (DESC *dptr, Int32 npage, Int32 size);
	Int32		(STDCALL* spac) (DESC *dptr);
	Int32		(STDCALL* nspac) (DESC *dptr, Int32 n);
	GSErr		(STDCALL* real) (DESC *dptr, Int32 lasti, Int32 maxi);
	void		(STDCALL* decr) (DESC *dptr);
	GSErr		(STDCALL* release) (DESC *dptr);
	void		(STDCALL* freedesc) (DESC *dptr);
	GSErr		(STDCALL* copyAll) (DESC *todesc, const DESC *fromdesc);
	GSErr		(STDCALL* addFromArr) (DESC *dptr, const void *arr, Int32 n);
	GSErr		(STDCALL* clearIndex) (DESC *dptr, Int32 index);
	GSErr		(STDCALL* sort) (DESC *dptr, GS::CmpFunction *cmpFunc);
	Int32		(STDCALL* search) (const DESC *dptr, const void *data, GS::CmpFunction *cmpFunc);
	GSErr		(STDCALL* deleteItems) (DESC *dptr, Int32 from, Int32 range);
	GSErr		(STDCALL* insertItem) (DESC *dptr, Int32 idx, const void *data);
	GSErr		(STDCALL* initNoAlloc) (DESC *dptr, Int32 npage, Int32 size);
	Int32		(STDCALL* spacKeep) (DESC *dptr);
	Int32		(STDCALL* nspacKeep) (DESC *dptr, Int32 n);
};

struct TVATManager {
	GSErr		(STDCALL* tInit) (VATDESC *dptr, Int32 npage, Int32 size);
	Int32		(STDCALL* tFind) (VATDESC *dptr);
	GSErr		(STDCALL* tClear) (VATDESC *dptr, Int32 ind);
	GSErr		(STDCALL* tUpdate) (VATDESC *dptr);
	void		(STDCALL* tFree) (VATDESC *dptr);
	Int32		(STDCALL* tNrElements) (VATDESC *dptr);
};

extern GSROOT_DLL_EXPORT TVAManager&	vaManager;
extern GSROOT_DLL_EXPORT TVATManager&	vatManager;

/*------------------------------------------------------------------------------*/
/*									Constant definitions						*/
/*------------------------------------------------------------------------------*/

#define	VAT_FREE		-99

/*------------------------------------------------------------------------------*/
/*									Function macros								*/
/*------------------------------------------------------------------------------*/

#if defined (DEBUVERS)

#define		VAUnused				vaManager.unused
#define		VAInit(d,n,s)		 	(vaManager.init (d, n, s))
#define		VASpac(d)			 	(vaManager.spac (d))
#define		VANspac(d,n)		 	(vaManager.nspac (d, n))
#define		VAReal(d,l,m)		 	(vaManager.real (d, l, m))
#define		VADecr(d)			 	(vaManager.decr (d))
#define		VARelease(d)		 	(vaManager.release (d))
#define		VAFree(d)			 	(vaManager.freedesc (d))
#define		VACopyAll(t,f)		 	(vaManager.copyAll (t, f))
#define		VAAddFromArr(d,a,n)	 	(vaManager.addFromArr (d, a, n))
#define		VAClearIndex(d,i)	 	(vaManager.clearIndex (d, i))
#define		VASort(d,c)			 	(vaManager.sort (d, c))
#define		VASearch(d,dt,c)	 	(vaManager.search (d, dt, c))
#define		VADelete(d,f,r)		 	(vaManager.deleteItems (d, f, r))
#define		VAInsert(d,i,dt)	 	(vaManager.insertItem (d, i, dt))
#define		VAInitNoAlloc(d,n,s) 	(vaManager.initNoAlloc (d, n, s))
#define		VASpacKeep(d)		 	(vaManager.spacKeep (d))
#define		VANspacKeep(d,n)	 	(vaManager.nspacKeep (d, n))

#define		VATInit(d,n,s)		 	(vatManager.tInit (d, n, s))
#define		VATFind(d)			 	(vatManager.tFind (d))
#define		VATClear(d,i)		 	(vatManager.tClear (d, i))
#define		VATUpdate(d)		 	(vatManager.tUpdate (d))
#define		VATFree(d)			 	(vatManager.tFree (d))
#define		VATNrElements(d)	 	(vatManager.tNrElements (d))

#else

inline	void	VAUnused (DESC *dptr)
					{	vaManager.unused (dptr);							}
inline	GSErr	VAInit (DESC *dptr, Int32 npage, Int32 size)
					{	return  vaManager.init (dptr, npage, size);			}
inline	Int32	VASpac (DESC *dptr)
					{	return  vaManager.spac (dptr);						}
inline	Int32	VANspac (DESC *dptr, Int32 n)
					{	return  vaManager.nspac (dptr, n);					}
inline	GSErr	VAReal (DESC *dptr, Int32 lasti, Int32 maxi)
					{	return  vaManager.real (dptr, lasti, maxi);			}
inline	void	VADecr (DESC *dptr)
					{	vaManager.decr (dptr);								}
inline	GSErr	VARelease (DESC *dptr)
					{	return  vaManager.release (dptr);					}
inline	void	VAFree (DESC *dptr)
					{	vaManager.freedesc (dptr);							}
inline	GSErr	VACopyAll (DESC *todesc, const DESC *fromdesc)
					{	return  vaManager.copyAll (todesc, fromdesc);		}
inline	GSErr	VAAddFromArr (DESC *dptr, const void *arr, Int32 n)
					{	return  vaManager.addFromArr (dptr, arr, n);		}
inline	GSErr	VAClearIndex (DESC *dptr, Int32 index)
					{	return  vaManager.clearIndex (dptr, index);			}
inline	GSErr	VASort (DESC *dptr, GS::CmpFunction *cmpFunc)
					{	return  vaManager.sort (dptr, cmpFunc);				}
inline	Int32	VASearch (const DESC *dptr, const void *data, GS::CmpFunction *cmpFunc)
					{	return  vaManager.search (dptr, data, cmpFunc);		}
inline	GSErr	VADelete (DESC *dptr, Int32 from, Int32 range)
					{	return  vaManager.deleteItems (dptr, from, range);	}
inline	GSErr	VAInsert (DESC *dptr, Int32 idx, const void *data)
					{	return  vaManager.insertItem (dptr, idx, data);		}
inline	GSErr	VAInitNoAlloc (DESC *dptr, Int32 npage, Int32 size)
					{	return  vaManager.initNoAlloc (dptr, npage, size);	}
inline	Int32	VASpacKeep (DESC *dptr)
					{	return  vaManager.spacKeep (dptr);					}
inline	Int32	VANspacKeep (DESC *dptr, Int32 n)
					{	return  vaManager.nspacKeep (dptr, n);				}

inline	GSErr	VATInit (VATDESC *dptr, Int32 npage, Int32 size)
					{	return  vatManager.tInit (dptr, npage, size);		}
inline	Int32	VATFind (VATDESC *dptr)
					{	return  vatManager.tFind (dptr);					}
inline	GSErr	VATClear (VATDESC *dptr, Int32 ind)
					{	return  vatManager.tClear (dptr, ind);				}
inline	GSErr	VATUpdate (VATDESC *dptr)
					{	return  vatManager.tUpdate (dptr);					}
inline	void	VATFree (VATDESC *dptr)
					{	vatManager.tFree (dptr);							}
inline	Int32	VATNrElements (VATDESC *dptr)
					{	return  vatManager.tNrElements (dptr);				}

#endif

#endif	/* VA_HPP */
