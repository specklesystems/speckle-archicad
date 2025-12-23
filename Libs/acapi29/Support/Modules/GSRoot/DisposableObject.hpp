
// *****************************************************************************
//
//                         Base class DisposableObject
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined DISPOSABLEOBJECT_HPP
#define DISPOSABLEOBJECT_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"

#include "Object.hpp"
#include "ObjectDisposer.hpp"



// ========================== Class DisposableObject ===========================

namespace GS {

class GSROOT_DLL_EXPORT DisposableObject: public Object,
										  public ObjectDisposer
{
public:
	inline void		MarkAsDisposable (void);
	inline void		MarkAsFinished   (void);

	virtual ~DisposableObject ();
};

}	// namespace GS


inline void		GS::DisposableObject::MarkAsDisposable (void)
{
	ObjectDisposer::MarkAsDisposable (*this);
}


inline void		GS::DisposableObject::MarkAsFinished (void)
{
	ObjectDisposer::MarkAsFinished (*this);
}
// __________________________ Class DisposableObject ___________________________


#endif
