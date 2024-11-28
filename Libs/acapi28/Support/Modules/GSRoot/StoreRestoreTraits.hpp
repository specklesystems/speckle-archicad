// *********************************************************************************************************************
// Description:		Store/Restore traits
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, KKr, SzoBe
//
// *********************************************************************************************************************

#ifndef STORERESTORETRAITS_HPP
#define STORERESTORETRAITS_HPP

#pragma once


#include "TypeTraits.hpp"

namespace GS { class ObjectState; }
namespace GS { class ErrorStatus; }


namespace GS {

// === HasInternalStore ================================================================================================

namespace Imp {
template <class T>
using HasInternalStoreMethodRequirement = decltype (ErrorStatus { std::declval<const T> ().Store (std::declval<ObjectState&> ()) });
}

template <class T>
constexpr bool	HasStoreMethod = IsSubstitutable<Imp::HasInternalStoreMethodRequirement, T>;


// === HasInternalRestore ==============================================================================================

namespace Imp {
template <class T>
using HasInternalRestoreMethodRequirement = decltype (ErrorStatus { std::declval<T> ().Restore (std::declval<const ObjectState&> ()) });
}

template <class T>
constexpr bool	HasRestoreMethod = IsSubstitutable<Imp::HasInternalRestoreMethodRequirement, T>;

} // namespace GS

#endif
