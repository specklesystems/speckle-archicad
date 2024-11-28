// *****************************************************************************
// File:			DGImage.hpp
//
// Description:		Image classes
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:		DG
//
// Contact person:	AZS, BM
//
// SG compatible
// *****************************************************************************

#ifndef DGIMAGE_HPP
#define DGIMAGE_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "DGItemProperty.hpp"


// --- Predeclarations ---------------------------------------------------------

namespace DG {
	class ImageItem;
}


// --- Class declarations ------------------------------------------------------

namespace DG {

// --- ImageClickEvent ---------------------------------------------------------

class DG_DLL_EXPORT ImageClickEvent: public ItemClickEvent
{
friend class ImageObserver;					// To access protected constructor

protected:
	explicit ImageClickEvent (const ItemClickEvent& ev);

public:
	~ImageClickEvent ();

	ImageItem*	GetSource (void) const;
};


// --- ImageDoubleClickEvent ---------------------------------------------------

class DG_DLL_EXPORT ImageDoubleClickEvent: public ItemDoubleClickEvent
{
friend class ImageObserver;					// To access protected constructor

protected:
	explicit ImageDoubleClickEvent (const ItemDoubleClickEvent& ev);

public:
	~ImageDoubleClickEvent ();

	ImageItem*	GetSource (void) const;
};


// --- ImageObserver -----------------------------------------------------------

class DG_DLL_EXPORT ImageObserver: public ItemObserver
{
protected:
	virtual	short	SpecClicked (const ItemClickEvent& ev) override;
	virtual	short	SpecDoubleClicked (const ItemDoubleClickEvent& ev) override;

	virtual void	ImageClicked (const ImageClickEvent& ev);
	virtual void	ImageDoubleClicked (const ImageDoubleClickEvent& ev);

public:
	ImageObserver ();
   ~ImageObserver ();
};


// --- Image -------------------------------------------------------------------

class DG_DLL_EXPORT ImageItem: public Item
{
protected:
	ImageItem ();
	ImageItem (const Panel& panel, short item);

public:
	enum FrameType {
		NoFrame		= DG_FT_NONE,
		StaticFrame	= DG_FT_STATIC,
		ClientFrame	= DG_FT_CLIENT,
		ModalFrame	= DG_FT_MODAL
	};

	~ImageItem ();

	void	Attach (ImageObserver& observer);
	void	Detach (ImageObserver& observer);
};


// --- IconItem ----------------------------------------------------------------

class DG_DLL_EXPORT IconItem: public ImageItem,
							  public ItemIconProperty
{
public:
	IconItem (const Panel& panel, short item);
	IconItem (const Panel& panel, short item, const DG::Icon& icon);
	IconItem (const Panel& panel, const Rect& rect, FrameType type = NoFrame);

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};


// --- PictureItem -------------------------------------------------------------

class DG_DLL_EXPORT PictureItem: public ImageItem
{
public:
	PictureItem (const Panel& panel, short item);
	PictureItem (const Panel& panel, const Rect& rect, FrameType type = NoFrame);
   ~PictureItem ();

	void			SetPicture (const DG::Picture& picture);
	DG::Picture		GetPicture (void) const;

	virtual GSErrCode Store (GS::ObjectState& os) const override;
};

}	// namespace DG

#endif
