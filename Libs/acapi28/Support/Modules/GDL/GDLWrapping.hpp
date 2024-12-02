// *********************************************************************************************************************
// Description:		GDLWrapping.hpp
//					Defines Texture wrapping types and flags.
//					http://wiki/w/Text%C3%BAra_vet%C3%ADt%C3%A9sek
//					http://wiki/w/Text%C3%BAra_vet%C3%ADt%C3%A9si_t%C3%ADpusok
//
// Module:			GDL
// Namespace:
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GDLWRAPPING_HPP)
#define GDLWRAPPING_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"GSDebug.hpp"

// from GDL
#include	"GDLExport.h"

// from GSUtils
#include	"GSUtilsDefs.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {
	class IChannel;
	class OChannel;
	class XMLIChannel;
	class XMLOChannel;
	class ObjectState;
}

// --- Constant definitions	--------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------------
// Wrapping method values.
// ---------------------------------------------------------------------------------------------------------------------
enum WrapMethod {
	W_FROMBODY		= 0,
	W_UNKNOWN		= 0,

	W_BOXPLANAR		= 1,
	W_CUBIC			= 2,
	W_CYLINDRIC		= 3,
	W_SPHERIC		= 4,

	W_PLANCYLIND	= 5,
	W_PLANAR		= 6,
	W_NURBSPARAM	= 7,

	W_PRISM			= 20,
	W_PWALL			= 21,
	W_BWALL			= 22,

	W_CYLINDSEC		= 23,
	W_CONE			= 24,

	W_ELLIPS		= 25,
	W_ELBOW			= 26,

//	W_PYRAMID		= 27,
//	W_SWEEP			= 28,
//	W_RULED			= 29,

	W_ROOF			= 30,

//	W_SITE			= 31,

	W_MINMAX		= 99,

	W_MAXVALUE		= 99	/* increment if you add a new value */
};


// ---------------------------------------------------------------------------------------------------------------------
// Wrapping flag values, use for Wrapping::flags.
// First two bits are free for future use.
// ---------------------------------------------------------------------------------------------------------------------
enum WrapFlag : STATL {
	W_NOFLAGS			= 0x0000,

	W_QUADRICFIT		= 0x0004,			/* 0b 00000000 00000100 */
	W_UVDISTANCE		= 0x0008,			/* 0b 00000000 00001000 */
	W_UVTRIANGLE		= 0x0010,			/* 0b 00000000 00010000 */
	W_UVMASKS			= W_QUADRICFIT
						| W_UVDISTANCE
						| W_UVTRIANGLE,

	W_GLOBAL_X			= 0x0020,			/* 0b 00000000 00100000 */
	W_GLOBAL_Y			= 0x0040,			/* 0b 00000000 01000000 */
	W_GLOBAL_Z			= 0x0080,			/* 0b 00000000 10000000 */
	W_GLOBAL_COORDS		= W_GLOBAL_X
						| W_GLOBAL_Y
						| W_GLOBAL_Z,

	W_GENERATE_ON_CUT	= 0x0100,			/* 0b 00000001 00000000 */

	W_ALLFLAGS			= W_GENERATE_ON_CUT
						| W_UVMASKS
						| W_GLOBAL_COORDS
};

// --- Type definitions	------------------------------------------------------------------------------------------------


// Texture wrapping type for bodies and polygons.
// @method	stores the texture wrapping method.
// @flags	stores various options of the wrapping.
//
// Note. Formerly wrapping was a short with the higher byte for flags and the lower byte for method values.
// In some places (e.g. Body::ReadVersion2 or in the GDL interpreter) you can find compatibility code that
// converts the old short value to a Wrapping struct.

class GDL_DLL_EXPORT Wrapping
{
public:
	GDL_DLL_EXPORT
	friend short GDL_CALL CmpWrappings (const Wrapping& lhs, const Wrapping& rhs);

	static const Wrapping NoWrapping;
	static const Wrapping DefaultBoxPlanar;
	static const Wrapping DefaultPlanar;
	static const Wrapping DefaultCubic;
	static const Wrapping DefaultPrism;
	static const Wrapping DefaultPWall;
	static const Wrapping DefaultBWall;
	static const Wrapping DefaultElbow;
	static const Wrapping DefaultRoof;
	static const Wrapping DefaultMinMax;

	static const Wrapping DefaultUV;

	static Wrapping FromOldWrapping (short oldWrap);
	static short	ToOldWrapping	(Wrapping newWrap);


	Wrapping () : Wrapping (W_UNKNOWN, W_NOFLAGS) {
		// do nothing
	}

	Wrapping (const WrapMethod inMethod) : Wrapping (inMethod, W_NOFLAGS) {
		// do nothing
	}

	Wrapping (const WrapMethod inMethod, const STATL inFlags) : method (inMethod), flags (inFlags) {
		DBASSERT (Check ());
		// do nothing
	}

	inline WrapMethod GetMethod () const {
		return method;
	}

	inline STATL GetFlags () const {
		return flags;
	}

	inline STATL GetUVFlags () const {
		return flags & W_UVMASKS;
	}

	inline void	AddFlags (STATL inFlags) {
		SET_FLAGS (flags, inFlags);
	}

	inline void	RemoveFlags (STATL inFlags = W_ALLFLAGS) {
		CLR_FLAGS (flags, inFlags);
	}

	// Return true if ALL of the given flags are set on this Wrapping.
	inline bool	HasAllFlag (STATL inFlag) const
	{
		return HAS_ALL_FLAGS (flags, inFlag);
	}

	// Return true if only the given flag @inFlag is set. If @inFlag is not set or
	// any other flag is set, return false.
	inline bool	HasOnlyFlag (STATL inFlag) const
	{
		return HAS_ALL_FLAGS (flags, inFlag) && HAS_ONLY_FLAGS (flags, inFlag);
	}

	// Returns true if any of the given flags are set.
	inline bool	HasAnyFlag (STATL inFlag = W_ALLFLAGS) const
	{
		return HAS_ANY_FLAGS (flags, inFlag);
	}

	inline bool	HasMethod (WrapMethod inMethod) const
	{
		return method == inMethod;
	}

	GSErrCode	Read		(GS::IChannel& ic);
	GSErrCode	Write		(GS::OChannel& oc) const;
	void		ReadXML		(GS::XMLIChannel& inXML);
	void		WriteXML	(GS::XMLOChannel& outXML) const;
	GSErrCode	Store		(GS::ObjectState& os) const;
	GSErrCode	Restore		(const GS::ObjectState& os);

	// Basic check if the wrapping instance is valid (has a valid @value and valid @flags).
	// This method could be called @IsValid, but this name can make confusion along with IsUnknown().
	inline bool	Check () const
	{
		const bool methodOk = method >= 0 && method <= W_MAXVALUE;
		const bool flagsOk = HAS_ONLY_FLAGS (flags, W_ALLFLAGS);

		return methodOk && flagsOk;
	}

private:
	WrapMethod	method;
	STATL		flags;
};


// --- Variable declarations -------------------------------------------------------------------------------------------


// --- Function declarations -------------------------------------------------------------------------------------------

GDL_DLL_EXPORT
short GDL_CALL CmpWrappings (const Wrapping& lhs, const Wrapping& rhs);

GDL_DLL_EXPORT
bool GDL_CALL operator== (const Wrapping& lhs, const Wrapping& rhs);

GDL_DLL_EXPORT
bool GDL_CALL operator!= (const Wrapping& lhs, const Wrapping& rhs);

#endif // GDLWRAPPING_HPP
