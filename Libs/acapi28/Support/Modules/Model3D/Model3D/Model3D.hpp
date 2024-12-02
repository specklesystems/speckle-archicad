// *****************************************************************************
// A Model3D is a full 3D model.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          FGY
//
// SG compatible
// *****************************************************************************

#if !defined(MODEL3D_HPP)
#define MODEL3D_HPP

#pragma once

// from GSRoot
#include	"GSRoot.hpp"
#include	"EventSource.hpp"
#include	"EventObserver.hpp"
#include	"FastLock.hpp"

// from Geometry
#include	"KDTree.hpp"
#include	"KDTreeTypes.hpp"
#include	"KDTreeKeys.hpp"
#include	"Box3DData.h"

// from Model3D
#include	"Model3D/model.h"
#include	"Model3D/Elem.hpp"
#include	"Model3D/BaseElem.hpp"
#include	"Model3D/MeshBody.hpp"
#include	"Model3D/MeshBodyPtr.hpp"
#include	"Model3D/ModStamp.hpp"
#include	"Model3D/MainContainerBase.hpp"
#include	"Model3D/ModelerAttributes.hpp"
#include	"Model3D/Swappable.hpp"


namespace Modeler {

typedef	bool   ElemPredicateProc (const Modeler::Elem& elem);

class ModelSynchronizationState;
class Model3D;
typedef GS::SharedPtr<Model3D>			Model3DPtr;
typedef GS::ConstSharedPtr<Model3D>		ConstModel3DPtr;
typedef GS::HashTable<const Modeler::BaseElem*, UInt32>	BaseElemSet;

class Model3DViewer;
class Model3DOnlyModifier;
class Model3DModifier;

class IntersectionQueryAlgorithm;

MODEL3D_DLL_EXPORT void	MODEL3D_CALL  CopyModel (Model3DPtr dest, const Model3D& src);
MODEL3D_DLL_EXPORT void	MODEL3D_CALL  MoveEnd	(Model3DModifier* src, Model3DModifier* dst, ULong fromElemIdx);


struct	MODEL3D_DLL_EXPORT	CompressElemData {
	Int32	newElemIndex;		// -1 means that the elem has been removed
	USize	pointCloudCount;
	USize	bodyCount;
};


class MODEL3D_DLL_EXPORT IModel3DObserver : public GS::EventObserver {
public:
	~IModel3DObserver ();
	virtual	void SyncDeletedElems (const Model3D& /*model3D*/, ULong /*fElemIdx*/, ULong /*lElemIdx*/, ULong /*num*/) {}
	virtual void ElemsTruncated (const Model3D& /*model3D*/, ULong /*newElemCount*/) {}
	virtual	void ElemDeleted (const Model3D& /*model3D*/, ULong /*elemIdx*/, const Modeler::ConstElemPtr& /*deletedElem*/) {}
	virtual void RestartDelBoundsBuilding (const Model3D& /*model3D*/) {}
	virtual void ConvertStateChanged (const Model3D& /*model3D*/, ULong /*fromElemIdx*/, ULong /*fromBodyIdx*/) {}
	virtual void ModelChanged (const Model3D& /*model3D*/) {}
	virtual void ModelCleared (const Model3D& /*model3D*/) {}
	virtual void ColorShadesChanged (const Model3D& /*model3D*/) {}
	virtual void AllConditionsCleared (const Model3D& /*model3D*/) {}
	virtual void EventBeforeClear (const Model3D& /*model3D*/) {}
	virtual void ConvertStarted (const Model3D& /*model3D*/) {}
	virtual void ModelCompressed (const Model3D& /*model3D*/, const GS::Array<Modeler::CompressElemData>& /*compressInfos*/) {}
};


class MODEL3D_DLL_EXPORT BitField {
private:
	typedef UInt32 DataType;
	GS::Array<DataType> bits;
	static const UInt32 DataSize = sizeof (DataType) * 8;
	DataType checkSum32;
public:
	BitField () : checkSum32 (0) {}
	bool Get (UInt32 index) const;
	void Set (UInt32 index, bool value, UInt32 size);
	Int32 Compare (const BitField& rhs) const;
	void  Merge	  (const BitField& other);
	void QuickWrite (GS::OChannel& oc) const;
	void QuickRead (GS::IChannel& ic);
	ULong GenerateHashValue () const;
	bool operator == (const BitField &rhs) const;
	bool operator != (const BitField &rhs) const;
};


struct MODEL3D_DLL_EXPORT RemainingEdgePart {
	STATL	status;
	short	color;
	COORD3	vert1, vert2;
	UIndex	bodyIdx;
	UIndex	edgeIdx;

