// =====================================================================================================================
// DGEventNotifier.hpp
// =====================================================================================================================

#ifndef DGEVENTNOTIFIER_HPP
#define DGEVENTNOTIFIER_HPP

#include <functional>
#include "DGUtility.hpp"

namespace {
template <typename T>
struct FunctionTraits
    : public FunctionTraits<decltype(&T::operator())>
{};

template <typename Class, typename Return, typename FirstArg, typename SecondArg>
struct FunctionTraits<Return(Class::*)(FirstArg, SecondArg) const>
{
	typedef Return ReturnType;
	typedef FirstArg FirstArgType;
	typedef SecondArg SecondArgType;
};

}

namespace DG {
class EventNotifierBase;

class DG_DLL_EXPORT EventTarget
{
	friend class EventNotifierBase;
	GS::Array<EventNotifierBase*> registeredNotifiers;
public:
	virtual ~EventTarget ();
};

class DG_DLL_EXPORT DefaultEventTargetProvider
{
public:
	virtual EventTarget* GetDefaultEventTarget () const = 0;
	virtual ~DefaultEventTargetProvider ();
};


class DG_DLL_EXPORT EventNotifierBase
{
	friend class EventTarget;
protected:
	virtual void UnRegisterEventTarget (EventTarget* eventTarget) = 0;
	void AddToTarget (EventTarget* target);
	void RemoveFromTarget (EventTarget* target);
public:
	virtual ~EventNotifierBase ();
};


template<typename S, typename E, typename T = void, bool B = true>
class EventNotifier : public EventNotifierBase
{
public:
	typedef S Source;
	typedef E EventArg;

	typedef std::function<T (const Source&, EventArg&)> Runnable;

private:
	struct RunnableHelper {
		EventTarget* eventTarget = nullptr;
		Runnable runnable;
		RunnableHelper (EventTarget* eventTarget, Runnable runnable) : eventTarget (eventTarget), runnable (runnable) { }
		RunnableHelper (Runnable runnable) : runnable (runnable) { }
	};

	GS::Array<RunnableHelper> runnables;
	std::function<void (bool)> notifierStateHandler;

	virtual void UnRegisterEventTarget (EventTarget* eventTarget) override;

public:
	EventNotifier ();
	~EventNotifier ();

	template<typename Object>
	EventNotifier&	operator+= (T (Object::*function)(const Source&, EventArg&));

	EventNotifier&	operator+= (T (*function)(const Source&, EventArg&));

	template<typename Lambda>
	EventNotifier&	operator+= (const Lambda& runnable);

	void SetNotifierStateHandler (std::function <void (bool)> stateHandler);

	T	NotifyAll (const Source&, EventArg&);
};


// EventNotifier partial template specialization: NotifyAll: void ----------------------------------------------------

template<typename S, typename E>
class EventNotifier<S, E, void, true> : public EventNotifierBase
{
public:
	typedef S Source;
	typedef E EventArg;

	typedef std::function<void (const Source&, EventArg&)> Runnable;

private:
	struct RunnableHelper {
		EventTarget* eventTarget = nullptr;
		Runnable runnable;
		RunnableHelper (EventTarget* eventTarget, Runnable runnable) : eventTarget (eventTarget), runnable (runnable) { }
		RunnableHelper (Runnable runnable) : runnable (runnable) { }
	};

	GS::Array<RunnableHelper> runnables;
	std::function<void (bool)> notifierStateHandler;

	virtual void UnRegisterEventTarget (EventTarget* eventTarget) override;

public:
	EventNotifier ();
	~EventNotifier ();

	template<typename Object>
	EventNotifier&	operator+= (void (Object::*function)(const Source&, EventArg&));

	EventNotifier&	operator+= (void (*function)(const Source&, EventArg&));

	template<typename Lambda>
	EventNotifier&	operator+= (const Lambda& runnable);

	template<typename Function, typename TargetType>
	EventNotifier&	Add (Function function, TargetType* target);
	EventNotifier&	Add (const Runnable& runnable, const EventTarget* target);

	void	SetNotifierStateHandler (std::function <void (bool)> stateHandler);

