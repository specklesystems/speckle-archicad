// *****************************************************************************
//
//                            class AppendInserter
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
// *****************************************************************************


#ifndef APPENDINSERTER_HPP
#define APPENDINSERTER_HPP

#pragma once


// === class AppendInserter ====================================================

namespace GS {

template <class Container>
class AppendInserter {
private:
	Container* container;

public:
	using ValueType = typename Container::ValueType;
	
	using DecayedFirstArgumentType = ValueType;

	explicit AppendInserter (Container* container);

	void     operator() (const ValueType& value) const;
	void     operator() (ValueType&& value) const;
};


// === Implemantation ==========================================================

template <class Container>
AppendInserter<Container>::AppendInserter (Container* container) :
	container (container)
{
}


template <class Container>
void	AppendInserter<Container>::operator()(const AppendInserter<Container>::ValueType& value) const
{
	container->Append (value);
}


template <class Container>
void	AppendInserter<Container>::operator()(AppendInserter<Container>::ValueType&& value) const
{
	container->Append (std::move (value));
}


} // namespace GS

#endif
