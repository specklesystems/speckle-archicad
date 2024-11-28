// *********************************************************************************************************************
// Description:		CandidateMeshBody and CandidateNurbsBody Check helper classes
//
// Module:			Modeler
// Namespace:		Modeler
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GS_MODELER_CHECKTASK_HPP)
#define GS_MODELER_CHECKTASK_HPP

#pragma once

#include "Definitions.hpp"

// from GSUtils
#include "comProc.h"

//from Brep
#include "NurbsBrepCheck.hpp"
#include "NurbsBrepConsistencyError.hpp"

// from Model3D
#include "Model3D/Model3DExport.h"
#include "Model3D/Nurbs/NurbsBodyConsistencyError.hpp"

namespace GS {
	class Guid;
}

namespace Modeler {

class	CheckTask {
public:
	enum Task {	
		CheckTopo				= 0,
		CheckGeom				= 1, 
		DontCheckAttrs			= 2,
		CheckNurbsLibDataPart	= 4
	};
	CheckTask (ULong task = CheckTopo)		: m_task (task)			{}
	CheckTask (const CheckTask& task)		: m_task (task.m_task)	{}
	bool CheckTopology () const				{ return true; }
	bool CheckGeometry () const				{ return (m_task & CheckGeom) != 0; }
	bool DontCheckAttributes () const		{ return (m_task & DontCheckAttrs) != 0; }
	bool CheckNurbsLibData () const			{ return (m_task & CheckNurbsLibDataPart) != 0; }
private:
	ULong m_task;
};

class	CheckStatus {
public:
	enum Status { Passed, Failed };
	CheckStatus (Status statusIn) : status (statusIn) {}
	CheckStatus (const CheckStatus& statusIn) : status (statusIn.status) {}
	const CheckStatus& operator= (const CheckStatus& statusIn) { status = statusIn.status; return *this; }
	bool operator== (Status statusIn) const { return status == statusIn; }
	bool operator!= (Status statusIn) const { return status != statusIn; }

private:
	Status status;
};


// ---------------------------------------------------------------------------------------------------------------------
// Tells if certain kinds of checks need to be performed on a body.
// It is currently used in CandidateNurbsBody.
// ---------------------------------------------------------------------------------------------------------------------
struct MODEL3D_DLL_EXPORT CheckControl {
	Brep::NurbsBrepCheckControl brepCheckControl;

	bool checkAttributes	: 1;
		
	CheckControl ();
	CheckControl AttributesOn	 () const;
	CheckControl AttributesOff	 () const;

	static CheckControl All ();
};


// ---------------------------------------------------------------------------------------------------------------------
// Wrapper class for report functions
// ---------------------------------------------------------------------------------------------------------------------
class MODEL3D_DLL_EXPORT CheckReporter {
public:
	CheckReporter (const GS::Guid&		elemGuid,
				   GetLocStrProc_UStr*	getLocStrProc,
				   MessageProc_UStr*	reportProc);

	void	SetAlwaysPrintWarnings () { alwaysPrintWarnings = true; }

	void	ReportMeshCheckFail (short resourceIndexOffset,
								 Int32 j1,
								 Int32 j2 = -MaxInt32,
								 Int32 j3 = -MaxInt32) const;

	void	ReportMeshCheckWarning (short resourceIndexOffset,
									Int32 j1,
									Int32 j2 = -MaxInt32,
									Int32 j3 = -MaxInt32) const;

	void ReportNurbsBrepError (const Brep::NurbsBrepConsistencyError& error) const;
	void ReportNurbsBodyError (const NurbsBodyConsistencyError& error) const;

	static const CheckReporter SilentReporter;

protected:
	GS::UniString	GetFormat (short resourceIndexOffset) const;
	void			DoReport (const GS::UniString& reportString) const;

private:
	const GS::Guid&		elemGuid;
	GetLocStrProc_UStr*	getLocStrProc;
	MessageProc_UStr*	reportProc;
	bool				alwaysPrintWarnings;

	void	DoMeshCheckReport (short resourceIndexOffset,
							   Int32 j1,
							   Int32 j2 = -MaxInt32,
							   Int32 j3 = -MaxInt32) const;

	GS::UniString	GetMeshCheckReportString (short resourceIndexOffset, Int32 j1, Int32 j2, Int32 j3) const;
	GS::UniString	GetNurbsBrepCheckReportString (const Brep::NurbsBrepConsistencyError& error) const;
	GS::UniString	GetNurbsBodyCheckReportString (const NurbsBodyConsistencyError& error) const;

	static short			GetNurbsBrepResourceId (Brep::NurbsBrepConsistencyError::Code errorCode);
	static short			GetNurbsBodyResourceId (Modeler::NurbsBodyConsistencyError errorCode);
	static GS::UniString	FillMeshFormatWithIndices (const GS::UniString& format,
													   Int32 j1,
													   Int32 j2,
													   Int32 j3);
													
	static GS::UniString	FillNurbsBrepFormatWithIndices (const GS::UniString& format,
															const Brep::NurbsBrepConsistencyError& error);

};

}	// namespace Modeler

#endif