	void	NotifyAll (const Source&, EventArg&);
};


template<typename S, typename E>
EventNotifier<S, E, void, true>::EventNotifier ()
{
}

template<typename S, typename E>
EventNotifier<S, E, void, true>::~EventNotifier ()
{
	for (auto& r : runnables) {
		RemoveFromTarget (r.eventTarget);
	}
	runnables.Clear ();
}

template<typename S, typename E>
void	EventNotifier<S, E, void, true>::NotifyAll (const Source& s, EventArg& e)
{
	for (auto& r : runnables) {
		r.runnable (s, e);
	}
}

template<typename S, typename E>
void	EventNotifier<S, E, void, true>::SetNotifierStateHandler (std::function <void (bool)> stateHandler)
{
	notifierStateHandler = stateHandler;
}

template<typename S, typename E>
template<typename Lambda>
EventNotifier<S, E, void, true>&	EventNotifier<S, E, void, true>::operator+= (const Lambda& runnable)
{
	typedef FunctionTraits<Lambda> traits;
	static_assert(std::is_same<void, typename traits::ReturnType>::value, "Return type of the lambda must be void!");
	static_assert(std::is_same<const Source&, typename traits::FirstArgType>::value, "First argument must be const Source&!");
	static_assert(std::is_same<EventArg&, typename traits::SecondArgType>::value, "Second argument must be EventArg&!");

	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (runnable));
	return *this;
}

template<typename S, typename E>
template<typename Object>
EventNotifier<S, E, void, true>&	EventNotifier<S, E, void, true>::operator+= (void (Object::*function)(const Source&, EventArg&))
{
	static_assert ((std::is_base_of<EventTarget, Object>::value), "Target type must be a sub-class of DG::EventTarget");
	auto fun = [function] (const Source& s, EventArg& e) {
		Object* target = dynamic_cast<Object*> (s.GetDefaultEventTarget ());
		if (DBERROR (target == nullptr)) {
			return;
		}
		return (target->*function) (s, e);
	};
	runnables.Push (RunnableHelper (fun));
	return *this;
}

template<typename S, typename E>
EventNotifier<S, E, void, true>&	EventNotifier<S, E, void, true>::operator+= (void (*function)(const Source&, EventArg&))
{
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (function));
	return *this;
}

template<typename S, typename E>
template<typename Function, typename TargetType>
EventNotifier<S, E, void, true>&	EventNotifier<S, E, void, true>::Add (Function function, TargetType* target)
{
	static_assert ((std::is_base_of<EventTarget, TargetType>::value), "TargetType must be a sub-class of DG::EventTarget");
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (target, std::bind (function, target, std::placeholders::_1, std::placeholders::_2)));
	AddToTarget (target);
	return *this;
}


template<typename S, typename E>
EventNotifier<S, E, void, true>& EventNotifier<S, E, void, true>::Add (const Runnable& runnable, const EventTarget* target)
{
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (target, runnable));
	AddToTarget (target);
	return *this;
}


template<typename S, typename E>
void EventNotifier<S, E, void, true>::UnRegisterEventTarget (EventTarget* eventTarget)
{
	runnables.DeleteAll ([eventTarget] (const RunnableHelper& runnable) {
		return runnable.eventTarget == eventTarget;
	});
	if (runnables.IsEmpty () && notifierStateHandler != nullptr) {
		notifierStateHandler (false);
	}
}

// EventNotifier partial template specialization: NotifyAll: true ----------------------------------------------------

template<typename S, typename E>
class EventNotifier<S, E, bool, true> : public EventNotifierBase
{
public:
	typedef S Source;
	typedef E EventArg;

	typedef std::function<bool (const Source&, EventArg&)> Runnable;

private:
	struct RunnableHelper {
		EventTarget* eventTarget = nullptr;
		Runnable runnable;
		RunnableHelper (EventTarget* eventTarget, Runnable runnable) : eventTarget (eventTarget), runnable (runnable) { }
		RunnableHelper (Runnable runnable) : runnable (runnable) { }
	};

	GS::Array<RunnableHelper> runnables;
	std::function<void (bool)> notifierStateHandler;

	virtual void UnRegisterEventTarget (EventTarget* eventTarget) override;

public:
	EventNotifier ();
	~EventNotifier ();

	template<typename Object>
	EventNotifier&	operator+= (bool (Object::*function)(const Source&, EventArg&));

	EventNotifier&	operator+= (bool (*function)(const Source&, EventArg&));

	template<typename Lambda>
	EventNotifier&	operator+= (const Lambda& runnable);

	template<typename Function, typename TargetType>
	EventNotifier&	Add (Function function, TargetType* target);
	EventNotifier&	Add (const Runnable& runnable, const EventTarget* target);

	void	SetNotifierStateHandler (std::function <void (bool)> stateHandler);

