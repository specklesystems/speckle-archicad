// *****************************************************************************
// Attributes is a collection of attributes.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          FGY
//
// Documentation:
//    http://wiki/w/Modeler_Attributes
//
// SG compatible
// *****************************************************************************

#if !defined(MODELERATTRIBUTES_HPP)
#define MODELERATTRIBUTES_HPP

#pragma once

// from GSRoot
#include	"GSRoot.hpp"
#include	"FastLock.hpp"

//from GSModeler
#include	"RTXT.hpp"
#include	"UFIL.hpp"
#include	"UMAT.hpp"
#include	"Model3D/ModStamp.hpp"
#include	"Model3D/MainContainerBase.hpp"
#include	"Model3D/AttributeArray.hpp"
#include	"Model3D/Model3DSizeReport.hpp"

#define	MAXRTXT		  10
#define	MAXUFIL		  10
#define	MAXUMAT		  10

#define	MAXFIDE		1000

enum LoadTextureParameters {TEXTURE_USE_ANTIALIAS, TEXTURE_DONT_USE_ANTIALIAS};
enum TextureUnloadOption {UnloadOnly, FullReset};

namespace GS {
	class ReentrantLock;
}

struct FMAT;

namespace GX {
	namespace Pattern {
		class FillData;
	}
}

namespace Modeler {
class MaterialData;
class TextureData;
class Attributes;
typedef GS::SharedPtr<Attributes>			AttributesPtr;
typedef GS::ConstSharedPtr<Attributes>		ConstAttributesPtr;

class Elem;
class CandidateMeshBody;

class IAttributeReader;
struct ModelILookup;
struct ModelOLookup;

enum class AttributesUpdateResult {
	Unchanged,
	AttributeIndicesChanged
};

class MODEL3D_DLL_EXPORT Attributes : public MainContainerBase
{

public:
	class Viewer;
	class OnlyModifier;
	class Modifier;

	friend class Viewer;
	friend class OnlyModifier;
	friend class Modifier;
	friend class GS::SharedPtr<Attributes>;
	friend class GS::ConstSharedPtr<Attributes>;

	enum MultithreadingMode {
		//no locking
		SingleThreaded,

		//reads are not locked, append operations are locked, others writes are disabled completely
		MultiThreaded
	};

private:
	ConstAttributesPtr					parentAttributes;
	ULong								parentTextureCount;
	ULong								parentUFILCount;
	ULong								parentUMATCount;

	AttributeArray<RTXT>				rtxt;
	AttributeArray<UFIL>				ufil;
	AttributeArray<UMAT>				umat;

	ModStamp							lastUpdateStamp;

	typedef	GS::ReentrantLock			LockType;
	LockType*							lock;

	// HACK: for reading binaries that don't contain materials / fills (eg. stair with newel)
	// first material/fill added to or used from the attribute set
	// during the generation of the current elem
	ULong								firstMaterial;
	ULong								firstFill;

	class GuardLock;

	MultithreadingMode					multithreadingMode;

	enum AttributeSetType {
		NormalAttributeSet,
		SourceAttributeSet				/*Always thread-safe attribute set. Can't be used for visualization.*/
	}									attrSetType;
	AttributesPtr						sourceAttributes;

	Int64	LoadTextures (short textureIndex, LoadTextureParameters textParam) const;

	// -----------------------------------------------------------------------------
	// These are for the safe Attributes creation in C++


	Attributes (const ConstAttributesPtr& parentAttributes, const AttributesPtr& sourceAttributes, AttributeSetType attrSetType, const GS::UniString& name);
	Attributes (const Attributes& src);				// disabled
	Attributes& operator= (const Attributes& src);	// disabled, use Copy

	static void* operator new (size_t size) { return new char[size]; }	// disabled, use New
	static void  operator delete (void* ptr) { delete[] reinterpret_cast<char*>(ptr); }

	static void* operator new[] (size_t size);			// disabled, use New
	static void  operator delete[] (void* ptr) { delete[] reinterpret_cast<char*>(ptr); }

	ULong		GetFillCount () const;
	ULong		GetTextureCount ()			const;
	ULong		GetMaterialCount () const;

