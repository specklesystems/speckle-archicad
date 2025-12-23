#ifndef GEOM_PPE_RESIDUALACCURACYCALCDATA_HPP
#define GEOM_PPE_RESIDUALACCURACYCALCDATA_HPP
#pragma once

class ResidualAccuracyCalcData
{
public: 
	ResidualAccuracyCalcData ();
	void UpdateMaxNormError (const double actError) const;

	mutable double	maxNormError; //collecting the max error!
	double	geometryEPS;
	bool	pleaseReportAccuracy;
};

#endif
