#ifndef THREADINGDEBUG_HPP
#define THREADINGDEBUG_HPP

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "GSDebug.hpp"


class GSROOT_DLL_EXPORT NonThreadSafeClass
{
	mutable GS::IntPtr	ownerThreadID;
	mutable Int32		delayCheck;

protected:
	NonThreadSafeClass (): ownerThreadID (0), delayCheck (0) {}
	void FunctionCalled (bool checkThread = true) const;

public:
	void LeaveThread (Int32 delayCheckP = 0) const
	{
		ownerThreadID = 0;
		delayCheck = delayCheckP;
	}

	void FUNCTIONCALLED (bool checkThread) const
	{
		FunctionCalled (checkThread);
	}

	void FUNCTIONCALLEDCHECKTHREAD () const
	{
		FunctionCalled ();
	}
};


inline NonThreadSafeClass& LEAVETHREAD (NonThreadSafeClass& nonThreadSafeClass, Int32 delayCheck = 0)
{
	nonThreadSafeClass.LeaveThread (delayCheck);

	return nonThreadSafeClass;
}


namespace GS {
	template <class T, class CounterT>
	class Ref;
}

template <class T, class CounterT>
inline GS::Ref<T, CounterT>& LEAVETHREAD (GS::Ref<T, CounterT>& ref, Int32 delayCheck = 0)
{
	if (ref != nullptr) {
		LEAVETHREAD (ref.GetCounter (), delayCheck);
	}

	return ref;
}

#endif // THREADINGDEBUG_HPP