	UFIL*		GetFillPtr				(ULong index);
	RTXT*		GetTexturePtr			(ULong index);
	UMAT*		GetMaterialPtr			(ULong index);


	const UFIL*	GetConstFillPtr					(ULong index)	const;
	const RTXT*	GetConstTexturePtr				(ULong index)	const;
	const UMAT*	GetConstMaterialPtr				(ULong index)	const;

	bool		ClearTextureCache ();

	void		SyncWithSource (const Modeler::IAttributeReader* attReader);

	ULong		AddFill (const UFIL& fillHead);
	void		SetFirstFill (ULong index);
	ULong		FindFill (const UFIL& aufil);

	ULong		AddMaterial (const UMAT& aumat);
	void		SetFirstMaterial (GSAttributeIndex index);
	void		CreateUpdatedCopyOfMaterial (ULong index, const Modeler::IAttributeReader& attReader, UMAT& updatedUmat);
	ULong		FindMaterial (const UMAT& umat_in);

	ULong		AddTexture  (const RTXT& artxt);
	ULong		FindTexture (const RTXT& rtxt);

	GSAttributeIndex	InsertFill (const Modeler::IAttributeReader* attReader, const UFIL& aufil);
	ULong				InsertUMAT	(const Modeler::IAttributeReader* attReader, const UMAT& umat);
	ULong				InsertMaterialData (const Modeler::IAttributeReader& attReader, const ADB::AttributeIndex& genfrom, const Modeler::MaterialData* mater);
	ULong				InsertTexture (const Modeler::IAttributeReader* attReader, const Modeler::TextureData& td);
	ULong				InsertTexture (const Modeler::IAttributeReader* attReader, const RTXT& rtxt);



public:
	virtual ~Attributes ();

	void 	ClearAttributes ();
	void	ResetAttributes ();

	AttributesUpdateResult	UpdateFromParent ();

	void	ReplaceParent (const ConstAttributesPtr& newParentAttributes);

	void	UnloadAllTexturesPixels (const TextureUnloadOption option = UnloadOnly) const;

	void	WriteXML (GS::XMLOChannel& outXML) const;
	void	ReadXML	 (GS::XMLIChannel& inXML);

	class MODEL3D_DLL_EXPORT ThreadingModeSetterGuard
	{
	public:
		ThreadingModeSetterGuard (const Modeler::AttributesPtr& thsInit, MultithreadingMode newMultithreadingMode);
		~ThreadingModeSetterGuard();
	private:
		MultithreadingMode			oldMultithreadingMode;
		Modeler::AttributesPtr		ths;
	};

	class MODEL3D_DLL_EXPORT Viewer : MainContainerBase::Viewer {
		protected:
			friend class	Attributes;
			ConstAttributesPtr	attributes;

			Viewer ();		// disabled

		public:
			Viewer  (const ConstAttributesPtr model);
			~Viewer ();

			Viewer&	operator= (const Viewer& src);
			bool	operator== (const Viewer& src) const;
			bool	operator!= (const Viewer& src) const;

			ULong	GetFillCount ()				const;
			ULong	GetTextureCount ()			const;
			ULong	GetMaterialCount ()			const;

			ULong	GetAllItemsCount ()			const;
			ULong	GetUsedBytes ()				const;
			ULong	GetAllocatedBytes ()		const;
			ULong	GetActualTexturePixelBytes ()		const;

			const UFIL*	GetConstFillPtr					(ULong index)	const;
			const RTXT*	GetConstTexturePtr				(ULong index)	const;
			const UMAT*	GetConstMaterialPtr				(ULong index)	const;

			void	WriteFillFile				(GS::OChannel& channel, ULong index, ULong count)	const;
			void	WriteTextureFile			(GS::OChannel& channel, ULong index, ULong count)	const;
			void	WriteMaterialFile			(GS::OChannel& channel, ULong index, ULong count)	const;

			Int64	LoadTexturePixels (short textureIndex, LoadTextureParameters textParam) const;
			Int64	LoadAllTexturesPixels (LoadTextureParameters textParam) const;

			void	UnloadAllTexturesPixels (const TextureUnloadOption option = UnloadOnly) const;

			bool	IsViewerOf (ConstAttributesPtr	attributes) const;

			const ModStamp&	GetLastUpdateStamp (void) const;

