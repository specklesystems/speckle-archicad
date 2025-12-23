// *****************************************************************************
//
//                            class AddInserter
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
// *****************************************************************************


#ifndef ADDINSERTER_HPP
#define ADDINSERTER_HPP

// from Standard Library
#include <utility>


// === class AddInserter =======================================================

namespace GS {

template <class Container>
class AddInserter {
private:
	Container* container;

public:
	using ValueType = typename Container::ValueType;
	
	using DecayedFirstArgumentType = ValueType;

	explicit AddInserter (Container* container);

	void	operator() (const ValueType& value) const;
	void	operator() (ValueType&& value) const;
};


// === Implementation ==========================================================

template <class Container>
AddInserter<Container>::AddInserter (Container* container) :
	container (container)
{
}


template <class Container>
void	AddInserter<Container>::operator()(const AddInserter<Container>::ValueType& value) const
{
	container->Add (value);
}


template <class Container>
void	AddInserter<Container>::operator()(AddInserter<Container>::ValueType&& value) const
{
	container->Add (std::move (value));
}


} // namespace GS

#endif
