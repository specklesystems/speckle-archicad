// *********************************************************************************************************************
// File:			MessageTarget.hpp
//
// Description:		Message Queue related classes
//
// Project:			GRAPHISOFT Root Module (GSRoot)
//
// Namespace:		GS
//
// Contact person:	MD, BM
//
// SG compatible
// *********************************************************************************************************************

#ifndef MESSAGETARGET_HPP
#define MESSAGETARGET_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "GSRootExport.hpp"
#include "Queue.hpp"
#include "SpinLock.hpp"


// --- Predeclarations, type definitions -------------------------------------------------------------------------------

namespace GS {
	class MessageTargetImpl;
	class Event;

	typedef void* SysMessage;
}


namespace GS {

// --- Message class ---------------------------------------------------------------------------------------------------

class GSROOT_DLL_EXPORT Message
{
public:
	enum Priority {
		Top,
		High,
		Normal,
		Low
	};

private:
	Event*					event;
	Priority				priority;
	bool					nonIgnorable;

public:
							Message ();
	explicit				Message (const Event& event, Priority priority = Normal, bool nonIgnorable = false);
							Message (const Message& message);
							Message (Message&& message);
						   ~Message ();

	Message&				operator= (const Message& message);
	Message&				operator= (Message&& message);

	inline const Event*		GetEvent (void) const;
	inline Priority			GetPriority (void) const;
	inline bool				IsNonIgnorable (void) const;
};


// --- Inline implementations ------------------------------------------------------------------------------------------

inline const Event*		Message::GetEvent (void) const
{
	return event;
}


inline Message::Priority	Message::GetPriority (void) const
{
	return priority;
}


inline bool		Message::IsNonIgnorable (void) const
{
	return nonIgnorable;
}


// --- MessageTarget class ---------------------------------------------------------------------------------------------

class GSROOT_DLL_EXPORT MessageTarget
{
public:
	enum State {
		Idle					= 0,
		Busy					= 1,
		WaitingForUserInput		= 2
	};
	class StateGuard;

private:
	MessageTargetImpl*		impl;

	mutable SpinLock		lock;
	Queue<Message>			postedMessages [Message::Low + 1];
	bool					quitSignal;
	int						returnCode;
	bool					messageLoopExited;
	State					state;
	StateGuard*				lastStateGuard;

protected:
							MessageTarget (const MessageTarget&);
	const MessageTarget&	operator = (const MessageTarget&);

	bool					GetSysMessage (SysMessage** sysMsg, bool delayEnabled);

	bool					SysMessagePending (void) const;
	bool					KeyboardMessagePending (void) const;
	bool					MouseMessagePending (void) const;

	void					RemoveKeyboardMessages (void);
	void					RemoveMouseMessages (void);

	virtual void			ProcessSysMessage (SysMessage* sysMsg);

	bool					ProcessRunnableMessage (const Message& message);

	bool					IsKeyboardMessage (SysMessage* sysMsg) const;
	bool					IsMouseMessage (SysMessage* sysMsg) const;

	bool					RetrievePostedMessage (Message* message, Message::Priority priority = Message::Low);
	bool					PeekPostedMessage (Message* message = nullptr, Message::Priority priority = Message::Low) const;

	virtual void			ProcessMessage (const Message& message);
	virtual bool			ProcessIdle (ULong idleCount);

	void					Terminate ();

public:
	MessageTarget ();
	virtual				   ~MessageTarget ();

	int						DoMessageLoop (void);
	inline void				SetQuitSignal (int returnCode = 0);
	inline bool				GetQuitSignal (void) const;

	bool					ProcessRunnableMessages (bool isMessageProcessingDisabled = false);

	virtual bool			PostMessage (Message&& message);
	void					MessageLoopExit ();
	bool					HasMessageLoopExited () const;
	
	virtual void			IsBusy ();
	virtual void			IsResponsive ();

public:
	class GSROOT_DLL_EXPORT [[nodiscard]] StateGuard
	{
	private:
		State				oldState;
		StateGuard*			oldStateGuard;
		bool				initialized;

	public:
		StateGuard ();
		explicit StateGuard (State newState);	// only Busy and WaitingForUserInput are legal
		~StateGuard ();

		void Init (State newState);				// only Busy and WaitingForUserInput are legal
		void Finish (void);
	};

	bool IsInIdleState (void) const;
	bool IsInBusyState (void) const;
	bool IsInWaitingForUserInputState (void) const;
	bool IsInMessagesPendingState (bool checkOnlySysMessages) const;
};


// --- Inline implementations ------------------------------------------------------------------------------------------

inline void		MessageTarget::SetQuitSignal (int code/* = 0 */)
{
	quitSignal = true;
	returnCode = code;
}


inline bool		MessageTarget::GetQuitSignal (void) const
{
	return quitSignal;
}

}	// namespace GS

#endif
