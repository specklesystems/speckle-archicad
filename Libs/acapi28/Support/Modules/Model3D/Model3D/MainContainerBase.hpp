// *****************************************************************************
// A Main Container Base is the collected functionality
// common to Attributes, MainContainerBase, and maybe the future View class.
// GSModeler, platform-independent
//
// Namespaces:        Contact person:
//    Modeler          FGY
//
// SG compatible
// *****************************************************************************

#if !defined(MAINCONTAINERBASE_HPP)
#define MAINCONTAINERBASE_HPP

#pragma once

// from GSRoot
#include	"GSRoot.hpp"
#include	"Array.hpp"
#include	"SharedObject.hpp"
#include	"Ref.hpp"
#include	"Optional.hpp"

// from InputOutput
#include	"Location.hpp"

// from GSUtils
#include	"GSUtilsDefs.h"		// STATL

// from Model3D
#include	"Model3D/Model3DPrivExp.h"
#include	"Model3D/Model3DMain.hpp"

namespace Modeler {

class MainContainerBase;
typedef GS::SharedPtr<MainContainerBase>		MainContainerBasePtr;
typedef GS::ConstSharedPtr<MainContainerBase>	ConstMainContainerBasePtr;

// from Model3D/SwapFolder.hpp
class SwapFolder;
typedef GS::Ref<SwapFolder, GS::AtomicCounter>	SwapFolderRef;


MODEL3D_DLL_EXPORT
void	MODEL3D_CALL DeepCopyMainContainerBase (MainContainerBasePtr dest, const MainContainerBase& src);

class MODEL3D_DLL_EXPORT MainContainerBase : public GS::SharedObject
{
public:
	class Viewer;
	class OnlyModifier;

	friend class Viewer;
	friend class OnlyModifier;
	friend class GS::SharedPtr<MainContainerBase>;
	friend class GS::ConstSharedPtr<MainContainerBase>;

protected:
	SwapFolderRef		swapFolder;			// swap folder shared with child classes and their members by reference counting
	DiskCachingMethod	cachingMethod;		// mainly for member containers: keep contents always in memory or may swap it to disk
	STATL				status;				// various status bits
	GS::UniString		name;

	mutable GS::Array<PropertyPair>	userProperties;	// it will be a key/value hash in the future

	MainContainerBase (DiskCachingMethod cachingMethodIn = Cache_KeepDataInMemory,
					   const GS::UniString& nameIn = GS::EmptyUniString);

	ULong	SearchUserDataKey (ULong seachKey) const;
	void	ClearUserData ();

	void	CreateSwapFolder (const GS::UniString& folderName);
	void	SetName (const GS::UniString& newName);

	static void* operator new      (size_t size) { return new char[size]; }			// disabled, use New
	static void  operator delete   (void* ptr) { delete[] reinterpret_cast<char*>(ptr); }

	static void* operator new[]	   (size_t size);									// disabled, use New
	static void  operator delete[] (void* ptr) { delete[] reinterpret_cast<char*>(ptr); }

public:
	friend	MODEL3D_DLL_EXPORT	void	MODEL3D_CALL	DeepCopyMainContainerBase (MainContainerBasePtr dest, const MainContainerBase& src);

	MainContainerBase (const MainContainerBase& source)								= delete;	// use DeepCopy instead
	MainContainerBase& operator= (const MainContainerBase& source)					= delete;	// use DeepCopy instead
	virtual ~MainContainerBase ();

	GS::Object*				GetUserData (ULong key) const;
	void					SetUserData (ULong key, GS::Object* userData) const;

	DiskCachingMethod		GetCachingMethod () const;

	const GS::UniString&	GetName () const;
	
	GS::Optional<IO::Location> GetSwapFolderLocation () const;

	class Viewer {
		protected:
			friend class	MainContainerBase;
			ConstMainContainerBasePtr	mainContainer;

			Viewer ();		// disabled

		public:
			Viewer  (const ConstMainContainerBasePtr model);
			Viewer	(const Viewer& src_viewer);
			~Viewer ();

			Viewer&		operator= (const Viewer& src);
	};

	class OnlyModifier {
		private:
			friend class	MainContainerBase;
			MainContainerBasePtr		mainContainer;

			OnlyModifier ();		// disabled

		public:
			OnlyModifier (const MainContainerBasePtr model);
			OnlyModifier (const OnlyModifier& src);

			~OnlyModifier ();

			OnlyModifier&	operator= (const OnlyModifier& src);
	};

	class Modifier : public Viewer, public OnlyModifier {
		private:
			friend class	MainContainerBase;

			Modifier();		// disabled

		public:
			Modifier (const MainContainerBasePtr src_model);
			~Modifier () {}

			Modifier&	operator= (const Modifier& src);
	};
};

inline DiskCachingMethod MainContainerBase::GetCachingMethod () const
{
	return cachingMethod;
}


inline MainContainerBase::Viewer::Viewer (const ConstMainContainerBasePtr src_mainContainer) :
	mainContainer (src_mainContainer)
{
	// do nothing
}


inline MainContainerBase::Viewer::Viewer (const Viewer& src_viewer) :
	mainContainer (src_viewer.mainContainer)
{
	// do nothing
}


inline MainContainerBase::Viewer::~Viewer ()
{
	// do nothing
}


inline MainContainerBase::Viewer&	MainContainerBase::Viewer::operator= (const MainContainerBase::Viewer& src)
{
	mainContainer = src.mainContainer;
	return *this;
}


inline MainContainerBase::OnlyModifier::OnlyModifier (const MainContainerBasePtr src_mainContainer) :
	mainContainer (src_mainContainer)
{
	// do nothing
}


inline MainContainerBase::OnlyModifier::OnlyModifier (const OnlyModifier& src) :
	mainContainer (src.mainContainer)
{
	// do nothing
}


inline MainContainerBase::OnlyModifier::~OnlyModifier ()
{
	// do nothing
}


inline MainContainerBase::OnlyModifier&	MainContainerBase::OnlyModifier::operator= (const MainContainerBase::OnlyModifier& src)
{
	mainContainer = src.mainContainer;
	return *this;
}


}	// namespace Modeler

#endif // !defined(MAINCONTAINERBASE_HPP)
