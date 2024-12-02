#ifndef VECTORIMAGEDUMP_HPP
#define VECTORIMAGEDUMP_HPP

#include "VectorImageExport.h"

class VectorImage;
class ProfileVectorImage;

VI_DLL_EXPORT
void	DumpImage (const VectorImage* vectorImage, short type);

VI_DLL_EXPORT
void	DumpProfileImage (const ProfileVectorImage* vectorImage, short type);

#endif
