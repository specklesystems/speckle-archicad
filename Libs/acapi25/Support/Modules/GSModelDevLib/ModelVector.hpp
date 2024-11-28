// *****************************************************************************
// Vector
// GSModeler, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (VECTOR_HPP)
#define VECTOR_HPP


// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class Vector {
public:
	double	x;
	double	y;
	double	z;

	Vector () : x (0.0), y (0.0), z (0.0) {}
	Vector (double x_, double y_, double z_) : x (x_), y (y_), z (z_) {}
	Vector (const Vector& v) : x (v.x), y (v.y), z (v.z) {}

	inline double	GetLengthSqr () const { return x*x + y*y + z*z; }

	inline Vector	operator- (const Vector& v) const { return Vector (x - v.x, y - v.y, z - v.z); }
	inline Vector&	operator= (const Vector& v) { x = v.x; y = v.y; z = v.z; return *this; }
};


} // namespace ModelerAPI


#endif
