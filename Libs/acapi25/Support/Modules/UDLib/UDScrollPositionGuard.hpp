namespace UD {

template<class ControlType>
class ScrollPositionGuard
{
private:
	const short scrollPosition;
	ControlType& control;
public:
	explicit ScrollPositionGuard (ControlType& control) : scrollPosition (control.GetScrollPosition ()), control (control) {}
	~ScrollPositionGuard () { control.SetScrollPosition (scrollPosition); }
};

}