	bool	IsInvisible () const {
		return HAS_ANY_FLAGS (status, INVISBIT);
	}

	bool	IsVisibleIfContour () const {
		return HAS_ANY_FLAGS (status, VISIBLEIFCONTOURBIT);
	}

	void QuickWrite (GS::OChannel& oc) const;
	void QuickRead (GS::IChannel& ic);
	Int32 Compare (const RemainingEdgePart& rhs) const;
	bool operator < (const RemainingEdgePart& rhs) const;
	ULong GenerateHashValue () const;
};


class MODEL3D_DLL_EXPORT ElemElimData : public GS::SharedObject {
private:
	GS::Array<BitField>				edgeFlags;
	GS::Array<RemainingEdgePart>	remainingEdgeParts;
	GS::Array<BitField>				pgonFlags;
public:
	bool						IsElimEdge  (UInt32 bodyIdx, UInt32 edgeIdx) const;
	void						SetElimEdge (UInt32 bodyIdx, UInt32 edgeIdx, UInt32 bodySize, UInt32 edgeSize, bool isElimEdge);
	bool						IsElimPGON  (UInt32 bodyIdx, UInt32 pgonIdx) const;
	void						SetElimPGON (UInt32 bodyIdx, UInt32 pgonIdx, UInt32 bodyCnt, UInt32 pgonCnt, bool isElimPGON);

	bool						operator == (const ElemElimData& rhs) const;
	Int32						Compare (const ElemElimData& rhs) const;
	UInt32						GetRemainingEdgePartCount () const;
	void						PushRemainingEdgePart (const RemainingEdgePart& part);
	const RemainingEdgePart&	GetRemainingEdgePartInElemLocalCoordinateSystem (UInt32 index) const;
	RemainingEdgePart			GetRemainingEdgePart (UInt32 index, const TRANMAT* elemLocalToWorldTrafo) const;
	void						Merge (const ElemElimData& other);
	void						SortRemainingEdgeParts (void);

	void						QuickWrite (GS::OChannel& oc) const;
	void						QuickRead (GS::IChannel& ic);

	ULong						GenerateHashValue () const;

    virtual						~ElemElimData ();
};


typedef GS::SharedPtr<ElemElimData>			ElemElimDataPtr;
typedef GS::ConstSharedPtr<ElemElimData>	ConstElemElimDataPtr;
typedef GS::PagedArray<ElemElimDataPtr>		ElimDataArray;

class MODEL3D_DLL_EXPORT Model3D : public MainContainerBase {
public:
	typedef GS::PagedArray<ConstElemPtr>		ElemArray;

	typedef struct {
		short	convert_3D;

		short	planar_cut;
		short	ushape_cut;

//		short	sunshadow;
//		short	lightshadow;
//		short	vectorShadow;

		short	compressit;
	} Conditions;

	enum Condition {
		Convert3D =	1,

		PlanarCut = 5,
		UShapeCut = 6,

//		SunShadow = 12,
//		VectorShadow = 13,
//		LightShadow = 15,

		CompressIt = 18
	};

	// Describes what to do if multiple Elems use the same BaseElem (with different transformation).
	enum BaseElemWritePolicy {
		WriteByValue,		// write the BaseElem multiple times
		WriteByReference	// write the BaseElem only once
	};

	friend class Model3DViewer;
	friend class Model3DOnlyModifier;
	friend class Model3DModifier;
	friend class GS::SharedPtr<Model3D>;
	friend class GS::ConstSharedPtr<Model3D>;
	friend class ModelSynchronizationState;

	struct ElemAbsoluteIndices {
		Int32					m_absBodyIndex;			// absolute index of the first Body of the Elem
		UIndex					m_absPointCloudIndex;	// absolute index of the first PointCloud of the Elem
		GS::PagedArray<Int32>	m_absPolygonIndices;	// absolute start index of polygons of the Elem for each Body
	};

