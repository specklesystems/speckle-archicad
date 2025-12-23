#ifndef GEOM_PPE_PARPROFILEENGOPTIONS_HPP
#define GEOM_PPE_PARPROFILEENGOPTIONS_HPP
#pragma once
#include "SolutionQuality.hpp"
#include "GeometricDefinitions.h"
#include "Ref.hpp"
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT ParProfileEngProcessControl
{
public: 
	virtual bool BreakEngineRun () const;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT ParProfileEngOptions
{
public:
	ParProfileEngOptions ();
	double GetEPS (const SolutionQuality solQ) const;

	double desiredSolutionAccuracy; //EPS
	GS::Ref<ParProfileEngProcessControl> procControl; 

	double goalFactor; //0 means keep all parameter on nominal value, 1 means full solution.
	bool DoContinuation () const;	//this option cannot be overridden!
	bool DisablePreStretching;
	bool ReportConvergenceData;
	bool ReportConvergenceTable;
	bool checkObjectiveSensCalculation;
	bool SVGDumpForStep;
	bool SVGDumpForStep_NominalModel;
	bool SVGDumpForStep_LastIter;
	bool SVGDumpForStep_StepLines;
	bool SVGDumpForStep_ProposedEdges;
	bool SVGDumpIterationData;
	bool SVGDumpIterationData_NominalModel;
	bool SVGDumpIterationData_OnlyLastIter;
	bool SVGDumpModelForSolution;
	bool SVGDumpInitialModel;
	bool ReportStepSolutionInfo;
	bool ReportProgress;
	bool ReportCurrentResidual;
	bool ReportSetup;
	std::string OutputFilePath;
	bool DumpSetup;
	std::string setupDumpFileName;
	bool ReportDBGInfo; //general all kinds of... 
	std::string SVGFileNamePrefix; 
};
#endif //GEOM_PPE_PARPROFILEENGOPTIONS_HPP
