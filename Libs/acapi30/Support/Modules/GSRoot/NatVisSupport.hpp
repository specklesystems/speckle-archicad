// *****************************************************************************
//
//					NatVis support
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
//
// *****************************************************************************


#ifndef GSNATVISSUPPORT_HPP
#define GSNATVISSUPPORT_HPP

#include "String.hpp"

namespace GS {
namespace NatVis {
namespace Imp {

inline void						ModuleDeterminer () { }
GSROOT_DLL_EXPORT GS::String	GetModuleName (void (*function)(void));

} // namespace Imp


inline GS::String	GetCurrentModuleName ()
{
	return Imp::GetModuleName (Imp::ModuleDeterminer);
}


} // namespace NatVis
} // namespace GS



#endif