	class MODEL3D_DLL_EXPORT	ElemComparator {
	public:
		virtual bool operator () (const ConstElemPtr& e1, const ConstElemPtr& e2) = 0;
		virtual ~ElemComparator  ();
	};

private:
	class MODEL3D_DLL_EXPORT ModelEventSource : public GS::EventSource
	{
	public:
		void	Attach (IModel3DObserver& observer);
		void	Detach (IModel3DObserver& observer);
		void	SendSyncDeletedElems (const Model3D& model3D, ULong fElemIdx, ULong lElemIdx, ULong num);
		void	SendElemsTruncated (const Model3D& model3D, Int32 newElemCount);
		void	SendElemDeleted (const Model3D& model3D, Int32 elemIdx, const Modeler::ConstElemPtr& deletedElem);
		void	SendRestartDelBoundsBuilding (const Model3D& model3D);
		void	SendConvertStateChanged (const Model3D& model3D, ULong fromElemIdx, ULong fromBodyIdx);
		void	SendModelChanged (const Model3D& model3D);
		void	SendModelCleared (const Model3D& model3D);
		void	SendColorShadesChanged (const Model3D& model3D);
		void	SendAllConditionsCleared (const Model3D& model3D);
		void	SendEventBeforeClear (const Model3D& model3D);
		void	SendConvertStarted (const Model3D& model3D);
		void    SendModelCompressed (const Model3D& model3D, GS::Array<Modeler::CompressElemData>& compressInfos);
        virtual ~ModelEventSource ();
	};

	class Box3DTreeSource;
	class RangeQueryAdapter;


	// ---------------------------------------------------------------------------------------------------------------------
	// Container for swappable model data
	// ---------------------------------------------------------------------------------------------------------------------
	class MODEL3D_DLL_EXPORT ElemContainer : public Swappable {
	private:
		SwapFolderRef	swapFolder;
		UInt32			elemCount;

		ElemArray							elems;
		ElimDataArray						elimData;
		GS::PagedArray<ElemAbsoluteIndices>	m_absoluteIndices;
		GS::PagedArray<F_Box3D>				m_modifiedBox3DList;

		GS::HashTable<GS::Guid, UInt32>		elemGuidIndexMap;

		bool								isElimDataUpToDate;
		bool								m_isAbsoluteIndicesValid;

		void						CalculateAbsoluteIndices ();

	protected:
		virtual void				Purge () override;
		virtual void				ReadPurged () override;
		virtual void				ReInitImp () override;

		IO::Name					GetSwapFileName () const;
		void						WriteToFile		(const IO::Location& swapFolderLoc) const;
		void						ReadFromFile	(const IO::Location& swapFolderLoc);

	public:
		ElemContainer ();
		virtual ~ElemContainer();

		const ElemArray&					GetElems		(void) const;
		void								SetElemsSize	(UInt32 size);
		void								ClearElems		(void);
		UInt32								GetElemCount	(void);
		void								SetElem			(UInt32 idx, const ConstElemPtr& elem);
		void								AddElem			(const ConstElemPtr& elem);

		GS::HashTable<GS::Guid, UInt32>&		GetElemGuidIndexMap (void);
		GS::PagedArray<ElemAbsoluteIndices>&	GetElemAbsoluteIndices (void);
		GS::PagedArray<F_Box3D>&				GetModifiedBox3DList (void);

		ElimDataArray&							GetElimDataArray (void);
		bool									IsElimDataUpToDate (void) const		{ return isElimDataUpToDate;		}
		void									SetElimDataUpToDate (bool upToDate)	{ isElimDataUpToDate = upToDate;	}

		void						PurgeToFile	();
		void						SetSwapFolder (const SwapFolderRef& folder);

		ULong						GetBind (ULong elemIdx, ULong bodyIdx);
		UIndex						GetAbsolutePointCloudIndex (UIndex elemIdx, UIndex pcIdx);

		Int32						GetElemIdx	(const GS::Guid& elemGuid);
		Int32						GetGlobPgonIdx (ULong elemIdx, ULong bodyIdx);

