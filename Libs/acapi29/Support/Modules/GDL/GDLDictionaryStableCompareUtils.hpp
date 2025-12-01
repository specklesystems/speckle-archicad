
#ifndef GDLDICTIONARYSTABLECOMPAREUTILS_HPP
#define GDLDICTIONARYSTABLECOMPAREUTILS_HPP

#pragma once

#include "GDLDictionary.hpp"
#include "GDLExport.h"

namespace GDL {

GDL_DLL_EXPORT		
void WriteForChecksum (GS::OChannel& oc, const GDL::Dictionary& dictionary, const GS::Optional<double>& eps);

}

#endif