
// *****************************************************************************
//
//                              Class EventSender
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined EVENTSENDER_HPP
#define EVENTSENDER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"

#include "Array.hpp"
#include "EventReceiver.hpp"
#include "TypeTraits.hpp"
#include "ParameterPackTraits.hpp"
#include <functional>


// ============================= Class EventSender =============================

namespace GS {


namespace ImpEventSender {

template <class T>
using IsFunctionPointer = EnableIf<!GS::IsMemberFunctionPointer<T>, bool>;

template <class T>
using IsMethodPointer = EnableIf<GS::IsMemberFunctionPointer<T>, bool>;

} // namespace ImpEventSender


class GSROOT_DLL_EXPORT EventSenderBase {
protected:


	friend class EventReceiver;		// to access ReceiverDeleted

	virtual ~EventSenderBase ();

	virtual void	ReceiverDeleted (EventReceiver& receiver) = 0;
};


template <class... Args>
class EventSenderBaseImp : public EventSenderBase {
public:
	using CallbackFunction = std::function<void (const Args&...)>;

private:
	struct Receiver {
		EventReceiver*	 receiver;
		CallbackFunction callbackFunction;

		Receiver (EventReceiver* receiver, CallbackFunction callbackFunction) : receiver (receiver), callbackFunction (std::move (callbackFunction)) {}
	};

	Array<Receiver>	receivers;			// receivers of the sender
	bool			sending;			// true during sending
	bool			reverseSendOrder;	// true if receivers are notified in the reverse order during sending, it is alternated after each send

	virtual void	ReceiverDeleted (EventReceiver& receiver) override;

	void	AttachCallbackFunction (EventReceiver& receiver, CallbackFunction callbackFunction);

	template <class TargetClass, class TargetBaseClass, class Result>
	void	AttachMethodPointer (EventReceiver& receiver, TargetClass& object, Result (TargetBaseClass::*method) (Args...));

	template <class TargetClass, class TargetBaseClass, class Result>
	void	AttachMethodPointer (EventReceiver& receiver, TargetClass& object, Result (TargetBaseClass::*method) (Args...) const);

	UInt32	FindFirst (const EventReceiver& receiver) const;
	bool	Contains (const EventReceiver& receiver) const;

protected:
	template <class... Args2>
	void	Send (const Args2&... args2);

public:
	EventSenderBaseImp ();
	~EventSenderBaseImp ();

	EventSenderBaseImp (const EventSenderBaseImp&) = delete;
	EventSenderBaseImp&	operator= (const EventSenderBaseImp&) = delete;

 	template <class EventReceiverType, class Function, ImpEventSender::IsFunctionPointer<Function> = true>
 	void	Attach (EventReceiverType& receiver, Function function);

	template <class EventReceiverType, class MethodPointer, ImpEventSender::IsMethodPointer<MethodPointer> = true>
	void	Attach (EventReceiverType& receiverObject, MethodPointer method);

	template <class Target, class MethodPointer>
	void	Attach (EventReceiver& receiver, Target& object, MethodPointer method);

	void	Detach (EventReceiver& receiver);

