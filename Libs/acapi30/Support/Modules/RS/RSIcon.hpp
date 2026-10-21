#ifndef GS_RS_ICON_HPP
#define GS_RS_ICON_HPP

#include "RSTypes.hpp"


namespace RS {


class Icon {
public:

	constexpr Icon (GSResModule, short) noexcept;

	constexpr GSResModule	GetModule (void) const noexcept;
	constexpr short			GetId	  (void) const noexcept;

private:

	GSResModule mModule;
	short		mId;
};


/* ================================================================================================================== */


constexpr Icon::Icon (GSResModule module, short id) noexcept
	: mModule { module }, mId { id }
{}


constexpr GSResModule	Icon::GetModule (void) const noexcept
{
	return mModule;
}


constexpr short		Icon::GetId (void) const noexcept
{
	return mId;
}


} // namespace RS


#endif /* GS_RS_ICON_HPP */
