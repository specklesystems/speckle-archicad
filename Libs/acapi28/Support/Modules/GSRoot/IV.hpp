// *********************************************************************************************************************
// Description:		GRAPHISOFT Basic Type Conversion
//
// Namespace:		-
// Contact person:	MM
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (IV_HPP)
#define	IV_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"GSRootExport.hpp"

// =====================================================================================================================
// Inline helper funtions
// =====================================================================================================================

GSROOT_DLL_EXPORT bool	NeedByteSwap (GS::PlatformSign platformSign);

GSROOT_DLL_EXPORT void	IVBool (GS::PlatformSign platform, bool* pBool);
GSROOT_DLL_EXPORT void	IVSByte (GS::PlatformSign platform, char* pSByte);
GSROOT_DLL_EXPORT void	IVUByte (GS::PlatformSign platform, unsigned char* pUByte);
GSROOT_DLL_EXPORT void	IVShort (GS::PlatformSign platform, short* pShort);
GSROOT_DLL_EXPORT void	IVUShort (GS::PlatformSign platform, unsigned short *pUShort);
GSROOT_DLL_EXPORT void	IVLong (GS::PlatformSign platform, Int32 *pLong);
GSROOT_DLL_EXPORT void	IVULong (GS::PlatformSign platform, UInt32 *pULong);
GSROOT_DLL_EXPORT void	IVInt64 (GS::PlatformSign platform, Int64 *pInt64);
GSROOT_DLL_EXPORT void	IVUInt64 (GS::PlatformSign platform, UInt64 *pUInt64);
GSROOT_DLL_EXPORT void	IVFloat (GS::PlatformSign platform, float *pFloat);
GSROOT_DLL_EXPORT void	IVDouble (GS::PlatformSign platform, double *pDouble);
GSROOT_DLL_EXPORT void	IVUString (GS::PlatformSign platform, Utf16Char* pUString, UInt32 stringLength);

GSROOT_DLL_EXPORT void	IVBools (GS::PlatformSign platform,bool* pBool, Int32 nBools);
GSROOT_DLL_EXPORT void	IVSBytes (GS::PlatformSign platform,char* pSByte, Int32 nSBytes);
GSROOT_DLL_EXPORT void	IVUBytes (GS::PlatformSign platform,unsigned char* pUByte, Int32 nUBytes);
GSROOT_DLL_EXPORT void	IVShorts (GS::PlatformSign platform,short* pShort, Int32 nShorts);
GSROOT_DLL_EXPORT void	IVUShorts (GS::PlatformSign platform,unsigned short *pUShort, Int32 nUShorts);
GSROOT_DLL_EXPORT void	IVLongs (GS::PlatformSign platform,Int32 *pLong, Int32 nLongs);
GSROOT_DLL_EXPORT void	IVULongs (GS::PlatformSign platform,UInt32 *pULong, Int32 nULongs);
GSROOT_DLL_EXPORT void	IVInt64s (GS::PlatformSign platform,Int64 *pInt64, Int32 nInt64s);
GSROOT_DLL_EXPORT void	IVUInt64s (GS::PlatformSign platform,UInt64 *pUInt64, Int32 nUInt64s);
GSROOT_DLL_EXPORT void	IVFloats (GS::PlatformSign platform,float *pFloat, Int32 nFloats);
GSROOT_DLL_EXPORT void	IVDoubles (GS::PlatformSign platform,double *pDouble, Int32 nDoubles);

GSROOT_DLL_EXPORT void	IVBool (GS::PlatformSign from, GS::PlatformSign to, bool* pBool);
GSROOT_DLL_EXPORT void	IVSByte (GS::PlatformSign from, GS::PlatformSign to, char* pSByte);
GSROOT_DLL_EXPORT void	IVUByte (GS::PlatformSign from, GS::PlatformSign to, unsigned char* pUByte);
GSROOT_DLL_EXPORT void	IVShort (GS::PlatformSign from, GS::PlatformSign to, short* pShort);
GSROOT_DLL_EXPORT void	IVUShort (GS::PlatformSign from, GS::PlatformSign to, unsigned short *pUShort);
GSROOT_DLL_EXPORT void	IVLong (GS::PlatformSign from, GS::PlatformSign to, Int32 *pLong);
GSROOT_DLL_EXPORT void	IVULong (GS::PlatformSign from, GS::PlatformSign to, UInt32 *pULong);
GSROOT_DLL_EXPORT void	IVInt64 (GS::PlatformSign from, GS::PlatformSign to, Int64 *pInt64);
GSROOT_DLL_EXPORT void	IVUInt64 (GS::PlatformSign from, GS::PlatformSign to, UInt64 *pUInt64);
GSROOT_DLL_EXPORT void	IVFloat (GS::PlatformSign from, GS::PlatformSign to, float *pFloat);
GSROOT_DLL_EXPORT void	IVDouble (GS::PlatformSign from, GS::PlatformSign to, double *pDouble);
GSROOT_DLL_EXPORT void	IVUString (GS::PlatformSign from, GS::PlatformSign to, Utf16Char* pUString, UInt32 stringLength);

GSROOT_DLL_EXPORT void	IVBools (GS::PlatformSign from, GS::PlatformSign to, bool* pBool, Int32 nBools);
GSROOT_DLL_EXPORT void	IVSBytes (GS::PlatformSign from, GS::PlatformSign to, char* pSByte, Int32 nSBytes);
GSROOT_DLL_EXPORT void	IVUBytes (GS::PlatformSign from, GS::PlatformSign to, unsigned char* pUByte, Int32 nUBytes);
GSROOT_DLL_EXPORT void	IVShorts (GS::PlatformSign from, GS::PlatformSign to, short* pShort, Int32 nShorts);
GSROOT_DLL_EXPORT void	IVUShorts (GS::PlatformSign from, GS::PlatformSign to, unsigned short *pUShort, Int32 nUShorts);
GSROOT_DLL_EXPORT void	IVLongs (GS::PlatformSign from, GS::PlatformSign to, Int32 *pLong, Int32 nLongs);
GSROOT_DLL_EXPORT void	IVULongs (GS::PlatformSign from, GS::PlatformSign to, UInt32 *pULong, Int32 nULongs);
GSROOT_DLL_EXPORT void	IVInt64s (GS::PlatformSign from, GS::PlatformSign to, Int64 *pInt64, Int32 nInt64s);
GSROOT_DLL_EXPORT void	IVUInt64s (GS::PlatformSign from, GS::PlatformSign to, UInt64 *pUInt64, Int32 nUInt64s);
GSROOT_DLL_EXPORT void	IVFloats (GS::PlatformSign from, GS::PlatformSign to, float *pFloat, Int32 nFloats);
GSROOT_DLL_EXPORT void	IVDoubles (GS::PlatformSign from, GS::PlatformSign to, double *pDouble, Int32 nDoubles);

#endif
