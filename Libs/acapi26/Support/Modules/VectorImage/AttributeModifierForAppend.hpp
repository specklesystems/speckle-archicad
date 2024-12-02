#ifndef ATTRIBUTEMODIFIERFORAPPEND_HPP
#define ATTRIBUTEMODIFIERFORAPPEND_HPP

#pragma once

#include "VectorImageExport.h"
#include "IAttributeModifier.hpp"
#include "ExtendedPen.hpp"

typedef GSIndex GSAttributeIndex;

class Sy_HotType;
class Sy_LinType;
class Sy_PolyLinType;
class Sy_ArcType;
class Sy_TextType;
class Sy_RichTextType;
class Sy_HatchType;
class HatchObject;
class Sy_SplineType;
class Sy_PixMapType;
class Sy_PointCloudType;

namespace VI {
	
class VI_DLL_CLASS_EXPORT AttributeModifierForAppend : public VI::IAttributeModifier {
public:
	short				overrideFragment;
	VBAttr::ExtendedPen	overridePen;
	GSAttributeIndex	overrideLType;
	short				overrideDrwIndex;
	short				overrideLineProperty;
	GSAttributeIndex	overrideFillIndex;

	AttributeModifierForAppend ()
		: overrideFragment(0)
		, overridePen(0)
		, overrideLType(0)
		, overrideDrwIndex(0)
		, overrideLineProperty(-1)
		, overrideFillIndex(0)
	{
	}
	virtual ~AttributeModifierForAppend ();

	virtual void Modify (Sy_HotType&		hots)								const override;
	virtual void Modify (Sy_LinType&		line)								const override;
	virtual void Modify (Sy_PolyLinType&	polyLine)							const override;
	virtual void Modify (Sy_ArcType&		arc)								const override;
	virtual void Modify (Sy_TextType&		text)								const override;
	virtual void Modify (Sy_RichTextType&	richText)							const override;
	virtual void Modify (Sy_HatchType&		hatchRef, HatchObject& hatch)		const override;
	virtual void Modify (Sy_SplineType&		spline)								const override;
	virtual void Modify (Sy_PixMapType&		pixMap)								const override;
	virtual void Modify (Sy_PointCloudType&	pointCloud)							const override;
};

}

#endif