	bool	IsAttached (const EventReceiver& receiver) const;
};


template <class T>
struct SendCaller;

template <class... Args>
class EventSender : public EventSenderBaseImp<Args...> {
public:
	using EventSenderBaseImp<Args...>::Send;
};


template <class Caller, class... Args>
class EventSender<SendCaller<Caller>, Args...> : public EventSenderBaseImp<Args...> {
	friend Caller;
};



// ================ EventSenderBaseImp ================ 

template <class... Args>
EventSenderBaseImp<Args...>::EventSenderBaseImp () :
	sending (false),
	reverseSendOrder (false)
{
}


template <class... Args>
EventSenderBaseImp<Args...>::~EventSenderBaseImp ()
{
	for (UInt32 i = 0; i < receivers.GetSize (); i++)
		receivers[i].receiver->eventSenders.DeleteFirst (this);
}


template <class... Args>
UInt32	EventSenderBaseImp<Args...>::FindFirst (const EventReceiver& receiver) const
{
	return receivers.FindFirst ([&] (const Receiver& r) { return r.receiver == &receiver; });
}


template <class... Args>
bool	EventSenderBaseImp<Args...>::Contains (const EventReceiver& receiver) const
{
	return FindFirst (receiver) != MaxUIndex;
}


template <class... Args>
void	EventSenderBaseImp<Args...>::AttachCallbackFunction (EventReceiver& receiver, CallbackFunction callbackFunction)
{
	receivers.PushNew (&receiver, std::move (callbackFunction));
	receiver.eventSenders.Push (this);
}


template <class... Args>
template <class TargetClass, class TargetBaseClass, class Result>
void	EventSenderBaseImp<Args...>::AttachMethodPointer (EventReceiver& receiver, TargetClass& object, Result (TargetBaseClass::*method) (Args...))
{
	static_assert (IsCompatible<TargetClass, TargetBaseClass>, "object must be compatible with method's class");

	AttachCallbackFunction (receiver, [&, method] (Args... args) { (object.*method) (args...); });
}


template <class... Args>
template <class TargetClass, class TargetBaseClass, class Result>
void	EventSenderBaseImp<Args...>::AttachMethodPointer (EventReceiver& receiver, TargetClass& object, Result (TargetBaseClass::*method) (Args...) const)
{
	static_assert (IsCompatible<TargetClass, TargetBaseClass>, "object must be compatible with method's class");

	AttachCallbackFunction (receiver, [&, method] (Args... args) { (object.*method) (args...); });
}


template <class... Args>
template <class EventReceiverType, class Function, ImpEventSender::IsFunctionPointer<Function>>
void	EventSenderBaseImp<Args...>::Attach (EventReceiverType& receiver, Function function)
{
	static_assert (IsCompatible<EventReceiverType, EventReceiver>, "object must be compatible with EventReceiver");
	static_assert (!GS::IsConst<EventReceiverType>, "Receiver must be non-const!");

	EventReceiver& receiverObject = static_cast<EventReceiver&> (receiver);

	DBASSERT (!Contains (receiverObject));
	DBASSERT (!sending);	// it needs further development to enable Attach during event sending (new receivers should be added only after event sending has been finished)

	AttachCallbackFunction (receiverObject, std::move (function));
}


template <class... Args>
template <class EventReceiverType, class MethodPointer, ImpEventSender::IsMethodPointer<MethodPointer>>
void	EventSenderBaseImp<Args...>::Attach (EventReceiverType& receiverObject, MethodPointer method)
{
	static_assert (IsCompatible<EventReceiverType, EventReceiver>, "object must be compatible with EventReceiver");
	static_assert (!GS::IsConst<EventReceiverType>, "Receiver must be non-const!");

	EventReceiver& receiver = static_cast<EventReceiver&> (receiverObject);

	DBASSERT (!Contains (receiverObject));
	DBASSERT (!sending);	// it needs further development to enable Attach during event sending (new receivers should be added only after event sending has been finished)

	AttachMethodPointer (receiver, receiverObject, method);
}


template <class... Args>
template <class Target, class MethodPointer>
void	EventSenderBaseImp<Args...>::Attach (EventReceiver& receiver, Target& object, MethodPointer method)
{
	DBASSERT (!Contains (receiver));
	DBASSERT (!sending);	// it needs further development to enable Attach during event sending (new receivers should be added only after event sending has been finished)

	static_assert (GS::IsMemberFunctionPointer<MethodPointer>, "methodPointer must be a MethodPointer");
	constexpr bool isConstMethod = DecomposeMethod<MethodPointer>::IsConst;
	static_assert (isConstMethod || !IsConst<Target>, "If the methodPointer is non-const, the targetObject must be a non-const");

	AttachMethodPointer (receiver, object, method);
}


template <class... Args>
void	EventSenderBaseImp<Args...>::Detach (EventReceiver& receiver)
{
	DBASSERT (!sending);	// it needs further development to enable Detach during event sending (existing receivers should be deleted only after event sending has been finished)

	UInt32 receiverIndex = FindFirst (receiver);

	if (receiverIndex != MaxUIndex) {
		receivers.Delete (receiverIndex);
		receiver.eventSenders.DeleteFirst (this);
	}
}


template <class... Args>
bool	EventSenderBaseImp<Args...>::IsAttached (const EventReceiver& receiver) const
{
	return receivers.Contains ([&] (const Receiver& r) { return r.receiver == &receiver; });
}


template <class... Args>
void	EventSenderBaseImp<Args...>::ReceiverDeleted (EventReceiver& receiver)
{
	DBASSERT (!sending);	// it is not allowed to delete receiver during event sending

	UInt32 receiverIndex = FindFirst (receiver);
	receivers.Delete (receiverIndex);
}


template <class... Args>
template <class... Args2>
void	EventSenderBaseImp<Args...>::Send (const Args2&... args2)
{
	sending = true;

	if (reverseSendOrder) {
		for (UInt32 i = receivers.GetSize (); i > 0; i--)
			receivers[i - 1].callbackFunction (args2...);
	} else {
		for (UInt32 i = 0; i < receivers.GetSize (); i++)
			receivers[i].callbackFunction (args2...);
	}

	reverseSendOrder = !reverseSendOrder;

	sending = false;
}


} // namespace GS 

#endif
