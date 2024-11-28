// *****************************************************************************
//
//                             Class AutoPtr, AutoArrayPtr
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MIJ
//
// SG compatible
//
// *****************************************************************************

#if !defined AUTOPTR_HPP
#define AUTOPTR_HPP

#pragma once


#include "Definitions.hpp"


// =============================== Class AutoPtr ===============================

namespace GS {

template<class Type>
class AutoPtr {
public:
	AutoPtr (Type* ptr = nullptr) : mPtr (ptr)				{}
	AutoPtr (AutoPtr&& rightOp)	  : mPtr (rightOp.mPtr)		{ rightOp.mPtr = nullptr; }
	~AutoPtr ()												{ delete mPtr; }

	AutoPtr&	operator= (AutoPtr&& rightOp)				{ Reset (rightOp.mPtr); rightOp.mPtr = nullptr; return *this; }

	void		Reset (Type* ptr = nullptr)					{ delete mPtr; mPtr = ptr; }
	Type*		Release ()									{ Type* ret = mPtr; mPtr = nullptr; return ret; }
	void		ReleasePtr ()								{ mPtr = nullptr; }

	Type*		Get ()										{ return mPtr; }
	const Type*	Get () const								{ return mPtr; }

	Type&		operator* ()								{ return *mPtr; }
	const Type&	operator* () const							{ return *mPtr; }

	Type*		operator-> ()								{ return mPtr; }
	const Type*	operator-> () const							{ return mPtr; }

	bool		operator== (const Type* ptr) const			{ return (mPtr == ptr); }
	bool		operator!= (const Type* ptr) const			{ return (mPtr != ptr); }

	template<class MemberType>
	MemberType& operator->* (MemberType Type::*memberPtr)	{ return mPtr->*memberPtr; }

private:
	AutoPtr (const AutoPtr&);				// disabled
	AutoPtr& operator= (const AutoPtr&);	// disabled

	Type*	mPtr;
};


template<class Type>
class AutoArrayPtr {
public:
	AutoArrayPtr (Type* ptr = nullptr)	  : mPtr (ptr)			{}
	AutoArrayPtr (AutoArrayPtr&& rightOp) : mPtr (rightOp.mPtr)	{ rightOp.mPtr = nullptr; }
	~AutoArrayPtr ()											{ delete [] mPtr; }

	AutoArrayPtr&	operator= (AutoArrayPtr&& rightOp)			{ Reset (rightOp.mPtr); rightOp.mPtr = nullptr; return *this; }

	void			Reset (Type* ptr = nullptr)					{ delete [] mPtr; mPtr = ptr; }
	Type*			Release ()									{ Type* ret = mPtr; mPtr = nullptr; return ret; }

	Type*			Get ()										{ return mPtr; }
	const Type*		Get () const								{ return mPtr; }

	Type&			operator* ()								{ return *mPtr; }
	const Type&		operator* () const							{ return *mPtr; }

	Type*			operator-> ()								{ return mPtr; }
	const Type*		operator-> () const							{ return mPtr; }

	Type&			operator[] (UIndex index)					{ return mPtr[index]; }
	const Type&		operator[] (UIndex index) const				{ return mPtr[index]; }

private:
	AutoArrayPtr (const AutoArrayPtr&);				// disabled
	AutoArrayPtr& operator= (const AutoArrayPtr&);	// disabled

	Type*	mPtr;
};

}	// namespace GS

// __________________________________ AutoPtr __________________________________

#endif
