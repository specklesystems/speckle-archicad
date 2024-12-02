#ifndef CHOICESSETUPDIALOG_HPP
#define CHOICESSETUPDIALOG_HPP

#include "DGModule.hpp"
#include "UDDefinitions.hpp"

namespace UD {


class UD_DLL_EXPORT ChoicesSetupEntry
{
public:
	enum ModificationType {
		None		= 0,
		Added		= 1,
		Deleted		= 2,
		Renamed		= 3
	};

private:
	UInt32				index;
	GS::UniString		name;
	ModificationType	modification;

public:
	ChoicesSetupEntry (UInt32 inIndex, const GS::UniString& inName) : index (inIndex), name (inName), modification (None) 
	{
	}

	UInt32					GetIndex (void) const				{ return index; }
	const GS::UniString&	GetName (void) const				{ return name; }
	ModificationType		GetModificationType (void) const	{ return modification; }
	
	void	SetIndex (Int32 inIndex)								{ index = inIndex; }
	void	SetName (const GS::UniString& inName)					{ name = inName; }
	void	SetModificationType (ModificationType inModification)	{ modification = inModification; }
};


class UD_DLL_EXPORT ChoicesSetupDialog :	public DG::ModalDialog,
											public DG::PanelObserver,
											public DG::ButtonItemObserver,
											public DG::TextEditBaseObserver,
											public DG::ListBoxObserver
{
public:
	enum
	{
		DialogStringsResourceId = 2102
	};

	enum
	{
		WarningText = 1,
		DuplicatedNames = 2,
		OKButtonText = 3,
		ListBoxHeaderText = 4,
		NewOptionText = 5
	};

private:
	const short iconColumnWidth;

	enum {
		DialogResourceId = 2102
	};

	enum {
		OKButtonId					= 1,
		CancelButtonId				= 2,
		NewButtonId					= 3,
		DeleteButtonId				= 4,
		MultipleChociesCheckBoxId	= 5,
		OnTabTextEditId				= 6,
		ListBoxId					= 7,
		SeparatorId					= 8
	};

	enum {
		ListBoxColumnCount = 2
	};

	enum {
		DragTabItem = 1,
		TextTabItem = 2
	};

	bool					isEditable;

	GS::Array<ChoicesSetupEntry> values;

	DG::Button				newButton;
	DG::Button				deleteButton;
	DG::Button				cancelButton;
	DG::Button				okButton;
	DG::CheckBox			multipleChoicesCheckBox;
	DG::TextEdit			onTabEdit;
	DG::SingleSelListBox	listBox;
	DG::Separator			separator;

	void	InitListboxTabFieldSizes (void);
	void	InitListbox (void);
	short	AddListboxItem (const ChoicesSetupEntry& choiceEntry);
	void	AddNewValue (void);
	void	DeleteValue (void);
	void	PutOnTabItem (void);
	bool	CheckValues (void) const;
	bool	ListHasValidValue (void) const;

	bool	IsDeleteEnabled (void) const;
	bool	IsOKEnabled (void) const;

	void	RefreshControlStatuses (void);

	virtual	void	PanelOpened (const DG::PanelOpenEvent& ev) override;
	virtual	void	PanelCloseRequested (const DG::PanelCloseRequestEvent& ev, bool* accepted) override;
	virtual void	ButtonClicked (const DG::ButtonClickEvent& ev) override;
	virtual void	ListBoxSelectionChanged (const DG::ListBoxSelectionEvent& ev) override;
	virtual void	ListBoxMouseMoved (const DG::ListBoxMouseMoveEvent & ev, short *inArea) override;
	virtual void	ListBoxItemDragged (const DG::ListBoxDragEvent& ev) override;
	virtual void	TextEditChanged (const DG::TextEditChangeEvent& ev) override;
	virtual void	PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual void	PanelResizeExited (const DG::PanelResizeEvent& ev) override;
	
	UInt32			GetArrayIndexToListIndex (short listIndex);

public:
	ChoicesSetupDialog (const GS::Array<ChoicesSetupEntry>& inValues);
	~ChoicesSetupDialog ();
		
	void							SetMultipleChoicesEnabled (bool enabled);
	void							SetEditable (bool isEditable);

	GS::Array<ChoicesSetupEntry>	GetData (void) const;
	bool							IsMultipleChoicesEnabled (void) const;
};


} // namespace UD


#endif // CHOICESSETUPDIALOG_HPP
