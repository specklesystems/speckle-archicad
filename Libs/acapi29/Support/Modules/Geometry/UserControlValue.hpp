#ifndef GEOM_PPE_USERCONTROLVALUE_HPP
#define GEOM_PPE_USERCONTROLVALUE_HPP
#pragma once
#include "GeometricDefinitions.h"
#include "VarIndexType.hpp"
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT UserControlValue
{
public:
	enum class ControlType { UserGoalValue, KeepNominalValue, SolveForValue, PerturbationOnly, Undefined };

	UserControlValue (const std::string& controlValueIDInit);
	UserControlValue (const std::string& controlValueIDInit, const ControlType ct);
	UserControlValue (const std::string& controlValueIDInit, const double controlValueInit);
	UserControlValue (const std::string& controlValueIDInit, const ProbVarIndex& variableIndexInit);
	virtual ~UserControlValue ();

	void SetUndefined (); 
	void SetType (const ControlType newType);

	void SetControlValue (const double controlValueInit);
	void SetVarIndex (const ProbVarIndex& newVarIndex);
	void SetID (const std::string& newID);

	ControlType GetType () const;		//Asserts for GetType () == Undefined
	double GetValue () const;			//only for GetType () == UserGoalValue
	ProbVarIndex GetVarIndex () const;	//only for GetType () == SolveForValue
	const std::string& GetID () const;

private:
	std::string controlValueID;
	ControlType controlT;
	double controlValue;			//only for controlT == UserGoalValue
	ProbVarIndex variableIndex;		//only for controlT == SolveForValue
};

extern const std::string EngineInternalUCV_ID;

#endif //GEOM_PPE_USERCONTROLVALUE_HPP

