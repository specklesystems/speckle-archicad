
// *****************************************************************************
//
//                                Class FontRegistryObserver
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	TP
//
// SG compatible
//
// *****************************************************************************


#if !defined FONTREGISTRYOBSERVER_HPP
#define FONTREGISTRYOBSERVER_HPP


// --------------------------------- Includes ----------------------------------

#include "TSEventObserver.hpp"
#include "TEBase.hpp"

// ============================== Class FontRegistryObserver ==============================

namespace TE {

class FontFamily;

class TE_DLL_EXPORT FontRegistryObserver : public GS::TS::EventObserver {
public:
	virtual			~FontRegistryObserver ();

	virtual void	FontAdded	 (const FontFamily& /*fontFamily*/) = 0;
};


}	// namespace TE
// ______________________________ Class FontRegistryObserver ______________________________

#endif
