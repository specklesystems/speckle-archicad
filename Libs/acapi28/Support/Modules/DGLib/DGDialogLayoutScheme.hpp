// *****************************************************************************
// File:			DGDialogLayoutScheme.hpp
//
// Description:		Dialog layout related classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	BLA
//
// SG compatible
// *****************************************************************************

#ifndef DGDIALOGLAYOUTSCHEME_HPP
#define DGDIALOGLAYOUTSCHEME_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRoot.hpp"
#include "StateEventSource.hpp"
#include "Object.hpp"
#include "HashTable.hpp"

#include "DGUtility.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace xercesc_3_0 {
class DOMElement;
}

namespace DG {
	class DialogLayoutSchemeImpl;
	class DialogLayoutSchemeManagerImpl;
	class SizeableDockData;
	class DockPalette;
}


// --- Enumerations ------------------------------------------------------------

namespace DG {

enum DockState {
	DockInvalid,
	DockLeft,
	DockTop,
	DockRight,
	DockBottom
};

namespace Dock {
	enum DockType {
		Sizeable,
		Fix,
		NoDock
	};
}


// --- FixedSizedDockData ------------------------------------------------------

class DG_DLL_EXPORT FixedSizedDockData
{
	DECLARE_ROOT_CLASS_INFO

public:
	enum State {
		Normal,
		Moving
	};

private:
	DockState	dockState;
	State		state;
	Point		moveDeltaPosition;	// the vector from the palette lefttop point to the point inside the palette,
	Int32		position;			// the palette position inside the row
	GSIndex		dockRow;
	Rect		floatingRect;
	double		scaleFactor;

public:
	static bool			readOldVersion;

						FixedSizedDockData ();

	bool				operator== (const FixedSizedDockData& source) const;
	bool				operator< (const FixedSizedDockData& source) const;

	DockState			GetDockState	(void) const;
	void				SetDockState	(DockState dockState);
	State				GetState		(void) const;
	void				SetState		(State state);
	Int32				GetPosition		(void) const;
	void				SetPosition		(Int32 position);
	GSIndex				GetDockRow		(void) const;
	void				SetDockRow		(GSIndex dockRow);
	Point				GetMoveDeltaPosition	(void) const;
	void				SetMoveDeltaPosition	(Point moveDeltaPosition);
	void				SetFloatingRect (const Rect& rect, double scaleFactor);
	Rect				GetFloatingRect	(void) const;
	double				GetScaleFactor (void) const;

	// serialization
	virtual	GSErrCode	Read		 (GS::IChannel& ic);
			GSErrCode	ReadVersion1 (GS::IChannel& ic);
			GSErrCode	ReadVersion2 (GS::IChannel& ic);
	virtual	GSErrCode	Write (GS::OChannel& oc) const;

	GSErrCode	Read	(xercesc_3_0::DOMElement* elem, short version);
	GSErrCode	Write	(xercesc_3_0::DOMElement* elem, short depth) const;
};


}	// namespace DG


namespace DG {

// --- DialogLayoutScheme ------------------------------------------------------

class DG_DLL_EXPORT DialogLayoutScheme: public	GS::Object
{
	friend class DialogLayoutSchemeManager;
	DECLARE_CLASS_INFO

	class RectData
	{
	public:
		Rect rect;
		double scaleFactor;

		RectData () : rect (), scaleFactor (1.0) {}
		RectData (Rect rect, double scaleFactor) : rect (rect), scaleFactor (scaleFactor) {}
		bool	operator== (const RectData& source) const
		{
			return rect == source.rect && fabs (scaleFactor - source.scaleFactor) < 1.0E-6;
		}

		GSErrCode	Read (GS::IChannel& ic)
		{
			rect.Read (ic);
			GSErrCode err = ic.Read (scaleFactor);
			return err;
		}

		GSErrCode	Write (GS::OChannel& oc) const
		{
			rect.Write (oc);
			GSErrCode err = oc.Write (scaleFactor);
			return err;
		}
	};

private:
	// attributes
	GS::HashTable<GS::Guid, bool>					dockedPalettes;

	GS::HashTable<GS::Guid, FixedSizedDockData>		fixedDockState;
	SizeableDockData*								sizeableDockRootNode;
	GS::Array<SizeableDockData*>					sizeableFloatingRootNodes;
	GS::HashTable<GS::UniString, RectData>			notDockableRects;

	void					DeleteRootNodes		(void);
	void					DeleteContent		(void);
	static GS::UniString	EncodePaletteId		(Int32 developerId, Int32 localId, Int32 dialResId);
	static GS::UniString	EncodePaletteId		(const GS::Guid& palette);

public:
	// constructors / destructors
			DialogLayoutScheme ();
			DialogLayoutScheme (const DialogLayoutScheme& source);
		   ~DialogLayoutScheme ();

	DialogLayoutScheme& operator= (const DialogLayoutScheme& source);
	bool	operator== (const DialogLayoutScheme& source) const;

	//data structure manipulation
	void					SetFloatingSibling		(const GS::Guid& palette, const GS::Guid& sibling, DockState side);
	void					SetDockedSibling		(const GS::Guid& palette, const GS::Guid& sibling, DockState side, USize size);

	DockPalette*			CreateDockPalette		(const GS::Guid& palette);

