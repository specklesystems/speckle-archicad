

#ifndef	_ENDIANSWAP_HPP_
#define	_ENDIANSWAP_HPP_

// Swap the endian with IV<Type> functions: IV<Type> (DifferentEndianPlatform (), variable)
// Doesn't work for IVChars!

#if defined (_MSC_VER)				// kzs-vs2005
#pragma warning (disable: 4127)		// conditional expression is constant
#endif


inline GS::PlatformSign		DifferentEndianPlatform ()
{
	switch (GS::Act_Platform_Sign) {
		case GS::Win_Platform_Sign:		return GS::Mac_Platform_Sign;
		case GS::Mac_Platform_Sign:		return GS::Win_Platform_Sign;
		case GS::Mactel_Platform_Sign:	return GS::Mac_Platform_Sign;
		default:						DBBREAK (); return GS::Act_Platform_Sign;
	}
}


inline bool ValidPlatform (GS::PlatformSign platform)
{
	return platform == GS::Mac_Platform_Sign || platform == GS::Win_Platform_Sign || platform == GS::Mactel_Platform_Sign;
}


#endif // _ENDIANSWAP_HPP_
