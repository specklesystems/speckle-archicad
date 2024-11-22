#ifndef GEOM_PPE_PARPROFILEENGSETUPINTERFACES_HPP
#define GEOM_PPE_PARPROFILEENGSETUPINTERFACES_HPP
#pragma once
#include "GeometricDefinitions.h"
#include "ModelIDs.hpp"

class ParProfileConstraintSetupInterface;
class ProfileModelSetupInterface;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GEOMETRY_DLL_EXPORT ParProfileEngSetupInterfaces
{
public:
	ParProfileEngSetupInterfaces ();
	virtual ~ParProfileEngSetupInterfaces ();

	ParProfileConstraintSetupInterface*	constraintSetup;
	ProfileModelSetupInterface*			modelSetup;
};
#endif //GEOM_PPE_PARPROFILEENGSETUPINTERFACES_HPP

