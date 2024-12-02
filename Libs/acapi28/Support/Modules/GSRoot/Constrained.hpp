// *****************************************************************************
//
// Contact person: MB, BkB
//
// *****************************************************************************

#ifndef GS_CONSTRAINED_HPP
#define GS_CONSTRAINED_HPP

#include "Typed.hpp"

namespace GS {

template<typename ValueType, typename TagType, auto... Conditions>
using Constrained = TypedImpl::Typed<ValueType, TagType, TypedImpl::Constraint<ValueType, Conditions...>>;

}
#endif
