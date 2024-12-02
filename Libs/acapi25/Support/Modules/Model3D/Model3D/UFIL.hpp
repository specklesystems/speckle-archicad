// *********************************************************************************************************************
// Description:		UFIL is the description of a fill attribute
//
// Module:			GSModeler
// Namespace:
// Contact person:	FGy
//
// SG compatible
// *********************************************************************************************************************

#if !defined (UFIL_HPP)
#define UFIL_HPP

// from GSRoot
#include	"Array.hpp"
#include	"CH.hpp"
#include	"AutoPtr.hpp"

// from GSUtils
#include	"GSUtilsDefs.h"

// from Model3D
#include	"Model3D/Model3DExport.h"
#include	"GDLAttributes.h"

//from Pattern
#include	"FillData.hpp"

struct OmittedUFILParts {
	Int32		ffide, nfide;
};


class MODEL3D_CPP_DLL_EXPORT UFIL {
	static GS::ClassInfo classInfo;

	static const UInt32	NameSize_old = 32;	

private:	
	GS::UniString					cname;
	STATW							status;
	GSAttributeIndex				genfrom;		/* > 0: AC_FILL ; = 0: GDL	*/
	GX::Pattern::FillData			fillData; 

public:
	UFIL ();

	const GS::UniString&			GetName () const		{ return cname; }
	STATW							GetStatus () const		{ return status; }
	GSAttributeIndex				GetGenfrom () const		{ return genfrom; }
	const GX::Pattern::FillData*	GetFillData () const	{ return &fillData; }
	void							GetFillDef (GS::AutoPtr <FillRecord>& filldefRecord) const;
	UInt32							GetFillDefSize () const;

	void							SetName (const GS::UniString& cname)	{ this->cname = cname; }
	void							SetStatus (STATW status)	{ this->status = status; }
	void							SetGenfrom (GSAttributeIndex genfrom)	{ this->genfrom = genfrom; }
	void							SetFillData (const GX::Pattern::FillData* fillDataInit);
	void							SetFillDef (const FillRecord* fillDefInit);

	GSErrCode						Read  (GS::IChannel& ic);
	GSErrCode						Write (GS::OChannel& oc) const;

	void							WriteXML (GS::XMLOChannel& outXML) const;
	void							ReadXML	 (GS::XMLIChannel& inXML) CAN_THROW ((GS::Exception));

	// Read for old version-frame-less writes.
	GSErrCode						DeprecatedRead_NoFillDescriptor  (GS::IChannel& ic, Int32 msizeVersion, OmittedUFILParts& omittedUFILParts);

private:
	GSErrCode						ReadVersion2		(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode						WriteVersion2		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode						ReadVersion3		(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode						WriteVersion3		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode						ReadVersion4		(GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode						WriteVersion4		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
};

#endif