		void						CalculateGPgons (ULong firstNewElemIdx);
		ULong						GetGPgonCount (void) const;
		void						InvalidateAbsoluteIndices ();
	};

	// -----------------------------------------------------------------------------------------------------------------
	// data members
	// -----------------------------------------------------------------------------------------------------------------
	mutable ModelEventSource	m_modelEventSource;

	ModStamp					m_modelInfStamp;	// Model information time: When anything is changed in the model
													// (not necessarily geometric change).
	ModStamp					m_prevConvModStamp;
	ModStamp					m_lastConvModStamp;

	GS::Guid					m_modelGuid;
	ULong						m_holesNumber;		// Number of holes of 3D data structure. These bodies were deleted
													// by partial conversion.
	Box3D						m_bounds;

	Conditions					m_progress;
	Conditions					m_condition;

	AttributesPtr				m_attributes;
	Model3DPtr					m_mainModel;		// the MainModel of @this model (may share Elems, BaseElems or Bodies with it)

	mutable ElemContainer		elemContainer;

	GS::FastLock				m_elemElimDataUpdateLock;

	typedef	Geometry::KDTree<Geometry::Box3DKey, const Modeler::Elem*, Geometry::KDTreeNodeBoundsEnabled>	ElemKDTree;
	mutable GS::Owner<ElemKDTree>	m_elemTree;

	GS::UniString				m_creatorName;

	// -----------------------------------------------------------------------------------------------------------------
	// These are for the safe Model3D creation in C++
	// -----------------------------------------------------------------------------------------------------------------

	// Constructors are private, use New to create a Model3D
	Model3D (AttributesPtr			attributesIn,
			 const GS::UniString&	creatorName,
			 DiskCachingMethod		cachingMethodIn	= Cache_KeepDataInMemory,
			 Model3DPtr				mainModel		= nullptr);

	Model3D (const Model3D& source);										// disabled
	Model3D& operator= (const Model3D& source);								// disabled, use Copy

	static void* operator new      (size_t size) { return new char[size]; }	// disabled, use New
	static void  operator delete   (void* ptr) { delete[] reinterpret_cast<char*>(ptr); }

	static void* operator new[]	   (size_t size);							// disabled, use New
	static void  operator delete[] (void* ptr) { delete[] reinterpret_cast<char*>(ptr); }

	// Low level access (will be moved into an internal class)
	const ElemArray&	GetElems () const;

	Int32			GetElemIdx		(const GS::Guid& elemGuid) const;

	void	UpdateFromMainModel (UInt32 fromElemIdx);

	void	PushLastConversionStamp (bool changed);
	void	ResetLastConversionStamp ();

	void	ElemAboutToBeAdded		(const Modeler::Elem& elem);
	void	ElemAboutToBeModified	(const UIndex srcElemIndex, const Modeler::Elem& trg);
	void	ElemAboutToBeDeleted	(const UIndex elemIndex);
	void	InvalidateElimData () const;
	bool	CollectElimDataToUpdate (GS::HashTable<UIndex, bool>& elimElems);
	void	UpdateElimData (GS::ProcessControl& processControl);

	const	ElemElimData&		GetElemElimData  (GS::ProcessControl& processControl, const UInt32 elemIdx)  const;

	void	Synchronize (ModelSynchronizationState& modelSynchronizationState, const Modeler::ConstModel3DPtr& sourceModel, ElemComparator& cmp);

	void	Compress ();
	void	ForceCompress ();

	void	LazyInitElemSearchTree () const;
	void	AddElemToSearchTrees (const Modeler::Elem& elem) const;
	void	ModifyElemInSearchTrees (const Modeler::Elem& oldElem, const Modeler::Elem& newElem) const;
	void	DeleteElemFromSearchTrees (const Modeler::Elem& elem) const;

	template <typename ElemQueryAdapterType>
	void	QueryElems		(const F_Box3D& floatBox, ElemQueryAdapterType& adapter) const;
	template <typename ElemQueryAdapterType>
	void	QueryElems		(const Box3D& box, ElemQueryAdapterType& adapter) const;
	template <typename ElemQueryAdapterType>
	void	QueryElems		(const IntersectionQueryAlgorithm& queryAlgorithm, ElemQueryAdapterType& adapter, GS::ProcessControl& processControl) const;
		
public:
	void		Check(void) const;
	void		DetailedCheck () const;

