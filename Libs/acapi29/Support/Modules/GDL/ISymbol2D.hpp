
#ifndef _ISYMBOL2D_HPP_
#define _ISYMBOL2D_HPP_

#include "SharedObject.hpp"
#include "GDLExport.h"

class GDL_DLL_EXPORT ISymbol2D : public GS::SharedObject {
public:
	typedef GS::SharedPtr<ISymbol2D>		Ref;
	typedef GS::ConstSharedPtr<ISymbol2D>	ConstRef;

public:
	virtual ~ISymbol2D ();

	virtual ISymbol2D* Clone (void) const = 0;
};

#endif
