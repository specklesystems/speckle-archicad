// *****************************************************************************
//
// Contact person: MB, PR
//
// *****************************************************************************

#ifndef GS_INSERTER_HPP
#define GS_INSERTER_HPP


namespace GS {


template<typename T>
struct InserterTraits;


template<typename Container>
auto	GetInserter (Container& cont)
{
	return InserterTraits<Container>::GetInserter (cont);
}


} // namespace GS


#endif /* GS_INSERTER_HPP */