	friend	MODEL3D_DLL_EXPORT void	MODEL3D_CALL CopyModel (Model3DPtr dest, const Model3D& src);
	friend	MODEL3D_DLL_EXPORT void	MODEL3D_CALL MoveEnd (Model3DModifier* src, Model3DModifier* dst, ULong fromElemIdx);

	static	Model3DPtr	New (
					AttributesPtr			attributesIn,
					const GS::UniString&	creatorName,
					DiskCachingMethod		cachingMethodIn     = Cache_KeepDataInMemory,
					Model3DPtr				mainModel           = nullptr);

	bool				Equals	   (const Model3D& other) const; // numerics "are close enough"
	
	virtual				~Model3D ();
	void				ClearModel ();
	void				TruncateElemCount (UInt32 newElemCount);


	void				TransferToMain ();
	void				Purge ();

	AttributesPtr		GetAttributesPtr ();
	ConstAttributesPtr	GetConstAttributesPtr () const;

	ULong		GetBodyCount		() const;
	USize		GetPointCloudCount	() const;


	void		Attach (IModel3DObserver& observer) const;
	void		Detach (IModel3DObserver& observer) const;

	void		SendSyncDeletedElems (ULong fElemIdx, ULong lElemIdx, ULong num);
	void		SendElemsTruncated (Int32 newElemCount);
	void		SendElemDeleted (Int32 elemIdx, const Modeler::ConstElemPtr& deletedElem);
	void		SendRestartDelBoundsBuilding ();
	void		SendConvertStateChanged (ULong fromElemIdx, ULong fromBodyIdx);
	void		SendModelChanged ();
	void		SendModelCleared ();
	void		SendColorShadesChanged () const;
	void		SendAllConditionsCleared ();
	void		SendEventBeforeClear ();
	void		SendConvertStarted ();
	void		SendModelCompressed (GS::Array<Modeler::CompressElemData>& compressInfos);

	Int32		GetGlobPgonIdx (ULong elemIdx, ULong bodyIdx) const;
	void		CalculateGPgons (ULong firstNewElemIdx);

	void		SortNewElems (ULong firstNewElem, ElemComparator& cmp) const;

	// Normal access

	void		GetBaseElemSet (BaseElemSet &baseElems) const;

	const Box3D&	GetBounds () const;
	void			CalculateBounds (ULong firstNewElem);

	const ModStamp&	GetInfStamp () const;
	void			SetInfStamp (const ModStamp& stamp);
	GS::Guid	GetGuid (void) const;

	const ModStamp&		GetLastConversionModStamp () const;
	const ModStamp&		GetPrevConversionModStamp () const;

	void		ClearAllConditions ();
	void		GetConditions (GSPtr condition, GSPtr progress) const;
	void		SetConditions (GSConstPtr condition, GSConstPtr progress);
	short		GetCondition (Condition typeID) const;
	void		SetCondition (Condition typeID, short newVal);
	short		GetProgressCondition (Condition typeID) const;
	void		SetProgressCondition (Condition typeID, short newVal);
	void		PrintConditions ();

	void		GetElemBodyIdx (ULong absBodyIdx, ULong* elemIdx, ULong* bodyIdx) const;
	ULong		GetBind (ULong elemIdx, ULong bodyIdx) const;
	UIndex		GetAbsolutePointCloudIndex (UIndex elemIdx, UIndex pcIdx) const;
	void		GetElemHotspotIdx (ULong absHotspotIdx, ULong *elemIdx, ULong *hotspotIdx) const;

	void		WriteXML (GS::XMLOChannel& outXML, BaseElemWritePolicy writePolicy = WriteByReference) const;
	void		WriteXMLToDBChannel () const;
	void		ReadXML	 (GS::XMLIChannel& inXML);

	const GS::UniString&	GetCreatorName () const;

	enum EliminationDataMergeMode
	{
		KeepSeparatedEliminationData,
		MergeEliminationData
	};

	enum ModelToReidentify {
		ReidentifyModel1,
		ReidentifyModel2
	};

	class MODEL3D_DLL_EXPORT ElemReidentifier
	{
	public:
		virtual GS::Guid GetNewElemGuid (const GS::Guid& oldGuid) = 0;
		virtual ~ElemReidentifier ();
	};

