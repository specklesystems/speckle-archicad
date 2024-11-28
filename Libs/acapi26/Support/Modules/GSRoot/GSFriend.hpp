
// *****************************************************************************
//
//									Class Friend
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// Description:		http://wiki/w/Friend
//
// *****************************************************************************


#ifndef GSFRIEND_HPP
#define GSFRIEND_HPP

#pragma once


namespace GS {


// === Class Friend ============================================================

template <class AuthorizedClass>
class Friend {
	friend AuthorizedClass;

private:
	Friend ()	{}
};


}	// namespace GS


#endif