	bool	NotifyAll (const Source&, EventArg&);
};


template<typename S, typename E>
EventNotifier<S, E, bool, true>::EventNotifier ()
{
}


template<typename S, typename E>
EventNotifier<S, E, bool, true>::~EventNotifier ()
{
	for (auto& r : runnables) {
		RemoveFromTarget (r.eventTarget);
	}
	runnables.Clear ();
}


template<typename S, typename E>
bool EventNotifier<S, E, bool, true>::NotifyAll (const Source& s, EventArg& e)
{
	bool ret = true;
	for (auto& r : runnables) {
		ret = ret && r.runnable (s, e);
		if (ret) break;
	}
	return ret;
}

template<typename S, typename E>
void	EventNotifier<S, E, bool, true>::SetNotifierStateHandler (std::function <void (bool)> stateHandler)
{
	notifierStateHandler = stateHandler;
}


template<typename S, typename E>
template<typename Object>
EventNotifier<S, E, bool, true>&	EventNotifier<S, E, bool, true>::operator+= (bool (Object::*function)(const Source&, EventArg&))
{
	static_assert ((std::is_base_of<EventTarget, Object>::value), "Target type must be a sub-class of DG::EventTarget");
	auto fun = [function] (const Source& s, EventArg& e) {
		Object* target = dynamic_cast<Object*> (s.GetDefaultEventTarget ());
		if (DBERROR (target == nullptr)) {
			return true;
		}
		return (target->*function) (s, e);
	};
	runnables.Push (RunnableHelper (fun));
	return *this;
}


template<typename S, typename E>
template<typename Lambda>
EventNotifier<S, E, bool, true>&	EventNotifier<S, E, bool, true>::operator+= (const Lambda& runnable)
{
	typedef FunctionTraits<Lambda> traits;
	static_assert(std::is_same<bool, typename traits::ReturnType>::value, "Return type of the lambda must be bool!");
	static_assert(std::is_same<const Source&, typename traits::FirstArgType>::value, "First argument must be const Source&!");
	static_assert(std::is_same<EventArg&, typename traits::SecondArgType>::value, "Second argument must be EventArg&!");

	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (runnable));
	return *this;
}


template<typename S, typename E>
template<typename Function, typename TargetType>
EventNotifier<S, E, bool, true>&	EventNotifier<S, E, bool, true>::Add (Function function, TargetType* target)
{
	static_assert ((std::is_base_of<EventTarget, TargetType>::value), "TargetType must be a sub-class of DG::EventTarget");
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (target, std::bind (function, target, std::placeholders::_1, std::placeholders::_2)));
	AddToTarget (target);
	return *this;
}


template<typename S, typename E>
EventNotifier<S, E, bool, true>& EventNotifier<S, E, bool, true>::Add (const Runnable& runnable, const EventTarget* target)
{
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (target, runnable));
	AddToTarget (target);
	return *this;
}


template<typename S, typename E>
void EventNotifier<S, E, bool, true>::UnRegisterEventTarget (EventTarget* eventTarget)
{
	runnables.DeleteAll ([eventTarget] (const RunnableHelper& runnable) {
		return runnable.eventTarget == eventTarget;
	});
	if (runnables.IsEmpty () && notifierStateHandler != nullptr) {
		notifierStateHandler (false);
	}
}

// EventNotifier partial template specialization: NotifyAll: false ---------------------------------------------------

template<typename S, typename E>
class EventNotifier<S, E, bool, false> : public EventNotifierBase
{
public:
	typedef S Source;
	typedef E EventArg;

	typedef std::function<bool (const Source&, EventArg&)> Runnable;

private:
	struct RunnableHelper {
		EventTarget* eventTarget = nullptr;
		Runnable runnable;
		RunnableHelper (EventTarget* eventTarget, Runnable runnable) : eventTarget (eventTarget), runnable (runnable) { }
		RunnableHelper (Runnable runnable) : runnable (runnable) { }
	};

	GS::Array<RunnableHelper> runnables;
	std::function<void (bool)> notifierStateHandler;

	virtual void UnRegisterEventTarget (EventTarget* eventTarget) override;

public:
	EventNotifier ();
	~EventNotifier ();

	template<typename Object>
	EventNotifier&	operator+= (bool (Object::*function)(const Source&, EventArg&));

	EventNotifier&	operator+= (bool (*function)(const Source&, EventArg&));

