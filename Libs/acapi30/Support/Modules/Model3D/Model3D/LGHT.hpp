// *********************************************************************************************************************
// Description:		LGHT record with some fundamental methods
//
// Module:			GDL
// Namespace:
// Contact person:	BA, FE, FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_GDL_LGHT_HPP)
#define GS_GDL_LGHT_HPP

#pragma once

// from GSRoot
#include	"GSGuid.hpp"

// from GSUtils
#include	"GSPix.h"	// GS_RGBColor

#include	"Model3D/Model3DExport.h"

//from Geometry
#include "TRANMAT.h"

#include "Model3D/PropList.hpp"


class MODEL3D_CPP_DLL_EXPORT LGHT {
public:
	short						ltype;
	GS_RGBColor					lightRGB;

private:
	float						posx, posy, posz;
	float						dirx, diry, dirz;
	float						upx, upy, upz;

public:
	float						radius;
	float						cosa;
	float						cosb;
	float						afall;
	float						dist1;
	float						dist2;
	float						dfall;
	Modeler::PropertyList		props;

public:
	LGHT ();
	~LGHT ();

	bool operator== (const LGHT& other) const;
	bool operator!= (const LGHT& other) const { return !(*this == other); }

	void Transform	(const TRANMAT *tran);
	void GetTransformedPosDirAndUp (	const TRANMAT *tran,
										double* posx, double* posy, double* posz,
										double* dirx, double* diry, double* dirz,
										double* upx, double* upy, double* upz) const;

	inline	void SetPos				(float posx, float posy, float posz) {this->posx = posx; this->posy = posy; this->posz = posz;}
			void SetDir				(float dirx, float diry, float dirz);
			void SetUpVector		(float upx, float upy, float upz);
			void SetDefaultUpVector	();

	GSErrCode		Read  (GS::IChannel& ic);
	GSErrCode		Read  (GS::IChannel& ic, Int32 msizeVersion);
	GSErrCode		Write (GS::OChannel& oc) const;

	void		QuickWrite (GS::OChannel& oc) const;	// no versioning, no checking
	void		QuickRead (GS::IChannel& ic);			// no versioning, no checking

	void	WriteXML (GS::XMLOChannel& outXML) const;
	void	ReadXML	 (GS::XMLIChannel& inXML);

	void		IV (GS::PlatformSign inplatform, GS::PlatformSign toplatform);

	GSErrCode	Store (GS::ObjectState&) const;
	GSErrCode	Restore (const GS::ObjectState&);

};			/* 2 + 6 + 13*4 + 4 + 4 = 68 */

#endif
