// *****************************************************************************
// Vertex
// GSModeler, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (VERTEX_HPP)
#define VERTEX_HPP


// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class Vertex {
public:
	double	x;
	double	y;
	double	z;

	Vertex () : x (0.0), y (0.0), z (0.0) {}
	Vertex (double x_, double y_, double z_) : x (x_), y (y_), z (z_) {}
	
};


} // namespace ModelerAPI


#endif