	static Model3DPtr MergeModels	(GS::ProcessControl&						processControl,
									const GS::UniString&						mergedAttributeName,
									const GS::UniString&						creatorName,
									ModelToReidentify							modelToReidentify,
									ConstModel3DPtr								modelToMerge1,
									ConstModel3DPtr								modelToMerge2,
									EliminationDataMergeMode					elimDataMergeMode,
									ElemReidentifier&							elemReidentifier);


	void		MergeModel (GS::ProcessControl&							processControl,
							ConstModel3DPtr								modelToMerge,
							ElemReidentifier* 							elemReidentifier,
							EliminationDataMergeMode					elimDataMergeMode);

private:
	bool		CalcElimDataBeforeMerge	(GS::ProcessControl& processControl, ConstModel3DPtr modelToMerge, EliminationDataMergeMode elimDataMergeMode);
	void		MergeAndReindexElements (ConstModel3DPtr modelToMerge, ElemReidentifier* elemReidentifier);
	void		MergeElimData			(ConstModel3DPtr modelToMerge, EliminationDataMergeMode elimDataMergeMode);

public:
	// For debug reporting
	ULong							GetUsedBytes ()		const;	// obsolete

	CompositeContainerSizeReport	ReportLogicalSize () const;
	CompositeContainerSizeReport	ReportActualSize () const;
	CompositeContainerSizeReport	ReportClippedModelAdditionalSize () const;
	void							ReportRepeatedTopologySavings (GS::OChannel& oChannel) const;
	
	static	GS::UniString			GetActiveModelsReport (void);

private:
	CompositeContainerSizeReport	ReportSize (const GS::UniString& name,
												SizeReportType reportType,
												const GS::HashSet<ConstElemPtr>& excludedElems,
												const GS::HashSet<const BaseElem*>& excludedBaseElems,
												const GS::HashSet<ConstMeshBodyPtr>& excludedMeshBodies,
												const GS::HashSet<ConstNurbsBodyPtr>& excludedNurbsBodies) const;

	ModelElementCounts GetModelElementCounts (SizeReportType reportType,
											  const GS::HashSet<ConstElemPtr>& excludedElems,
											  const GS::HashSet<const BaseElem*>& excludedBaseElems,
											  const GS::HashSet<ConstMeshBodyPtr>& excludedMeshBodies,
											  const GS::HashSet<ConstNurbsBodyPtr>& excludedNurbsBodies) const;

#ifdef CHECKED_VERSION
public:
	void	DumpGDL () const;
#endif
};

class MODEL3D_DLL_EXPORT Model3DViewer : public MainContainerBase::Viewer {
	protected:
		friend class	Model3D;
		ConstModel3DPtr	model;

		Model3DViewer ();		// disabled

	private:
		GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

	public:
		Model3DViewer  (const ConstModel3DPtr model);
		Model3DViewer	(const Model3DViewer& src_viewer);
		~Model3DViewer ();

		Model3DViewer&	operator= (const Model3DViewer& src);
		bool			operator== (const Model3DViewer& src) const;
		bool			operator!= (const Model3DViewer& src) const;

		inline bool		IsNull		(void)				const { return model == nullptr; }

		UInt32		GetElemCount	()					const;
		UInt32		GetBaseElemCount ()					const;
		const Modeler::Elem&	GetConstElem	(UIndex elemIndex) const;
		Modeler::ConstElemPtr	GetConstElemPtr	(UIndex elemIndex) const;
		const Modeler::Elem*	GetConstElemPtr	(const GS::Guid& elemGuid) const;
		Int32		GetElemIdx	(const GS::Guid& elemGuid) const;
		const Modeler::MeshBody& GetConstMeshBody	(ULong elemIdx, ULong bodyIdx) const;

		Int32		GetGlobPgonIdx			  (ULong elemIdx, ULong bodyIdx) const;
		const Modeler::MeshBody*	GetConstMeshBodyRecPtr		  (ULong elemIdx, ULong bodyIdx) const;
		const GS::ConstSharedPtr<Modeler::MeshBody>&		GetConstMeshBodySharedPtr		  (ULong elemIdx, ULong bodyIdx) const;
		const HOTS*	GetConstHotspotRecPtr	(ULong index) const;

