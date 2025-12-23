#pragma once

#include "UDDefinitions.hpp"
#include "DGUserControl.hpp"

namespace ACUserInterfaceTest {
	class UserControlDisplayerMock;
}

namespace UD {

class UD_DLL_EXPORT UserControlDisplayer
{
	// For instantiating without usercontrol -> instantiating a panel -> interacting with dgGlob
	friend class ACUserInterfaceTest::UserControlDisplayerMock;
public:
	UserControlDisplayer (DG::UserControl& userControlArg);

public:
	virtual ~UserControlDisplayer ();
	virtual void SetValue (const Int32 newValue);
	virtual void EnableDisplayer ();
	virtual void DisableDisplayer ();
	virtual void Show ();
	virtual void Hide ();
private:
	UserControlDisplayer () {};
	DG::UserControl* userControl;
};

} // namespace UD
