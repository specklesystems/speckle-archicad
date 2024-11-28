#ifndef GS_ON_EXIT_HPP
#define GS_ON_EXIT_HPP

#pragma once

#include <functional>


namespace GS {

// --- OnExit class ----------------------------------------------------------------------------------------------------

class [[nodiscard]] OnExit {
public:
	template <class Function>
	OnExit (const Function& exitFunction);
	~OnExit ();

	OnExit (OnExit&&)				  = default;
	OnExit (const OnExit&)			  = delete;
	OnExit& operator= (const OnExit&) = delete;

	void	Activate ();
	void	Deactivate ();

private:
	const std::function<void (void)>	exitFunction;
	bool								isActive;
};


template <class Function>
OnExit::OnExit (const Function& exitFunction) :
	exitFunction (exitFunction),
	isActive	 (true)
{
}


inline OnExit::~OnExit ()
{
	if (isActive)
		exitFunction ();
}


inline void		OnExit::Activate ()
{
	isActive = true;
}


inline void		OnExit::Deactivate ()
{
	isActive = false;
}

}	// namespace GS


#endif