	template<typename Lambda>
	EventNotifier&	operator+= (const Lambda& runnable);

	template<typename Function, typename TargetType>
	EventNotifier&	Add (Function function, TargetType* target);
	EventNotifier&	Add (const Runnable& runnable, const EventTarget* target);

	void	SetNotifierStateHandler (std::function <void (bool)> stateHandler);

	bool	NotifyAll (const Source&, EventArg&);
};


template<typename S, typename E>
EventNotifier<S, E, bool, false>::EventNotifier ()
{
}


template<typename S, typename E>
EventNotifier<S, E, bool, false>::~EventNotifier ()
{
	for (auto& r : runnables) {
		RemoveFromTarget (r.eventTarget);
	}
	runnables.Clear ();
}


template<typename S, typename E>
bool	EventNotifier<S, E, bool, false>::NotifyAll (const Source& s, EventArg& e)
{
	bool ret = false;
	for (auto& r : runnables) {
		ret = ret || r.runnable (s, e);
	}
	return ret;
}


template<typename S, typename E>
void	EventNotifier<S, E, bool, false>::SetNotifierStateHandler (std::function <void (bool)> stateHandler)
{
	notifierStateHandler = stateHandler;
}


template<typename S, typename E>
template<typename Lambda>
EventNotifier<S, E, bool, false>&		EventNotifier<S, E, bool, false>::operator+= (const Lambda& runnable)
{
	typedef FunctionTraits<Lambda> traits;
	static_assert(std::is_same<bool, typename traits::ReturnType>::value, "Return type of the lambda must be bool!");
	static_assert(std::is_same<const Source&, typename traits::FirstArgType>::value, "First argument must be const Source&!");
	static_assert(std::is_same<EventArg&, typename traits::SecondArgType>::value, "Second argument must be EventArg&!");

	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (runnable));
	return *this;
}

template<typename S, typename E>
template<typename Object>
EventNotifier<S, E, bool, false>&	EventNotifier<S, E, bool, false>::operator+= (bool (Object::*function)(const Source&, EventArg&))
{
	static_assert ((std::is_base_of<EventTarget, Object>::value), "Target type must be a sub-class of DG::EventTarget");
	auto fun = [function] (const Source& s, EventArg& e) {
		Object* target = dynamic_cast<Object*> (s.GetDefaultEventTarget ());
		if (DBERROR (target == nullptr)) {
			return false;
		}
		return (target->*function) (s, e);
	};
	runnables.Push (RunnableHelper (fun));
	return *this;
}

template<typename S, typename E>
EventNotifier<S, E, bool, false>&	EventNotifier<S, E, bool, false>::operator+= (bool (*function)(const Source&, EventArg&))
{
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (function));
	return *this;
}

template<typename S, typename E>
template<typename Function, typename TargetType>
EventNotifier<S, E, bool, false>& EventNotifier<S, E, bool, false>::Add (Function function, TargetType* target)
{
	static_assert ((std::is_base_of<EventTarget, TargetType>::value), "TargetType must be a sub-class of DG::EventTarget");
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (target, std::bind (function, target, std::placeholders::_1, std::placeholders::_2)));
	AddToTarget (target);
	return *this;
}


template<typename S, typename E>
EventNotifier<S, E, bool, false>& EventNotifier<S, E, bool, false>::Add (const Runnable& runnable, const EventTarget* target)
{
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (target, runnable));
	AddToTarget (target);
	return *this;
}


template<typename S, typename E>
void EventNotifier<S, E, bool, false>::UnRegisterEventTarget (EventTarget* eventTarget)
{
	runnables.DeleteAll ([eventTarget] (const RunnableHelper& runnable) {
		return runnable.eventTarget == eventTarget;
	});
	if (runnables.IsEmpty () && notifierStateHandler != nullptr) {
		notifierStateHandler (false);
	}
}


// EventNotifier partial template specialization: NotifyAll: short ---------------------------------------------------

template<typename S, typename E>
class EventNotifier<S, E, short, true> : public EventNotifierBase
{
public:
	typedef S Source;
	typedef E EventArg;

	typedef std::function<short (const Source&, EventArg&)> Runnable;

private:
	struct RunnableHelper {
		EventTarget* eventTarget = nullptr;
		Runnable runnable;
		RunnableHelper (EventTarget* eventTarget, Runnable runnable) : eventTarget (eventTarget), runnable (runnable) { }
		RunnableHelper (Runnable runnable) : runnable (runnable) { }
	};

