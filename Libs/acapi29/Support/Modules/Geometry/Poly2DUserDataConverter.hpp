#ifndef GEOMETRY_POLY_2D_USER_DATA_CONVERTER_HPP_
#define GEOMETRY_POLY_2D_USER_DATA_CONVERTER_HPP_

namespace Geometry {

template <class VertexUserDataSrc, class EdgeUserDataSrc, class ContourUserDataSrc, class PolygonUserDataSrc,
		  class VertexUserDataTarget, class EdgeUserDataTarget, class ContourUserDataTarget, class PolygonUserDataTarget>
class Poly2DUserDataConverter
{
public:
	virtual bool ConvertVertexUserData (const VertexUserDataSrc& /*from*/, VertexUserDataTarget& /*to*/) const { return false; }
	virtual bool ConvertEdgeUserData (const EdgeUserDataSrc& /*from*/, EdgeUserDataTarget& /*to*/) const { return false; }
	virtual bool ConvertContourUserData (const ContourUserDataSrc& /*from*/, ContourUserDataTarget& /*to*/) const { return false; }
	virtual bool ConvertPolygonUserData (const PolygonUserDataSrc& /*from*/, PolygonUserDataTarget& /*to*/) const { return false; }
};

}		// namespace Geometry

#endif		// GEOMETRY_POLY_2D_USER_DATA_CONVERTER_HPP_