// *****************************************************************************
// Color
// GSModeler, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MODELCOLOR_HPP)
#define MODELCOLOR_HPP


// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class Color {
public:
	double	red;
	double	green;
	double	blue;

	Color () : red (0.0), green (0.0), blue (0.0) {}
	Color (double r, double g, double b) : red (r), green (g), blue (b) {}

	inline bool		operator== (const Color& other) const;
	inline bool		operator!= (const Color& other) const;
	inline bool		operator< (const Color& other) const;
};


// ----------------------- Class implementation --------------------------------

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

bool		Color::operator== (const Color& other) const
{
	return red == other.red && green == other.green && blue == other.blue;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

bool		Color::operator!= (const Color& other) const
{
	return !(*this == other);
}


bool		Color::operator< (const Color& other) const
{
	if (red != other.red)
		return red < other.red;
	if (green != other.green)
		return green < other.green;
	if (blue != other.blue)
		return blue < other.blue;

	return false;
}


} // namespace ModelerAPI


#endif