	GS::Array<RunnableHelper> runnables;
	std::function<void (bool)> notifierStateHandler;

	virtual void UnRegisterEventTarget (EventTarget* eventTarget) override;

public:
	EventNotifier ();
	~EventNotifier ();

	template<typename Object>
	EventNotifier&	operator+= (short (Object::*function)(const Source&, EventArg&));

	EventNotifier&	operator+= (short (*function)(const Source&, EventArg&));

	template<typename Lambda>
	EventNotifier&	operator+= (const Lambda& runnable);

	template<typename Function, typename TargetType>
	EventNotifier&	Add (Function function, TargetType* target);
	EventNotifier&	Add (const Runnable& runnable, const EventTarget* target);

	void SetNotifierStateHandler (std::function <void (bool)> stateHandler);

	short	NotifyAll (const Source&, EventArg&);
};

template<typename S, typename E>
EventNotifier<S, E, short, true>::EventNotifier ()
{
}

template<typename S, typename E>
EventNotifier<S, E, short, true>::~EventNotifier ()
{
	for (auto& r : runnables) {
		RemoveFromTarget (r.eventTarget);
	}
	runnables.Clear ();
}

template<typename S, typename E>
short	EventNotifier<S, E, short, true>::NotifyAll (const Source& s, EventArg& e)
{
	short ret = 0;
	for (auto& r : runnables) {
		short funRet = r.runnable (s, e);
		if (funRet != 0)
			ret = funRet;
	}
	return ret;
}


template<typename S, typename E>
void	EventNotifier<S, E, short, true>::SetNotifierStateHandler (std::function <void (bool)> stateHandler)
{
	notifierStateHandler = stateHandler;
}

template<typename S, typename E>
template<typename Lambda>
EventNotifier<S, E, short, true>&		EventNotifier<S, E, short, true>::operator+= (const Lambda& runnable)
{
	typedef FunctionTraits<Lambda> traits;
	static_assert(std::is_same<short, typename traits::ReturnType>::value, "Return type of the lambda must be short!");
	static_assert(std::is_same<const Source&, typename traits::FirstArgType>::value, "First argument must be const Source&!");
	static_assert(std::is_same<EventArg&, typename traits::SecondArgType>::value, "Second argument must be EventArg&!");

	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (runnable));
	return *this;
}

template<typename S, typename E>
template<typename Object>
EventNotifier<S, E, short, true>&	EventNotifier<S, E, short, true>::operator+= (short (Object::*function)(const Source&, EventArg&))
{
	static_assert ((std::is_base_of<EventTarget, Object>::value), "Target type must be a sub-class of DG::EventTarget");
	auto fun = [function] (const Source& s, EventArg& e) {
		Object* target = dynamic_cast<Object*> (s.GetDefaultEventTarget ());
		if (DBERROR (target == nullptr)) {
			return (short)0;
		}
		return (target->*function) (s, e);
	};
	runnables.Push (RunnableHelper (fun));
	return *this;
}

template<typename S, typename E>
EventNotifier<S, E, short, true>&	EventNotifier<S, E, short, true>::operator+= (short (*function)(const Source&, EventArg&))
{
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (function));
	return *this;
}

template<typename S, typename E>
template<typename Function, typename TargetType>
EventNotifier<S, E, short, true>& EventNotifier<S, E, short, true>::Add (Function function, TargetType* target)
{
	static_assert ((std::is_base_of<EventTarget, TargetType>::value), "TargetType must be a sub-class of DG::EventTarget");
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (target, std::bind (function, target, std::placeholders::_1, std::placeholders::_2)));
	AddToTarget (target);
	return *this;
}

template<typename S, typename E>
EventNotifier<S, E, short, true>& EventNotifier<S, E, short, true>::Add (const Runnable& runnable, const EventTarget* target)
{
	if (notifierStateHandler != nullptr) {
		notifierStateHandler (true);
	}
	runnables.Push (RunnableHelper (target, runnable));
	AddToTarget (target);
	return *this;
}

template<typename S, typename E>
void EventNotifier<S, E, short, true>::UnRegisterEventTarget (EventTarget* eventTarget)
{
	runnables.DeleteAll ([eventTarget] (const RunnableHelper& runnable) {
		return runnable.eventTarget == eventTarget;
	});
	if (runnables.IsEmpty () && notifierStateHandler != nullptr) {
		notifierStateHandler (false);
	}
}

}

#endif // DGEVENTNOTIFIER_HPP
