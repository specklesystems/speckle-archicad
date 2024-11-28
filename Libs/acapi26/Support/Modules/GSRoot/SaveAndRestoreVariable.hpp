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
#include "Definitions.hpp"
#include "Ref.hpp"
#include "Array.hpp"
#include "TypeTraits.hpp"


namespace GS {

// --- SaveAndRestoreVariableT class -----------------------------------------------------------------------------------

template<class Type>
class SaveAndRestoreVariableT
{
public:
	explicit SaveAndRestoreVariableT (Type& variable):
		oldValue (variable),
		variableRef (variable)
	{
	}

	template <class NewType>
	SaveAndRestoreVariableT (Type& variable, NewType&& newValue):
		oldValue (std::forward<NewType> (newValue)),
		variableRef (variable)
	{
		GS::Swap (variableRef, oldValue);
	}

	~SaveAndRestoreVariableT ()
	{
		variableRef = std::move (oldValue);
	}

private:
	Type	oldValue;
	Type&	variableRef;

private:
	SaveAndRestoreVariableT ()											= delete;
	SaveAndRestoreVariableT (const SaveAndRestoreVariableT&)			= delete;
	SaveAndRestoreVariableT& operator= (const SaveAndRestoreVariableT&)	= delete;
};


// --- SaveAndRestoreVariable class ------------------------------------------------------------------------------------

class SaveAndRestoreVariable
{
public:
	template <class Type>
	explicit SaveAndRestoreVariable (Type& variable):
		impl (new Impl<Type> (variable))
	{
	}

	template <class Type1, class Type2>
	SaveAndRestoreVariable (Type1& variable, const Type2& newValue): 
		impl (new Impl<Type1> (variable, newValue))
	{
	}

	template <class Type1, class Type2>
	SaveAndRestoreVariable (Type1& variable, Type2&& newValue): 
		impl (new Impl<Type1> (variable, std::forward<Type2> (newValue)))
	{
	}

	~SaveAndRestoreVariable ()
	{
		delete impl;
	}

private:
	template <class Type>
	struct Impl:	public GS::Object,
					public SaveAndRestoreVariableT<Type>
	{
		Impl (Type& variable):
			SaveAndRestoreVariableT<Type> (variable)
		{
		}
		template <class NewType>
		Impl (Type& variable, const NewType& newValue):
			SaveAndRestoreVariableT<Type> (variable, newValue)
		{
		}
		template <class NewType>
		Impl (Type& variable, NewType&& newValue):
			SaveAndRestoreVariableT<Type> (variable, std::forward<NewType> (newValue))
		{
		}
	};

private:
	GS::Object* impl;

private:
	SaveAndRestoreVariable ()											= delete;
	SaveAndRestoreVariable (const SaveAndRestoreVariable&)				= delete;
	SaveAndRestoreVariable& operator= (const SaveAndRestoreVariable&)	= delete;
};


#undef NO_REF_TYPE


// --- SaveAndRestoreOnFailure class -----------------------------------------------------------------------------------

class SaveAndRestoreOnFailure
{
public:
	template <class Type>
	explicit SaveAndRestoreOnFailure (Type& variable)
		: impl (new Impl<Type, Type> (variable))
		, succeded (false)
	{
	}

	template <class Type1, class Type2>
	SaveAndRestoreOnFailure (Type1& variable, const Type2& newValue)
		: impl (new Impl<Type1, Type2> (variable, newValue))
		, succeded (false)
	{
	}

	~SaveAndRestoreOnFailure ()
	{
		if (!succeded) {
			impl->Restore ();
		}
		delete impl;
	}

	void	Succeded ()
	{
		succeded = true;
	}

private:
	struct GSROOT_DLL_EXPORT BaseImpl
	{
		virtual ~BaseImpl ();

		virtual void Restore () = 0;
	};

	template <class Type1, class Type2>
	struct Impl: public BaseImpl
	{
		Impl (Type1& variable):
			variableRef (variable),
			oldValue (variable)
		{
		}
		Impl (Type1& variable, const Type2& newValue):
			variableRef (variable),
			oldValue (variable)
		{
			variable = newValue;
		}
		virtual void Restore () override
		{
			variableRef = oldValue;
		}
		Type1&		variableRef;
		const Type1	oldValue;
	};

private:
	BaseImpl* impl;
	bool	succeded;

private:
	SaveAndRestoreOnFailure ()											= delete;
	SaveAndRestoreOnFailure (const SaveAndRestoreOnFailure&)			= delete;
	SaveAndRestoreOnFailure& operator= (const SaveAndRestoreOnFailure&)	= delete;
};

typedef GS::Ref<SaveAndRestoreOnFailure>		SaveAndRestoreOnFailureRef;
typedef GS::Array<SaveAndRestoreOnFailureRef>	SaveAndRestoreOnFailureCollection;


// --- SaveAndRestoreByCall class --------------------------------------------------------------------------------------

class SaveAndRestoreByCall
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
	if (GS::CallInPair LINENAME_PAIR(d) = GS::CallInPair(expression1,expression2)) { for (;;); } else

#endif
