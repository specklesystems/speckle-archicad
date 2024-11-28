// *********************************************************************************************************************
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NZ
//
// SG compatible
//
// *********************************************************************************************************************

#if !defined SAVEANDRESTOREVARIABLE_HPP
#define SAVEANDRESTOREVARIABLE_HPP

#pragma once

#include "GSRootExport.hpp"
#include "Object.hpp"
#include "BaseAlgorithms.hpp"


namespace GS {

// --- SaveAndRestoreVariable class ------------------------------------------------------------------------------------

template<class Type>
class [[nodiscard]] SaveAndRestoreVariable
{
public:
	explicit SaveAndRestoreVariable (Type& variable):
		oldValue (variable),
		variableRef (variable)
	{
	}

	template <class NewType>
	SaveAndRestoreVariable (Type& variable, NewType&& newValue):
		oldValue (std::forward<NewType> (newValue)),
		variableRef (variable)
	{
		GS::Swap (variableRef, oldValue);
	}

	~SaveAndRestoreVariable ()
	{
		variableRef = std::move (oldValue);
	}

private:
	Type	oldValue;
	Type&	variableRef;

private:
	SaveAndRestoreVariable ()											= delete;
	SaveAndRestoreVariable (const SaveAndRestoreVariable&)				= delete;
	SaveAndRestoreVariable& operator= (const SaveAndRestoreVariable&)	= delete;
};

// --- SaveAndRestoreVariableUntyped class -----------------------------------------------------------------------------

class [[nodiscard]] SaveAndRestoreVariableUntyped
{
public:
	template <class Type>
	explicit SaveAndRestoreVariableUntyped (Type& variable):
		impl (new Impl<Type> (variable))
	{
	}

	template <class Type1, class Type2>
	SaveAndRestoreVariableUntyped (Type1& variable, const Type2& newValue): 
		impl (new Impl<Type1> (variable, newValue))
	{
	}

	template <class Type1, class Type2>
	SaveAndRestoreVariableUntyped (Type1& variable, Type2&& newValue): 
		impl (new Impl<Type1> (variable, std::forward<Type2> (newValue)))
	{
	}

	~SaveAndRestoreVariableUntyped ()
	{
		delete impl;
	}

private:
	template <class Type>
	struct Impl:	public GS::Object,
					public SaveAndRestoreVariable<Type>
	{
		Impl (Type& variable):
			SaveAndRestoreVariable<Type> (variable)
		{
		}
		template <class NewType>
		Impl (Type& variable, const NewType& newValue):
			SaveAndRestoreVariable<Type> (variable, newValue)
		{
		}
		template <class NewType>
		Impl (Type& variable, NewType&& newValue):
			SaveAndRestoreVariable<Type> (variable, std::forward<NewType> (newValue))
		{
		}
	};

private:
	GS::Object* impl;

private:
	SaveAndRestoreVariableUntyped ()												= delete;
	SaveAndRestoreVariableUntyped (const SaveAndRestoreVariableUntyped&)			= delete;
	SaveAndRestoreVariableUntyped& operator= (const SaveAndRestoreVariableUntyped&)	= delete;
};

// --- SaveAndRestoreOnFailure class -----------------------------------------------------------------------------------

template<class Type>
class [[nodiscard]] SaveAndRestoreOnFailure
{
public:
	explicit SaveAndRestoreOnFailure (Type& variable):
		oldValue (variable),
		variableRef (variable),
		succeeded (false)
	{
	}

	template <class NewType>
	SaveAndRestoreOnFailure (Type& variable, NewType&& newValue):
		oldValue (std::forward<NewType> (newValue)),
		variableRef (variable),
		succeeded (false)
	{
		GS::Swap (variableRef, oldValue);
	}

	~SaveAndRestoreOnFailure ()
	{
		if (!succeeded) {
			variableRef = std::move (oldValue);
		}
	}

	void	Succeeded ()
	{
		succeeded = true;
	}

private:
	Type	oldValue;
	Type&	variableRef;
	bool	succeeded;

private:
	SaveAndRestoreOnFailure ()											= delete;
	SaveAndRestoreOnFailure (const SaveAndRestoreOnFailure&)			= delete;
	SaveAndRestoreOnFailure& operator= (const SaveAndRestoreOnFailure&)	= delete;
};

// --- SaveAndRestoreByCall class --------------------------------------------------------------------------------------

class [[nodiscard]] SaveAndRestoreByCall
{
public:
	template <class Type1, class Type2>
	SaveAndRestoreByCall (Type1 fun, Type2 fun2):
		impl (InitImpl (fun (), fun2))
	{
	}

	template <class Type1, class Type2, class Type3>
	SaveAndRestoreByCall (Type1 fun, Type2 fun2, const Type3& val):
		impl (InitImpl (fun (), fun2, val))
	{
	}

	~SaveAndRestoreByCall ()
	{
		delete impl;
	}

private:
	template <class ValueT, class Type2>
	GS::Object* InitImpl (const ValueT& val, Type2 fun2)
	{
		return new Impl<ValueT, Type2, ValueT> (val, fun2);
	}

	template <class ValueT, class Type2, class ValueT2>
	GS::Object* InitImpl (const ValueT& val, Type2 fun2, const ValueT2& initialVal)
	{
		return new Impl<ValueT, Type2, ValueT2> (val, fun2, initialVal);
	}

	template <class ValueT, class Type2, class ValueT2>
	struct Impl: public GS::Object
	{
		Impl (const ValueT& val, Type2 fun2):
			val (val),
			fun2 (fun2)
		{
		}
		Impl (const ValueT& val, Type2 fun2, const ValueT2& initialVal):
			val (val),
			fun2 (fun2)
		{
			fun2 (initialVal);
		}
		virtual ~Impl ()
		{
			fun2 (std::move (val));
		}
		ValueT	val;
		Type2	fun2;
	};

private:
	GS::Object* impl;

private:
	SaveAndRestoreByCall ()											= delete;
	SaveAndRestoreByCall (const SaveAndRestoreByCall&)				= delete;
	SaveAndRestoreByCall& operator= (const SaveAndRestoreByCall&)	= delete;
};


// --- CallInPair class ------------------------------------------------------------------------------------------------

class CallInPair
{
public:
	CallInPair (const std::function<void (void)>& fun, const std::function<void (void)>& fun2):
		fun2 (fun2),
		valid (true)
	{
		fun ();
	}

	~CallInPair ()
	{
		if (valid) {
			fun2 ();
		}
	}

	operator bool () const
	{
		return false;
	}

	CallInPair (CallInPair&& a):
		fun2 (a.fun2),
		valid (a.valid)
	{
		a.valid = false;
	}

private:
	const std::function<void (void)> fun2;
	bool valid;

private:
	CallInPair ()								= delete;
	CallInPair (const CallInPair&)				= delete;
	CallInPair& operator= (const CallInPair&)	= delete;
};

}	// namespace GS

#define _LINENAME_CAT_PAIR(name, line) name##line
#define _LINENAME_PAIR(name, line) _LINENAME_CAT_PAIR(name, line)
#define LINENAME_PAIR(name) _LINENAME_PAIR(name, __LINE__)

#define betweenCalls(expression1,expression2)					\
	if (GS::CallInPair LINENAME_PAIR(d) {expression1,expression2}) { for (;;); } else

#endif
