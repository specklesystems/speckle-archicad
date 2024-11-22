// *****************************************************************************
//
//                            class PushInserter
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
// *****************************************************************************


#ifndef PUSHINSERTER_HPP
#define PUSHINSERTER_HPP

#pragma once


// === class PushInserter ======================================================

namespace GS {

template <class Container>
class PushInserter {
private:
	Container* container;

public:
	using ValueType = typename Container::ValueType;

	using DecayedFirstArgumentType = ValueType;

	explicit PushInserter (Container* container);

	void     operator() (const ValueType& value) const;
	void     operator() (ValueType&& value) const;
};


// === Implemantation ==========================================================

template <class Container>
PushInserter<Container>::PushInserter (Container* container) :
	container (container)
{
}


template <class Container>
void	PushInserter<Container>::operator() (const PushInserter<Container>::ValueType& value) const
{
	container->Push (value);
}


template <class Container>
void	PushInserter<Container>::operator() (PushInserter<Container>::ValueType&& value) const
{
	container->Push (std::move (value));
}


} // namespace GS

#endif // PUSHINSERTER_HPP
