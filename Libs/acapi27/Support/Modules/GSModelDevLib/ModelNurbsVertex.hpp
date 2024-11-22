#ifndef ModelNurbsVertex_h__
#define ModelNurbsVertex_h__

#include "Vertex.hpp"
#include "ModelNurbsElementWithTolerance.hpp"

namespace ModelerAPI
{
	class NurbsVertex : public Vertex, public NurbsElementWithTolerance {
	public:
		NurbsVertex (double x, double y, double z, double tolerance) : Vertex (x, y, z), NurbsElementWithTolerance (tolerance) {}
	};
} // namespace ModelerAPI
#endif // ModelNurbsVertex_h__