			ULong	GetFillDescriptorSize () const;

			ULong	GetFirstMaterial	() const;
			ULong	GetFirstFill		() const;

			// For debug reporting
			CompositeContainerSizeReport	ReportSize ();
	};

	enum CompatibilityLevel {
		FullyCompatible,
		CheckLimits,
		NotCompatible
	};

	struct CompatibilityLimits {
		UInt32 textureLimit; 
		UInt32 materialLimit;
		CompatibilityLimits () : textureLimit (0), materialLimit (0) {}
	};

	class MODEL3D_DLL_EXPORT OnlyModifier : MainContainerBase::OnlyModifier {
		private:
			friend class	Attributes;

			AttributesPtr	attributes;

			OnlyModifier ();		// disabled

			Int32 	InsertVBAttrFill (const Modeler::IAttributeReader& attReader, const ADB::AttributeIndex& fillind);
			void	GenerateFillName (short iufil, GS::UniString& fname);
			void	ConvertToUfil (UFIL* aufil, const UFilGenFrom& genfrom, const GS::UniString& name, const GX::Pattern::FillData* fillData);

			void				SetMaterial (UMAT& umat, ULong index);
			ULong				InsertPenMaterial (const Modeler::IAttributeReader& attReader, short color);
			Int32				InsertGeneralMaterial (const Modeler::IAttributeReader& attReader, const ADB::AttributeIndex& glima, short color);
			ULong				InsertDummyMaterial (const Modeler::IAttributeReader* attReader);

		public:
			OnlyModifier (const OnlyModifier& src);
			OnlyModifier (const AttributesPtr attributes);
			~OnlyModifier ();

			OnlyModifier&	operator= (const OnlyModifier& src);
			bool			operator== (const OnlyModifier& src) const;
			bool			operator!= (const OnlyModifier& src) const;

			void 	ClearAttributes ();
			void	ResetAttributes ();
			Modeler::AttributesUpdateResult	UpdateFromParent ();

			GSAttributeIndex	InsertFill (const Modeler::IAttributeReader* attReader, const UFIL& aufil);
			ULong				InsertCustomFill (const Modeler::IAttributeReader* attReader, const UFIL& aufil);
			GSAttributeIndex	InsertFillDefFill (const Modeler::IAttributeReader* attReader, const UFilGenFrom& genfrom, const GX::Pattern::FillData* filldef);
			void				Fills2Fides (const Modeler::IAttributeReader& attReader);
			void				ToSelfContained (const Modeler::IAttributeReader& attReader);

			ULong	InsertUMAT	(const Modeler::IAttributeReader* attReader, const UMAT& umat);
			ULong	InsertMaterialData (const Modeler::IAttributeReader& attReader, const Modeler::MaterialData& mater);
			Int32	GenfromToMaterialIndex (const Modeler::IAttributeReader& attReader, const UMatGenFrom& genfrom);
			Int32	GlimaToMaterialIndex (const Modeler::IAttributeReader& attReader, short color, const GlimaIdx& glima);
			void	UpdateMaterials (const Modeler::IAttributeReader& attReader);

			ULong	InsertTexture (const Modeler::IAttributeReader* attReader, const Modeler::TextureData& td);
			ULong	InsertTexture (const Modeler::IAttributeReader* attReader, const RTXT& rtxt);
			ULong 	InsertTexture (const Modeler::IAttributeReader* attReader, double xsiz, double ysiz, STATW status, const GS::UniString& imageName, short pictIndex, Int32 hsiz, Int32 vsiz, GSHandle tpixs);

			CompatibilityLevel	IsCompatibleTargetAttributeSet (const Modeler::IAttributeReader* attReader, const Viewer& srcAttributesViewer, CompatibilityLimits& compatibilityLimits) const;

			void	SetLastUpdateStamp (const ModStamp& lastUpdateStamp);
	};

	class MODEL3D_DLL_EXPORT Modifier : public Viewer, public OnlyModifier {
		private:
			friend class	Attributes;

			Modifier();		// disabled

		public:
			Modifier (const AttributesPtr attributes);
			~Modifier () {}

			Modifier&	operator= (const Modifier& src);
			bool		operator== (const Modifier& src) const;
			bool		operator!= (const Modifier& src) const;
	};

