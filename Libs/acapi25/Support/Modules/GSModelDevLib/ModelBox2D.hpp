// *****************************************************************************
// Box2D
// GSModeler, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MODELBOX2D_HPP)
#define MODELBOX2D_HPP


// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class Box2D {
public:
	double	xMin;
	double	xMax;
	double	yMin;
	double	yMax;

	Box2D () : xMin (0.0), xMax (0.0), yMin (0.0), yMax (0.0) {}
	Box2D (double xMi, double xMa, double yMi, double yMa) : xMin (xMi), xMax (xMa), yMin (yMi), yMax (yMa) {}
};


} // namespace ModelerAPI


#endif
