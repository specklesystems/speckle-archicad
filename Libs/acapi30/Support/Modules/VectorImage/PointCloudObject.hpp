// *********************************************************************************************************************
// Description:		Storage of point clouds in a VectorImage
//
// Module:			VectorImage
// Namespace:		
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (POINTCLOUDOBJECT_HPP)
#define POINTCLOUDOBJECT_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from PointCloud
#include	"PointCloudView.hpp"

// from VectorImage
#include	"VectorImageObject.hpp" 

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

class VI_DLL_CLASS_EXPORT PointCloudObject : public VectorImageObject
{
	DECLARE_DYNAMIC_CLASS_INFO (PointCloudObject)

private:
	PointCloud::ConstViewPtr mCloud;

public:
	PointCloudObject ();
	PointCloudObject (const PointCloud::ConstViewPtr& cloud);

	// method overrides

	Box2DData			GetBounds (void) const override;
	void				Offset (const Geometry::Vector2d& offsCo) override;
	void				Transform (const TRANMAT& tran) override;
	
	virtual USize		GetSizeInBytes (void) const override;
	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const override;
	virtual GSErrCode	ReadXML (GS::XMLIChannel& ic) override;
	virtual GSErrCode	WriteXML (GS::XMLOChannel& oc) const override;

	virtual PointCloudObject*	Clone () const override;
	
	virtual bool				Compare			(const VectorImageObject& op) const override;
	virtual bool				CompareGeometry (const VectorImageObject& op, double eps) const override;
	virtual bool				CompareSettings (const VectorImageObject& op) const override;
	virtual bool				CompareMaterial (const VectorImageObject& op) const override;

	virtual GSErrCode			WriteGeometryForChecksum (GS::OChannel& oc, double eps) const override;
	virtual GSErrCode			WriteSettingsForChecksum (GS::OChannel& oc) const override;
	virtual GSErrCode			WriteMaterialForChecksum (GS::OChannel& oc) const override;

public:
	PointCloud::ConstViewPtr	GetPointCloud () const;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


#endif // POINTCLOUDOBJECT_HPP
