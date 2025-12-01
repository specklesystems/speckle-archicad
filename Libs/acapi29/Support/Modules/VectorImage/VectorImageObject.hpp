#if !defined (VECTORIMAGEOBJECT_HPP)
#define VECTORIMAGEOBJECT_HPP

#pragma once

// from GSRoot
#include "GSRoot.hpp"

// from Geometry
#include "Vector2D.hpp"

// from VectorImage
#include "VectorImageExport.h"

class Box2DData;
struct TRANMAT;

class VI_DLL_CLASS_EXPORT VectorImageObject : public GS::Object
{
public:
	virtual Box2DData			GetBounds		(void)						const				= 0;
	virtual void				Offset			(const Geometry::Vector2d& offsCo)				= 0;
	virtual void				Transform		(const TRANMAT& tran)							= 0;
	virtual USize				GetSizeInBytes	(void)						const				= 0;

	virtual GSErrCode			Read			(GS::IChannel& ic)					override	= 0;
	virtual GSErrCode			Write			(GS::OChannel& oc)			const	override	= 0;
	virtual GSErrCode			ReadXML			(GS::XMLIChannel& ic)							= 0;
	virtual GSErrCode			WriteXML		(GS::XMLOChannel& oc)		const				= 0;

	virtual VectorImageObject*	Clone			(void)						const	override	= 0;

	virtual bool				Compare			(const VectorImageObject& op)				const = 0;
	virtual bool				CompareGeometry (const VectorImageObject& op, double eps)	const = 0;
	virtual bool				CompareSettings (const VectorImageObject& op)				const = 0;
	virtual bool				CompareMaterial (const VectorImageObject& op)				const = 0;

	virtual GSErrCode			WriteGeometryForChecksum (GS::OChannel& oc, double eps)		const = 0;
	virtual GSErrCode			WriteSettingsForChecksum (GS::OChannel& oc)					const = 0;
	virtual GSErrCode			WriteMaterialForChecksum (GS::OChannel& oc)					const = 0;


    virtual ~VectorImageObject ();
};


#endif
