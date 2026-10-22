#ifndef VECTORIMAGE_GEOMETRY_HPP
#define VECTORIMAGE_GEOMETRY_HPP
#pragma once

#include "VectorImage.hpp"


namespace VI {

class VI_DLL_EXPORT VectorImageGeometry
{
public:
	VectorImageGeometry (const VectorImage& image);

	void EnumerateHatchPolygons (const std::function<void (const Geometry::Polygon2D&)>&);
	void EnumerateHatchMultiPolygons (const std::function<void (const Geometry::MultiPolygon2D&)>&);
	void EnumerateHatchIrregularPolygons (const std::function<void (const Geometry::IrregularPolygon2D&)>&);

private:
	const VectorImage& image;
};

}

#endif
