#ifndef UDPANELRESIZER_HPP
#define UDPANELRESIZER_HPP

#include "UDDefinitions.hpp"
#include "HashTable.hpp"
#include "DGPanel.hpp"


namespace UD {

class ListBoxColumnResizer;

class UD_DLL_EXPORT PanelResizer : public DG::PanelObserver
{
private:
	DG::Panel& panel;
	GS::HashTable<short, GS::GSFlags> itemAnchors;
	GS::Array<UD::ListBoxColumnResizer*> listBoxColumnResizers;

public:
	enum Anchor {
		Top			= 0x01,
		Bottom		= 0x02,
		Left		= 0x04,
		Right		= 0x08,

		TopLeft		= Top | Left,
		BottomRight	= Bottom | Right,
		LeftRight	= Left | Right,
		AllSides	= Top | Bottom | Left | Right
	};

public:
	explicit PanelResizer (DG::Panel& panel);
	virtual ~PanelResizer ();

public:
	void Attach (const DG::Item& item, const GS::GSFlags& anchor);
	void Detach (const DG::Item& item);
	void AttachListBoxColumnResizer (UD::ListBoxColumnResizer* columnResizer);

protected:
	virtual void PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual void PanelResizeExited (const DG::PanelResizeEvent& ev) override;

private:
	void ResizeItems (const DG::PanelResizeEvent& ev);
	void ResizeListboxColumnResizers ();
};

}

#endif
