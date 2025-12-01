// *********************************************************************************************************************
// Description:		Lexicographical comparison support.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef LEXICOGRAPHICALCOMPARISON_HPP
#define LEXICOGRAPHICALCOMPARISON_HPP

#pragma once


namespace GS {


// === LexicographicalIsLess () ========================================================================================

template <class Type, class Class, class MemberVariableType>
bool	LexicographicalIsLess (const Type& leftOp, const Type& rightOp, MemberVariableType Class::*memberPointer)
{
	return leftOp.*memberPointer < rightOp.*memberPointer;
}


template <class Type, class Class, class MemberFunctionReturnType>
bool	LexicographicalIsLess (const Type& leftOp, const Type& rightOp, MemberFunctionReturnType (Class::*memberPointer) () const)
{
	return (leftOp.*memberPointer) () < (rightOp.*memberPointer) ();
}


template <class Type, class Class, class MemberVariableType, class... MemberPointers>
bool	LexicographicalIsLess (const Type& leftOp, const Type& rightOp, MemberVariableType Class::*memberPointer, MemberPointers... memberPointers)
{
	if (leftOp.*memberPointer != rightOp.*memberPointer)
		return leftOp.*memberPointer < rightOp.*memberPointer;

	return LexicographicalIsLess (leftOp, rightOp, memberPointers...);
}


template <class Type, class Class, class MemberFunctionReturnType, class... MemberPointers>
bool	LexicographicalIsLess (const Type& leftOp, const Type& rightOp, MemberFunctionReturnType (Class::*memberPointer) () const, MemberPointers... memberPointers)
{
	const MemberFunctionReturnType& leftKey  = (leftOp.*memberPointer) ();
	const MemberFunctionReturnType& rightKey = (rightOp.*memberPointer) ();

	if (leftKey != rightKey)
		return leftKey < rightKey;

	return LexicographicalIsLess (leftOp, rightOp, memberPointers...);
}


}	// namespace GS


#endif
