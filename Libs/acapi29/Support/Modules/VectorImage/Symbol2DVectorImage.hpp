
#ifndef _SYMBOL2D_VECTORIMAGE_HPP_
#define _SYMBOL2D_VECTORIMAGE_HPP_

#include "ISymbol2D.hpp"
#include "VectorImageExport.h"
#include "VectorImage.hpp"

class VI_DLL_CLASS_EXPORT Symbol2DVectorImage : public ISymbol2D {
private:
	VectorImage vectorImage;

public:
	typedef GS::SharedPtr<Symbol2DVectorImage>			Ref;
	typedef GS::ConstSharedPtr<Symbol2DVectorImage>		ConstRef;

public:
	Symbol2DVectorImage ()									: vectorImage ()				{													}
	Symbol2DVectorImage (const VectorImage& vectorImage)	: vectorImage (vectorImage)		{													}
	virtual ~Symbol2DVectorImage ();

	virtual Symbol2DVectorImage* Clone (void) const override								{	return new Symbol2DVectorImage (vectorImage);	}

			VectorImage& GetVectorImage (void)												{	return vectorImage;								}
	const	VectorImage& GetVectorImage (void)	const										{	return vectorImage;								}

private:
	Symbol2DVectorImage (const Symbol2DVectorImage& op);			// disable
	Symbol2DVectorImage& operator= (const Symbol2DVectorImage&);	// disable
};

#endif