		ULong	GetBodyCount ()					const;
		USize	GetPointCloudCount	()			const;
		ULong	GetVisibleBodyCount ()			const;
		ULong	GetLightSourceCount ()			const;
		ULong	GetModelPolygonCount ()			const;
		ULong	GetModelPolyEdgeCount ()		const;
		ULong	GetModelEdgeCount ()			const;
		ULong	GetModelVertexCount ()			const;
		ULong	GetModelPolyNormalCount ()		const;
 		ULong	GetHotspotCount ()				const;
		ULong	GetModelTextureVertexCount ()	const;
		ULong	GetVOCACount ()					const;

		ULong	GetAllItemsCount ()				const;
		ULong	GetUsedBytes ()					const;
		ULong	GetAllocatedBytes ()			const;
		ULong	GetPolygonConvexPolyBytes ()	const;

		const ElemElimData&		GetElemElimData  (GS::ProcessControl& processControl, const UInt32 elemIdx)  const;
	
		void	GetConditions (GSPtr condition, GSPtr progress) const;
		short	GetCondition (Model3D::Condition typeID) const;
		short	GetProgressCondition (Model3D::Condition typeID) const;

		const Box3D&	GetBounds () const;

		void	GetBaseElemSet (BaseElemSet &baseElems) const;


		const ModStamp&	GetInfStamp () const;
		GS::Guid		GetGuid () const;
		const ModStamp&	GetPrevConversionModStamp () const;
		const ModStamp&	GetLastConversionModStamp () const;

		void			WriteLightSources (GS::OChannel& channel) const;


		void			CheckModel (void) const;
		void			DetailedCheckModel () const;

		bool				HasSameModel (ConstModel3DPtr refModel) const;
		ConstAttributesPtr	GetConstAttributesPtr () const;

		// Fast query methods
		void InitElemSearchTree () const;

		template <typename ElemQueryAdapterType>
		void QueryElems		(const F_Box3D& floatBox, ElemQueryAdapterType& adapter) const;
		template <typename ElemQueryAdapterType>
		void QueryElems		(const Box3D& box, ElemQueryAdapterType& adapter) const;
		template <typename ElemQueryAdapterType>
		void QueryElems		(const IntersectionQueryAlgorithm& queryAlgorithm, ElemQueryAdapterType& adapter, GS::ProcessControl& processControl) const;

		void			GetElemBodyIdx (ULong absBodyIdx, ULong *elemIdx, ULong *bodyIdx) const;
		ULong			GetBind (ULong elemIdx, ULong bodyIdx) const;
		UIndex			GetAbsolutePointCloudIndex (UIndex elemIdx, UIndex pcIdx) const;

		GS::Object*		GetUserData (ULong key) const;

		bool			IsViewerOf (ConstModel3DPtr model) const;
		bool			IsMainModelViewer () const;

		ConstModel3DPtr	GetConstModel3DPtr () const;
};

class MODEL3D_DLL_EXPORT Model3DOnlyModifier : MainContainerBase::OnlyModifier {
	private:
		void	RemoveInvalidElems ();

	protected:
		friend class	Model3D;
		Model3DPtr		model;

		Model3DOnlyModifier ();		// disabled

	public:
		Model3DOnlyModifier (const Model3DPtr model);
		Model3DOnlyModifier (const Model3DOnlyModifier& src);

		~Model3DOnlyModifier ();

		Model3DOnlyModifier&	operator= (const Model3DOnlyModifier& src);
		bool			operator== (const Model3DOnlyModifier& src) const;
		bool			operator!= (const Model3DOnlyModifier& src) const;

		ULong   AddElem (ConstElemPtr elemPtr);
		void	ReplaceElem (UInt32 elemIdx, ConstElemPtr elemPtr);
		void	EmptyElem (UInt32 elemIdx);	// keeps same number of bodies and point clouds

		void	CalculateBounds (ULong firstNewElem = 0);

		void	TruncateElemCount (UInt32 newElemCount);

		void	SetInfStamp (const ModStamp& stamp);
		void	PushLastConversionStamp (bool changed);
		void	ResetLastConversionStamp ();

