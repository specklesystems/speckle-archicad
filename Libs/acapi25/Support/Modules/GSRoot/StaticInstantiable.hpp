// *********************************************************************************************************************
//
// Description:	   A class that enables user-defined ordering of global static variable construction.
//
// Module:		   GSRoot
// Namespace:	   GS
// Contact person: MB, BIM
//
// *********************************************************************************************************************


#ifndef STATICINSTANTIABLE_HPP
#define STATICINSTANTIABLE_HPP

#pragma once


#include <functional>
#include "GSRootExport.hpp"

namespace GS { template <class T> class HashSet; }


namespace GS {


// === class StaticInstantiable ========================================================================================

class GSROOT_DLL_EXPORT StaticInstantiable {
public:

	void		ObjectInitialized () const;

	void		ObjectInitializedIf (const StaticInstantiable*						prerequisite,
									 const std::function<void ()>&					constructorFunction) const;

	void		ObjectInitializedIf (const GS::HashSet<const StaticInstantiable*>&	prerequisites,
									 const std::function<void ()>&					constructorFunction) const;

	bool		IsRegisteredForInitialization () const;


protected:
	~StaticInstantiable ();

	void		ObjectConstructed () const;

	void		ObjectConstructedIf (const StaticInstantiable*						prerequisite,
									 const std::function<void ()>&					constructorFunction) const;

	void		ObjectConstructedIf (const GS::HashSet<const StaticInstantiable*>&	prerequisites,
									 const std::function<void ()>&					constructorFunction) const;

	static bool IsAlive (const StaticInstantiable* object);

private:
	class DependencyTable;

	static DependencyTable&		GetDependencyTable ();
};


}	// namespace GS


#endif
