// *****************************************************************************
// Rect
// GSModeler, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MODELRECT_HPP)
#define MODELRECT_HPP

#include "Definitions.hpp"
// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class Rect {
public:
	Int32	left;
	Int32	right;
	Int32	top;
	Int32	bottom;

	inline Rect ();
	inline Rect (Int32 left, Int32 top, Int32 right, Int32 bottom);
};


// ----------------------- Class implementation --------------------------------

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline	Rect::Rect (Int32 l, Int32 t, Int32 r, Int32 b) :
	left (l),
	right (r),
	top (t),
	bottom (b)
{
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

inline	Rect::Rect () :
	left (0),
	right (0),
	top (0),
	bottom (0)
{
}


} // namespace ModelerAPI


#endif
