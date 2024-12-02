#ifndef CONDITIONAL_INITIALIZATION_HPP
#define CONDITIONAL_INITIALIZATION_HPP

#include "Definitions.hpp"
#include <functional>
#include "GSRootExport.hpp"

namespace GS { template <class T> class HashSet; }

namespace GS {

class ConditionalInitializationManager;

class GSROOT_DLL_EXPORT InitializationCondition {
public:
	static bool IsFulfilled (const InitializationCondition* condition);

public:
	~InitializationCondition();

	void MarkAsFulfilled ();	
};


class GSROOT_DLL_EXPORT ConditionallyInitialized {
	friend class ConditionalInitializationManager;

	USize					unfulfilledConditions;			// number of conditions, this object is waiting to
	std::function<void ()>	initializerFunction;			// function to call, if all conditions are fulfilled

public:
	ConditionallyInitialized ();

	void ObjectInitializedIf (const InitializationCondition* condition, const std::function<void ()>& initializerFunction);
	void ObjectInitializedIf (const GS::HashSet<const InitializationCondition*>& conditions, const std::function<void ()>& initializerFunction);


	bool IsRegisteredForInitialization () const;
};

}


#endif