		void	ClearModel ();

		void	WriteAll ();
		void	CalculateGPgons (ULong firstNewElemIdx);

		void	SetConditions (GSConstPtr condition, GSConstPtr progress);
		void	SetCondition (Model3D::Condition typeID, short newVal);
		void	SetProgressCondition (Model3D::Condition typeID, short newVal);

		void	UpdateFromMainModel (UInt32 fromElemIdx);

		AttributesPtr	GetAttributesPtr ();

		void	SetUserData (ULong key, GS::Object* userData);

		void	Synchronize (ModelSynchronizationState& modelSynchronizationState, const Modeler::ConstModel3DPtr& sourceModel, Model3D::ElemComparator& cmp);

		void	Compress ();
		void	ForceCompress ();
};

class MODEL3D_DLL_EXPORT Model3DModifier : public Model3DViewer, public Model3DOnlyModifier {
	private:
		friend class	Model3D;

		Model3DModifier();		// disabled

	public:
		Model3DModifier (const Model3DPtr src_model);
		Model3DModifier (const Model3DModifier& src);
		~Model3DModifier () {}

		Model3DModifier&	operator= (const Model3DModifier& src);
		bool			operator== (const Model3DModifier& src) const;
		bool			operator!= (const Model3DModifier& src) const;

		friend	MODEL3D_DLL_EXPORT void	MODEL3D_CALL MoveEnd (Model3DModifier* src, Model3DModifier* dst, ULong fromElemIdx);

		void	DeleteElems (ElemPredicateProc* shouldDelete);
		void	DeleteElem (Int32 elemIdx);

		void	SendRestartDelBoundsBuilding ();
		void	SendConvertStateChanged (ULong fromElemIdx, ULong fromBodyIdx);
		void	SendModelChanged ();
		void	SendModelCleared ();
		void	SendColorShadesChanged ();
		void	SendConvertStarted ();
		void	SendModelCompressed (GS::Array<Modeler::CompressElemData>& compressInfos);

		Model3D*	GetModel3D ();
};

}	// namespace Modeler

#ifdef CHECKED_VERSION
inline void Modeler::Model3D::DumpGDL () const
{
	const ElemArray & elems = GetElems ();
	const USize nElems = elems.GetSize ();
	DBPRINTF ("! Dumpimg models %d elements:\n", nElems);
	for (USize elemIndex = 0; elemIndex < nElems; ++elemIndex) {
		ConstElemPtr elemPtr = elems[elemIndex];
		DBPRINTF ("! Dumping elem  %s \n",  elemPtr->GetElemId ().elemGuid.ToUniString ().ToCStr ().Get ());

		const TRANMAT* currTran = elemPtr->GetConstTrafoPtr ();
		if (currTran != nullptr) {
			Vector3d vec1, vec2, vec3, vec4;
			currTran->GetMatrix ().GetColVectors3d (vec1, vec2, vec3, vec4);
			GS::UniString str = GS::UniString::Printf (
				"xform\t%12g, %12g, %12g, %12g,\n\t\t%12g, %12g, %12g, %12g,\n\t\t%12g, %12g, %12g, %12g\n",
				vec1.x, vec2.x, vec3.x, vec4.x,
				vec1.y, vec2.y, vec3.y, vec4.y,
				vec1.z, vec2.z, vec3.z, vec4.z
			);


			dbChannel.WriteBin (reinterpret_cast<const char*> (str.ToCStr ().Get ()), str.GetLength () * sizeof (char));
		}

		ULong nBody = elemPtr->GetTessellatedBodyCount ();
		for (ULong bodyIdx = 0; bodyIdx < nBody; ++bodyIdx) {
			DBPRINTF ("! m_bodies [%d]:\n", bodyIdx);
			const MeshBody & body = elemPtr->GetConstTessellatedBody (bodyIdx);
			body.DumpGDLToDBChannel ();
		}

		if (currTran != nullptr) {
			GS::UniString str ("del \t1\n");
			dbChannel.WriteBin (reinterpret_cast<const char*> (str.ToCStr ().Get ()), str.GetLength () * sizeof (char));
		}
	}
}
#endif

#include "Model3D/Model3DImp.hpp"
#endif // !defined(MODEL3D_HPP)
