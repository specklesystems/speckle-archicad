// *********************************************************************************************************************
// Description:		Model Synchronization State
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	BeA
//
// SG compatible
// *********************************************************************************************************************

#if !defined (MODELSYNCHRONIZATIONSTATE_HPP)
#define MODELSYNCHRONIZATIONSTATE_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

#include	"Model3D/Model3D.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

class MODEL3D_DLL_EXPORT FirstNewElemState : private IModel3DObserver {
private:
	UInt32 firstNewElem;
	const Model3D* model;
	
	FirstNewElemState (const FirstNewElemState&);

	FirstNewElemState& operator = (FirstNewElemState&);

public:
	FirstNewElemState ();

	// GS::EventObserver
	virtual void	SourceDestroyed (GS::EventSource* source) override;

	// IModel3DObserver
	virtual void	ModelCleared (const Model3D& /*model3D*/) override;
	virtual void	ModelCompressed (const Model3D& /*model3D*/, const GS::Array<Modeler::CompressElemData>& /*compressInfos*/) override;

	void Setup (const Model3D* model);

	UInt32 Get () const;
	void Set (UInt32 firstNewElem);

	~FirstNewElemState ();
};


class MODEL3D_DLL_EXPORT ModelChangeTracer: public IModel3DObserver {
	Model3D* model;
	FirstNewElemState firstNewElem;

	GS::HashSet<GS::Guid> deletedElems;
	bool fullRebuild;

	virtual	void ElemDeleted (const Modeler::Model3D& /*model3D*/, ULong /*elemIdx*/, const Modeler::ConstElemPtr& deletedElem) override;
	virtual void EventBeforeClear (const Modeler::Model3D& /*model3D*/) override;

	ModelChangeTracer (const ModelChangeTracer&) = delete;
	ModelChangeTracer& operator = (const ModelChangeTracer&) = delete;

public:
	ModelChangeTracer (Model3D* model);

	void Reset ();

	// returns : fullRebuild
	// if full rebuild happened changedElems is not filled
	bool GetChanges (GS::HashSet<GS::Guid>& changedElems);
};


class MODEL3D_DLL_EXPORT ModelSynchronizationState : private IModel3DObserver {
private:
	friend class Model3D;

	bool		initialized;
	
	Model3D::ModelEventSource*	dst;
	bool						dstChanged;
	UInt32						dstElemCount;
	
	Model3D::ModelEventSource*	src;
	ModStamp					srcInfStamp;
	bool						srcCompressed;
	FirstNewElemState			firstNewElemInSrc;
	GS::Array<GS::Guid>			deletedElems;


	// GS::EventObserver
	virtual void	SourceDestroyed (GS::EventSource* source) override;

	// IModel3DObserver
	virtual	void	SyncDeletedElems (const Model3D& /*model3D*/, ULong /*fElemIdx*/, ULong /*lElemIdx*/, ULong /*num*/) override;
	virtual void	ElemsTruncated (const Model3D& /*model3D*/, ULong /*newElemCount*/) override;
	virtual	void	ElemDeleted (const Model3D& /*model3D*/, ULong /*elemIdx*/, const Modeler::ConstElemPtr& deletedElem) override;
	virtual void	ModelChanged (const Model3D& /*model3D*/) override;
	virtual void	ModelCleared (const Model3D& /*model3D*/) override;
	virtual void	ModelCompressed (const Model3D& /*model3D*/, const GS::Array<Modeler::CompressElemData>& /*compressInfos*/) override;

	bool Init (Model3D* dst, const Model3D* src);

public:
	ModelSynchronizationState ();
	~ModelSynchronizationState ();
};
	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Modeler

#endif // MODELSYNCHRONIZATIONSTATE_HPP
