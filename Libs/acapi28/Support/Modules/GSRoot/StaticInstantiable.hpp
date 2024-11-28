// *********************************************************************************************************************
//
// Description:	   A class that enables user-defined ordering of global static variable construction.
//
// Module:		   GSRoot
// Namespace:	   GS
// Contact person: MB
//
// *********************************************************************************************************************


#ifndef STATICINSTANTIABLE_HPP
#define STATICINSTANTIABLE_HPP

#pragma once


#include "ConditionalInitialization.hpp"

namespace GS {


// === class StaticInstantiable ========================================================================================

class GSROOT_DLL_EXPORT StaticInstantiable : public InitializationCondition, private ConditionallyInitialized {
protected:
	void		ObjectConstructed ();

	void		ObjectConstructedIf (const StaticInstantiable*						prerequisite,
									 const std::function<void ()>&					constructorFunction);

	void		ObjectConstructedIf (const GS::HashSet<const StaticInstantiable*>&	prerequisites,
									 const std::function<void ()>&					constructorFunction);

	static bool IsAlive (const StaticInstantiable* object);
};


}	// namespace GS


#endif
