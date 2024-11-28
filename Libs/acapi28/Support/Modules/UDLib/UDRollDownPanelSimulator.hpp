#ifndef ROLL_DOWN_PANEL_SIMULATOR_HPP
#define ROLL_DOWN_PANEL_SIMULATOR_HPP

#include "UDDefinitions.hpp"
#include "Array.hpp"

namespace UD {
	
class UD_DLL_EXPORT RollDownPanelSimulator {
private:
	struct ControlGroup {
		short dialID;
		short headerID;
		short height;
		GS::Array<short> itemIDs;
		GS::Array<bool> itemStates;
		ControlGroup (short dialIDP, short headerIDP, short heightP) : dialID (dialIDP), headerID (headerIDP), height (heightP) { }
		bool Collapse ();
		bool Expand ();
		void Move (short dx, short dy);
		bool IsExpanded () const;
	};
	short mainDialId;
	short minID;
	GS::Array<ControlGroup> groups;
	short height;
	short additionalControlTabPageID;
	
	const ControlGroup* GetConstControlGroupForIDs (short tabpageID, short headerID) const;
	ControlGroup* GetControlGroupForIDs (short tabpageID, short headerID);
	short CalcHeightNeeds () const;
	bool CanExpand(ControlGroup* cgP);
	void LayoutGroupsAfterStateChanged(short tabpageID, short headerID, bool isExpanded);
	bool LayoutGroupsCaseNotEnoughSpace (short actIndex = -1);
	void LayoutAfterExpand (short tabpageID, short headerID);
	void LayoutAfterCollapse (short tabpageID, short headerID);
	void OffsetHeadersUnder (short headerID, short offsetValue);

public:
	RollDownPanelSimulator (short mainDialIdP);
	~RollDownPanelSimulator ();
	void BuildControlGroupsForTabpage (short tabpageID, short maxID, short minID = 1);
	
	void AddControlGroup (short tabpageID, short headerID, short itemNum);
	
	void HeaderClicked (short tabpageID, short headerID);
	void ShowHideGroup (short tabpageID, short headerID, bool shown);
	void EnableDisableGroup (short tabpageID, short headerID, bool enabled);
	void HeightChanged (short newHeight);
	void Move (short offsetX, short offsetY);
	void ShowHideControl (short tabpageID, short controlID, bool visible);
	void ResetDialID (short newDialID);

	USize GetNumOfGroups () const { return groups.GetSize(); }
	short GetActHeight () const;
	short GetCollapsedNum () const;
	bool IsExpanded (short tabpageID, short headerID) const;
};
	
}

#endif // ROLL_DOWN_PANEL_SIMULATOR_HPP