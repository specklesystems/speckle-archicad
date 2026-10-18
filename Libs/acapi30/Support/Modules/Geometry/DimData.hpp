#ifndef GEOM_PPE_DIMDATA_HPP
#define GEOM_PPE_DIMDATA_HPP
#pragma once

#include "GeometricDefinitions.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT DimData
{
public:
	enum class MetricType
	{
		Euclidean, Projected, Undefined
	};

	DimData ();
	virtual ~DimData ();

	MetricType GetType () const;
	void SetProjected (const double projAngleRadInit);
	void SetEuclidean ();
	void GetProjectionDir (double& dirX, double& dirY) const;
	double GetProjectionAngle () const;
private:
	MetricType	metric;
	double		projAngleRad;

};


#endif //GEOM_PPE_DIMDATA_HPP