	static AttributesPtr New (const ConstAttributesPtr& parentAttributes, const GS::UniString& name);
	static AttributesPtr NewWithSource (const AttributesPtr& sourceAttributes, const GS::UniString& name);
	static AttributesPtr NewSourceAttributeSet (const GS::UniString& name);

	static void	DisposeActiveAttributesFileRefs (void);

private:
	static	GS::HashSet<Attributes*>	activeAttributes;
	static	GS::FastLock				activeAttributesLock;
};

inline ULong Attributes::GetFillCount () const
{
	return parentUFILCount + ufil.GetSize ();
}


inline ULong Attributes::GetTextureCount () const
{
	return parentTextureCount + rtxt.GetSize ();
}


inline ULong Attributes::GetMaterialCount () const
{
	return parentUMATCount + umat.GetSize ();
}


inline UFIL*	Attributes::GetFillPtr (ULong index)
{
	if (DBERROR (multithreadingMode != SingleThreaded && index <= parentUFILCount)) {
		throw GS::AccessViolationException ();
	}
	return &ufil [index - parentUFILCount - 1];
}


inline RTXT*	Attributes::GetTexturePtr	(ULong index)
{
	if (DBERROR (multithreadingMode != SingleThreaded && index <= parentTextureCount)) {
		throw GS::AccessViolationException ();
	}
	return &rtxt [index - parentTextureCount - 1];
}


inline UMAT*	Attributes::GetMaterialPtr (ULong index)
{
	if (DBERROR (multithreadingMode != SingleThreaded && index <= parentUMATCount)) {
		throw GS::AccessViolationException ();
	}
	return &umat [index - parentUMATCount - 1];
}

inline const UFIL*	Attributes::GetConstFillPtr (ULong index) const
{
	if (index < 1 || index > GetFillCount ()) {
		throw GS::IllegalArgumentException ("Fill (ufil) index out of range", __FILE__, __LINE__);
	}

	return index <= parentUFILCount ? parentAttributes->GetConstFillPtr (index) : &ufil [index - parentUFILCount - 1];
}

inline const RTXT*	Modeler::Attributes::GetConstTexturePtr (ULong index) const
{
	if (index < 1 || index > GetTextureCount ()) {
		throw GS::IllegalArgumentException ("Texture (rtxt) index out of range", __FILE__, __LINE__);
	}
	return index <= parentTextureCount ? parentAttributes->GetConstTexturePtr (index) : &rtxt [index - parentTextureCount - 1];
}


inline const UMAT*	Attributes::GetConstMaterialPtr (ULong index) const
{
	if (index < 1 || index > GetMaterialCount ()) { // index - 1 >= attributes->umat.GetSize ()
		throw GS::IllegalArgumentException ("Material (umat) index out of range", __FILE__, __LINE__);
	}
	return index <= parentUMATCount ? parentAttributes->GetConstMaterialPtr (index) : &umat[index - parentUMATCount - 1];
}


inline Attributes::Viewer::Viewer (const ConstAttributesPtr src_attributes) :
	MainContainerBase::Viewer (src_attributes.operator->()),
	attributes (src_attributes)
{
}


inline Attributes::Viewer::~Viewer ()
{
}

inline Attributes::Viewer&	Attributes::Viewer::operator= (const Attributes::Viewer& src)
{
	MainContainerBase::Viewer::operator= (src);
	attributes = src.attributes;
	return *this;
}

inline bool	Attributes::Viewer::operator== (const Attributes::Viewer& src) const
{
	return attributes == src.attributes;
}

inline bool	Attributes::Viewer::operator!= (const Attributes::Viewer& src) const
{
	return !operator== (src);
}

inline ULong Attributes::Viewer::GetFillCount () const
{
	return attributes->GetFillCount ();
}

inline ULong Attributes::Viewer::GetTextureCount () const
{
	return attributes->GetTextureCount ();
}

inline ULong Attributes::Viewer::GetMaterialCount () const
{
	return attributes->GetMaterialCount ();
}

inline const UFIL* Attributes::Viewer::GetConstFillPtr (ULong index) const
{
	return attributes->GetConstFillPtr (index);
}

inline const RTXT* Attributes::Viewer::GetConstTexturePtr (ULong index) const
{
	return attributes->GetConstTexturePtr (index);
}

inline const UMAT* Attributes::Viewer::GetConstMaterialPtr (ULong index) const
{
	return attributes->GetConstMaterialPtr (index);
}

inline void	Attributes::Viewer::UnloadAllTexturesPixels (const TextureUnloadOption option /*= UnloadOnly*/) const
{
	attributes->UnloadAllTexturesPixels (option);
}

inline bool Attributes::Viewer::IsViewerOf (ConstAttributesPtr	attributes) const
{
	return this->attributes == attributes;
}

inline const ModStamp& Attributes::Viewer::GetLastUpdateStamp (void) const
{
	return attributes->lastUpdateStamp;
}

inline ULong	Attributes::Viewer::GetFirstMaterial (void) const
{
	return attributes->firstMaterial;
}

inline ULong	Attributes::Viewer::GetFirstFill (void) const
{
	return attributes->firstFill;
}

inline Attributes::OnlyModifier::OnlyModifier (const OnlyModifier& src) :
	MainContainerBase::OnlyModifier (src.attributes.operator->()),
	attributes (src.attributes)
{
}

inline Attributes::OnlyModifier::OnlyModifier (const AttributesPtr src_attributes) :
	MainContainerBase::OnlyModifier (src_attributes.operator->()),
	attributes (src_attributes)
{
}


inline Attributes::OnlyModifier::~OnlyModifier ()
{
}


inline Attributes::OnlyModifier&	Attributes::OnlyModifier::operator= (const Attributes::OnlyModifier& src)
{
	MainContainerBase::OnlyModifier::operator= (src);
	attributes = src.attributes;
	return *this;
}

inline bool	Attributes::OnlyModifier::operator== (const Attributes::OnlyModifier& src) const
{
	return attributes == src.attributes;
}

inline bool	Attributes::OnlyModifier::operator!= (const Attributes::OnlyModifier& src) const
{
	return !operator== (src);
}

inline void		Attributes::OnlyModifier::SetLastUpdateStamp (const ModStamp& lastUpdateStamp)
{
	if (DBVERIFY (attributes->multithreadingMode == SingleThreaded)) {
		attributes->lastUpdateStamp = lastUpdateStamp;
	}
}

inline void		Attributes::SetFirstMaterial (GSAttributeIndex index)
{
	if (multithreadingMode == SingleThreaded) {
		if (firstMaterial == 0) {
			firstMaterial = index;
		}
	}
}


inline void		Attributes::OnlyModifier::SetMaterial (UMAT& umat, ULong index)
{
	*(attributes->GetMaterialPtr (index)) = umat;
}


inline void		Attributes::SetFirstFill (ULong index)
{
	if (multithreadingMode == SingleThreaded) {
		if (firstFill == 0) {
			firstFill = index;
		}
	}
}

inline Attributes::Modifier::Modifier (const AttributesPtr src_attribute) :
	Viewer (src_attribute), OnlyModifier (src_attribute)
{
}

inline Attributes::Modifier&	Attributes::Modifier::operator= (const Attributes::Modifier& src)
{
	Attributes::Viewer::operator= (src);
	Attributes::OnlyModifier::operator= (src);
	return *this;
}

inline bool	Attributes::Modifier::operator== (const Attributes::Modifier& src) const
{
	return Attributes::Viewer::operator== (src) && Attributes::OnlyModifier::operator== (src);
}

inline bool	Attributes::Modifier::operator!= (const Attributes::Modifier& src) const
{
	return !operator== (src);
}

}	// namespace Modeler

MODEL3D_DLL_EXPORT
short MODEL3D_CALL StretchTextureBounds (short distcode, double xsize, double ysize,
										 Int32 *dd, GSRect *picRect);
MODEL3D_DLL_EXPORT
GSHandle MODEL3D_CALL PixMap2TexturePixels (GSPixMapHandle aPixMap, double xsize, double ysize, short depth,
											Int32 hsize, Int32 vsize, STATW* status, bool needAdjust);
MODEL3D_DLL_EXPORT
GSPixMapHandle MODEL3D_CALL TexturePixels2PixMap (const RTXT* rtxt);

#endif // !defined(ATTRIBUTES_HPP)
