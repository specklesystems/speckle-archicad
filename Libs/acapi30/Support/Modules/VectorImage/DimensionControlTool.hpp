#ifndef DIMENSIONCONTROLTOOL_HPP
#define DIMENSIONCONTROLTOOL_HPP

#include "VectorImageExport.h"
#include "VectorImageTypedefs.hpp"

#include "DimProjectionType.hpp"

namespace PVI { // ProfileVectorImage
class VI_DLL_CLASS_EXPORT DimensionControlTool : public GS::Object
{
	DECLARE_CLASS_INFO

public: 
	enum class MetricType : int
	{
		Euclidean = 1, ProjectedToNominalDimDirection = 2, ProjectedToDirectionByAngle = 3, Undefined = -1 //TODO B530 M2 AACS: refactor for ProjectedToNominalDimDirection, ProjectedToDirectionByAngle
	};

private:
	GSErrCode							ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode							WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;


	ProfileAnchorId						begAnchorID;
	ProfileAnchorId						endAnchorID;
	ProfileParameterId					controlParamID;
	ProfileParameterId					outputParamID;

	MetricType							metric;
	double								projAngleRad;

	void								Setup (
											const ProfileAnchorId& begAnchorID,
											const ProfileAnchorId& endAnchorID,
											const ProfileParameterId& controlParamID);

public:
	DimensionControlTool ();

	bool								operator == (const DimensionControlTool& rhs) const;
	bool								operator != (const DimensionControlTool& rhs) const;
	bool								Compare (const DimensionControlTool& rhs, double eps) const;

	GSErrCode							WriteForChecksum (GS::OChannel& oc, double eps) const;


	static DimensionControlTool			CreateEmpty ();

	static DimensionControlTool			CreateProjectedSizeTool (	const ProfileAnchorId& begAnchorID,
																	const ProfileAnchorId& endAnchorID,
																	const DimProjectionType	projType,
																	const double			projAngleRadInit,
																	const ProfileParameterId& paramID);

	static DimensionControlTool			CreateHorizontalSizeTool (const ProfileAnchorId& begAnchorID,
																  const ProfileAnchorId& endAnchorID,
																  const ProfileParameterId& paramID);

	static DimensionControlTool			CreateHorizontalPositionTool (const ProfileAnchorId& anchorID,
																	  const ProfileParameterId& paramID);

	static DimensionControlTool			CreateVerticalSizeTool (const ProfileAnchorId& begAnchorID,
																  const ProfileAnchorId& endAnchorID,
																  const ProfileParameterId& paramID);

	static DimensionControlTool			CreateVerticalPositionTool (const ProfileAnchorId& anchorID,
																	  const ProfileParameterId& paramID);

	bool								IsEmpty () const; //if empty, it still connects referee to a parameter!
	bool								IsControllable () const;
	void								DisableControl (); 
	bool								IsControllingSize () const;		//in case it has two different valid anchors
	bool								IsControllingPosition () const; //in case it has only one valid anchor


	const ProfileAnchorId&				GetBegAnchorID () const;
	const ProfileAnchorId&				GetEndAnchorID () const;
	const ProfileParameterId&			GetControlParamID () const;
	const ProfileParameterId&			GetOutputParamID () const;
	bool								IsEuclideanType () const;
	bool								IsProjectedToNominalDirType () const;
	bool								IsProjectedToAngleDirType () const;
	bool								IsProjectedType () const;
	double								GetProjAngleRad () const;

	virtual GSErrCode					Read (GS::IChannel& ic) override;
	virtual GSErrCode					Write (GS::OChannel& oc) const	override;
	GSErrCode							ReadXML (GS::XMLIChannel& ic);
	GSErrCode							WriteXML (GS::XMLOChannel& oc) const;
};

}


#endif
