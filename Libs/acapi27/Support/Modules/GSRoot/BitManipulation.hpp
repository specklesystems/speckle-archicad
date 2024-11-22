// *****************************************************************************
//
//                  			BitManipulation
//                            
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************

#pragma once

#ifndef BIT_MANIPULATION_HPP
#define BIT_MANIPULATION_HPP


#include "Definitions.hpp"


namespace GS {

// ============================ Bit test set clear =============================

bool GSROOT_DLL_EXPORT TestBit (const void* bytePtr, Int32 bitNum);
void GSROOT_DLL_EXPORT SetBit (void* bytePtr, Int32 bitNum);
void GSROOT_DLL_EXPORT ClearBit (void* bytePtr, Int32 bitNum);

}

#endif	// #ifndef BIT_MANIPULATION_HPP