	void					SetDockState			(const GS::Guid& palette, bool docked);
	void					SetFloatingRect			(const GS::Guid& palette,
													 Int32           developerId,
													 Int32           localId,
													 Int32           dialResId,
													 const Rect&     rect,
													 double          scaleFactor);
	Rect					GetFloatingRect			(const GS::Guid& palette) const;
	Rect					GetFloatingRect			(Int32 developerId, Int32 localId, Int32 dialResId) const;
	double					GetScaleFactor			(const GS::Guid& palette) const;
	double					GetScaleFactor			(Int32 developerId, Int32 localId, Int32 dialResId) const;

	bool					IsDocked				(const GS::Guid& palette) const;
	Dock::DockType			GetDockType				(const GS::Guid& palette) const;

	void					ClearAllVisibility		(void);
	void					SetVisibility			(const GS::Guid& palette, bool visible);

	void					ClearAllFloatingData	(void);

	//TODO: temp
	FixedSizedDockData&		GetFixedSizeDockData	(const GS::Guid& palette);


	// operations
	bool					HasPalette				(const GS::Guid& palette) const;
	bool					HasPalette				(Int32 developerId, Int32 localId, Int32 dialResId) const;

	void					ActivateDockLayout					(void);

	void					CheckAndValidateDockedPaletteData ();

	SizeableDockData*		GetSizeableDockRootNode				(void);
	void					SetSizeableDockRootNode				(SizeableDockData* newRoot);

	USize					GetSizeableFloatingRootNodeCount	(void) const;
	SizeableDockData*		GetSizeableFloatingRootNode			(UIndex index) const;
	UIndex					GetSizeableFloatingRootNodeIndex	(SizeableDockData* dockRootNode) const;
	void					AddSizeableFloatingRootNode			(SizeableDockData* dockRootNode);
	void					DeleteSizeableFloatingRootNode		(UIndex index);

	SizeableDockData*		SearchPaletteFloatingRoot			(const GS::Guid& paletteGuid) const;
	DockPalette*			SearchPaletteFloatingDockWindow		(const GS::Guid& paletteGuid) const;

	SizeableDockData*		SearchPaletteRoot					(const GS::Guid& paletteGuid);
	DockPalette*			SearchPaletteDockWindow				(const GS::Guid& paletteGuid) const;

	void					Scale (double newScaleFactor, double oldScaleFactor);

	// serialization
	virtual	GSErrCode	Read	(GS::IChannel& ic) override;
			GSErrCode	ReadVersion1	(GS::IChannel& ic);
			GSErrCode	ReadVersion2	(GS::IChannel& ic);
			GSErrCode	ReadVersion3	(GS::IChannel& ic);
	virtual	GSErrCode	Write	(GS::OChannel& oc) const override;

	GSErrCode	Read	(xercesc_3_0::DOMElement* elem);
	GSErrCode	Write	(xercesc_3_0::DOMElement* elem, short depth) const;
};



// --- DialogLayoutSchemeManager -----------------------------------------------

class DG_DLL_EXPORT DialogLayoutSchemeManager: public GS::StateEventSource
{
	friend DG_DLL_EXPORT void CCALL		DGShowModelessDialog (short dialId, short refDialId);
	friend DG_DLL_EXPORT void CCALL		DGHideModelessDialog (short dialId);
	friend DG_DLL_EXPORT void CCALL		DGDestroyPalette (short dialId);

	friend class DialogLayoutScheme;

public:
	class DG_DLL_EXPORT FixedDockStateGuard {
	public:
		FixedDockStateGuard ();
		~FixedDockStateGuard ();
	};

private:
	// implementation
	DialogLayoutSchemeManagerImpl*		impl;

	// active dialog layout scheme
	USize								cascadeCount;

	// active fixedDockState guard
	USize								fixedDockStateGuardCount;

	DialogLayoutSchemeManager				(const DialogLayoutSchemeManager& source);		// disable copy
	DialogLayoutSchemeManager& operator=	(const DialogLayoutSchemeManager& source);		// disable assignment

public:
	// constructors / destructors
			DialogLayoutSchemeManager ();
		   ~DialogLayoutSchemeManager ();

	// accessors
	bool						IsDialogIdentifiable		(const GS::Guid& guid) const;
	short						GetDialogId					(const GS::Guid& guid) const;

	// operations
	void						SendChange (void) { GS::StateEventSource::SendChange (); };

	void						BeginLayout			(const DialogLayoutScheme* dialogLayoutScheme = nullptr);
	void						EndLayout			(void);
	void						SaveLayout			(DialogLayoutScheme* dialogLayoutScheme);

	bool						IsProcessingEnabled (void);

	bool						IsFixedDockStateGuardEnabled (void);
};


// --- Global instance of DialogLayoutSchemeManager ----------------------------

extern DG_DLL_EXPORT DialogLayoutSchemeManager dialogLayoutSchemeManager;

class PaletteLayoutHelper
{
public:
	PaletteLayoutHelper ()
	{
		dialogLayoutSchemeManager.BeginLayout ();
	};
	~PaletteLayoutHelper ()
	{
		dialogLayoutSchemeManager.EndLayout ();
	};

};

}	// namespace DG

#endif
