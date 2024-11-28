// *****************************************************************************
//
//                                Class Extension
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************

#ifndef EXTENSION_HPP
#define EXTENSION_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "Object.hpp"
#include "StaticInstantiable.hpp"

namespace GS { class ClassInfo; }



// ============================== Class Extension ==============================

namespace GS  {


class GSROOT_DLL_EXPORT ExtensionClass {
public:
	ExtensionClass ()									= default;
	ExtensionClass (const ExtensionClass&)				= delete;
	ExtensionClass& operator= (const ExtensionClass&)	= delete;
};


class GSROOT_DLL_EXPORT Extension : public StaticInstantiable {
private:
	const ExtensionClass*	extensionClass;		// used to identify the extension obtained from derived classes
	ClassInfo*				target;				// target class to be extended

protected:
	Extension (const ExtensionClass* extensionClass, ClassInfo* target);

public:
	const ExtensionClass*	GetExtensionClass () const;

	Extension (const Extension&) = delete;
	Extension& operator= (const Extension&) = delete;
	
	virtual ~Extension ();
};


template <class ExtensionType>
ExtensionType*	GetExtension (const Object* object)
{
	return object->GetClassInfo ()->GetExtension<ExtensionType> ();
}


}	// namespace GS


#endif
