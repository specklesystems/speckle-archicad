// *********************************************************************************************************************
// Description:		Stack.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef STACK_HPP
#define STACK_HPP

#pragma once


#include "PagedArray.hpp"


namespace GS {


// === class Stack =====================================================================================================

template <class Type>
class Stack {
private:
	PagedArray<Type>	stack;

public:
	Stack ();
	Stack (std::initializer_list<Type> items);

	void		Push (const Type& item);
	void		Push (Type&& item);

	template <class... Args>
	void		PushNew (Args&&... args);

	Type		Pop ();
	void		DeleteTop ();

	void		Clear ();

	bool		IsEmpty () const;

	Type&		GetTop () gs_lifebound;
	const Type&	GetTop () const gs_lifebound;
};


// === Stack inline methods ============================================================================================

template <class Type>
Stack<Type>::Stack ()
{
}


template <class Type>
Stack<Type>::Stack (std::initializer_list<Type> items) :
	stack (items)
{
}


template <class Type>
void	Stack<Type>::Push (const Type& item)
{
	stack.Push (item);
}


template <class Type>
void	Stack<Type>::Push (Type&& item)
{
	stack.Push (std::move (item));
}


template <class Type>
template <class... Args>
void	Stack<Type>::PushNew (Args&&... args)
{
	stack.PushNew (std::forward<Args> (args)...);
}


template <class Type>
Type	Stack<Type>::Pop ()
{
	Type top = std::move (stack.GetLast ());
	stack.DeleteLast ();
	return top;
}


template <class Type>
void	Stack<Type>::DeleteTop ()
{
	stack.DeleteLast ();
}


template <class Type>
void	Stack<Type>::Clear ()
{
	stack.Clear ();
}


template <class Type>
bool	Stack<Type>::IsEmpty () const
{
	return stack.IsEmpty ();
}


template <class Type>
Type&	Stack<Type>::GetTop ()
{
	return stack.GetLast ();
}


template <class Type>
const Type&		Stack<Type>::GetTop () const
{
	return stack.GetLast ();
}


}	// namespace GS


#endif
